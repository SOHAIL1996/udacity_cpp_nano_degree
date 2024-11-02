#include "game.h"
#include "food.h"
#include <iostream>
#include <memory>
#include <thread>
#include <atomic>
#include <future>

Game::Game(std::size_t grid_width, std::size_t grid_height)
    : snake(grid_width, grid_height),
      engine(dev()),
      random_w(0, static_cast<int>(grid_width - 1)),
      random_h(0, static_cast<int>(grid_height - 1)),
      running(true),
      paused(false)
{
  score = new int(0); // Allocate memory for score
  PlaceFood();
}

void Game::Run(Controller const &controller, Renderer &renderer, std::size_t target_frame_duration)
{

  // Create a promise and future to communicate the game state
  std::future<bool> future = promise.get_future();

  // Start a thread for handling input
  std::thread inputThread(&Game::HandleInput, this, std::ref(controller));

  Uint32 title_timestamp = SDL_GetTicks();
  Uint32 frame_start, frame_end, frame_duration;
  int frame_count = 0;

  while (running)
  {
    frame_start = SDL_GetTicks();
    // controller.HandleInput(running, paused, snake);

    if (!paused)
    {
      running = Update();
      renderer.Render(snake, food->position, food->GetColor()); // Pass food color to Render
    }

    frame_end = SDL_GetTicks();
    frame_count++;
    frame_duration = frame_end - frame_start;

    if (frame_end - title_timestamp >= 1000)
    {
      renderer.UpdateWindowTitle(*score, frame_count);
      frame_count = 0;
      title_timestamp = frame_end;
    }

    if (frame_duration < target_frame_duration)
    {
      SDL_Delay(target_frame_duration - frame_duration);
    }
  }

  // Clean up the input thread
  inputThread.join();

  // Get the result from the future
  if (future.valid())
  {
    bool finalRunningState = future.get();
    std::cout << "Final game running state: " << finalRunningState << std::endl;
  }
}

void Game::HandleInput(Controller const &controller)
{
  // Handle input in a separate thread
  while (running)
  {
    controller.HandleInput(running, paused, snake);

    // If the game is no longer running, set the promise value
    if (!running)
    {
      promise.set_value(false);
      return;
    }

    // Add a small sleep to prevent busy-waiting
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
  }

  // If the game ended normally, set the promise value
  promise.set_value(true);
}

void Game::PlaceFood()
{
  int x = random_w(engine);
  int y = random_h(engine);

  int type = rand() % 3;
  switch (type)
  {
  case 0:
    std::cout << ("Frenzy food") << std::endl;
    food = std::make_unique<FrenzyFood>(x, y);
    break;
  case 1:
    std::cout << ("Poison food") << std::endl;
    food = std::make_unique<PoisonFood>(x, y);
    break;
  case 2:
    std::cout << ("Big food") << std::endl;
    food = std::make_unique<DoubleSizeFood>(x, y);
    break;
  }
}

bool Game::Update()
{
  if (!snake.alive)
    return false; // Return false to indicate the game should end

  snake.Update();

  int new_x = static_cast<int>(snake.head_x);
  int new_y = static_cast<int>(snake.head_y);

  if (food->position.x == new_x && food->position.y == new_y)
  {
    (*score)++;
    snake.GrowBody();
    food->ApplyEffect(*this);
    PlaceFood();
    std::cout << "Score: " << *score << std::endl;
    std::cout << "Size: " << snake.size << std::endl;
  }

  // Check for self-collision
  if (!snake.alive)
  {
    std::cout << "Game Over! Snake hit itself." << std::endl;
    return false; // Game should end if snake collides with itself
  }

  return true; // Continue running the game if no collision
}

// Implementations for specific effects
void Game::SlowDownSnake()
{
  snake.speed = std::max(0.1, snake.speed - 0.05);
}

void Game::DoubleSnakeSize()
{
  snake.DoubleGrowBody();
}

int Game::GetSize() const
{
  return snake.size;
}

int Game::GetScore() const
{
  return *score; // Return the value pointed to by score
}

void Game::DoublePoints()
{
  *score += 4; // Dereference the pointer to modify the score
}

void Game::DecreaseScore()
{
  *score = std::max(0, *score - 1); // Dereference and modify the score
}

Game::~Game()
{
  delete score; // Free the allocated memory
}
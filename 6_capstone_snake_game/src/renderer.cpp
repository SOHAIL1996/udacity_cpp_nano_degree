#include "renderer.h"
#include <iostream>
#include <string>

Renderer::Renderer(const std::size_t screen_width,
                   const std::size_t screen_height,
                   const std::size_t grid_width, const std::size_t grid_height)
    : screen_width(screen_width),
      screen_height(screen_height),
      grid_width(grid_width),
      grid_height(grid_height)
{
  // Initialize SDL
  if (SDL_Init(SDL_INIT_VIDEO) < 0)
  {
    std::cerr << "SDL could not initialize.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }

  // Create Window
  sdl_window = SDL_CreateWindow("Snake Game", SDL_WINDOWPOS_CENTERED,
                                SDL_WINDOWPOS_CENTERED, screen_width,
                                screen_height, SDL_WINDOW_SHOWN);

  if (nullptr == sdl_window)
  {
    std::cerr << "Window could not be created.\n";
    std::cerr << " SDL_Error: " << SDL_GetError() << "\n";
  }

  // Create renderer
  sdl_renderer = SDL_CreateRenderer(sdl_window, -1, SDL_RENDERER_ACCELERATED);
  if (nullptr == sdl_renderer)
  {
    std::cerr << "Renderer could not be created.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }
}

Renderer::~Renderer()
{
  SDL_DestroyWindow(sdl_window);
  SDL_Quit();
}

void Renderer::Render(Snake const &snake, SDL_Point const &food_position, SDL_Color const &food_color) {
    SDL_Rect block;
    block.w = screen_width / grid_width;  // Calculate the width of each block
    block.h = screen_height / grid_height; // Calculate the height of each block

    // Set background color and clear the renderer
    SDL_SetRenderDrawColor(sdl_renderer, 0x1E, 0x1E, 0x1E, 0xFF);
    SDL_RenderClear(sdl_renderer);

    // Set food color and render the food
    SDL_SetRenderDrawColor(sdl_renderer, food_color.r, food_color.g, food_color.b, food_color.a);
    block.x = food_position.x * block.w;
    block.y = food_position.y * block.h;
    SDL_RenderFillRect(sdl_renderer, &block);

    // Set snake body color (e.g., white)
    SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    for (SDL_Point const &point : snake.body) {
        block.x = point.x * block.w;
        block.y = point.y * block.h;
        SDL_RenderFillRect(sdl_renderer, &block);
    }

    // Set snake head color based on whether it's alive
    block.x = static_cast<int>(snake.head_x) * block.w;
    block.y = static_cast<int>(snake.head_y) * block.h;
    SDL_SetRenderDrawColor(sdl_renderer, snake.alive ? 0x00 : 0xFF, 
                           snake.alive ? 0x7A : 0x00, 
                           snake.alive ? 0xCC : 0x00, 
                           0xFF);
    SDL_RenderFillRect(sdl_renderer, &block);

    // Present the renderer
    SDL_RenderPresent(sdl_renderer);
}
void Renderer::UpdateWindowTitle(int score, int fps)
{
  std::string title{"Snake Score: " + std::to_string(score) + " FPS: " + std::to_string(fps)};
  SDL_SetWindowTitle(sdl_window, title.c_str());
}

void Renderer::RenderEndScreen(int score)
{
  // Clear the screen to black
  SDL_SetRenderDrawColor(sdl_renderer, 0x00, 0x00, 0x00, 0xFF); // Black background
  SDL_RenderClear(sdl_renderer);

  // Define block size and starting position for numbers
  int block_width = screen_width / 32;
  int block_height = screen_height / 32;
  int start_x = screen_width / 2 - 4 * block_width; // Centered
  int start_y = screen_height / 2 - 2 * block_height;

  // Set color to white for drawing number blocks
  SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0xFF, 0xFF, 0xFF);

  // Function to render a single digit using block patterns
  auto renderDigit = [&](int digit, int x, int y)
  {
    SDL_Rect rect = {x, y, block_width, block_height};
    // Patterns for 0-9 digits (using a 5x3 grid per digit)
    bool patterns[10][5][3] = {
        // 0
        {{1, 1, 1},
         {1, 0, 1},
         {1, 0, 1},
         {1, 0, 1},
         {1, 1, 1}},
        // 1
        {{0, 1, 0},
         {1, 1, 0},
         {0, 1, 0},
         {0, 1, 0},
         {1, 1, 1}},
        // 2
        {{1, 1, 1},
         {0, 0, 1},
         {1, 1, 1},
         {1, 0, 0},
         {1, 1, 1}},
        // 3
        {{1, 1, 1},
         {0, 0, 1},
         {1, 1, 1},
         {0, 0, 1},
         {1, 1, 1}},
        // 4
        {{1, 0, 1},
         {1, 0, 1},
         {1, 1, 1},
         {0, 0, 1},
         {0, 0, 1}},
        // 5
        {{1, 1, 1},
         {1, 0, 0},
         {1, 1, 1},
         {0, 0, 1},
         {1, 1, 1}},
        // 6
        {{1, 1, 1},
         {1, 0, 0},
         {1, 1, 1},
         {1, 0, 1},
         {1, 1, 1}},
        // 7
        {{1, 1, 1},
         {0, 0, 1},
         {0, 1, 0},
         {0, 1, 0},
         {0, 1, 0}},
        // 8
        {{1, 1, 1},
         {1, 0, 1},
         {1, 1, 1},
         {1, 0, 1},
         {1, 1, 1}},
        // 9
        {{1, 1, 1},
         {1, 0, 1},
         {1, 1, 1},
         {0, 0, 1},
         {1, 1, 1}},
    };

    // Draw blocks for the current digit
    for (int row = 0; row < 5; ++row)
    {
      for (int col = 0; col < 3; ++col)
      {
        if (patterns[digit][row][col])
        {
          rect.x = x + col * block_width;
          rect.y = y + row * block_height;
          SDL_RenderFillRect(sdl_renderer, &rect);
        }
      }
    }
  };

  // Render each digit in the score
  std::string score_text = std::to_string(score);
  int x_offset = start_x;
  for (char &ch : score_text)
  {
    int digit = ch - '0'; // Convert character to integer
    renderDigit(digit, x_offset, start_y);
    x_offset += 4 * block_width; // Space between digits
  }

  SDL_RenderPresent(sdl_renderer); // Update the screen

  // Delay to allow the user to see the end screen
  SDL_Delay(2000);
}
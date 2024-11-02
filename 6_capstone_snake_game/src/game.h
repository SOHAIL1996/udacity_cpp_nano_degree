// game.h
#ifndef GAME_H
#define GAME_H

#include <memory>
#include <future>

#include "food.h"
#include "SDL.h"
#include "controller.h"
#include "renderer.h"
#include "snake.h"

class Game {
public:
    Game(std::size_t grid_width, std::size_t grid_height);
    void Run(Controller const &controller, Renderer &renderer, std::size_t target_frame_duration);
    int GetScore() const;
    int GetSize() const;
    
    void DoublePoints();
    void DecreaseScore();
    void SlowDownSnake();
    void DoubleSnakeSize();

    void HandleInput(Controller const &controller); // Multi threading for input

    ~Game();  // Destructor to free allocated memory

private:
    Snake snake;
    std::unique_ptr<Food> food;  // Pointer to Food base class

    std::random_device dev;
    std::mt19937 engine;
    std::uniform_int_distribution<int> random_w;
    std::uniform_int_distribution<int> random_h;

    // int score{0};
    int* score;

    void PlaceFood();
    bool Update();;

    bool running;
    bool paused;

    std::promise<bool> promise;
};

#endif

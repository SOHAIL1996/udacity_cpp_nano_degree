#include "snake.h"
#include <cmath>
#include <iostream>

void Snake::Update()
{
  SDL_Point prev_cell{
      static_cast<int>(head_x),
      static_cast<int>(
          head_y)}; // We first capture the head's cell before updating.
  UpdateHead();
  SDL_Point current_cell{
      static_cast<int>(head_x),
      static_cast<int>(head_y)}; // Capture the head's cell after updating.

  // Update all of the body vector items if the snake head has moved to a new
  // cell.
  if (current_cell.x != prev_cell.x || current_cell.y != prev_cell.y)
  {
    UpdateBody(current_cell, prev_cell);
  }
}

void Snake::UpdateHead()
{
  switch (direction)
  {
  case Direction::kUp:
    head_y -= speed;
    break;
  case Direction::kDown:
    head_y += speed;
    break;
  case Direction::kLeft:
    head_x -= speed;
    break;
  case Direction::kRight:
    head_x += speed;
    break;
  }

  // Wrap the Snake around to the beginning if it goes off-screen
  head_x = std::fmod(head_x + grid_width, grid_width);
  head_y = std::fmod(head_y + grid_height, grid_height);

  // Handle cases where `fmod` might return a negative value
  if (head_x < 0)
    head_x += grid_width;
  if (head_y < 0)
    head_y += grid_height;
}

void Snake::UpdateBody(SDL_Point &current_head_cell, SDL_Point &prev_head_cell)
{
  // Add previous head location to vector
  body.push_back(prev_head_cell);

  if (!growing)
  {
    // Remove the tail from the vector
    body.erase(body.begin());
  }

  else
  {
    growing = false;
    size++;
  }

  if (d_growth)
  {
    d_growth = false;
    size += 5;
    body.insert(body.end(), 4, prev_head_cell); // Add prev_head_cell 4 times
  }

  // Check if the snake has died by colliding with itself.
  for (auto const &item : body)
  {
    if (current_head_cell.x == item.x && current_head_cell.y == item.y)
    {
      alive = false;
      return; // Stop further updates to the body after collision
    }
  }
}

void Snake::GrowBody() { growing = true; }
void Snake::DoubleGrowBody() { d_growth = true; }

// Inefficient method to check if cell is occupied by snake.
bool Snake::SnakeCell(int x, int y)
{
  if (x == static_cast<int>(head_x) && y == static_cast<int>(head_y))
  {
    return true;
  }
  for (auto const &item : body)
  {
    if (x == item.x && y == item.y)
    {
      return true;
    }
  }
  return false;
}
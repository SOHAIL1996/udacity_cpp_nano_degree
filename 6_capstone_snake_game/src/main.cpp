#include <iostream>
#include <fstream> // Include for file I/O

#include "controller.h"
#include "game.h"
#include "renderer.h"

int main()
{
  constexpr std::size_t kFramesPerSecond{60};
  constexpr std::size_t kMsPerFrame{1000 / kFramesPerSecond};
  constexpr std::size_t kScreenWidth{640};
  constexpr std::size_t kScreenHeight{640};
  constexpr std::size_t kGridWidth{32};
  constexpr std::size_t kGridHeight{32};

  Renderer renderer(kScreenWidth, kScreenHeight, kGridWidth, kGridHeight);
  Controller controller;
  Game game(kGridWidth, kGridHeight);

  // Run the game
  game.Run(controller, renderer, kMsPerFrame);

  // Display end score screen
  renderer.RenderEndScreen(game.GetScore());

  // Display score and size in console
  std::cout << "Game has terminated successfully!\n";
  std::cout << "Score: " << game.GetScore() << "\n";
  std::cout << "Size: " << game.GetSize() << "\n";

  // Save the score to a file
  std::ofstream scoreFile("score.txt", std::ios::app); // Open file in append mode
  if (scoreFile.is_open())
  {
    scoreFile << "Score: " << game.GetScore() << ", Size: " << game.GetSize() << "\n";
    scoreFile.close(); // Close the file
    std::cout << "Score saved to score.txt\n";
  }
  else
  {
    std::cerr << "Unable to open file to save score.\n";
  }

  return 0;
}

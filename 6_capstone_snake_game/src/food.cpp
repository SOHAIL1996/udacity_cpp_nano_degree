#include "food.h"
#include "game.h"

void FrenzyFood::ApplyEffect(Game &game) const {
    game.DoublePoints();
}

void PoisonFood::ApplyEffect(Game &game) const {
    game.DecreaseScore();
    game.SlowDownSnake();
}

void DoubleSizeFood::ApplyEffect(Game &game) const {
    game.DoubleSnakeSize();
}

#ifndef FOOD_H
#define FOOD_H

#include "SDL.h"
#include <string>
#include <random>

class Food
{
public:
    virtual ~Food() = default;
    virtual void ApplyEffect(class Game &game) const = 0; // Pure virtual function for applying effect
    virtual SDL_Color GetColor() const = 0;
    SDL_Point position;
};

// FrenzyFood class: doubles score for a limited time
class FrenzyFood : public Food
{
public:
    SDL_Color GetColor() const override { return {255, 0, 0, 255}; } // Red
    FrenzyFood(int x, int y) { position = {x, y}; }

protected:
    void ApplyEffect(Game &game) const override;
};

// PoisonFood class: reduces score 
class PoisonFood : public Food
{
public:
    SDL_Color GetColor() const override { return {0, 255, 0, 255}; } // Green
    PoisonFood(int x, int y) { position = {x, y}; }

protected:
    void ApplyEffect(Game &game) const override;
};

// DoubleSizeFood class: Qunituples the snake size 
class DoubleSizeFood : public Food
{
public:
    SDL_Color GetColor() const override { return {0, 0, 255, 255}; } // Blue
    DoubleSizeFood(int x, int y) { position = {x, y}; }

protected:
    void ApplyEffect(Game &game) const override;
};

#endif

#pragma once
#include <SFML/Graphics.hpp>

class Collision {
public:
    static bool checkSpriteCollision(const sf::Sprite& spriteA, const sf::Sprite& spriteB);
};
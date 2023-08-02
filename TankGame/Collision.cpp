#include "Collision.h"

bool Collision::checkSpriteCollision(const sf::Sprite& spriteA, const sf::Sprite& spriteB)
{
    return spriteA.getGlobalBounds().intersects(spriteB.getGlobalBounds());
}
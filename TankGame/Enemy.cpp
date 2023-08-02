#include "Enemy.h"

Enemy::Enemy()
{
    if (!textures.empty()) {
        sprite.setTexture(textures[currentAnimation]);
    }
}
void Enemy::setPosition(float x, float y) {
    sprite.setPosition(x, y);
}

void Enemy::move(float offsetX, float offsetY) {
    sprite.move(offsetX, offsetY);
}

void Enemy::draw(sf::RenderWindow& window) {
    window.draw(sprite);
}

void Enemy::setScale(float scaleX, float scaleY) {
    sprite.setScale(scaleX, scaleY);
}

void Enemy::updateAnimation(float deltaTime) {

    elapsedTime += deltaTime;
    if (elapsedTime > animationTime) {
        // Cambiar al siguiente cuadro
        currentFrame = (currentFrame + 1) % numFrames[currentAnimation];
        elapsedTime = 0.0f; // Reiniciar el tiempo transcurrido
    }

    // Obtener la textura actual y actualizar la región de textura para mostrar el cuadro actual
    sf::Texture& currentTexture = textures[currentAnimation];
    int frameWidth = currentTexture.getSize().x / numFrames[currentAnimation];
    int frameHeight = currentTexture.getSize().y;
    sprite.setTexture(currentTexture);
    sprite.setTextureRect(sf::IntRect(currentFrame * frameWidth, 0, frameWidth, frameHeight));

}

void Enemy::addAnimation(const string& filePath, unsigned int numFrames)
{
    sf::Texture texture;
    if (!texture.loadFromFile(filePath)) {
        // Manejo de error en caso de que la carga de la imagen falle
        // Puedes lanzar una excepción o mostrar un mensaje de error aquí
        return;
    }
    textures.push_back(texture);
    this->numFrames.push_back(numFrames);
}

void Enemy::setCurrentAnimation(unsigned int animationIndex)
{
    if (animationIndex < textures.size()) {
        currentAnimation = animationIndex;
        currentFrame = 0;
        elapsedTime = 0.0f;
        sprite.setTexture(textures[currentAnimation]);
    }
}

sf::Vector2f Enemy::getPosition() const
{
    return sprite.getPosition();
}




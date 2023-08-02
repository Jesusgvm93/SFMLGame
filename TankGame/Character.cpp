#include "Character.h"

Character::Character() {

    if (!textures.empty()) {
        sprite.setTexture(textures[currentAnimation]);
    }
}

void Character::setPosition(float x, float y) {
    sprite.setPosition(x, y);
}

void Character::move(float offsetX, float offsetY) {
    sprite.move(offsetX, offsetY);
}

void Character::draw(sf::RenderWindow& window) {
    window.draw(sprite);
}

void Character::setScale(float scaleX, float scaleY) {
    sprite.setScale(scaleX, scaleY);
}

void Character::updateAnimation(float deltaTime) {

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

void Character::addAnimation(const string& filePath, unsigned int numFrames)
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

void Character::setCurrentAnimation(unsigned int animationIndex)
{
    if (animationIndex < textures.size()) {
        currentAnimation = animationIndex;
        currentFrame = 0;
        elapsedTime = 0.0f;
        sprite.setTexture(textures[currentAnimation]);
    }
}

sf::Vector2f Character::getPosition() const
{
    return sprite.getPosition();
}




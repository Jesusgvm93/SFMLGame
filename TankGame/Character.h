#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
using namespace std;
using namespace sf;



class Character {
private:
    vector<Texture> textures;     // Vector de texturas para las diferentes animaciones
    vector<unsigned int> numFrames;
    Texture texture;
    Sprite sprite;
    Clock animationClock; // Variable para controlar el tiempo de animaci�n
    float animationTime = 0.15f; // Tiempo en segundos para cada cuadro de animaci�n
    unsigned int currentFrame = 0; // �ndice del cuadro actual
    unsigned int currentAnimation = 0; // �ndice de la animaci�n actual
    float elapsedTime = 0.0f; // Tiempo transcurrido desde el �ltimo cuadro
    int health = 100;
    int damage = 10;



public:
    Character();
    void setPosition(float x, float y);
    void move(float offsetX, float offsetY);
    void draw(sf::RenderWindow& window);
    void setScale(float scaleX, float scaleY);
    void updateAnimation(float deltaTime);
    void addAnimation(const string& filePath, unsigned int numFrames);
    void setCurrentAnimation(unsigned int animationIndex);
    Vector2f getPosition() const;
    Sprite& getSprite() { return sprite; }
    int getHealth() const { return health; }
    void takeDamage(int amount) { health -= amount; }
    int getDamage() const { return damage; }
};
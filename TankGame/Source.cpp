#include <iostream>
#include "Character.h"
#include "Enemy.h"
#include "Collision.h"
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;


int main() {

    RenderWindow window(sf::VideoMode(1024, 792), "Imagen de fondo con SFML");
    Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile("Resources/Textures/Escenario.jpg")) {
        return 1;
    }

    Sprite backgroundSprite;
    backgroundSprite.setTexture(backgroundTexture);

    Character character;

    //Agregar las animaciones al Character
    character.addAnimation("Resources/Textures/Idle_colored_Sekiro.png", 4);   // La primera animación tiene 4 cuadros
    character.addAnimation("Resources/Textures/run_colored_Sekiro.png", 6);   // La segunda animación tiene 6 cuadros
    character.addAnimation("Resources/Textures/attack_1_colored_Sekiro.png", 7);   // La tercera animación tiene 7 cuadros

    //Puedes establecer la posición del sprite o moverlo usando los métodos de la clase
    character.setPosition(200.0f, 650.0f);
    character.setScale(3.0f, 3.0f);
    Clock clock;

    bool isKeyPressedA = false;
    bool isKeyPressedD = false;
    bool isKeyPressedK = false;

    Enemy enemy;

    enemy.addAnimation("Resources/Textures/setalth - Copia.png", 1);
    enemy.addAnimation("Resources/Textures/run.png", 6);
    enemy.addAnimation("Resources/Textures/slash - Copia.png", 6);
    enemy.addAnimation("Resources/Textures/take_hit - Copia.png", 5);
    enemy.setPosition(600.0f, 650.0f);
    enemy.setScale(-3.0f, 3.0f);

    bool isCharacterInRange = false;
    bool isCharacterInSmallRange = false;
    float smallDetectionRange = 30.0f;
    float detectionRange = 150.0f;

    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event))
        {

            switch (event.type)
            {
            case Event::Closed:
                window.close();
            case Event::KeyPressed:
                if (event.key.code == Keyboard::D && !isKeyPressedD)
                {
                    isKeyPressedD = true;
                    character.setCurrentAnimation(1);
                }
                else if (!event.key.code == Keyboard::D && isKeyPressedD)
                {
                    isKeyPressedD = false;
                    character.setCurrentAnimation(1);
                }

                if (event.key.code == Keyboard::A && !isKeyPressedA)
                {
                    isKeyPressedA = true;
                    character.setCurrentAnimation(1);
                }
                else if (!event.key.code == Keyboard::A && isKeyPressedA)
                {
                    isKeyPressedA = false;
                    character.setCurrentAnimation(1);
                }

                if (event.key.code == Keyboard::K && !isKeyPressedK)
                {
                    isKeyPressedK = true;
                    character.setCurrentAnimation(2);
                }
                else if (!event.key.code == Keyboard::K && isKeyPressedK)
                {
                    isKeyPressedK = false;
                    character.setCurrentAnimation(2);
                }
                break;
            case sf::Event::KeyReleased:
                if (event.key.code == Keyboard::D)
                {
                    isKeyPressedD = false;
                    character.setCurrentAnimation(0);
                }
                if (event.key.code == Keyboard::K)
                {
                    isKeyPressedK = false;
                    character.setCurrentAnimation(0);
                }
                if (event.key.code == Keyboard::A)
                {
                    isKeyPressedA = false;
                    character.setCurrentAnimation(0);
                }
                break;
            default:
                break;
            }
        }

        Time deltaTime = clock.restart();

        if (isKeyPressedD)
        {
            character.setScale(3.0f, 3.0f);
            character.move(200.0f * deltaTime.asSeconds(), 0.0f);
        }
        else if (isKeyPressedA)
        {
            character.setScale(-3.0f, 3.0f);
            character.move(200.0f * -(deltaTime.asSeconds()), 0.0f);
        }

        if (character.getHealth() <= 0)
        {
            cout << "El Character ha sido derrotado." << endl;
            //window.close();
        }
        else if (enemy.getHealth() <= 0)
        {
            cout << "El Enemy ha sido derrotado." << endl;
            //window.close();
        }

        // Usar la detección de colisión más la letra k para el ataque del Character
        if (Collision::checkSpriteCollision(character.getSprite(), enemy.getSprite()))
        {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::K))
            {
                enemy.takeDamage(character.getDamage());
                cout << "Enemy recibe " << character.getDamage() << " de daño del Character. Salud restante: " << enemy.getHealth() << endl;
                enemy.setCurrentAnimation(3);
            }
        }

        Vector2f characterPosition = character.getPosition();
        Vector2f enemyPosition = enemy.getPosition();

        // Calcular la dirección entre el enemigo y el personaje principal
        Vector2f direction = characterPosition - enemyPosition;

        float distance = sqrt(direction.x * direction.x + direction.y * direction.y);

        if (distance != 0) 
        {
            direction /= distance;
        }

        // Establecer la velocidad deseada del enemigo
        float enemySpeed = 50.0f;

        // Verificar si el personaje está dentro del rango de detección
        if (distance <= detectionRange) 
        {
            
            enemy.move(direction.x * enemySpeed * deltaTime.asSeconds(), direction.y * enemySpeed * deltaTime.asSeconds());

            // Actualizar la posición del enemigo usando setPosition
            enemy.setPosition(enemy.getPosition().x + direction.x * enemySpeed * deltaTime.asSeconds(),
                enemy.getPosition().y + direction.y * enemySpeed * deltaTime.asSeconds());

            // El personaje está dentro del rango, establece la animación de "perseguir"
            if (!isCharacterInRange) 
            {
                enemy.setCurrentAnimation(1); 
                isCharacterInRange = true;
            }

            // Ajustar la escala en el eje X según la dirección del personaje
            if (direction.x > 0) 
            {
                enemy.setScale(3.0f, 3.0f); 
            }
            else 
            {
                enemy.setScale(-3.0f, 3.0f); 
            }
        }
        else 
        {
            // Si el personaje está fuera del rango, establece la animación de Idle
            if (isCharacterInRange) {
                enemy.setCurrentAnimation(0); 
                isCharacterInRange = false;
            }
        }

        // Verificar si el personaje está dentro del rango de detección pequeño para atacar
        if (distance <= smallDetectionRange) 
        {
            
            if (!isCharacterInSmallRange) 
            {
                enemy.setCurrentAnimation(2); 
                isCharacterInSmallRange = true;
            }
        }
        else 
        {
            if (isCharacterInSmallRange) {
                enemy.setCurrentAnimation(0); 
                isCharacterInSmallRange = false;
            }
        }

        character.updateAnimation(deltaTime.asSeconds());
        enemy.updateAnimation(deltaTime.asSeconds());

        window.clear();

        window.draw(backgroundSprite);
        character.draw(window);
        enemy.draw(window);
        window.display();
    }

    return 0;
}
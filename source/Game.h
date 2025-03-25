#pragma once

#include <iostream>
#include <vector>
#include <ctime>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include <SFML/Network.hpp>


class Game {
private:
    // WINDOW
    sf::RenderWindow* window;
    sf::Event ev;
    sf::VideoMode videomode;

    // MOUSE POSITION
    sf::Vector2i mousePosWindow;
    sf::Vector2f mousePosView;

    // GAME LOGIC
    int points;
    float enemySpawnTimer;
    float enemySpawnTimerMax;
    unsigned int maxEnemies;

    // GAME OBJECTS
    std::vector<sf::RectangleShape> enemies;

    sf::RectangleShape enemy;


    // Private Functions
    void initVariables();
    void initWindow();
    void initEnemies();

public:
    // Constructors / Destructors
    Game();
    virtual ~Game();

    // Accessors
    const bool running() const;

    // Functions
    void spawnEnemy();

    void pollEvents();
    void updateMousePos();
    void updateEnemies();
    void update();

    void renderEnemies();
    void render();

    // Getter for window (added to access window from main.cpp)
    sf::RenderWindow* getWindow() {
        return window;
    }
};

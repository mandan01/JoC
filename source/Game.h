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
    /// window
    sf::RenderWindow* window;
    sf::Event ev;
    sf::VideoMode videomode;

    /// pozitie mouse
    sf::Vector2i mousePosWindow;
    sf::Vector2f mousePosView;

    /// elemente joc
    bool endGame;
    unsigned points;
    int health;
    float enemySpawnTimer;
    float enemySpawnTimerMax;
    unsigned int maxEnemies;
    bool mouseHeld;

    /// dec. inamici
    std::vector<sf::RectangleShape> enemies;

    sf::RectangleShape enemy;


    /// functii
    void initVariables();
    void initWindow();
    void initEnemies();

public:
    /// constructors / destructors
    Game();
    virtual ~Game();

    /// accessors
    const bool running() const;
    const bool getEndGame() const;

    /// functii
    void spawnEnemy();

    void pollEvents();
    void updateMousePos();
    void updateEnemies();
    void update();

    void renderEnemies();
    void render();

    /// getter for window (added to access window from main.cpp)
    sf::RenderWindow* getWindow() {
        return window;
    }
};


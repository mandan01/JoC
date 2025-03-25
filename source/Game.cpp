#include "Game.h"

#include <iostream>


// Private functions
void Game::initVariables() {
    this->window = nullptr;
    
    //GAME LOGIC
    int points;
    float enemySpawnTimer;
    float enemySpawnTimerMax;
    unsigned int maxEnemies; 
    this -> points = 0;
    this -> enemySpawnTimerMax = 1000.f;
    this -> enemySpawnTimer = this -> enemySpawnTimerMax;
    this -> maxEnemies = 5;
}

void Game::initWindow() {
    this -> videomode.width = 800;
    this -> videomode.height = 600;
    this -> window = new sf::RenderWindow(this->videomode, "JoC", sf::Style::Titlebar | sf::Style::Close);
    this -> window -> setFramerateLimit(60);
}

void Game::initEnemies(){
    this -> enemy.setPosition(375.f, 275.f);
    this -> enemy.setSize(sf::Vector2f(50.f, 50.f));
    this -> enemy.setFillColor(sf::Color::Cyan);
    this -> enemy.setOutlineColor(sf::Color::Black);
    this -> enemy.setOutlineThickness(1);
}

// Constructors / Destructors
Game::Game() {
    this->initVariables();
    this->initWindow();
    this->initEnemies();
}

Game::~Game() {
    delete this->window;
}

// Accessor
const bool Game::running() const {
    return this->window->isOpen();
}

// Functions
void Game::spawnEnemy(){
    this -> enemy.setPosition(
        static_cast<float>(rand() % static_cast<int> (this -> window -> getSize().x - this -> enemy.getSize().x)),
        0.f
    );
    this -> enemy.setFillColor(sf::Color::Green);
    this -> enemies.push_back(this -> enemy);

}


void Game::pollEvents() {
    while (this->window->pollEvent(this->ev)) {
        switch (this->ev.type) {
            case sf::Event::Closed:
            this->window->close();
            break;
            case sf::Event::KeyPressed:
                if (this->ev.key.code == sf::Keyboard::Escape) {
                    this->window->close();
                }
                break;
        }
    }
}


void Game::updateMousePos(){
    this -> mousePosWindow = sf::Mouse::getPosition(*this -> window); 
    this -> mousePosView = this -> window ->mapPixelToCoords(this -> mousePosWindow);
}

void Game::updateEnemies(){
    if(this -> enemies.size() < this -> maxEnemies){
        if(this -> enemySpawnTimer >= this -> enemySpawnTimerMax){
            this -> spawnEnemy();
            this -> enemySpawnTimer = this -> enemySpawnTimerMax;
        }
        else{
            this -> enemySpawnTimer += 1.f;
        }
    }
    // misca inamicii
    for(int i = 0; i < this -> enemies.size(); i++){
        this -> enemies[i].move(0.f, 1.f);
    }    

    // verifica daca se da click pe un inamic
    if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){

    }

    // elimina inamicii cand au depasit ecranul
    // if(this -> enemy.getPosition().y > this -> window -> )
}

void Game::update() {

    this -> pollEvents();

    this -> updateMousePos();
    
    this -> updateEnemies();
}


void Game::renderEnemies(){
    for(auto &e : this -> enemies){
        this -> window -> draw(e);
    }    
}

void Game::render() {
    // Clear old frame and render objects
    this->window->clear(sf::Color(0, 0, 0));

    // Draw game objects
    this -> renderEnemies();
    this->window->display();
}

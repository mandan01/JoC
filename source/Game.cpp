#include "Game.h"

#include <iostream>


/// functii private
void Game::initVariables() {
    this->window = nullptr;
    
    /// elemente joc
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

    this -> enemy.setOutlineColor(sf::Color(5, 15, 30));
    this -> enemy.setOutlineThickness(5.f);
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

// functii
void Game::spawnEnemy(){
    this -> enemy.setPosition(
        static_cast<float>(rand() % static_cast<int> (this -> window -> getSize().x - this -> enemy.getSize().x)),
        0.f
    );
    this -> enemy.setFillColor(sf::Color(255, 0, 255));
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
        
        bool deleted = false;
        this -> enemies[i].move(0.f, 2.f);
    

    /// cursor pe inamici -> dispar
    for (size_t i = 0; i < this->enemies.size(); i++) {
        if (this->enemies[i].getGlobalBounds().contains(this->mousePosView)) {
            this -> enemies.erase(this -> enemies.begin() + i);
            /// increment the points on each enemy killed
            this -> points += 1.f;


            i--;    // Adjust index after erasing an element
            std::cout << this -> points << std::endl;
        }
    }

    /// click pe inamici -> dispar
    /*if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
        if(this -> enemies[i].getGlobalBounds().contains(this -> mousePosView)){
            this -> enemies.erase(this -> enemies.begin() + i);
            this -> points += 1.f;    

        }
    }*/

    // elimina inamicii cand au depasit ecranul

        if(this -> enemies[i].getPosition().y > this -> window -> getSize().y){
            this -> enemies.erase(this -> enemies.begin() + i);
        }
    }
}

void Game::update(){

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
    this->window->clear(sf::Color(50, 205, 50));

    // Draw game objects
    this -> renderEnemies();
    this->window->display();
}

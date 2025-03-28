#include "Game.h"
#include <iostream>
#include <sstream>

// Initializare variabile
void Game::initVariables() {
    this->window = nullptr;
    this->points = 0;
    this->enemySpawnTimerMax = 20.f;
    this->enemySpawnTimer = 0.f;
    this->maxEnemies = 5;
    this->mouseHeld = false;
    this->health = 100;
    this->endGame = false;
}

// Initializare fereastra
void Game::initWindow() {
    this->videomode.width = 800;
    this->videomode.height = 600;
    this->window = new sf::RenderWindow(
        this->videomode, 
        "JoC", 
        sf::Style::Titlebar | sf::Style::Close
    );
    this->window->setFramerateLimit(60);
}

// Initializare inamici
void Game::initEnemies() {
    this->enemy.setSize(sf::Vector2f(50.f, 50.f));
    this->enemy.setOutlineColor(sf::Color(5, 15, 30));
    this->enemy.setOutlineThickness(3.f);
}

// Initializare font
void Game::initFonts() {
    if (!this->font.loadFromFile("Arial.ttf")) {
        std::cerr << "ERROR: Failed to load font!\n";
    }
}

// Initializare text
void Game::initText() {
    // Text normal
    this->text.setFont(this->font);
    this->text.setCharacterSize(24);
    this->text.setFillColor(sf::Color::Yellow);
    this->text.setPosition(20.f, 20.f);

    // Text Game Over
    this->gameOverText.setFont(this->font);
    this->gameOverText.setCharacterSize(60);
    this->gameOverText.setFillColor(sf::Color::Red);
    this->gameOverText.setString("GAME OVER");
    // Centrare text
    sf::FloatRect bounds = this->gameOverText.getLocalBounds();
    this->gameOverText.setOrigin(
        bounds.left + bounds.width/2.0f,
        bounds.top + bounds.height/2.0f
    );
    this->gameOverText.setPosition(
        this->videomode.width/2.0f,
        this->videomode.height/2.0f
    );
}

// Constructor
Game::Game() {
    this->initVariables();
    this->initWindow();
    this->initFonts();
    this->initText();
    this->initEnemies();
}

// Destructor
Game::~Game() {
    delete this->window;
}

// Verificare daca fereastra este deschisa
const bool Game::running() const {
    return this->window->isOpen();
}

// Verificare stare joc
const bool Game::getEndGame() const {
    return this->endGame;
}

// Generare inamic
void Game::spawnEnemy() {
    this->enemy.setPosition(
        static_cast<float>(rand() % static_cast<int>(this->window->getSize().x - this->enemy.getSize().x)),
        0.f
    );

    // Tipuri random de inamici
    int type = rand() % 5;
    switch (type) {
        case 0:
            this->enemy.setSize(sf::Vector2f(10.f, 10.f));
            this->enemy.setFillColor(sf::Color::Cyan);
            break;
        case 1:
            this->enemy.setSize(sf::Vector2f(30.f, 30.f));
            this->enemy.setFillColor(sf::Color::Blue);
            break;
        case 2:
            this->enemy.setSize(sf::Vector2f(50.f, 50.f));
            this->enemy.setFillColor(sf::Color::Red);
            break;
        case 3:
            this->enemy.setSize(sf::Vector2f(70.f, 70.f));
            this->enemy.setFillColor(sf::Color::Green);
            break;
        case 4:
            this->enemy.setSize(sf::Vector2f(100.f, 100.f));
            this->enemy.setFillColor(sf::Color::White);
            break;
        default:
            this->enemy.setSize(sf::Vector2f(100.f, 100.f));
            this->enemy.setFillColor(sf::Color::Magenta);
            break;
    }

    this->enemies.push_back(this->enemy);
}

void Game::restartGame(){
    delete this->window;

    // Reinitializează jocul complet
    this->initVariables();
    this->initWindow();
    this->initFonts();
    this->initText();
    this->initEnemies();
}

// Procesare evenimente
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
                else if (this->ev.key.code == sf::Keyboard::R && this->endGame) {
                    this->restartGame();
                }
                break;

            default:
                break;
        }
    }
}


// Actualizare pozitie mouse
void Game::updateMousePos() {
    this->mousePosWindow = sf::Mouse::getPosition(*this->window);
    this->mousePosView = this->window->mapPixelToCoords(this->mousePosWindow);
}

// Actualizare text
void Game::updateText() {
    std::stringstream ss;
    ss << "Points: " << this->points << "\nHP: " << this->health;
    this->text.setString(ss.str());
}

// Actualizare inamici
void Game::updateEnemies() {
    // Generare inamici noi
    if (this->enemies.size() < this->maxEnemies) {
        if (this->enemySpawnTimer >= this->enemySpawnTimerMax) {
            this->spawnEnemy();
            this->enemySpawnTimer = 0.f;
        } else {
            this->enemySpawnTimer += 1.f;
        }
    }

    // Miscare inamici
    for (size_t i = 0; i < this->enemies.size(); ) {
        this->enemies[i].move(0.f, 1.f);

        // Verificare iesire de pe ecran
        if (this->enemies[i].getPosition().y > this->window->getSize().y) {
            // Scadere viata in functie de tipul inamicului
            sf::Color enemyColor = this->enemies[i].getFillColor();
            if (enemyColor == sf::Color::Cyan) this->health -= 2;
            else if (enemyColor == sf::Color::Blue) this->health -= 5;
            else if (enemyColor == sf::Color::Red) this->health -= 10;
            else if (enemyColor == sf::Color::Green) this->health -= 15;
            else if (enemyColor == sf::Color::White) this->health -= 25;

            this->enemies.erase(this->enemies.begin() + i);
        } else {
            i++;
        }
    }

    // Verificare click pe inamici
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        if (!this->mouseHeld) {
            this->mouseHeld = true;
            bool deleted = false;
            for (size_t i = 0; i < this->enemies.size() && !deleted; i++) {
                if (this->enemies[i].getGlobalBounds().contains(this->mousePosView)) {
                    // Adaugare puncte in functie de tipul inamicului
                    sf::Color enemyColor = this->enemies[i].getFillColor();
                    if (enemyColor == sf::Color::Cyan) {
                        this->points += 10;
                        this->health += 3;
                    } else if (enemyColor == sf::Color::Blue) {
                        this->points += 7;
                    } else if (enemyColor == sf::Color::Red) {
                        this->points += 5;
                    } else if (enemyColor == sf::Color::Green) {
                        this->points += 3;
                    } else if (enemyColor == sf::Color::White) {
                        this->points += 2;
                    }
                    deleted = true;
                    this->enemies.erase(this->enemies.begin() + i);
                }
            }
        }
    } else {
        this->mouseHeld = false;
    }
}

// Actualizare joc
void Game::update() {
    this->pollEvents();

    if (!this->endGame) {
        this->updateMousePos();
        this->updateText();
        this->updateEnemies();

        if (this->health <= 0) {
            this->endGame = true;
        }
    }
    //
}

// Randare text
void Game::renderText(sf::RenderTarget& target) {
    target.draw(this->text);
}

// Randare inamici
void Game::renderEnemies(sf::RenderTarget& target) {
    for (auto& e : this->enemies) {
        target.draw(e);
    }
}

// Randare joc
void Game::render() {
    this->window->clear(sf::Color(50, 205, 50));

    if (this->endGame) {
        this->window->draw(this->gameOverText);
    }
    else{
        this->renderEnemies(*this->window);
        this->renderText(*this->window);
    }
    

    this->window->display();
}

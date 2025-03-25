#include <iostream>
#include "Game.h"

int main() {
    // NR RANDOM
    std::srand(static_cast<unsigned>(time(NULL)));


    // INIT GAME ENGINE
    Game game;

    // Game Loop1d3
    while (game.running()) {
        // Update
        
        game.update();

        
        // Render
        game.render();
    }

    return 0;
}

#include <iostream>
#include "Game.h"

int main() {
    /// nr random
    std::srand(static_cast<unsigned>(time(NULL)));


    /// init joc
    Game game;

    /// game loop
    while (game.running() && !game.getEndGame()) {
        /// update
        
        game.update();

        
        /// render
        game.render();
    }

    return 0;
}

#include <iostream>

#ifdef _WIN32
#include <Windows.h>
#endif

#include <sstream>
#include <time.h>
#include <conio.h>
#include <thread>
#include <chrono>

#include "common.hpp"
#include "player.hpp"
#include "display.hpp"
#include "gamestate.hpp"

int main() {
    GameState game;
    clear();
    srand(time(NULL));
    game.score = 0;
    game.pct = .14;
    std::cout << "Welcome to Shardgate. You are ";
    COLOR("@", 1);
    std::cout << ".\nYou are trying to reach ";
    COLOR("0", 6);
    std::cout << " without touching #.\nOnce you reach ";
    COLOR("0", 6);
    std::cout << ", you receive points equal to your life total, and the % of dangerous board increases.\n\nPress anything to continue.";
    getch();
    while (true) {
        game.pct += .03;
        game.display.init(BLACK);
        for (int _ = 0; _ < X_LEN*Y_LEN*game.pct; _++) game.display.set_pixel(randint(X_LEN), randint(Y_LEN), WHITE);
        game.display.set_pixel(randint(X_LEN), randint(Y_LEN), TARGET);
        game.display.set_pixel(randint(X_LEN), randint(Y_LEN), TARGET);
        game.display.save();
        game.display.set_pixel(randint(X_LEN), randint(Y_LEN), MED_PACK);
        game.display.set_pixel(X_LEN/2, Y_LEN/2, PLAYER);
        game.update();
        while (true) {
            if (game.handle(getch())) {
                game.update();
                std::cout << "Next level...";
                game.reset();
                std::this_thread::sleep_for(std::chrono::milliseconds(750));
                break;
            }

            if (game.display.status()) game.update();
            
            if (game.player.hp <= 0) {
                std::cout << "You died!\nGame Over!";
                exit(0);
            }
        }
    }
}
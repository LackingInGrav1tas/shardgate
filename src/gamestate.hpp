#ifndef SHRD_GST
#define SHRD_GST

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
#include "display.hpp"
#include "player.hpp"

#define HANDLE_SPOT()\
    do { \
        switch (display.get_pixel(player.x, player.y)) { \
            case WHITE: display.message = "Ouch! That hurts!"; player.hp -= 1; break; \
            case TARGET: score += player.hp + pct*10; return true; \
            case MED_PACK: display.message = "You gain some life."; player.hp += 2; break; \
        } \
    } while (false)

class GameState {
    public:
    int score;
    Display display;
    Player player;
    double pct;

    bool handle(int c) {
        switch (c) {
            case 'w':
                if (player.y != 0) {
                    display.set_pixel(player.x, player.y, display.base[player.y][player.x]);
                    player.y -= 1;
                    HANDLE_SPOT();
                    display.set_pixel(player.x, player.y, PLAYER);
                } else {
                    display.set_pixel(player.x, player.y, display.base[player.y][player.x]);
                    player.y = Y_LEN-1;
                    HANDLE_SPOT();
                    display.set_pixel(player.x, player.y, PLAYER);
                }
                break;
            case 'a':
                if (player.x != 0) {
                    display.set_pixel(player.x, player.y, display.base[player.y][player.x]);
                    player.x -= 1;
                    HANDLE_SPOT();
                    display.set_pixel(player.x, player.y, PLAYER);
                } else {
                    display.set_pixel(player.x, player.y, display.base[player.y][player.x]);
                    player.x = X_LEN-1;
                    HANDLE_SPOT();
                    display.set_pixel(player.x, player.y, PLAYER);
                }
                break;
            case 's':
                if (player.y != Y_LEN-1) {
                    display.set_pixel(player.x, player.y, display.base[player.y][player.x]);
                    player.y += 1;
                    HANDLE_SPOT();
                    display.set_pixel(player.x, player.y, PLAYER);
                } else {
                    display.set_pixel(player.x, player.y, display.base[player.y][player.x]);
                    player.y = 0;
                    HANDLE_SPOT();
                    display.set_pixel(player.x, player.y, PLAYER);
                }
                break;
            case 'd':
                if (player.x != X_LEN-1) {
                    display.set_pixel(player.x, player.y, display.base[player.y][player.x]);
                    player.x += 1;
                    HANDLE_SPOT();
                    display.set_pixel(player.x, player.y, PLAYER);
                } else {
                    display.set_pixel(player.x, player.y, display.base[player.y][player.x]);
                    player.x = 0;
                    HANDLE_SPOT();
                    display.set_pixel(player.x, player.y, PLAYER);
                }
                break;
            case 'h':
                clear();
                std::cout << "Commands:\nw: move up\na: move left\ns: move down\nd: move right\ne: exit\n\nBoard:\n@: player\n#: obstacle\n0: target\n" << (char)233 << ": health pack" << std::endl;
                getch();
                display.status() = true;
                break;
            case 'e': exit(0);
            default:
                display.message = std::string("Unrecognized character ") + (char)c;
                display.status() = true;
        }
        return false;
    }
    void update() {
        display.print();
        std::cout << "x: " << player.x << "  y: " << player.y << "  hp: " << player.hp << "  score: " << score << "\n %: " << pct << std::endl;
    }
    void reset() {
        player = Player();
    }

    void save_state();
};

#endif
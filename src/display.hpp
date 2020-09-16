#ifndef SHRD_DIS
#define SHRD_DIS


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

class Display {
    P_Chars display[Y_LEN][X_LEN];
    bool changed = false;
    P_Chars base_char;
    public:
    std::string message;
    P_Chars base[Y_LEN][X_LEN];

    void init(P_Chars base) {
        base_char = base;
        message = "press h for help.";
#ifdef _WIN32
        system(("mode con: cols=" + std::to_string(X_LEN+2) + " lines=" + std::to_string(Y_LEN+7)).c_str());
#endif
        for (int o = 0; o < Y_LEN; o++) for (int i = 0; i < X_LEN; i++) display[o][i] = base;
    }

    void save() {
        for (int o = 0; o < Y_LEN; o++) for (int i = 0; i < X_LEN; i++) base[o][i] = display[o][i];
    }

    void print() {
        system("cls");
        std::string s;
        s += message + "\n ________________________________\n" + (char)179;
        for (int o = 0; o < Y_LEN; o++) {
            for (int i = 0; i < X_LEN; i++) {
                switch (display[o][i]) {
                    case WHITE:
                        s +=  "#";
                        break;
                    case BLACK:
                        //if (i % 2) s += (char)176;
                        //else s += (char)177;
                        s += " ";
                        break;
                    case PLAYER:
                        std::cout << s;
                        s = "";
                        COLOR("@", 1);
                        break;
                    case TARGET:
                        std::cout << s;
                        s = "";
                        COLOR("0", 6);
                        break;
                    case MED_PACK:
                        //s += (char)233;
                        std::cout << s;
                        s = "";
                        s += (char)233;
                        COLOR(s, 5);
                        s = "";
                        break;
                }
            }
            s += std::string("") + (char)179 + "\n" + (char)179;
        }
        s.pop_back();
        s += (char)192;
        for (int _ = 0; _ < X_LEN; _++) {
            s += (char)196;
        }
        s += (char)217;
        std::cout << s;
        std::cout.flush();
        changed = false;
    }

    void set_pixel(int x, int y, P_Chars value) {
        changed = true;
        display[y][x] = value;
    }
    P_Chars get_pixel(int x, int y) {
        return display[y][x];
    }
    bool &status() {
        return changed;
    }
};

#endif
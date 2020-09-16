#ifndef SHRD_COMMON
#define SHRD_COMMON


#include <iostream>

#ifdef _WIN32
#include <Windows.h>
#endif

#include <sstream>
#include <time.h>
#include <conio.h>
#include <thread>
#include <chrono>

#define Y_LEN 16
#define X_LEN 32

void COLOR(std::string text, int num) {
#ifdef _WIN32
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, num);
    std::cout << text;
    std::cout.flush();
    SetConsoleTextAttribute(hConsole, 7);
    return;
#endif
    std::cout << text;
    std::cout.flush();
}

void clear() {
#ifdef _WIN32
    system("cls");
    return;
#endif
    system("clear");
}

int randint(int range) {
    return rand() % range;
}

int randint(int rb, int re) {
    return (rand() % re) + rb;
}

enum P_Chars {
    BLACK, WHITE, PLAYER, TARGET, MED_PACK
};

#endif
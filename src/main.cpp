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
                        s += (char)176;
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

struct Player {
    int x;
    int y;
    int hp;
    Player() {
        x = X_LEN/2;
        y = Y_LEN/2;
        hp = 2;
    }
};

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
} game;

int main() {
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
#include <SFML/Graphics.hpp>
#include "Menu.h"
#include "Game.h"
#include "globals.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include "AudioManager.h"  // Thêm include AudioManager

int main() {
    srand(static_cast<unsigned int>(time(0)));

    sf::RenderWindow app(sf::VideoMode(W, H), "Asteroids with Menu");
    app.setFramerateLimit(60);

    AudioManager audio;  // Tạo AudioManager

    // Load nhạc nền và phát (loop = true)
    if (!audio.playMusic("audio/background.wav")) {
        std::cerr << "Failed to play background music!\n";
    }

    // Load hiệu ứng âm thanh (nếu có)
    audio.loadSound("laser", "laser.wav");
    audio.loadSound("explosion", "explosion.wav");

    Menu menu(W, H);

    int coin = 100;
    menu.setCoin(coin);

    int score = 0;
    menu.setScore(score);

    bool inMenu = true;
    while (app.isOpen() && inMenu) {
        sf::Event event;
        while (app.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                app.close();

            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Up)
                    menu.MoveUp();
                else if (event.key.code == sf::Keyboard::Down)
                    menu.MoveDown();
                else if (event.key.code == sf::Keyboard::Enter) {
                    int selected = menu.GetPressedItem();
                    if (selected == 0)
                        inMenu = false;  // Bắt đầu game
                    else if (selected == 3)
                        app.close();     // Thoát game
                }
            }
        }

        app.clear();
        menu.draw(app);
        app.display();
    }

    if (!app.isOpen()) return 0;

    /
    Game game(app /*, audio*/);  // Nếu game không nhận audio, giữ nguyên

    game.init();
    game.run();

    return 0;
}

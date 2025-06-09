#include <SFML/Graphics.hpp>
#include "Menu.h"
#include "Game.h"
#include "globals.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

int main() {
    srand(static_cast<unsigned int>(time(0)));

    sf::RenderWindow app(sf::VideoMode(W, H), "Asteroids with Menu");
    app.setFramerateLimit(60);

    Menu menu(W, H);

    int coin = 100;  // Ví dụ số coin hiện tại
    menu.setCoin(coin);  // Cập nhật coin hiển thị trong menu

    int score = 0;    // Khởi tạo điểm số
    menu.setScore(score); // Cập nhật điểm số hiển thị trong menu

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
                        inMenu = false;  // Thoát menu để bắt đầu game
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

    // Khởi tạo game, gọi init rồi gọi run (vòng lặp chính trong Game)
    Game game(app);
    game.init();
    game.run();

    return 0;
}

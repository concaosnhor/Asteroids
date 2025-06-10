#include <SFML/Graphics.hpp>
#include "Menu.h"
#include "Game.h"
#include "globals.h"    // Chứa enum class GameState
#include <iostream>
#include <cstdlib>
#include <ctime>
#include "AudioManager.h"

int main() {
    srand(static_cast<unsigned int>(time(0)));

    sf::RenderWindow app(sf::VideoMode(W, H), "Asteroids with Menu");
    app.setFramerateLimit(60);

    AudioManager audio;
    if (!audio.playMusic("audio/background.wav")) {
        std::cerr << "Failed to play background music!\n";
    }
    audio.loadSound("laser", "laser.wav");
    audio.loadSound("explosion", "explosion.wav");

    int coin = 100;
    int score = 0;

    GameState gameState = GameState::MainMenu;  // dùng GameState::MainMenu thay vì MainMenu

    while (app.isOpen() && gameState != GameState::Exit) {
        if (gameState == GameState::MainMenu) {  // dùng GameState::MainMenu
            Menu mainMenu(W, H, MenuType::Main);
            mainMenu.setCenterX(W / 2.f);
            mainMenu.setOffsetY((H - 210.f) / 2.f);
            mainMenu.setCoin(coin);
            mainMenu.setScore(score);

            bool inMainMenu = true;

            while (app.isOpen() && inMainMenu) {
                sf::Event event;
                while (app.pollEvent(event)) {
                    if (event.type == sf::Event::Closed) {
                        app.close();
                        gameState = GameState::Exit;
                        inMainMenu = false;
                    }
                    else if (event.type == sf::Event::KeyPressed) {
                        if (event.key.code == sf::Keyboard::Up)
                            mainMenu.MoveUp();
                        else if (event.key.code == sf::Keyboard::Down)
                            mainMenu.MoveDown();
                        else if (event.key.code == sf::Keyboard::Enter) {
                            int selected = mainMenu.GetPressedItem();
                            if (selected == 0) {
                                audio.stopMusic();
                                gameState = GameState::Playing;
                                inMainMenu = false;
                            }
                            else if (selected == 3) {
                                app.close();
                                gameState = GameState::Exit;
                                inMainMenu = false;
                            }
                        }
                    }
                }
                app.clear();
                mainMenu.draw(app);
                app.display();
            }
        }
        else if (gameState == GameState::Playing) {
            Game game(app);
            game.init();
            game.run();

            coin += game.getTotalCoin();
            score += game.getTotalScore();

            gameState = GameState::GameOver;
        }
        else if (gameState == GameState::GameOver) {
            Menu gameOverMenu(W, H, MenuType::GameOver);
            gameOverMenu.setCenterX(W / 2.f);
            gameOverMenu.setOffsetY((H - 210.f) / 2.f);

            gameOverMenu.setMenuItemString(0, "Play Again");
            gameOverMenu.setMenuItemString(1, "Return to Menu");
            gameOverMenu.setMenuItemString(2, "Exit");

            bool inGameOverMenu = true;

            while (app.isOpen() && inGameOverMenu) {
                sf::Event event;
                while (app.pollEvent(event)) {
                    if (event.type == sf::Event::Closed) {
                        app.close();
                        gameState = GameState::Exit;
                        inGameOverMenu = false;
                    }
                    else if (event.type == sf::Event::KeyPressed) {
                        if (event.key.code == sf::Keyboard::Up)
                            gameOverMenu.MoveUp();
                        else if (event.key.code == sf::Keyboard::Down)
                            gameOverMenu.MoveDown();
                        else if (event.key.code == sf::Keyboard::Enter) {
                            int selected = gameOverMenu.GetPressedItem();
                            if (selected == 0) {
                                gameState = GameState::Playing;
                                inGameOverMenu = false;
                            }
                            else if (selected == 1) {
                                gameState = GameState::MainMenu;
                                inGameOverMenu = false;
                            }
                            else if (selected == 2) {
                                app.close();
                                gameState = GameState::Exit;
                                inGameOverMenu = false;
                            }
                        }
                    }
                }
                app.clear();
                gameOverMenu.draw(app);
                app.display();
            }
        }
    }

    return 0;
}

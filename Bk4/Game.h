#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "Animation.h"
#include "Entity.h"
#include "player.h"
#include "asteroid.h"
#include "globals.h"  
#include "bullet.h"
#include "Menu.h"

class Game {
private:
    sf::RenderWindow& app;

    // Texture giữ lâu dài
    sf::Texture t1, t2, t3, t4, t5, t6, t7;

    // Animation
    Animation sExplosion, sRock, sRock_small, sBullet, sPlayer, sPlayer_go, sExplosion_ship;

    sf::Sprite background;

    player* p;
    std::vector<Entity*> entities;

    int score = 0;        // Điểm
    int totalCoin = 0;    // Tổng số coin (nếu bạn dùng coin trong game)
    int lives = 3;

    // HUD
    sf::Font font;
    sf::Text scoreText;
    sf::Text livesText;
    sf::Text timerText;

    sf::Clock gameClock;

    Menu pauseMenu;
    Menu gameOverMenu;

    GameState gameState = GameState::Playing;

    void handleEvents();
    void update();
    void draw();
    bool isCollide(Entity* a, Entity* b);

    void restartGame();

public:
    Game(sf::RenderWindow& window);
    ~Game();

    void init();
    void run();

    // Hàm lấy giá trị coin và score
    int getTotalCoin() const { return totalCoin; }
    int getTotalScore() const { return score; }
};

#endif // GAME_H

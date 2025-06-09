#include "Game.h"
#include <iostream>
#include <cmath>
#include "globals.h"
#include <cstdlib>



// Constructor: khởi tạo biến app, Menu, thiết lập ban đầu, gọi init()
Game::Game(sf::RenderWindow& window)
    : app(window),
    pauseMenu(600.f, 600.f),      // Khởi tạo Menu với width, height
    gameOverMenu(600.f, 600.f)
{
    score = 0;
    lives = 3;
    gameState = GameState::Playing;
    init();
}

// Destructor: giải phóng bộ nhớ entities
Game::~Game() {
    for (auto e : entities) delete e;
    entities.clear();
}

// Khởi tạo textures, font, background, animation, HUD text, spawn asteroid và player
void Game::init() {
    if (!t1.loadFromFile("images/spaceship.png") ||
        !t2.loadFromFile("images/background.jpg") ||
        !t3.loadFromFile("images/explosions/type_C.png") ||
        !t4.loadFromFile("images/rock.png") ||
        !t5.loadFromFile("images/fire_blue.png") ||
        !t6.loadFromFile("images/rock_small.png") ||
        !t7.loadFromFile("images/explosions/type_B.png")) {
        std::cerr << "Error loading textures" << std::endl;
        std::exit(-1);
    }

    if (!font.loadFromFile("fonts/Emulator.otf")) {
        std::cerr << "Error loading font" << std::endl;
        std::exit(-1);
    }

    t1.setSmooth(true);
    t2.setSmooth(true);

    background.setTexture(t2);
    background.setScale(float(W) / t2.getSize().x, float(H) / t2.getSize().y);

    sExplosion = Animation(t3, 0, 0, 256, 256, 48, 0.5f);
    sRock = Animation(t4, 0, 0, 64, 64, 16, 0.2f);
    sRock_small = Animation(t6, 0, 0, 64, 64, 16, 0.2f);
    sBullet = Animation(t5, 0, 0, 32, 64, 16, 0.8f);
    sPlayer = Animation(t1, 40, 0, 40, 40, 1, 0.f);
    sPlayer_go = Animation(t1, 40, 40, 40, 40, 1, 0.f);
    sExplosion_ship = Animation(t7, 0, 0, 192, 192, 64, 0.5f);

    // HUD Texts
    scoreText.setFont(font);
    scoreText.setCharacterSize(20);
    scoreText.setFillColor(sf::Color::Cyan);
    scoreText.setPosition(10.f, 10.f);
    scoreText.setString("Score: 0");

    livesText.setFont(font);
    livesText.setCharacterSize(20);
    livesText.setFillColor(sf::Color::Red);
    livesText.setPosition(10.f, 40.f);
    livesText.setString("Lives: 3");

    timerText.setFont(font);
    timerText.setCharacterSize(20);
    timerText.setFillColor(sf::Color::White);
    timerText.setPosition(10.f, 70.f);
    timerText.setString("Time: 0");

    gameClock.restart();

    // Spawn asteroids
    for (int i = 0; i < 15; i++) {
        asteroid* a = new asteroid();
        a->settings(sRock, rand() % W, rand() % H, rand() % 360, 25.f);
        float speed = ((rand() % 3 + 1) * 0.5f) * 3.f;
        a->dx = cos(a->angle * 3.14159f / 180.f) * speed;
        a->dy = sin(a->angle * 3.14159f / 180.f) * speed;
        entities.push_back(a);
    }

    p = new player();
    p->settings(sPlayer, 200.f, 200.f, 0.f, 20.f);
    entities.push_back(p);
}

// Kiểm tra va chạm giữa 2 entity (dùng khoảng cách tâm và bán kính)
bool Game::isCollide(Entity* a, Entity* b) {
    if (!a || !b) return false;
    float dx = a->x - b->x;
    float dy = a->y - b->y;
    float dist = sqrt(dx * dx + dy * dy);
    return dist < (a->R + b->R);
}

// Xử lý sự kiện (đóng cửa sổ, phím bắn, pause, menu)
void Game::handleEvents() {
    sf::Event event;
    while (app.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            app.close();

        if (gameState == GameState::Playing) {
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Space) {
                    bullet* b = new bullet();
                    b->settings(sBullet, p->x, p->y, p->angle, 10.f);
                    entities.push_back(b);
                }
                else if (event.key.code == sf::Keyboard::Escape) {
                    gameState = GameState::Paused;
                }
            }
        }
        else if (gameState == GameState::Paused) {
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Escape) {
                    gameState = GameState::Playing; // Tiếp tục chơi
                }
                else if (event.key.code == sf::Keyboard::Up) {
                    pauseMenu.MoveUp();
                }
                else if (event.key.code == sf::Keyboard::Down) {
                    pauseMenu.MoveDown();
                }
                else if (event.key.code == sf::Keyboard::Enter) {
                    int choice = pauseMenu.GetPressedItem();
                    switch (choice) {
                    case 0: // Continue
                        gameState = GameState::Playing;
                        break;
                    case 1: // Restart
                        restartGame();
                        break;
                    case 2: // Exit to Main Menu
                        app.close(); // Hoặc chuyển scene
                        break;
                    }
                }
            }
        }
        else if (gameState == GameState::GameOver) {
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Up) {
                    gameOverMenu.MoveUp();
                }
                else if (event.key.code == sf::Keyboard::Down) {
                    gameOverMenu.MoveDown();
                }
                else if (event.key.code == sf::Keyboard::Enter) {
                    int choice = gameOverMenu.GetPressedItem();
                    switch (choice) {
                    case 0: // Retry
                        restartGame();
                        break;
                    case 1: // Exit to Main Menu
                        app.close(); // Hoặc chuyển scene
                        break;
                    }
                }
            }
        }
    }

    // Điều khiển player khi đang chơi
    if (gameState == GameState::Playing && p != nullptr) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) p->angle += 3.f;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) p->angle -= 3.f;
        p->thrust = sf::Keyboard::isKeyPressed(sf::Keyboard::Up);
    }
}

// Cập nhật trạng thái game (va chạm, điểm, mạng, tạo asteroid mới, xóa entities)
void Game::update() {
    if (gameState != GameState::Playing || p == nullptr) return;

    std::vector<Entity*> newEntities;

    for (auto a : entities) {
        for (auto b : entities) {
            if (a == nullptr || b == nullptr) continue;

            if (a->name == "asteroid" && b->name == "bullet" && isCollide(a, b)) {
                a->life = b->life = false;

                Entity* e = new Entity();
                e->settings(sExplosion, a->x, a->y);
                e->name = "explosion";
                newEntities.push_back(e);

                score += 10; // +10 điểm
                scoreText.setString("Score: " + std::to_string(score));

                for (int i = 0; i < 2; i++) {
                    if (a->R == 15.f) continue;

                    Entity* e = new asteroid();
                    e->settings(sRock_small, a->x, a->y, rand() % 360, 15.f);
                    float speed = ((rand() % 3 + 1) * 0.5f) * 3.f;
                    e->dx = cos(e->angle * 3.14159f / 180.f) * speed;
                    e->dy = sin(e->angle * 3.14159f / 180.f) * speed;
                    newEntities.push_back(e);
                }
            }
            else if (a->name == "player" && b->name == "asteroid" && isCollide(a, b)) {
                b->life = false;

                Entity* e = new Entity();
                e->settings(sExplosion_ship, a->x, a->y);
                e->name = "explosion_ship";
                newEntities.push_back(e);

                lives--;
                livesText.setString("Lives: " + std::to_string(lives));

                if (lives <= 0) {
                    gameState = GameState::GameOver;
                }
                else {
                    // Đặt lại vị trí player sau va chạm
                    p->x = W / 2.f;
                    p->y = H / 2.f;
                    p->dx = 0.f;
                    p->dy = 0.f;
                    p->angle = 0.f;
                    p->thrust = false;
                }
            }
        }
    }

    // Xóa entities đã chết (life == false)
    for (auto it = entities.begin(); it != entities.end();) {
        if (!(*it)->life) {
            delete* it;
            it = entities.erase(it);
        }
        else {
            ++it;
        }
    }

    // Thêm entities mới sinh ra (explosion, asteroid nhỏ)
    entities.insert(entities.end(), newEntities.begin(), newEntities.end());

    // Cập nhật tất cả entities
    for (auto e : entities) {
        e->update();
    }

    // Cập nhật timerText
    int timeElapsed = static_cast<int>(gameClock.getElapsedTime().asSeconds());
    timerText.setString("Time: " + std::to_string(timeElapsed));
}

// Vẽ game: background, entities, HUD, menu theo trạng thái
void Game::draw() {
    app.clear();

    app.draw(background);

    for (auto e : entities) {
        e->draw(app);
    }

    // Vẽ HUD
    app.draw(scoreText);
    app.draw(livesText);
    app.draw(timerText);

    // Vẽ menu nếu đang pause hoặc gameover
    if (gameState == GameState::Paused) {
        pauseMenu.draw(app);
    }
    else if (gameState == GameState::GameOver) {
        gameOverMenu.draw(app);
    }

    app.display();
}

// Khởi động lại game
void Game::restartGame() {
    // Xóa hết entities cũ
    for (auto e : entities) delete e;
    entities.clear();

    score = 0;
    lives = 3;
    scoreText.setString("Score: 0");
    livesText.setString("Lives: 3");
    gameClock.restart();

    gameState = GameState::Playing;

    // Spawn lại asteroid và player
    for (int i = 0; i < 15; i++) {
        asteroid* a = new asteroid();
        a->settings(sRock, rand() % W, rand() % H, rand() % 360, 25.f);
        float speed = ((rand() % 3 + 1) * 0.5f) * 3.f;
        a->dx = cos(a->angle * 3.14159f / 180.f) * speed;
        a->dy = sin(a->angle * 3.14159f / 180.f) * speed;
        entities.push_back(a);
    }

    p = new player();
    p->settings(sPlayer, 200.f, 200.f, 0.f, 20.f);
    entities.push_back(p);
}

// Hàm chạy game (game loop)
void Game::run() {
    while (app.isOpen()) {
        handleEvents();
        update();
        draw();
    }
}

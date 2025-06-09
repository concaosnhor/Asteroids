#include "Game.h"
#include <iostream>
#include <cmath>
#include <cstdlib>

Game::Game(sf::RenderWindow& window) : app(window), p(nullptr), score(0), lives(3) {}

Game::~Game() {
    for (auto e : entities) delete e;
    entities.clear();
}

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

bool Game::isCollide(Entity* a, Entity* b) {
    if (!a || !b) return false;
    float dx = a->x - b->x;
    float dy = a->y - b->y;
    float dist = sqrt(dx * dx + dy * dy);
    return dist < (a->R + b->R);
}

void Game::handleEvents() {
    if (p == nullptr) return;

    sf::Event event;
    while (app.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            app.close();

        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space) {
            bullet* b = new bullet();
            b->settings(sBullet, p->x, p->y, p->angle, 10.f);
            entities.push_back(b);
        }
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) p->angle += 3.f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))  p->angle -= 3.f;
    p->thrust = sf::Keyboard::isKeyPressed(sf::Keyboard::Up);
}

void Game::update() {
    if (p == nullptr) return;

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
                e->name = "explosion";
                newEntities.push_back(e);
                p->settings(sPlayer, W / 2.f, H / 2.f, 0.f, 20.f);
                p->dx = p->dy = 0;
                lives--;
                livesText.setString("Lives: " + std::to_string(lives));
                if (lives <= 0) app.close(); // Game over
            }
        }
    }

    p->anim = p->thrust ? sPlayer_go : sPlayer;

    for (auto e : entities)
        if (e->name == "explosion" && e->anim.isEnd())
            e->life = false;

    int countAsteroids = 0;
    for (auto e : entities)
        if (e->name == "asteroid") countAsteroids++;

    while (countAsteroids < 15) {
        asteroid* a = new asteroid();
        float x, y;
        do {
            x = rand() % W;
            y = rand() % H;
        } while (std::abs(x - p->x) < 100 && std::abs(y - p->y) < 100);

        a->settings(sRock, x, y, rand() % 360, 25.f);
        float speed = ((rand() % 3 + 1) * 0.5f) * 3.f;
        a->dx = cos(a->angle * 3.14159f / 180.f) * speed;
        a->dy = sin(a->angle * 3.14159f / 180.f) * speed;

        newEntities.push_back(a);
        countAsteroids++;
    }

    for (auto e : newEntities) entities.push_back(e);

    for (auto i = entities.begin(); i != entities.end();) {
        Entity* e = *i;
        e->update();
        e->anim.update();
        if (!e->life) {
            if (e == p) p = nullptr;
            i = entities.erase(i);
            delete e;
        }
        else ++i;
    }

    int seconds = static_cast<int>(gameClock.getElapsedTime().asSeconds());
    timerText.setString("Time: " + std::to_string(seconds));
}

void Game::draw() {
    app.clear();
    app.draw(background);
    for (auto e : entities) e->draw(app);
    app.draw(scoreText);
    app.draw(livesText);
    app.draw(timerText);
    app.display();
}

void Game::run() {
    while (app.isOpen()) {
        handleEvents();
        update();
        draw();
    }
}

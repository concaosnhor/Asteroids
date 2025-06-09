#include "Display.h"
#include <iostream>
#include <iomanip>
#include <sstream>

Display::Display()
    : elapsedTime(0.f), showCoin(true)  // khởi tạo biến showCoin
{
    // Constructor có thể để trống hoặc để những phần khởi tạo mặc định khác
}

void Display::init() {
    if (!font.loadFromFile("fonts/Emulator.otf")) {
        // Xử lý lỗi font, ví dụ:
        std::cerr << "Error loading font Emulator.otf\n";
    }
    textScore.setFont(font);
    textScore.setCharacterSize(20);
    textScore.setFillColor(sf::Color::White);
    textScore.setPosition(10.f, 10.f);

    textCoin.setFont(font);
    textCoin.setCharacterSize(20);
    textCoin.setFillColor(sf::Color::Yellow);
    textCoin.setPosition(10.f, 40.f);

    textLives.setFont(font);
    textLives.setCharacterSize(20);
    textLives.setFillColor(sf::Color::Green);
    textLives.setPosition(10.f, 70.f);

    textTime.setFont(font);
    textTime.setCharacterSize(20);
    textTime.setFillColor(sf::Color::Cyan);
    textTime.setPosition(10.f, 100.f);
}

void Display::setScore(int score) {
    textScore.setString("Score: " + std::to_string(score));
}

void Display::setCoin(int coin) {
    textCoin.setString("Coin: " + std::to_string(coin));
}

void Display::setLives(int lives) {
    textLives.setString("Lives: " + std::to_string(lives));
}

void Display::setElapsedTime(float seconds) {
    elapsedTime = seconds;

    int mins = static_cast<int>(elapsedTime) / 60;
    int secs = static_cast<int>(elapsedTime) % 60;

    std::stringstream ss;
    ss << "Time: " << mins << ":" << std::setw(2) << std::setfill('0') << secs;

    textTime.setString(ss.str());
}

void Display::setShowCoin(bool show) {
    showCoin = show;
}

void Display::draw(sf::RenderWindow& window) {
    window.draw(textScore);
    if (showCoin) {
        window.draw(textCoin);
    }
    window.draw(textLives);
    window.draw(textTime);
}

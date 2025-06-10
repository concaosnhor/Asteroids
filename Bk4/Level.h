// Level.h
#pragma once
#include <SFML/System.hpp>

class Level {
public:
    int number;              // Màn chơi số mấy
    int asteroidCount;       // Số lượng asteroid ban đầu
    float asteroidSpeed;     // Tốc độ asteroid
    sf::Time timeLimit;      // Thời gian giới hạn màn chơi

    Level(int num, int count, float speed, sf::Time limit)
        : number(num), asteroidCount(count), asteroidSpeed(speed), timeLimit(limit) {
    }
};



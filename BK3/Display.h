#ifndef DISPLAY_H
#define DISPLAY_H

#include <SFML/Graphics.hpp>
#include <string>

class Display {
private:
    sf::Font font;
    sf::Text textScore;
    sf::Text textCoin;
    sf::Text textLives;
    sf::Text textTime;

    int score;
    int coin;
    int lives;
    float elapsedTime;

    bool showCoin;

public:
    Display();

    void init();

    void setScore(int s);
    void setCoin(int c);
    void setLives(int l);
    void setElapsedTime(float t);
    void setShowCoin(bool show);

    void draw(sf::RenderWindow& window);
};

#endif // DISPLAY_H

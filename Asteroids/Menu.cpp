#include "Menu.h"
#include <iostream>

Menu::Menu(float width, float height)
    : selectedItemIndex(0), coin(0), score(0)
{
    if (!font.loadFromFile("fonts/Emulator.otf")) {
        std::cerr << "Error loading font from fonts/Emulator.otf" << std::endl;
    }

    numberOfItems = MAX_NUMBER_OF_ITEMS;

    background.setSize(sf::Vector2f(width, height));
    background.setFillColor(sf::Color(20, 20, 60));

    if (backgroundTexture.loadFromFile("images/menu_background.png")) {
        background.setTexture(&backgroundTexture);
        background.setFillColor(sf::Color::White);
        useTexture = true;
    }
    else {
        std::cerr << "Error loading background image from images/menu_background.png\n";
        background.setFillColor(sf::Color(20, 20, 60));
        useTexture = false;
    }

    std::string labels[MAX_NUMBER_OF_ITEMS] = { "Play", "Options", "About", "Exit" };

    for (int i = 0; i < numberOfItems; i++) {
        menu[i].setFont(font);
        menu[i].setFillColor(sf::Color::White);
        menu[i].setString(labels[i]);
        menu[i].setCharacterSize(28);

        sf::FloatRect bounds = menu[i].getLocalBounds();
        float x = center_x - bounds.width / 2.f - bounds.left;
        float y = y_positions[i] - bounds.height / 2.f - bounds.top + offsetY;

        menu[i].setPosition(sf::Vector2f(x, y));
    }

    // Coin text
    coinText.setFont(font);
    coinText.setCharacterSize(20);
    coinText.setFillColor(sf::Color::Yellow);
    coinText.setPosition(10.f, 10.f);
    coinText.setString("Coin: 0");

    // Score text
    scoreText.setFont(font);
    scoreText.setCharacterSize(20);
    scoreText.setFillColor(sf::Color::Cyan);
    scoreText.setPosition(10.f, 40.f);
    scoreText.setString("Score: 0");

    menu[selectedItemIndex].setFillColor(sf::Color::Red);
}

Menu::~Menu() {}

void Menu::draw(sf::RenderWindow& window)
{
    window.draw(background);
    window.draw(coinText);
    window.draw(scoreText);

    for (int i = 0; i < numberOfItems; i++) {
        window.draw(menu[i]);
    }
}

void Menu::MoveUp()
{
    menu[selectedItemIndex].setFillColor(sf::Color::White);
    selectedItemIndex--;
    if (selectedItemIndex < 0)
        selectedItemIndex = numberOfItems - 1;
    menu[selectedItemIndex].setFillColor(sf::Color::Red);
}

void Menu::MoveDown()
{
    menu[selectedItemIndex].setFillColor(sf::Color::White);
    selectedItemIndex++;
    if (selectedItemIndex >= numberOfItems)
        selectedItemIndex = 0;
    menu[selectedItemIndex].setFillColor(sf::Color::Red);
}

void Menu::setNumberOfItems(int num)
{
    if (num > 0 && num <= MAX_NUMBER_OF_ITEMS)
        numberOfItems = num;
}

void Menu::setMenuItemString(int index, const std::string& str)
{
    if (index >= 0 && index < numberOfItems) {
        menu[index].setString(str);

        sf::FloatRect bounds = menu[index].getLocalBounds();
        float x = center_x - bounds.width / 2.f - bounds.left;
        float y = y_positions[index] - bounds.height / 2.f - bounds.top + offsetY;
        menu[index].setPosition(sf::Vector2f(x, y));
    }
}

void Menu::updateMenuPositions(float width)
{
    background.setSize(sf::Vector2f(width, background.getSize().y));

    for (int i = 0; i < numberOfItems; i++) {
        sf::FloatRect bounds = menu[i].getLocalBounds();
        float x = center_x - bounds.width / 2.f - bounds.left;
        float y = y_positions[i] - bounds.height / 2.f - bounds.top + offsetY;
        menu[i].setPosition(sf::Vector2f(x, y));
    }
}

sf::Vector2f Menu::getMenuItemPosition(int index) const
{
    if (index >= 0 && index < numberOfItems)
        return menu[index].getPosition();
    return sf::Vector2f(0.f, 0.f);
}

void Menu::setMenuItemPosition(int index, const sf::Vector2f& pos)
{
    if (index >= 0 && index < numberOfItems)
        menu[index].setPosition(pos);
}

void Menu::setCoin(int c)
{
    coin = c;
    coinText.setString("Coin: " + std::to_string(coin));
}

void Menu::setScore(int s)
{
    score = s;
    scoreText.setString("Score: " + std::to_string(score));
}

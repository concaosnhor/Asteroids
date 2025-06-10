#include "Menu.h"
#include <iostream>

Menu::Menu(float width, float height, MenuType type)
    : selectedItemIndex(0), numberOfItems(MAX_NUMBER_OF_ITEMS), coin(0), score(0), currentMenuType(type), useTexture(false)
{
    if (!font.loadFromFile("fonts/Emulator.otf")) {
        std::cerr << "Error loading font from fonts/Emulator.otf" << std::endl;
    }

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

    center_x = width / 2.f;
    offsetY = 0.f;

    // Khởi tạo vị trí Y cho từng item menu (có thể tùy chỉnh thêm)
    y_positions[0] = 200.f;
    y_positions[1] = 270.f;
    y_positions[2] = 340.f;
    y_positions[3] = 410.f;

    std::string labels[MAX_NUMBER_OF_ITEMS];

    if (currentMenuType == MenuType::Main) {
        numberOfItems = 4;
        labels[0] = "Play";
        labels[1] = "Options";
        labels[2] = "About";
        labels[3] = "Exit";

        // Khởi tạo text coin, score cho menu chính
        coinText.setFont(font);
        coinText.setCharacterSize(20);
        coinText.setFillColor(sf::Color::Yellow);
        coinText.setString("Coin: 0");
        coinText.setPosition(1.f, 10.f);

        scoreText.setFont(font);
        scoreText.setCharacterSize(20);
        scoreText.setFillColor(sf::Color::Cyan);
        scoreText.setString("Score: 0");
        scoreText.setPosition(1.f, 40.f);
    }
    else if (currentMenuType == MenuType::GameOver) {
        numberOfItems = 3;
        labels[0] = "Play Again";
        labels[1] = "Return to Menu";
        labels[2] = "Exit";

        // Không hiển thị coin, score ở menu game over
    }
    else {
        // Nếu có loại menu khác, đặt mặc định hoặc tùy chỉnh ở đây
        numberOfItems = 0;
    }

    // Khởi tạo từng menu item với font, màu, string, cỡ chữ
    for (int i = 0; i < numberOfItems; i++) {
        menu[i].setFont(font);
        menu[i].setFillColor(sf::Color::White);
        menu[i].setString(labels[i]);
        menu[i].setCharacterSize(28);
    }

    updateMenuPositions(width);

    if (numberOfItems > 0)
        menu[selectedItemIndex].setFillColor(sf::Color::Red);
}

Menu::~Menu() {}

void Menu::draw(sf::RenderWindow& window)
{
    window.draw(background);

    if (currentMenuType == MenuType::Main) {
        window.draw(coinText);
        window.draw(scoreText);
    }

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
    if (num > 0 && num <= MAX_NUMBER_OF_ITEMS) {
        numberOfItems = num;
        selectedItemIndex = 0; // reset selection
    }
}

void Menu::setMenuItemString(int index, const std::string& str)
{
    if (index >= 0 && index < numberOfItems) {
        menu[index].setString(str);
        updateMenuPositions(background.getSize().x);
    }
}

void Menu::updateMenuPositions(float width)
{
    float bgHeight = background.getSize().y;
    background.setSize(sf::Vector2f(width, bgHeight));

    float bgWidth = background.getSize().x;

    // giữ nguyên phần này theo yêu cầu:
    float windowWidth = 1200;
    float windowHeight = 800.f;

    float posX = (windowWidth - bgWidth) / 2.f;
    float posY = (windowHeight - bgHeight) / 2.f;

    background.setPosition(posX, posY);

    for (int i = 0; i < numberOfItems; i++) {
        sf::FloatRect bounds = menu[i].getLocalBounds();
        float x = posX + center_x - (bounds.width / 2.f) - bounds.left;
        float y = posY + y_positions[i] - (bounds.height / 2.f) - bounds.top + offsetY;
        menu[i].setPosition(sf::Vector2f(x, y));
    }

    if (currentMenuType == MenuType::Main) {
        sf::FloatRect bounds = coinText.getLocalBounds();
        float x = posX + center_x - bounds.width / 2.f - bounds.left;
        float y = posY + (coinText.getPosition().y - posY);
        coinText.setPosition(x, y);

        bounds = scoreText.getLocalBounds();
        x = posX + center_x - bounds.width / 2.f - bounds.left;
        y = posY + (scoreText.getPosition().y - posY);
        scoreText.setPosition(x, y);
    }
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
    updateMenuPositions(background.getSize().x);
}

void Menu::setScore(int s)
{
    score = s;
    scoreText.setString("Score: " + std::to_string(score));
    updateMenuPositions(background.getSize().x);
}

void Menu::setOffsetY(float offset)
{
    offsetY = offset;
    updateMenuPositions(background.getSize().x);
}

void Menu::setCenterX(float cx)
{
    center_x = cx;
    updateMenuPositions(background.getSize().x);
}

void Menu::setMenuType(MenuType type)
{
    currentMenuType = type;
}

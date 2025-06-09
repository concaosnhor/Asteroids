#ifndef MENU_H
#define MENU_H

#include <SFML/Graphics.hpp>
#include <string>

#define MAX_NUMBER_OF_ITEMS 4

class Menu {
public:
    Menu(float width, float height);
    ~Menu();

    void draw(sf::RenderWindow& window);
    void MoveUp();
    void MoveDown();

    int GetPressedItem() const { return selectedItemIndex; }

    void setNumberOfItems(int num);
    void setMenuItemString(int index, const std::string& str);
    void updateMenuPositions(float width);

    sf::Vector2f getMenuItemPosition(int index) const;
    void setMenuItemPosition(int index, const sf::Vector2f& pos);

    void setCoin(int c);
    void setScore(int s);

private:
    int selectedItemIndex;
    int numberOfItems;

    sf::Font font;
    sf::Text menu[MAX_NUMBER_OF_ITEMS];
    sf::Text coinText;
    sf::Text scoreText;

    int coin;
    int score;

    sf::RectangleShape background;
    sf::Texture backgroundTexture;
    bool useTexture;

    // Các vị trí y cố định dùng để căn menu item
    float y_positions[MAX_NUMBER_OF_ITEMS] = { 175.f, 265.f, 355.f, 445.f };
    float center_x = 295.f;
    float offsetY = 160.f;
};

#endif // MENU_H

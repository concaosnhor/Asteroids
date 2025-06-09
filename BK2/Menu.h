#ifndef MENU_H
#define MENU_H

#include <SFML/Graphics.hpp>
#include <string>

#define MAX_NUMBER_OF_ITEMS 4

class Menu
{
private:
    int selectedItemIndex;
    int numberOfItems;
    sf::Font font;
    sf::Text menu[MAX_NUMBER_OF_ITEMS];

    // Text riêng cho coin
    sf::Text coinText;
    int coin;

    // Text riêng cho score
    sf::Text scoreText;
    int score;

    // Background
    sf::RectangleShape background;
    sf::Texture backgroundTexture;
    bool useTexture = false;

    // Vị trí Y cố định từng menu item (dựa trên ảnh nền)
    float y_positions[MAX_NUMBER_OF_ITEMS] = { 175.f, 265.f, 355.f, 445.f };
    // Tâm X cố định của ô menu (dựa trên ảnh nền)
    float center_x = 295.f;

public:
    Menu(float width, float height);
    ~Menu();

    void draw(sf::RenderWindow& window);
    void MoveUp();
    void MoveDown();

    int GetPressedItem() const { return selectedItemIndex; }

    void setNumberOfItems(int num);
    void setMenuItemString(int index, const std::string& str);

    // Cập nhật vị trí menu item theo width
    void updateMenuPositions(float width);

    // Set coin và cập nhật text coin
    void setCoin(int c);

    // Set score và cập nhật text score
    void setScore(int s);

    // Get/set vị trí menu item
    sf::Vector2f getMenuItemPosition(int index) const;
    void setMenuItemPosition(int index, const sf::Vector2f& pos);
};

#endif // MENU_H

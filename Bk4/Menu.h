#ifndef MENU_H
#define MENU_H

#include <SFML/Graphics.hpp>
#include <string>

#define MAX_NUMBER_OF_ITEMS 4

// Kiểu menu: menu chính hoặc menu khi chết
enum class MenuType {
    Main,
    GameOver
};

class Menu {
public:
    Menu(float width, float height, MenuType type = MenuType::Main);
    ~Menu();

    void draw(sf::RenderWindow& window);
    void MoveUp();
    void MoveDown();

    int GetPressedItem() const { return selectedItemIndex; }

    void setNumberOfItems(int num);
    void setMenuItemString(int index, const std::string& str);

    // Cập nhật vị trí menu khi thay đổi kích thước
    void updateMenuPositions(float width);

    sf::Vector2f getMenuItemPosition(int index) const;
    void setMenuItemPosition(int index, const sf::Vector2f& pos);

    void setCoin(int c);
    void setScore(int s);

    // Điều chỉnh vị trí menu theo Y và X
    void setOffsetY(float offset);
    void setCenterX(float cx);

    // Chuyển đổi kiểu menu (main <-> game over)
    void setMenuType(MenuType type);

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

    // Vị trí Y cố định cho các mục menu
    float y_positions[MAX_NUMBER_OF_ITEMS] = { 175.f, 265.f, 355.f, 445.f };

    // Tâm ngang trong background, dùng để căn giữa text menu
    float center_x = 295.f;

    // Offset dịch theo trục Y cho menu (dùng để điều chỉnh vị trí dọc menu)
    float offsetY = 160.f;

    // Khoảng cách giữa các dòng menu
    float itemSpacing = 90.f;

    // Vị trí Y tương đối trong background để đặt coinText và scoreText
    float coinTextRelativeY = 10.f;
    float scoreTextRelativeY = 40.f;

    MenuType currentMenuType;  // <-- Thêm biến lưu kiểu menu hiện tại

    // Hàm nội bộ để cập nhật vị trí menu item
    void updatePositions();
};

#endif // MENU_H

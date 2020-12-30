#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "MenuItem.h"

class Menu {
private:
	sf::RectangleShape menu;
	std::vector<MenuItem> items;
public:
	Menu();
	Menu(sf::Color color);
	void addItem(MenuItem item);
	void setPosition(int x, int y);
	void draw(sf::RenderWindow &window);
	sf::Vector2f getPosition();
	MenuItem& getSelectedMenu(int x, int y);
	MenuItem::Action getAction(int x, int y);
	sf::RectangleShape getMenu();
};
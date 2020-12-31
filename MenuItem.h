#pragma once
#include <SFML/Graphics.hpp>


class MenuItem : public sf::RectangleShape {
public:
	enum class Action {
		DELETE = 0, ADD = 1, NONE = 2, RESIZE = 3, ROTATE = 4, CHANGE_DIRECTION = 5
	};
	MenuItem(int width, int height, Action action);
	MenuItem(int width, int height, Action action, sf::Color color);
	MenuItem(sf::Text text, Action action);
	Action getAction();
	sf::Text& getText();
private:
	sf::Text text;
	Action action;
};


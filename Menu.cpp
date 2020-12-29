#include "Menu.h"

const int gap = 5;
sf::Color color(199, 209, 207);

Menu::Menu() {
	menu.setFillColor(color);
	menu.setSize(sf::Vector2f(10, 10));
}

Menu::Menu(sf::Color color) {
	menu.setFillColor(color);
	menu.setSize(sf::Vector2f(10, 10));
}

void Menu::addItem(MenuItem item) {
	items.push_back(item);
	int x = this->menu.getSize().x > item.getSize().x + gap ? this->menu.getSize().x
		: item.getSize().x + 2 * gap;
	menu.setSize(sf::Vector2f(x, this->menu.getSize().y + gap + item.getSize().y));
}

void Menu::setPosition(int x, int y) {
	menu.setPosition(x, y);
	int y_start = gap + menu.getPosition().y;
	int x_start = gap + menu.getPosition().x;
	for (int i = 0; i < items.size(); i++) {
		items.at(i).setPosition(x_start, y_start);
		items.at(i).getText().setPosition(x_start, y_start - 5);
		y_start += gap + items.at(i).getSize().y;
	}
}

void Menu::draw(sf::RenderWindow& window) {
	window.draw(menu);
	for (MenuItem item : items) {
		item.setSize(sf::Vector2f(menu.getSize().x - 2 * gap, item.getSize().y));
		window.draw(item);
		window.draw(item.getText());
	}
}

sf::Vector2f Menu::getPosition() {
	return menu.getPosition();
}

MenuItem::Action Menu::getAction(int x, int y) {
	for (MenuItem item : items) {
		if (item.getGlobalBounds().contains(x, y)) {
			return item.getAction();
		}
	}
	return MenuItem::Action::NONE;
}

sf::RectangleShape Menu::getMenu() {
	return menu;
}
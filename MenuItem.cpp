#include "MenuItem.h"

sf::Color color_item(227, 232, 231);
const int gap = 5;

MenuItem::MenuItem(int width, int height, Action a) {
	setSize(sf::Vector2f(width, height));
	m_action = a;
	setFillColor(color_item);
}

MenuItem::MenuItem(int width, int height, Action a, sf::Color color) {
	setSize(sf::Vector2f(width, height));
	m_action = a;
	setFillColor(color);
}

MenuItem::MenuItem(sf::Text t, Action a) {
	m_text = t;
	m_action = a;
	m_text.setOrigin(0, 0);
	setSize(sf::Vector2f(t.getLocalBounds().width + gap, t.getLocalBounds().height + gap));
	setFillColor(color_item);
}

MenuItem::Action MenuItem::getAction() {
	return m_action;
}

sf::Text& MenuItem::getText() {
	return m_text;
}
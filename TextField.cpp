#include "TextField.h"

TextField::TextField(unsigned int initialSize) :
	m_size(initialSize),
	m_rect(sf::Vector2f(15 * m_size, 20 + 3 * GAP)),
	m_hasfocus(false)
{
	m_font.loadFromFile("fonts/Roboto-Black.ttf");
	m_rect.setOutlineThickness(2);
	m_rect.setOutlineColor(sf::Color(127, 127, 127));
	m_rect.setPosition(this->getPosition());
	m_rect.setFillColor(sf::Color::Transparent);
	m_rendered_text.setFont(m_font);
	m_rendered_text.setFillColor(sf::Color::Black);
	setOrigin(m_rect.getLocalBounds().width / 2, m_rect.getLocalBounds().height / 2);
	m_rect.setOrigin(m_rect.getLocalBounds().width / 2, m_rect.getLocalBounds().height / 2);
}

const std::string TextField::getText() const {
	return m_text;
}

FloatRect TextField::getGlobalBounds() {
	return m_rect.getGlobalBounds();
}

void TextField::setPosition(float x, float y) {
	sf::Transformable::setPosition(x, y);
	m_rect.setPosition(x, y);
	m_rendered_text.setPosition(m_rect.getGlobalBounds().left + GAP, m_rect.getGlobalBounds().top);
}

bool TextField::contains(sf::Vector2f point) const {
	return m_rect.getGlobalBounds().contains(point);
}

void TextField::setFocus(bool focus) {
	m_hasfocus = focus;
	if (focus) {
		m_rect.setOutlineColor(sf::Color::Blue);
	}
	else {
		m_rect.setOutlineColor(sf::Color(127, 127, 127)); // Gray color
	}
}

bool TextField::hasFocus() {
	return m_hasfocus;
}

void TextField::handleInput(sf::Event e) {
	Vector2f v = m_rect.getPosition();
	if (!m_hasfocus || e.type != sf::Event::TextEntered)
		return;

	if (e.text.unicode == 8) {   // Delete key
		m_text = m_text.substr(0, m_text.size() - 1);
	}
	else {
		m_text += e.text.unicode;
	}
	m_rect.setSize(Vector2f(m_text.size() != 0 ? 15 * m_text.size() + 2 * GAP : 28, 20 + 3 * GAP));
	setOrigin(m_rect.getLocalBounds().width / 2, m_rect.getLocalBounds().height / 2);
	m_rect.setOrigin(m_rect.getLocalBounds().width / 2, m_rect.getLocalBounds().height / 2);
	m_rendered_text.setString(m_text);
	setPosition(v.x, v.y);
}
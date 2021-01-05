#pragma once
#include <SFML/Graphics.hpp>

const int GAP = 5;

class TextField : public sf::Transformable, public sf::Drawable {
public:
	TextField(unsigned int initialSize) :
		m_size(initialSize),
		m_rect(sf::Vector2f(15 * m_size, 20 + 3 * GAP)),
		m_hasfocus(false)
	{
		m_font.loadFromFile("fonts/Roboto-Black.ttf");
		m_rect.setOutlineThickness(2);
		m_rect.setOutlineColor(sf::Color(127, 127, 127));
		m_rect.setPosition(this->getPosition());
		m_rect.setFillColor(sf::Color::Transparent);
		rendered_text.setFont(m_font);
		rendered_text.setFillColor(sf::Color::Black);
		setOrigin(m_rect.getLocalBounds().width / 2, m_rect.getLocalBounds().height / 2);
		m_rect.setOrigin(m_rect.getLocalBounds().width / 2, m_rect.getLocalBounds().height / 2);
	}

	const std::string getText() const {
		return m_text;
	}

	auto getGlobalBounds() {
		return m_rect.getGlobalBounds();
	}

	void setPosition(float x, float y) {
		sf::Transformable::setPosition(x, y);
		m_rect.setPosition(x, y);
		rendered_text.setPosition(m_rect.getGlobalBounds().left + GAP, m_rect.getGlobalBounds().top);
	}

	bool contains(sf::Vector2f point) const {
		return m_rect.getGlobalBounds().contains(point);
	}

	void setFocus(bool focus) {
		m_hasfocus = focus;
		if (focus) {
			m_rect.setOutlineColor(sf::Color::Blue);
		}
		else {
			m_rect.setOutlineColor(sf::Color(127, 127, 127)); // Gray color
		}
	}

	bool hasFocus() {
		return m_hasfocus;
	}

	void handleInput(sf::Event e) {
		Vector2f v = m_rect.getPosition();
		if (!m_hasfocus || e.type != sf::Event::TextEntered)
			return;

		if (e.text.unicode == 8) {   // Delete key
			m_text = m_text.substr(0, m_text.size() - 1);
		}
		else {
			m_text += e.text.unicode;
		}
		m_rect.setSize(Vector2f(m_text.size() != 0 ? 15 * m_text.size() + 2 * GAP: 28, 20 + 3 * GAP));
		setOrigin(m_rect.getLocalBounds().width / 2, m_rect.getLocalBounds().height / 2);
		m_rect.setOrigin(m_rect.getLocalBounds().width / 2, m_rect.getLocalBounds().height / 2);
		rendered_text.setString(m_text);
		setPosition(v.x, v.y);
	}

private:
	unsigned int m_size;
	sf::Font m_font;
	std::string m_text;
	sf::Text rendered_text;
	sf::RectangleShape m_rect;
	bool m_hasfocus;

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		target.draw(m_rect, states);
		target.draw(rendered_text, states);
	}
};


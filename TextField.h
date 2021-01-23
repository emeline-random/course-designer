#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

const int GAP = 5;

class TextField : public sf::Transformable, public sf::Drawable {
public:
	TextField(unsigned int initialSize);
	const std::string getText() const;
	FloatRect getGlobalBounds();
	void setPosition(float x, float y);
	bool contains(sf::Vector2f point) const;
	void setFocus(bool focus);
	bool hasFocus();
	void handleInput(sf::Event e);

private:
	unsigned int m_size;
	sf::Font m_font;
	std::string m_text;
	sf::Text m_rendered_text;
	sf::RectangleShape m_rect;
	bool m_hasfocus;

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		target.draw(m_rect, states);
		target.draw(m_rendered_text, states);
	}
};


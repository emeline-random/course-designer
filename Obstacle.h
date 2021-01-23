#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Vertical : public Sprite
{
public:
	static void initVertical();
	Vertical();
	int getNbBarres();
	void setNbBarres(int barres);
	void changeDirection();
	Sprite& getArrow();
private:
	int m_nbBarres = 3;
	Sprite m_arrow;
};

namespace Verticaux
{
	static bool init = false;
	static Texture texture;
	static Texture arrow_texture;
}

class Oxer : public Sprite
{
public:
	static void initOxer();
	Oxer();
	int getNbBarres();
	void setNbBarres(int barres);
	void changeDirection();
	Sprite& getArrow();
private:
	int m_nbBarres = 4;
	Sprite m_arrow;
};

namespace Oxers
{
	static bool init = false;
	static Texture texture;
	static Texture arrow_texture;
}
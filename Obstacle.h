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
	int nbBarres = 3;
	Sprite arrow;
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
	int nbBarres = 4;
	Sprite arrow;
};

namespace Oxers
{
	static bool init = false;
	static Texture texture;
	static Texture arrow_texture;
}
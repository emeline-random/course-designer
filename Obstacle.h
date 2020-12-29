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
private:
	int nbBarres = 3;
};

namespace Verticaux
{
	static bool init = false;
	static Texture texture;
}

class Oxer : public Sprite
{
public:
	static void initOxer();
	Oxer();
	int getNbBarres();
	void setNbBarres(int barres);
private:
	int nbBarres = 4;
};

namespace Oxers
{
	static bool init = false;
	static Texture texture;
}
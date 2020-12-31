#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Barre : public Sprite
{
public:
	static void initBarre();
	Barre();
private:
	bool leftToRight = false;
};

namespace Barres {
	static bool init = false;
	static Texture texture;
};


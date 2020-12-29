#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Chandelier : public Sprite
{
public:
	static void initChandelier();
	Chandelier();
};

namespace Chandeliers {
	static bool init = false;
	static Texture texture;
};


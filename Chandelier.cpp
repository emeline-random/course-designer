#include "Chandelier.h"

using namespace sf;

void Chandelier::initChandelier()
{
	if (!Chandeliers::init)
	{
		Chandeliers::texture.loadFromFile("graphics/chandelier.png");
		Chandeliers::init = true;
	}
}

Chandelier::Chandelier()
{
	initChandelier();
	setTexture(Chandeliers::texture);
	setOrigin(getLocalBounds().width / 2, getLocalBounds().height / 2);
}

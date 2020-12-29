#include "Barre.h"

using namespace sf;

void Barre::initBarre()
{
	if (!Barres::init)
	{
		Barres::texture.loadFromFile("graphics/barre.png");
		Barres::init = true;
	}
}

Barre::Barre()
{
	initBarre();
	setTexture(Barres::texture);
	setOrigin(getLocalBounds().width / 2, getLocalBounds().height / 2);
}

#include "Obstacle.h"

void Vertical::initVertical()
{
	if (!Verticaux::init)
	{
		Verticaux::texture.loadFromFile("graphics/vertical.png");
		Verticaux::init = true;
	}
}

Vertical::Vertical()
{
	initVertical();
	setTexture(Verticaux::texture);
	setOrigin(getLocalBounds().width / 2, getLocalBounds().height / 2);
}

int Vertical::getNbBarres()
{
	return nbBarres;
}

void Vertical::setNbBarres(int barres)
{
	nbBarres = barres;
}

void Oxer::initOxer()
{
	if (!Oxers::init)
	{
		Oxers::texture.loadFromFile("graphics/oxer.png");
		Oxers::init = true;
	}
}

Oxer::Oxer()
{
	initOxer();
	setTexture(Oxers::texture);
	setOrigin(getLocalBounds().width / 2, getLocalBounds().height / 2);
}

int Oxer::getNbBarres()
{
	return nbBarres;
}

void Oxer::setNbBarres(int barres)
{
	nbBarres = barres;
}
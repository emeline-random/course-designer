#include "Obstacle.h"

void Vertical::initVertical()
{
	if (!Verticaux::init)
	{
		Verticaux::texture.loadFromFile("graphics/vertical.png");
		Verticaux::arrow_texture.loadFromFile("graphics/arrow.png");
		Verticaux::init = true;
	}
}

Vertical::Vertical()
{
	initVertical();
	setTexture(Verticaux::texture);
	setOrigin(getLocalBounds().width / 2, getLocalBounds().height / 2);
	arrow.setTexture(Verticaux::arrow_texture);
	arrow.setOrigin(arrow.getLocalBounds().width / 2, arrow.getLocalBounds().height / 2);
}

int Vertical::getNbBarres()
{
	return nbBarres;
}

void Vertical::setNbBarres(int barres)
{
	nbBarres = barres;
}

void Vertical::changeDirection() {
	arrow.rotate(180);
}

Sprite& Vertical::getArrow() {
	return arrow;
}

void Oxer::initOxer()
{
	if (!Oxers::init)
	{
		Oxers::texture.loadFromFile("graphics/oxer.png");
		Oxers::arrow_texture.loadFromFile("graphics/arrow.png");
		Oxers::init = true;
	}
}

Sprite& Oxer::getArrow() {
	return arrow;
}

Oxer::Oxer()
{
	initOxer();
	setTexture(Oxers::texture);
	setOrigin(getLocalBounds().width / 2, getLocalBounds().height / 2);
	arrow.setTexture(Oxers::arrow_texture);
	arrow.setOrigin(arrow.getLocalBounds().width / 2, arrow.getLocalBounds().height / 2);
}

int Oxer::getNbBarres()
{
	return nbBarres;
}

void Oxer::setNbBarres(int barres)
{
	nbBarres = barres;
}

void Oxer::changeDirection() {
	arrow.rotate(180);
}
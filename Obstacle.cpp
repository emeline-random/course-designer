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
	m_arrow.setTexture(Verticaux::arrow_texture);
	m_arrow.setOrigin(m_arrow.getLocalBounds().width / 2, m_arrow.getLocalBounds().height / 2);
}

int Vertical::getNbBarres()
{
	return m_nbBarres;
}

void Vertical::setNbBarres(int barres)
{
	m_nbBarres = barres;
}

void Vertical::changeDirection() {
	m_arrow.rotate(180);
}

Sprite& Vertical::getArrow() {
	return m_arrow;
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
	return m_arrow;
}

Oxer::Oxer()
{
	initOxer();
	setTexture(Oxers::texture);
	setOrigin(getLocalBounds().width / 2, getLocalBounds().height / 2);
	m_arrow.setTexture(Oxers::arrow_texture);
	m_arrow.setOrigin(m_arrow.getLocalBounds().width / 2, m_arrow.getLocalBounds().height / 2);
}

int Oxer::getNbBarres()
{
	return m_nbBarres;
}

void Oxer::setNbBarres(int barres)
{
	m_nbBarres = barres;
}

void Oxer::changeDirection() {
	m_arrow.rotate(180);
}
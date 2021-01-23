#include "Parcours.h"
#include "NullSprite.cpp"
#include <iostream>
#include <math.h>

template<typename Base, typename T>
inline bool instanceof(const T*) {
	return std::is_base_of<Base, T>::value;
}
bool shouldMove(Sprite sprite, int x);
bool shouldMove(TextField field, int x);
int getBarre(std::vector<Barre>& barres, int x, int y);
int getOxer(std::vector<Oxer> &oxers, int x, int y);
int getVertical(std::vector<Vertical> &verticaux, int x, int y);
int getField(std::vector<TextField>& fields, int x, int y);

NullSprite s;
bool init = false;
Texture arrow_texture;
TextField f(2);

Parcours::Parcours() : m_selectedBarre(-1), m_selectedOxer(-1), m_selectedVertical(-1)
{
	if (!init) {
		arrow_texture.loadFromFile("graphics/arrow.png");
		init = true;
	}
	for (int i = 0; i < 5; i++) {
		Barre barre;
		barre.setPosition(220, 170);
		m_barres.push_back(barre);
	}
	for (int i = 0; i < 5; i++) {
		Oxer oxer;
		oxer.setPosition(900, 195);
		oxer.getArrow().setPosition(900, 195);
		m_oxers.push_back(oxer);
	}
	for (int i = 0; i < 5; i++) {
		Vertical vertical;
		vertical.setPosition(550, 170);
		vertical.getArrow().setPosition(550, 170);
		m_verticaux.push_back(vertical);
	}
	f.setPosition(1100, 170);
	m_fields.push_back(f);
	m_carriere.setPointCount(4);
	m_carriere.setPosition(50, 100);
	m_carriere.setPoint(0, Vector2f(0, 0));
	m_carriere.setPoint(1, Vector2f(4000, 0));
	m_carriere.setPoint(3, Vector2f(0, 2000));
	m_carriere.setPoint(2, Vector2f(4000, 2000));
	m_carriere.setFillColor(Color(230, 204, 179));
}

int Parcours::getNbVerticaux()
{
	return m_verticaux.size();
}

int Parcours::getNbOxers()
{
	return m_oxers.size();
}

int Parcours::getNbBarres()
{
	return m_barres.size();
}

void Parcours::setNbVerticaux(int nb)
{
	m_verticaux.resize(nb);
}

void Parcours::setNbOxers(int nb)
{
	m_oxers.resize(nb);
}

void Parcours::setNbBarres(int nb)
{
	m_barres.resize(nb);
}

bool Parcours::handleUserAction(int x, int y)
{
	if (!m_move && !m_rotate) {

		m_selectedField = getField(m_fields, x, y);
		if (m_selectedField != -1) {
			m_move = shouldMove(m_fields.at(m_selectedField), x);
			m_fields.at(m_selectedField).setFocus(true);
			m_rotate = !m_move;
		}
		else {
			m_selectedBarre = getBarre(m_barres, x, y);
			if (m_selectedBarre != -1) {
				m_move = shouldMove(m_barres.at(m_selectedBarre), x);
				m_rotate = !m_move;
			}
			else {
				m_selectedOxer = getOxer(m_oxers, x, y);
				if (m_selectedOxer != -1) {
					m_move = shouldMove(m_oxers.at(m_selectedOxer), x);
					m_rotate = !m_move;
				}
				else {
					m_selectedVertical = getVertical(m_verticaux, x, y);
					if (m_selectedVertical != -1) {
						m_move = shouldMove(m_verticaux.at(m_selectedVertical), x);
						m_rotate = !m_move;
					}
				}
			}
		}
	}
	if (m_move || m_rotate) {
		if (m_move) {
			if (m_selectedBarre != -1) {
				m_barres.at(m_selectedBarre).setPosition(x, y);
			}
			else if (m_selectedVertical != -1) {
				m_verticaux.at(m_selectedVertical).setPosition(x, y);
				m_verticaux.at(m_selectedVertical).getArrow().setPosition(x, y);
			}
			else if (m_selectedOxer != -1) {
				m_oxers.at(m_selectedOxer).setPosition(x, y);
				m_oxers.at(m_selectedOxer).getArrow().setPosition(x, y);
			}
			else {
				m_fields.at(m_selectedField).setPosition(x, y);
			}
		}
		else if (m_rotate) {
			if (m_selectedBarre != -1) {
				if (!m_barres.at(m_selectedBarre).getGlobalBounds().contains(x, y)) {
					m_barres.at(m_selectedBarre).rotate(1.f);
				}
			}
			else if (m_selectedVertical != -1) {
				if (!m_verticaux.at(m_selectedVertical).getGlobalBounds().contains(x, y)) {
					m_verticaux.at(m_selectedVertical).rotate(1.f);
					m_verticaux.at(m_selectedVertical).getArrow().rotate(1.f);
				}
			}
			else if (m_selectedOxer != -1) {
				if (!m_oxers.at(m_selectedOxer).getGlobalBounds().contains(x, y)) {
					m_oxers.at(m_selectedOxer).rotate(1.f);
					m_oxers.at(m_selectedOxer).getArrow().rotate(1.f);
				}
			}
			else {
				if (!m_fields.at(m_selectedField).getGlobalBounds().contains(x, y)) {
					m_fields.at(m_selectedField).rotate(1.f);
				}
			}

		}
	}
	return m_move || m_rotate;
}

bool Parcours::handleRightClickAction(int x, int y) {
	m_move = m_rotate = false;
	m_selectedBarre = getBarre(m_barres, x, y);
	if (m_selectedBarre != -1) {
		return true;
	}
	else {
		m_selectedOxer = getOxer(m_oxers, x, y);
		if (m_selectedOxer != -1) {
			return true;
		}
		else {
			m_selectedVertical = getVertical(m_verticaux, x, y);
			if (m_selectedVertical != -1) {
				return true;
			}
			else {
				m_selectedField = getField(m_fields, x, y);
				if (m_selectedField != -1) {
					return true;
				}
			}
		}
	}
	return false;
}

void Parcours::handleInput(Event e) {
	if (m_selectedField != -1) {
		m_fields.at(m_selectedField).handleInput(e);
	}
}

int getBarre(std::vector<Barre> &barres, int x, int y) {
	for (int i = 0; i < barres.size(); i++) {
		Barre barre = barres.at(i);
		if (barre.getGlobalBounds().contains(x, y)) {
			return i;
		}
	}
	return -1;
}

int getVertical(std::vector<Vertical> &verticaux, int x, int y) {
	for (int i = 0; i < verticaux.size(); i++) {
		Vertical vertical = verticaux.at(i);
		if (vertical.getGlobalBounds().contains(x, y)) {
			return i;
		}
	}
	return -1;
}

int getOxer(std::vector<Oxer> &oxers, int x, int y) {
	for (int i = 0; i < oxers.size(); i++) {
		Oxer oxer = oxers.at(i);
		if (oxer.getGlobalBounds().contains(x, y)) {
			return i;
		}
	}
	return -1;
}

int getField(std::vector<TextField>& fields, int x, int y) {
	for (int i = 0; i < fields.size(); i++) {
		TextField field = fields.at(i);
		if (field.contains(Vector2f(x, y))) {
			return i;
		}
	}
	return -1;
}

bool shouldMove(Sprite sprite, int x)
{
	return x > sprite.getGlobalBounds().left + 0.1 * sprite.getLocalBounds().width;
}

bool shouldMove(TextField field, int x) {
	return x > field.getGlobalBounds().left + 0.1 * field.getGlobalBounds().width;
}

void Parcours::draw(RenderWindow& window) {
	window.draw(getCarriere());
	for (Barre barre : getBarres()) {
		window.draw(barre);
	}
	for (Vertical vertical : getVerticaux()) {
		window.draw(vertical);
		window.draw(vertical.getArrow());
	}
	for (Oxer oxer : getOxers()) {
		window.draw(oxer);
		window.draw(oxer.getArrow());
	}
	for (TextField field : m_fields) {
		window.draw(field);
	}
}

void Parcours::actionOver() {
	if (m_rotate || m_move) {
		m_move = false;
		m_rotate = false;
		m_selectedBarre = -1;
		m_selectedOxer = -1;
		m_selectedVertical = -1;
	}
}

TextField field(2); 
void Parcours::add() {
	if (m_selectedBarre != -1) {
		m_barres.push_back(Barre());
	}
	else if (m_selectedOxer != -1) {
		m_oxers.push_back(Oxer());
	}
	else if (m_selectedVertical != -1) {
		m_verticaux.push_back(Vertical());
	} 
	else if (m_selectedField != -1) {
		m_fields.push_back(field);
	}
}

void Parcours::del() {
	if (m_selectedBarre != -1) {
		m_barres.erase(m_barres.begin() + m_selectedBarre);
	}
	else if (m_selectedOxer != -1) {
		m_oxers.erase(m_oxers.begin() + m_selectedOxer);
	}
	else if (m_selectedVertical != -1) {
		m_verticaux.erase(m_verticaux.begin() + m_selectedVertical);
	}
	else if (m_selectedField != -1) {
		m_fields.erase(m_fields.begin() + m_selectedField);
	}
}

void Parcours::resetRotation() {
	if (m_selectedBarre != -1) {
		m_barres.at(m_selectedBarre).setRotation(0);
	}
	else if (m_selectedOxer != -1) {
		m_oxers.at(m_selectedOxer).setRotation(0);
		m_oxers.at(m_selectedOxer).getArrow().setRotation(0);
	}
	else if (m_selectedVertical != -1) {
		m_verticaux.at(m_selectedVertical).setRotation(0);
		m_verticaux.at(m_selectedVertical).getArrow().setRotation(0);
	}
	else if (m_selectedField != -1) {
		m_fields.at(m_selectedField).setRotation(0);
	}
}

void Parcours::addField(int x, int y) {
	field.setPosition(x, y);
	m_fields.push_back(field);
}

void Parcours::changeDirection() {
	if (m_selectedOxer != -1) {
		m_oxers.at(m_selectedOxer).changeDirection();
	}
	else if (m_selectedVertical != -1) {
		m_verticaux.at(m_selectedVertical).changeDirection();
	}
}

ConvexShape Parcours::getCarriere() {
	return m_carriere;
}

std::vector<Vertical> Parcours::getVerticaux()
{
	return m_verticaux;
}

std::vector<Oxer> Parcours::getOxers()
{
	return m_oxers;
}

std::vector<Barre> Parcours::getBarres()
{
	return m_barres;
}

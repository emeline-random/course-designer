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
TextField f(5);

Parcours::Parcours() : selectedBarre(-1), selectedOxer(-1), selectedVertical(-1)
{
	if (!init) {
		arrow_texture.loadFromFile("graphics/arrow.png");
		init = true;
	}
	for (int i = 0; i < 5; i++) {
		Barre barre;
		barre.setPosition(100, 100);
		barres.push_back(barre);
	}
	for (int i = 0; i < 5; i++) {
		oxers.push_back(Oxer());
	}
	for (int i = 0; i < 5; i++) {
		verticaux.push_back(Vertical());
	}
	fields.push_back(f);
	carriere.setPointCount(4);
	carriere.setPosition(50, 100);
	carriere.setPoint(0, Vector2f(0, 0));
	carriere.setPoint(1, Vector2f(4000, 0));
	carriere.setPoint(3, Vector2f(0, 2000));
	carriere.setPoint(2, Vector2f(4000, 2000));
	carriere.setFillColor(Color(230, 204, 179));
}

int Parcours::getNbVerticaux()
{
	return verticaux.size();
}

int Parcours::getNbOxers()
{
	return oxers.size();
}

int Parcours::getNbBarres()
{
	return barres.size();
}

void Parcours::setNbVerticaux(int nb)
{
	verticaux.resize(nb);
}

void Parcours::setNbOxers(int nb)
{
	oxers.resize(nb);
}

void Parcours::setNbBarres(int nb)
{
	barres.resize(nb);
}

bool Parcours::handleUserAction(int x, int y)
{
	if (!move && !rotate) {

		selectedField = getField(fields, x, y);
		if (selectedField != -1) {
			move = shouldMove(fields.at(selectedField), x);
			fields.at(selectedField).setFocus(true);
			rotate = !move;
		}
		else {
			selectedBarre = getBarre(barres, x, y);
			if (selectedBarre != -1) {
				move = shouldMove(barres.at(selectedBarre), x);
				rotate = !move;
			}
			else {
				selectedOxer = getOxer(oxers, x, y);
				if (selectedOxer != -1) {
					move = shouldMove(oxers.at(selectedOxer), x);
					rotate = !move;
				}
				else {
					selectedVertical = getVertical(verticaux, x, y);
					if (selectedVertical != -1) {
						move = shouldMove(verticaux.at(selectedVertical), x);
						rotate = !move;
					}
				}
			}
		}
	}
	if (move || rotate) {
		if (move) {
			if (selectedBarre != -1) {
				barres.at(selectedBarre).setPosition(x, y);
			}
			else if (selectedVertical != -1) {
				verticaux.at(selectedVertical).setPosition(x, y);
				verticaux.at(selectedVertical).getArrow().setPosition(x, y);
			}
			else if (selectedOxer != -1) {
				oxers.at(selectedOxer).setPosition(x, y);
				oxers.at(selectedOxer).getArrow().setPosition(x, y);
			}
			else {
				fields.at(selectedField).setPosition(x, y);
			}
		}
		else if (rotate) {
			if (selectedBarre != -1) {
				if (!barres.at(selectedBarre).getGlobalBounds().contains(x, y)) {
					barres.at(selectedBarre).rotate(1.f);
				}
			}
			else if (selectedVertical != -1) {
				if (!verticaux.at(selectedVertical).getGlobalBounds().contains(x, y)) {
					verticaux.at(selectedVertical).rotate(1.f);
					verticaux.at(selectedVertical).getArrow().rotate(1.f);
				}
			}
			else if (selectedOxer != -1) {
				if (!oxers.at(selectedOxer).getGlobalBounds().contains(x, y)) {
					oxers.at(selectedOxer).rotate(1.f);
					oxers.at(selectedOxer).getArrow().rotate(1.f);
				}
			}
			else {
				if (!fields.at(selectedField).getGlobalBounds().contains(x, y)) {
					fields.at(selectedField).rotate(1.f);
				}
			}

		}
	}
	return move || rotate;
}

bool Parcours::handleRightClickAction(int x, int y) {
	move = rotate = false;
	selectedBarre = getBarre(barres, x, y);
	if (selectedBarre != -1) {
		return true;
	}
	else {
		selectedOxer = getOxer(oxers, x, y);
		if (selectedOxer != -1) {
			return true;
		}
		else {
			selectedVertical = getVertical(verticaux, x, y);
			if (selectedVertical != -1) {
				return true;
			}
			else {
				selectedField = getField(fields, x, y);
				if (selectedField != -1) {
					return true;
				}
			}
		}
	}
	return false;
}

void Parcours::handleInput(Event e) {
	if (selectedField != -1) {
		fields.at(selectedField).handleInput(e);
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
	for (TextField field : fields) {
		window.draw(field);
	}
}

void Parcours::actionOver() {
	if (rotate || move) {
		move = false;
		rotate = false;
		selectedBarre = -1;
		selectedOxer = -1;
		selectedVertical = -1;
	}
}

TextField field(5); 
void Parcours::add() {
	if (selectedBarre != -1) {
		barres.push_back(Barre());
	}
	else if (selectedOxer != -1) {
		oxers.push_back(Oxer());
	}
	else if (selectedVertical != -1) {
		verticaux.push_back(Vertical());
	} 
	else if (selectedField != -1) {
		fields.push_back(field);
	}
}

void Parcours::del() {
	if (selectedBarre != -1) {
		barres.erase(barres.begin() + selectedBarre);
	}
	else if (selectedOxer != -1) {
		oxers.erase(oxers.begin() + selectedOxer);
	}
	else if (selectedVertical != -1) {
		verticaux.erase(verticaux.begin() + selectedVertical);
	}
	else if (selectedField != -1) {
		fields.erase(fields.begin() + selectedField);
	}
}

void Parcours::resetRotation() {
	if (selectedBarre != -1) {
		barres.at(selectedBarre).setRotation(0);
	}
	else if (selectedOxer != -1) {
		oxers.at(selectedOxer).setRotation(0);
		oxers.at(selectedOxer).getArrow().setRotation(0);
	}
	else if (selectedVertical != -1) {
		verticaux.at(selectedVertical).setRotation(0);
		verticaux.at(selectedVertical).getArrow().setRotation(0);
	}
	else if (selectedField != -1) {
		fields.at(selectedField).setRotation(0);
	}
}

void Parcours::addField(int x, int y) {
	field.setPosition(x, y);
	fields.push_back(field);
}

void Parcours::changeDirection() {
	if (selectedOxer != -1) {
		oxers.at(selectedOxer).changeDirection();
	}
	else if (selectedVertical != -1) {
		verticaux.at(selectedVertical).changeDirection();
	}
}

ConvexShape Parcours::getCarriere() {
	return carriere;
}

std::vector<Vertical> Parcours::getVerticaux()
{
	return verticaux;
}

std::vector<Oxer> Parcours::getOxers()
{
	return oxers;
}

std::vector<Barre> Parcours::getBarres()
{
	return barres;
}

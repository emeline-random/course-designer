#include "Parcours.h"
#include "NullSprite.cpp"
#include <iostream>
#include <math.h>

template<typename Base, typename T>
inline bool instanceof(const T*) {
	return std::is_base_of<Base, T>::value;
}
bool shouldMove(Sprite sprite, int x);
int getBarre(std::vector<Barre> &barres, int x, int y);
int getOxer(std::vector<Oxer> &oxers, int x, int y);
int getVertical(std::vector<Vertical> &verticaux, int x, int y);

NullSprite s;

Parcours::Parcours() : selectedBarre(-1), selectedOxer(-1), selectedVertical(-1)
{
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

void Parcours::handleUserAction(int x, int y)
{
	if (!move && !rotate) {
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
	if (move || rotate) {
		if (move) {
			if (selectedBarre != -1) {
				barres.at(selectedBarre).setPosition(x, y);
			}
			else if (selectedVertical != -1) {
				verticaux.at(selectedVertical).setPosition(x, y);
			}
			else {
				oxers.at(selectedOxer).setPosition(x, y);
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
				}
			}
			else {
				if (!oxers.at(selectedOxer).getGlobalBounds().contains(x, y)) {
					oxers.at(selectedOxer).rotate(1.f);
				}
			}
		}
	}
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
		}
	}
	return false;
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

bool shouldMove(Sprite sprite, int x)
{
	return x > sprite.getGlobalBounds().left + 0.1 * sprite.getLocalBounds().width;
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

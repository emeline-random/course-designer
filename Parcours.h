#pragma once
#include "Obstacle.h"
#include "Barre.h"
#include "TextField.h"
#include <vector>

class Parcours {
public:
	Parcours();
	int getNbVerticaux();
	int getNbOxers();
	int getNbBarres();
	void setNbVerticaux(int nb);
	void setNbOxers(int nb);
	void setNbBarres(int nb);
	bool handleUserAction(int x, int y);
	bool handleRightClickAction(int x, int y);
	void handleInput(Event e);
	void draw(RenderWindow& window);
	void actionOver();
	void add();
	void del();
	void resetRotation();
	void addField(int x, int y);
	void changeDirection();
	ConvexShape getCarriere();
	std::vector<Vertical> getVerticaux();
	std::vector<Oxer> getOxers();
	std::vector<Barre> getBarres();
private:
	std::vector<Vertical> verticaux;
	std::vector<Oxer> oxers;
	std::vector<Barre> barres;
	std::vector<TextField> fields;
	ConvexShape carriere;
	bool move = false;
	bool rotate = false;
	int selectedBarre = -1;
	int selectedVertical = -1;
	int selectedOxer = -1;
	int selectedField = -1;
};
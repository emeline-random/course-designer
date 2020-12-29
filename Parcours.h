#pragma once
#include "Obstacle.h"
#include "Barre.h"
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
	void handleUserAction(int x, int y);
	bool handleRightClickAction(int x, int y);
	void actionOver();
	void add();
	void del();
	std::vector<Vertical> getVerticaux();
	std::vector<Oxer> getOxers();
	std::vector<Barre> getBarres();
private:
	std::vector<Vertical> verticaux;
	std::vector<Oxer> oxers;
	std::vector<Barre> barres;
	bool move = false;
	bool rotate = false;
	int selectedBarre = -1;
	int selectedVertical = -1;
	int selectedOxer = -1;
};
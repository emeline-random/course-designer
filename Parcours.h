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
	std::vector<Vertical> m_verticaux;
	std::vector<Oxer> m_oxers;
	std::vector<Barre> m_barres;
	std::vector<TextField> m_fields;
	ConvexShape m_carriere;
	bool m_move = false;
	bool m_rotate = false;
	int m_selectedBarre = -1;
	int m_selectedVertical = -1;
	int m_selectedOxer = -1;
	int m_selectedField = -1;
};
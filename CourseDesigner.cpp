// Include important libraries here
#include <SFML/Graphics.hpp>
#include <sstream>
#include <math.h>  
#include "Parcours.h"
#include "Menu.h"
// Make code easier to type with "using namespace"
using namespace sf;


int main()
{
	// Create a video mode object
	VideoMode vm(1000, 750);
	// Create and open a window
	RenderWindow window(vm, "Course designer", Style::Default);
	window.setVerticalSyncEnabled(true);
	View view = window.getView();
	bool menuShown = false;
	bool input = true;
	/********SPRITES*******/
	Parcours parcours = Parcours();
	int selectedBarre = -1;
	int selectedVertical = -1;
	int selectedOxer = -1;
	/********MENU*******/
	Menu menu(Color(155, 155, 155));
	Font f;
	f.loadFromFile("fonts/Roboto-Black.ttf");
	Text t;
	t.setString("Remove");
	t.setFont(f);
	Text t2;
	t2.setString("Add");
	t2.setFont(f);
	menu.addItem(MenuItem(t2, MenuItem::Action::ADD));
	menu.addItem(MenuItem(t, MenuItem::Action::DELETE));
	while (window.isOpen())
	{
		/*****************************************
				Handle the players input
		*****************************************/
		auto mouse_pos = sf::Mouse::getPosition(window);
		auto translated_pos = window.mapPixelToCoords(mouse_pos);
		int y = translated_pos.y;
		int x = translated_pos.x;
		if (Keyboard::isKeyPressed(Keyboard::Escape)) {
			window.close();
		}
		if (Mouse::isButtonPressed(Mouse::Left)) {
			if (menuShown && menu.getMenu().getGlobalBounds().contains(x, y)) {
				switch (menu.getAction(x, y)) {
				case MenuItem::Action::ADD:
					parcours.add();
					menuShown = false;
					input = false;
					break;
				case MenuItem::Action::DELETE:
					parcours.del();
					menuShown = false;
					input = false;
					break;
				}
			}
			else if (menuShown) {
				menuShown = false;
				input = false;
			}
			else {
				parcours.handleUserAction(x, y);
			}
		}
		if (Mouse::isButtonPressed(Mouse::Right) && input) {
			if (menuShown) {
				menuShown = false;
				input = false;
				parcours.actionOver();
			}
			else {
				if (parcours.handleRightClickAction(x, y)) {
					menu.setPosition(x, y);
					menuShown = true;
					input = false;
				}
			}
		}
		Event event;
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed) {
				window.close();
			}
			else if (event.type == sf::Event::MouseWheelScrolled)
			{
				if (event.mouseWheelScroll.wheel == Mouse::VerticalWheel) {
					if (event.mouseWheelScroll.delta > 0) {
						View view = window.getView();
						view.zoom(0.99);
						window.setView(view);
					}
					else {
						View view = window.getView();
						view.zoom(1.01);
						window.setView(view);
					}
				}
			}
			else if (event.type == sf::Event::MouseButtonReleased) {
				input = true;
				parcours.actionOver();
			}
		}

		/*****************************************
					Draw the scene
		*****************************************/
		window.clear(Color(183, 163, 163));

		for (Barre barre : parcours.getBarres()) {
			window.draw(barre);
		}
		for (Vertical vertical : parcours.getVerticaux()) {
			window.draw(vertical);
		}
		for (Oxer oxer : parcours.getOxers()) {
			window.draw(oxer);
		}
		if (menuShown) {
			menu.draw(window);
		}

		window.display();
	}
	return 0;
}

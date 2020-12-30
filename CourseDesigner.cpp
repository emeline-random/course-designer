// Include important libraries here
#include <SFML/Graphics.hpp>
#include <sstream>
#include <math.h>  
#include "Parcours.h"
#include "Menu.h"
#include "TextField.h"
// Make code easier to type with "using namespace"
using namespace sf;


int main()
{
	// Create a video mode object
	ContextSettings settings;
	settings.antialiasingLevel = 8;
	VideoMode vm(1000, 750);
	// Create and open a window
	RenderWindow window(vm, "Course designer", Style::Default, settings);
	window.setVerticalSyncEnabled(true);
	View view = window.getView();
	bool menuShown = false;
	bool input = true;
	/********SPRITES*******/
	Parcours parcours = Parcours();
	int selectedBarre = -1;
	int selectedVertical = -1;
	int selectedOxer = -1;
	TextField title(50);
	title.setPosition(500, 50);
	/********MENU*******/
	Menu menu(Color(155, 155, 155));
	Font f;
	f.loadFromFile("fonts/Roboto-Black.ttf");
	Text t;
	t.setString("Remove");
	t.setFont(f);
	t.setFillColor(Color::Black);
	Text t2;
	t2.setString("Add");
	t2.setFont(f);
	t2.setFillColor(Color::Black);
	menu.addItem(MenuItem(t2, MenuItem::Action::ADD));
	menu.addItem(MenuItem(t, MenuItem::Action::DELETE));
	int lastx = 0, lasty = 0;
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
			if (title.contains(Vector2f(x, y))) {
				if (title.hasFocus()) {
					title.setPosition(x, y);
				}
				title.setFocus(true);
				lastx = lasty = 0;
			}
			else if (title.hasFocus()) {
				title.setFocus(false);
				lastx = lasty = 0;
			}
			else if (menuShown && menu.getMenu().getGlobalBounds().contains(x, y)) {
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
				lastx = lasty = 0;
			}
			else if (menuShown) {
				menuShown = false;
				input = false;
				lastx = lasty = 0;
			}
			else {
				if (!parcours.handleUserAction(x, y)) {
					if (lastx == 0 && lasty == 0) {
						lastx = x;
						lasty = y;
					}
					View v = window.getView();
					v.setCenter(v.getCenter().x - x + lastx, v.getCenter().y - y + lasty);
					window.setView(v);
					lastx = x;
					lasty = y;
				}
			}
			input = false;
		}
		if (Mouse::isButtonPressed(Mouse::Right) && input) {
			if (menuShown) {
				menuShown = false;
				parcours.actionOver();
			}
			else {
				if (parcours.handleRightClickAction(x, y)) {
					menu.setPosition(x, y);
					menuShown = true;
				}
			}
			input = false;
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
				lastx = 0;
				lasty = 0;
			}
			else if (event.type == sf::Event::TextEntered) {
				if (title.hasFocus()) {
					title.handleInput(event);
				}
			}
		}

		/*****************************************
					Draw the scene
		*****************************************/
		window.clear(Color::White);

		window.draw(parcours.getCarriere());
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
		window.draw(title);

		window.display();
	}
	return 0;
} 
// Include important libraries here
#include <SFML/Graphics.hpp>
#include <sstream>
#include <math.h>  
#include "Parcours.h"
#include "Menu.h"
#include "TextField.h"
// Make code easier to type with "using namespace"
using namespace sf;

Text getText(String s);
void titleIn(TextField& title, int x, int y);
void titleOut(TextField& title);
void handleMenuAction(MenuItem::Action action, Parcours& parcours, bool& input, bool& menuShown);
void handleMainMenuAction(MenuItem::Action action, Parcours& parcours, bool& input, bool& menuShown, int x, int y);
void hideMenus(bool& input, bool& menuShown, bool mainMenuShown);
Font f;
int lastx = 0, lasty = 0;


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
	bool input = true;
	bool moveView = false;
	/********SPRITES*******/
	f.loadFromFile("fonts/Roboto-Black.ttf");
	Parcours parcours = Parcours();
	int selectedBarre = -1;
	int selectedVertical = -1;
	int selectedOxer = -1;
	TextField title(50);
	title.setPosition(500, 50);
	/********MENU*******/
	Menu menu(Color(155, 155, 155));
	menu.addItem(MenuItem(getText("Add"), MenuItem::Action::ADD));
	menu.addItem(MenuItem(getText("Remove"), MenuItem::Action::DELETE));
	menu.addItem(MenuItem(getText("Reset rotation"), MenuItem::Action::ROTATE));
	menu.addItem(MenuItem(getText("Change direction"), MenuItem::Action::CHANGE_DIRECTION));
	bool menuShown = false;
	Menu mainMenu(Color(155, 155, 155));
	mainMenu.addItem(MenuItem(getText("Resize"), MenuItem::Action::RESIZE));
	mainMenu.addItem(MenuItem(getText("Add text"), MenuItem::Action::ADD_TEXT));
	bool mainMenuShown = false;

	view.zoom(3);
	window.setView(view);
	while (window.isOpen())
	{
		moveView = false;
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
			if (title.contains(Vector2f(x, y)) || (title.hasFocus() && !input)) {
				titleIn(title, x, y);
			}
			else if (title.hasFocus()) {
				titleOut(title);
			}
			else if (menuShown && menu.getMenu().getGlobalBounds().contains(x, y)) {
				handleMenuAction(menu.getAction(x, y), parcours, input, menuShown);
			}
			else if (mainMenuShown && mainMenu.getMenu().getGlobalBounds().contains(x, y)) {
				handleMainMenuAction(mainMenu.getAction(x, y), parcours, input, mainMenuShown, x, y);
			}
			else if (menuShown || mainMenuShown) {
				hideMenus(input, menuShown, mainMenuShown);
			}
			else {
				moveView = !parcours.handleUserAction(x, y);
			}
			input = false;
		}
		if (Mouse::isButtonPressed(Mouse::Right) && input) {
			if (menuShown || mainMenuShown) {
				menuShown = mainMenuShown = false;
				parcours.actionOver();
			}
			else {
				if (parcours.handleRightClickAction(x, y)) {
					menu.setPosition(x, y);
					menuShown = true;
				}
				else {
					mainMenu.setPosition(x, y);
					mainMenuShown = true;
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
			else if (event.type == sf::Event::MouseMoved && moveView) {
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
			else if (event.type == sf::Event::TextEntered) {
				if (title.hasFocus()) {
					title.handleInput(event);
				}
				else {
					parcours.handleInput(event);
				}
			}
		}

		/*****************************************
					Draw the scene
		*****************************************/
		window.clear(Color::White);

		parcours.draw(window);
		if (menuShown) {
			menu.draw(window);
		}
		else if (mainMenuShown) {
			mainMenu.draw(window);
		}
		window.draw(title);

		window.display();
	}
	return 0;
}

Text getText(String s) {
	Text t;
	t.setString(s);
	t.setFont(f);
	t.setFillColor(Color::Black);
	return t;
}
void titleIn(TextField& title, int x, int y) {
	if (title.hasFocus()) {
		title.setPosition(x, y);
	}
	else {
		title.setFocus(true);
	}
	lastx = lasty = 0;
}
void titleOut(TextField& title) {
	title.setFocus(false);
	lastx = lasty = 0;
}

void handleMenuAction(MenuItem::Action action, Parcours& parcours, bool& input, bool& menuShown) {
	switch (action) {
	case MenuItem::Action::ADD:
		parcours.add();
		menuShown = input = false;
		break;
	case MenuItem::Action::DELETE:
		parcours.del();
		menuShown = input = false;
		break;
	case MenuItem::Action::ROTATE:
		parcours.resetRotation();
		menuShown = input = false;
		break;
	case MenuItem::Action::CHANGE_DIRECTION:
		parcours.changeDirection();
		menuShown = input = false;
		break;
	}
	lastx = lasty = 0;
}

void handleMainMenuAction(MenuItem::Action action, Parcours& parcours, bool& input, bool& menuShown, int x, int y) {
	switch (action) {
	case MenuItem::Action::RESIZE: //TODO
		menuShown = input = false;
		break;
	case MenuItem::Action::ADD_TEXT:
		parcours.addField(x, y);
		menuShown = input = false;
		break;

	}
	lastx = lasty = 0;
}

void hideMenus(bool& input, bool& menuShown, bool mainMenuShown) {
	menuShown = mainMenuShown = input = false;
	lastx = lasty = 0;
}
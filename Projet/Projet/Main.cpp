#include <cstdlib>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

int main()
{
	RenderWindow window(VideoMode(770, 770), "PacMan_alpha_0.1");
	window.setKeyRepeatEnabled(false);

	Texture sheet;
	Texture sheet2;
	Sprite pac_man;
	Sprite fond;

	if (!sheet.loadFromFile("images\\Sprites_Pac_Man_King_Arthur_0_1.png", IntRect(4, 10, 16, 16))) // Si le chargement du fichier a échoué
	{
		cout << "Erreur durant le chargement de la texture" << endl;
		return EXIT_FAILURE; // On ferme le programme
	}

	if(!sheet2.loadFromFile("images\\Pac_man_sprite_X4.png", IntRect(1500, 1143, 772, 773)))
	{
		cout << "Erreur durant le chargement de la texture" << endl;
		return EXIT_FAILURE; // On ferme le programme
	}

	pac_man.setTexture(sheet);
	fond.setTexture(sheet2);


	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
		}

		if (event.type == Event::KeyPressed)
		{
			switch (event.key.code)
			{
			case(Keyboard::Numpad4):
				pac_man.move(Vector2f(-1, 0));
				break;

			case(Keyboard::Numpad6):
				pac_man.move(Vector2f(1, 0));
				break;

			case(Keyboard::Numpad8):
				pac_man.move(Vector2f(0, -1));
				break;

			case(Keyboard::Numpad2):
				pac_man.move(Vector2f(0, 1));
				break;

			default:

				break;
			}
		}

		window.clear();

		window.draw(fond);
		window.draw(pac_man);

		//window.draw(shape);
		window.display();
	}
	return 0;
}

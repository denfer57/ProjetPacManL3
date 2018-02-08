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
	RenderWindow window(VideoMode(900, 600), "PacMan_alpha_0.1");
	window.setKeyRepeatEnabled(false);

	Texture sheet;
	Sprite pac_man;

	if (!sheet.loadFromFile("images\\Sprites_Pac_Man_King_Arthur_0_1.png", IntRect(4, 10, 16, 16))) // Si le chargement du fichier a échoué
	{
		cout << "Erreur durant le chargement de la texture" << endl;
		return EXIT_FAILURE; // On ferme le programme
	}

	pac_man.setTexture(sheet);



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
            switch(event.key.code)
            {
                case(Keyboard::Left):
                    pac_man.move(Vector2f(-1, 0));
                break;

                case(Keyboard::Right):
                    pac_man.move(Vector2f(1, 0));
                break;

                case(Keyboard::Up):
                    pac_man.move(Vector2f(0, -1));
                break;

                case(Keyboard::Down):
                    pac_man.move(Vector2f(0, 1));
                break;

                default:

                break;
            }
        }

		window.clear();


		window.draw(pac_man);

		//window.draw(shape);
		window.display();
	}
	return 0;
}

#include <cstdlib>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

using namespace std;
using namespace sf;

int main()
{
	RenderWindow window(VideoMode(900, 600), "PacMan_alpha_0.1");
	CircleShape shape(100.f);
	shape.setFillColor(Color::Green);

	Texture sheet;
	Sprite pac_man;

	if (!sheet.loadFromFile("images\\Sprites_Pac_Man_King_Arthur_0_1.png", IntRect(10, 10, 32, 32))) // Si le chargement du fichier a échoué
	{
		cout << "Erreur durant le chargement de la texture" << endl;
		return EXIT_FAILURE; // On ferme le programme
	}

	if (!sheet.create(200, 200))
	{
		cout << "Erreur durant la création de la texture" << endl;
		return EXIT_FAILURE; // On ferme le programme
	}

	pac_man.setTexture(sheet);

	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();


		window.draw(pac_man);

		window.draw(shape);
		window.display();
	}
	return 0;
}

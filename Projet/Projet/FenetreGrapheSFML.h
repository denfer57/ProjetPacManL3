
#include<SFML/Graphics/RenderWindow.hpp>
#include<SFML/Graphics/VertexArray.hpp>
//#include <SFML/Graphics/Vertex.hpp>
#include<SFML/GRAPHICS/CircleShape.hpp>
#include<SFML/GRAPHICS/ConvexShape.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>

#include "Sommet.h"
#include "Arete.h"

using namespace sf;
using namespace std;

class FenetreGrapheSFML
{
public:
	RenderWindow fenetre;

	FenetreGrapheSFML(const string & titre,const int largeur,
		const int hauteur, const Font & font1) {
		RenderWindow window(VideoMode(largeur, hauteur), titre);
		window.setKeyRepeatEnabled(false);

		Texture sheet;
		Texture sheet2;
		Sprite pac_man;
		Sprite fond;

		if (!sheet.loadFromFile("images\\Sprites_Pac_Man_King_Arthur_0_1.png", IntRect(4, 10, 16, 16))) // Si le chargement du fichier a �chou�
		{
			cout << "Erreur durant le chargement de la texture" << endl;
		}

		if (!sheet2.loadFromFile("images\\Pac_man_sprite_X4.png", IntRect(1500, 1143, 772, 773)))
		{
			cout << "Erreur durant le chargement de la texture" << endl;
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
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad8))
					pac_man.move(0, -1);

				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad4))
					pac_man.move(-1, 0);

				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad2))
					pac_man.move(0, 1);

				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad6))
					pac_man.move(1, 0);
			}

			window.clear();

			window.draw(fond);
			window.draw(pac_man);

			//window.draw(shape);
			window.display();
		}
	}
	/**
	Dessine un sommet du graphe. Exemples :  nom, couleur, informations associ�es, etc.
	renvoie true en cas de succ�s, false en cas d'�chec
	On suppose que les coordonn�es du sommet sont d�finies par rapport au rep�re du monde
	*/
	template <class T>
	bool dessine(const Sommet<T> * sommet);

	/**
	Dessine l'ar�te (d�but->fin) en utilisant la couleur "couleur"
	renvoie true en cas de succ�s, false en cas d'�chec
	On suppose que les coordonn�es des sommets sont d�finies par rapport au rep�re du monde
	*/
	template <class T>
	bool dessine(const Sommet<T> * debut, const Sommet<T> * fin, unsigned int couleur);

	/**
	Dessine un ar�te du graphe. Exemples :  nom, couleur, informations associ�es, etc.
	renvoie true en cas de succ�s, false en cas d'�chec
	On suppose que les coordonn�es des sommets sont d�finies par rapport au rep�re du monde
	*/
	template <class S, class T>
	bool dessine(const Arete<S, T> * arete);

};
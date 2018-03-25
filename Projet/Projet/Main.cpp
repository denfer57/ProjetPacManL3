#include <cstdlib>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "Graphe.h"
#include "PElement.h"
#include "InfoArete.h"
#include "InfoSommet.h"
#include "FenetreGrapheSFML.h"

using namespace std;
using namespace sf;

Graphe<InfoArete, InfoSommet> * creeGrapheTest()
{
	cout << "Construction d'un graphe complet de 25 sommets..." << endl;

	const int nbSommet = 25;
	const int nbArete = nbSommet * (nbSommet - 1) / 2;//nombre max d'arêtes possibles

	Graphe<InfoArete, InfoSommet> * graphe = new Graphe<InfoArete, InfoSommet>();

	// Création des sommets
	Sommet<InfoSommet> * sommets[nbSommet];

	sommets[0] = graphe->creeSommet(InfoSommet("S0"));
	sommets[1] = graphe->creeSommet(InfoSommet("S1"));
	sommets[2] = graphe->creeSommet(InfoSommet("S2"));
	sommets[3] = graphe->creeSommet(InfoSommet("S3"));
	sommets[4] = graphe->creeSommet(InfoSommet("S4"));
	sommets[5] = graphe->creeSommet(InfoSommet("S5"));
	sommets[6] = graphe->creeSommet(InfoSommet("S6"));
	sommets[7] = graphe->creeSommet(InfoSommet("S7"));
	sommets[8] = graphe->creeSommet(InfoSommet("S8"));
	sommets[9] = graphe->creeSommet(InfoSommet("S9"));
	sommets[10] = graphe->creeSommet(InfoSommet("S10"));
	sommets[11] = graphe->creeSommet(InfoSommet("S11"));
	sommets[12] = graphe->creeSommet(InfoSommet("S12"));
	sommets[13] = graphe->creeSommet(InfoSommet("S13"));
	sommets[14] = graphe->creeSommet(InfoSommet("S14"));
	sommets[15] = graphe->creeSommet(InfoSommet("S15"));
	sommets[16] = graphe->creeSommet(InfoSommet("S16"));
	sommets[17] = graphe->creeSommet(InfoSommet("S17"));
	sommets[18] = graphe->creeSommet(InfoSommet("S18"));
	sommets[19] = graphe->creeSommet(InfoSommet("S19"));
	sommets[20] = graphe->creeSommet(InfoSommet("S20"));
	sommets[21] = graphe->creeSommet(InfoSommet("S21"));
	sommets[22] = graphe->creeSommet(InfoSommet("S22"));
	sommets[23] = graphe->creeSommet(InfoSommet("S23"));
	sommets[24] = graphe->creeSommet(InfoSommet("S24"));

	// Création des arêtes
	Arete<InfoArete, InfoSommet> * aretes[nbArete];
	aretes[0] = graphe->creeArete(InfoArete(5), sommets[0], sommets[1]);
	aretes[1] = graphe->creeArete(InfoArete(3), sommets[0], sommets[2]);
	aretes[2] = graphe->creeArete(InfoArete(1), sommets[0], sommets[3]);
	aretes[3] = graphe->creeArete(InfoArete(2), sommets[0], sommets[4]);
	aretes[4] = graphe->creeArete(InfoArete(8), sommets[0], sommets[5]);
	aretes[5] = graphe->creeArete(InfoArete(6), sommets[0], sommets[6]);
	aretes[6] = graphe->creeArete(InfoArete(7), sommets[0], sommets[7]);
	aretes[7] = graphe->creeArete(InfoArete(9), sommets[0], sommets[8]);

	return graphe;
}

int main()
{
	Graphe<InfoArete, InfoSommet> * graphe = creeGrapheTest();

	String titreFenetre = "PacMan";
	Font font1;
	string nomFichierFonte1 = "Polices\\Action Man Bold.ttf";
	bool ok = font1.loadFromFile(nomFichierFonte1);
	int hauteur = 770, largeur = 770;

	//cout << "Affichage du graphe : " << endl << *graphe << endl;
	FenetreGrapheSFML * fenetre = new FenetreGrapheSFML(titreFenetre, largeur, hauteur, font1);
	
	return 0;
}

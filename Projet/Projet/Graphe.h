#pragma once

#include <vector>

#include "Arete.h"
//Classe template repr�sentant le graphe.
//S est le type de l'information contenue par les ar�tes.
//T est le type de l'information contenue par les sommets.
template<class S, class T>
class Graphe
{
private:
	//Indice de la cl� suivante (pour un sommet ou une ar�te).
	int cleSuivante;

	void cloneListes(const Graphe & g);

	void effaceListes();

	template<class U>
	void effaceListe(vector<U> & liste) const;

public:
	//Liste des sommets, ar�tes
	vector<Sommet<T> *> listeSommets;
	vector<Arete<S, T> *> listeAretes;

	//Constructeur du graphe vide.
	Graphe();

	//Constructeur de copie
	Graphe(const Graphe<S, T> & graphe);

	virtual ~Graphe();

	const Graphe<S, T> & operator=(const Graphe<S, T> & graphe);

	//D�termine le nombre de sommets.
	int nombreSommets() const;

	//D�termine le nombre d'ar�tes.
	int nombreAretes() const;

	Sommet<T> * creeSommet(const T & info);

	//Cr�e une ar�te joignant 2 sommets debut et fin
	Arete<S, T> * creeArete(Sommet<T> * debut, Sommet<T> * fin, const S & info);

	//Recherche la liste des paires (voisin, ar�te) adjacentes de sommet dans le graphe.
	vector<pair<Sommet<T>*, Arete<S, T>*>>* Graphe<S, T>::adjacences(const Sommet<T>* sommet, bool getPred = true, bool getSucc = true) const;

	//Convertit en chaine de caract�res
	operator string() const;

	//Recherche une ar�te qui relie deux sommets. Retourne l'ar�te ou NULL s'il n'y en a pas.
	Arete<S, T> * getAreteParSommets(const Sommet<T> * s1, const Sommet<T> * s2) const;
};

template<class S, class T>
void Graphe<S, T>::cloneListes(const Graphe & g)
{
	//Copie tous les sommets � partir du graphe g
	for (vector<Sommet<T>*>::const_iterator it = g.listeSommets.cbegin(); it != g.listeSommets.cend(); ++it)
		listeSommets.push_back(new Sommet<T>(**it));

	//Copie toutes les ar�tes � partir du graphe g
	for (vector<Arete<S, T>*>::const_iterator it = g.listeAretes.cbegin(); it != g.listeAretes.cend(); ++it)
	{
		Arete<S, T> * nouvelleArete = new Arete<S, T>(**it);

		int cleSommetDebut = nouvelleArete->debut->cle;
		int cleSommetFin = nouvelleArete->fin->cle;
		nouvelleArete->debut = NULL;
		nouvelleArete->fin = NULL;

		//Affecte les sommets copi�es aux sommets d�but et fin des ar�tes.
		int trouve = 0;
		for (vector<Sommet<T>*>::const_iterator it = listeSommets.cbegin(); it != listeSommets.cend() && trouve < 2; ++it)
		{
			if (cleSommetDebut == (*it)->cle)
			{
				nouvelleArete->debut = *it;
				trouve++;
			}
			else if (cleSommetFin == (*it)->cle)
			{
				nouvelleArete->fin = *it;
				trouve++;
			}
		}

		listeAretes.push_back(nouvelleArete);
	}
}

template<class S, class T>
void Graphe<S, T>::effaceListes()
{
	effaceListe(listeSommets);
	effaceListe(listeAretes);
}

template<class S, class T>
template<class U>
void Graphe<S, T>::effaceListe(vector<U> & liste) const
{
	for (vector<U>::iterator it = liste.begin(); it != liste.end(); ++it)
		delete *it;
	liste.clear();
}

//Constructeur par d�faut
template<class S, class T>
Graphe<S, T>::Graphe() : cleSuivante(0), listeSommets(NULL), listeAretes(NULL) { }

//Copie les listes des ar�tes et des sommets
template<class S, class T>
Graphe<S, T>::Graphe(const Graphe<S, T> & graphe) : cleSuivante(graphe.cleSuivante)
{
	cloneListes(graphe);
}

//Destructeur
template<class S, class T>
Graphe<S, T>::~Graphe()
{
	effaceListes();
}

//Operateur =
template<class S, class T>
const Graphe<S, T>& Graphe<S, T>::operator=(const Graphe<S, T> & graphe)
{
	if (this != &graphe)
	{
		effaceListes();
		cloneListes(graphe);
		prochaineCle = graphe.prochaineCle;
	}
	return *this;
}

//D�termine le nombre de sommets
template<class S, class T>
int Graphe<S, T>::nombreSommets() const
{
	return (int)listeSommets.size();
}

//D�termine le nombre d'ar�tes
template<class S, class T>
int Graphe<S, T>::nombreAretes() const
{
	return (int)listeAretes.size();
}

//Cr�e un sommet
template<class S, class T>
Sommet<T>* Graphe<S, T>::creeSommet(const T & info)
{
	Sommet<T> * sommetCree = new Sommet<T>(cleSuivante++, info);
	listeSommets.push_back(sommetCree);
	return sommetCree;
}

//Cr�e une ar�te
template<class S, class T>
Arete<S, T>* Graphe<S, T>::creeArete(Sommet<T>* debut, Sommet<T>* fin, const S & info)
{
	if (find(listeSommets.cbegin(), listeSommets.cend(), debut) == listeSommets.cend())
		throw exception("D�but d'ar�te non d�fini");
	if (find(listeSommets.cbegin(), listeSommets.cend(), fin) == listeSommets.cend())
		throw exception("Fin d'ar�te non d�finie");

	Arete<S, T> * nouvelleArete = new Arete<S, T>(cleSuivante++, debut, fin, info);
	listeAretes.push_back(nouvelleArete);

	debut->degre++;
	fin->degre++;

	return nouvelleArete;
}

//D�termine le vecteur d'adjacence
template<class S, class T>
vector<pair<Sommet<T>*, Arete<S, T>*>>* Graphe<S, T>::adjacences(const Sommet<T>* sommet, bool getPred = true, bool getSucc = true) const
{
	vector<pair<Sommet<T> *, Arete<S, T> *>> * res = new vector<pair<Sommet<T> *, Arete<S, T> *>>();
	for (vector<Arete<S, T>*>::const_iterator it = listeAretes.cbegin(); it != listeAretes.cend(); ++it)
	{
		if (sommet == (*it)->debut && getSucc)
			res->push_back(pair<Sommet<T> *, Arete<S, T> *>((*it)->fin, *it));
		else if (sommet == (*it)->fin && getPred)
			res->push_back(pair<Sommet<T> *, Arete<S, T> *>((*it)->debut, *it));
	}
	return res;
}

//Convertit en chaine de caract�res
template<class S, class T>
Graphe<S, T>::operator string() const
{
	ostringstream oss;

	oss << "Graphe (" << endl;
	oss << "cl� suivante = " << this->cleSuivante << endl;

	oss << "nombre de sommets = " << this->nombreSommets() << endl;
	for (vector<Sommet<T>*>::const_iterator it = listeSommets.cbegin(); it != listeSommets.cend(); ++it)
		oss << **it << endl;

	oss << endl << "nombre d'aretes = " << this->nombreAretes() << endl;
	for (vector<Arete<S, T>*>::const_iterator it = listeAretes.cbegin(); it != listeAretes.cend(); ++it)
		oss << **it << endl;

	oss << ")";

	return oss.str();
}

template <class S, class T>
ostream & operator<<(ostream & os, const Graphe<S, T> & graphe)
{
	return os << (string)graphe;
}

//Cherche une ar�te qui relie deux sommets, NULL s'il n'y en a pas.
template<class S, class T>
Arete<S, T>* Graphe<S, T>::getAreteParSommets(const Sommet<T>* s1, const Sommet<T>* s2) const
{
	for (vector<Arete<S, T>*>::const_iterator it = listeAretes.cbegin(); it != listeAretes.cend(); ++it)
	{
		if ((*it)->relie(s1, s2))
			return *it;
	}
	return NULL;
}
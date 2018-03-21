#pragma once

#include <vector>

#include "Arete.h"
//Classe template représentant le graphe.
//S est le type de l'information contenue par les arêtes.
//T est le type de l'information contenue par les sommets.
template<class S, class T>
class Graphe
{
private:
	//Indice de la clé suivante (pour un sommet ou une arête).
	int cleSuivante;

	void cloneListes(const Graphe & g);

	void effaceListes();

	template<class U>
	void effaceListe(vector<U> & liste) const;

public:
	//Liste des sommets, arêtes
	vector<Sommet<T> *> listeSommets;
	vector<Arete<S, T> *> listeAretes;

	//Constructeur du graphe vide.
	Graphe();

	//Constructeur de copie
	Graphe(const Graphe<S, T> & graphe);

	virtual ~Graphe();

	const Graphe<S, T> & operator=(const Graphe<S, T> & graphe);

	//Détermine le nombre de sommets.
	int nombreSommets() const;

	//Détermine le nombre d'arêtes.
	int nombreAretes() const;

	Sommet<T> * creeSommet(const T & info);

	//Crée une arête joignant 2 sommets debut et fin
	Arete<S, T> * creeArete(Sommet<T> * debut, Sommet<T> * fin, const S & info);

	//Recherche la liste des paires (voisin, arête) adjacentes de sommet dans le graphe.
	vector<pair<Sommet<T>*, Arete<S, T>*>>* Graphe<S, T>::adjacences(const Sommet<T>* sommet, bool getPred = true, bool getSucc = true) const;

	//Convertit en chaine de caractères
	operator string() const;

	//Recherche une arête qui relie deux sommets. Retourne l'arête ou NULL s'il n'y en a pas.
	Arete<S, T> * getAreteParSommets(const Sommet<T> * s1, const Sommet<T> * s2) const;
};

template<class S, class T>
void Graphe<S, T>::cloneListes(const Graphe & g)
{
	//Copie tous les sommets à partir du graphe g
	for (vector<Sommet<T>*>::const_iterator it = g.listeSommets.cbegin(); it != g.listeSommets.cend(); ++it)
		listeSommets.push_back(new Sommet<T>(**it));

	//Copie toutes les arêtes à partir du graphe g
	for (vector<Arete<S, T>*>::const_iterator it = g.listeAretes.cbegin(); it != g.listeAretes.cend(); ++it)
	{
		Arete<S, T> * nouvelleArete = new Arete<S, T>(**it);

		int cleSommetDebut = nouvelleArete->debut->cle;
		int cleSommetFin = nouvelleArete->fin->cle;
		nouvelleArete->debut = NULL;
		nouvelleArete->fin = NULL;

		//Affecte les sommets copiées aux sommets début et fin des arêtes.
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

//Constructeur par défaut
template<class S, class T>
Graphe<S, T>::Graphe() : cleSuivante(0), listeSommets(NULL), listeAretes(NULL) { }

//Copie les listes des arêtes et des sommets
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

//Détermine le nombre de sommets
template<class S, class T>
int Graphe<S, T>::nombreSommets() const
{
	return (int)listeSommets.size();
}

//Détermine le nombre d'arêtes
template<class S, class T>
int Graphe<S, T>::nombreAretes() const
{
	return (int)listeAretes.size();
}

//Crée un sommet
template<class S, class T>
Sommet<T>* Graphe<S, T>::creeSommet(const T & info)
{
	Sommet<T> * sommetCree = new Sommet<T>(cleSuivante++, info);
	listeSommets.push_back(sommetCree);
	return sommetCree;
}

//Crée une arête
template<class S, class T>
Arete<S, T>* Graphe<S, T>::creeArete(Sommet<T>* debut, Sommet<T>* fin, const S & info)
{
	if (find(listeSommets.cbegin(), listeSommets.cend(), debut) == listeSommets.cend())
		throw exception("Début d'arête non défini");
	if (find(listeSommets.cbegin(), listeSommets.cend(), fin) == listeSommets.cend())
		throw exception("Fin d'arête non définie");

	Arete<S, T> * nouvelleArete = new Arete<S, T>(cleSuivante++, debut, fin, info);
	listeAretes.push_back(nouvelleArete);

	debut->degre++;
	fin->degre++;

	return nouvelleArete;
}

//Détermine le vecteur d'adjacence
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

//Convertit en chaine de caractères
template<class S, class T>
Graphe<S, T>::operator string() const
{
	ostringstream oss;

	oss << "Graphe (" << endl;
	oss << "clé suivante = " << this->cleSuivante << endl;

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

//Cherche une arête qui relie deux sommets, NULL s'il n'y en a pas.
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
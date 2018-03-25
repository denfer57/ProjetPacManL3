#pragma once

#include <utility>
#include "PElement.h"
#include "Erreur.h"
#include "Sommet.h"
#include "Arete.h"

/*
classe sachant dessiner un graphe

template <class S, class T> class Dessinateur; */

template <class S, class T>
class Graphe
{
protected:

	int prochaineClef;
private:

	Sommet<T> * creeSommet1(const int clef, const T & info);

	void majProchaineClef(const int clef) { prochaineClef = max(1 + clef, prochaineClef); }

	Sommet<T> * creeSommet(const int clef, const T & info) { majProchaineClef(clef); return creeSommet1(clef, info); }

	Arete<S, T> * creeArete1(const int clef, const S & info, Sommet<T> * debut, Sommet<T> * fin);

	Arete<S, T> * creeArete(const int clef, const S & info, Sommet<T> * debut, Sommet<T> * fin)
	{
		majProchaineClef(clef);
		return creeArete1(clef, info, debut, fin);
	}

	void copie(const Graphe<S, T> & graphe);

	void effaceTout();
public:

	PElement< Sommet<T> > * lSommets; // liste de sommets
	PElement< Arete<S, T> > * lAretes; // liste d'arêtes

	Sommet<T> * creeSommet(const T & info) { return creeSommet1(prochaineClef++, info); }

	Arete<S, T> * creeArete(const S & info, Sommet<T> * debut, Sommet<T> * fin) { return creeArete1(prochaineClef++, info, debut, fin); }

	Graphe() : prochaineClef(0), lSommets(NULL), lAretes(NULL) {}

	Graphe(const Graphe<S, T> & graphe) : Graphe() { this->copie(graphe); }

	const Graphe<S, T> & operator = (const Graphe<S, T> & graphe) { this->effaceTout(); this->copie(graphe); return *this; }


	~Graphe() { this->effaceTout(); }


	int nombreSommets() const { return PElement< Sommet<T> >::taille(lSommets); }
	int nombreAretes() const { return PElement< Arete<S, T> >::taille(lAretes); }

	PElement< pair< Sommet<T> *, Arete<S, T>* > >  *  adjacences(const Sommet<T> * sommet) const;
	PElement< Arete<S, T> > *  aretesAdjacentes(const Sommet<T> * sommet) const;
	PElement< Sommet<T> > *  voisins(const Sommet<T> * sommet) const;

	Arete<S, T> * getAreteParSommets(const Sommet<T> * s1, const Sommet<T> * s2) const;

	operator string() const;

	template< class FENETRE>
	bool dessineToutesAretes(FENETRE & fenetre) const;

	template< class FENETRE>
	bool dessineTousSommets(FENETRE & fenetre) const;

	template  <class FENETRE>
	bool dessine(FENETRE & fenetre) const;
};

template <class S, class T>
ostream & operator << (ostream & os, const Graphe<S, T> & gr) { return os << (string)gr; }

template <class S, class T>
Sommet<T> * Graphe<S, T>::creeSommet1(const int clef, const T & info)
{
	Sommet<T> * sommetCree = new Sommet<T>(clef, info);
	lSommets = new PElement< Sommet<T> >(sommetCree, lSommets);

	return sommetCree;
}

template <class S, class T>
Arete<S, T> * Graphe<S, T>::creeArete1(const int clef, const S & info, Sommet<T> * debut, Sommet<T> * fin)
{
	if (!PElement< Sommet<T> >::appartient(debut, lSommets)) throw Erreur("début d'arête non défini");
	if (!PElement< Sommet<T> >::appartient(fin, lSommets)) throw Erreur("fin d'arête non définie");

	Arete<S, T> *  nouvelleArete = new Arete<S, T>(clef, info, debut, fin);

	lAretes = new PElement< Arete<S, T> >(nouvelleArete, lAretes);

	return nouvelleArete;
}


template <class T>
class SommetDejaPresentDansLaCopie
{
public:
	const Sommet<T> * s;
	SommetDejaPresentDansLaCopie(const Sommet<T> * s) :s(s) {}
	bool operator () (const Sommet<T> * sommet) const { return sommet->clef == s->clef; }
};

template <class S, class T>
void Graphe<S, T>::copie(const Graphe<S, T> & graphe)
{
	const PElement<Sommet<T>> * pS;

	// -------------- d'abord on recopie les sommets --------------------

	for (pS = graphe.lSommets; pS; pS = pS->s)
	{									// parcourt les sommets du graphe "graphe" et les crée un par un dans *this en tant que sommets isolés
		const Sommet<T> * sommet = pS->v;				// sommet courant à recopier
		this->creeSommet(sommet->clef, sommet->v);		// on crée la copie du sommet courant avec la même clef
	}

	const PElement<Arete<S, T>> * pA;
	for (pA = graphe.lAretes; pA; pA = pA->s)	// parcourt les arêtes de l'ancien graphe et les recopie une par une
	{
		const Arete<S, T> * a = pA->v;			// arête courante à recopier
		Sommet<T> * d, *f;						// le début et la fin de la nouvelle arête qui va être créée
		PElement< Sommet<T> > * p;				// pour retrouver d et f dans la nouvelle liste de sommets grâce aux clefs qui ont été conservées

												// on recherche d dans la nouvelle liste de sommets grâce à sa clef
		SommetDejaPresentDansLaCopie<T> conditionDebut(a->debut);
		p = PElement< Sommet<T> >::appartient(lSommets, conditionDebut);
		d = p->v;

		// on recherche f dans la nouvelle liste de sommets grâce à sa clef
		SommetDejaPresentDansLaCopie<T> conditionFin(a->fin);
		p = PElement< Sommet<T> >::appartient(lSommets, conditionFin);
		f = p->v;

		this->creeArete(a->clef, a->v, d, f);
	}
}

template <class S, class T>
void Graphe<S, T>::effaceTout()
{
	PElement< Arete<S, T>>::efface2(this->lAretes);
	PElement<Sommet<T> >::efface2(this->lSommets);
	this->prochaineClef = 0;
}

template <class S, class T>
PElement< pair< Sommet<T> *, Arete<S, T>* > >  *  Graphe<S, T>::adjacences(const Sommet<T> * sommet) const
{
	const PElement< Arete<S, T> > * l;

	PElement< pair< Sommet<T> *, Arete<S, T>* > > * r;				// pair< Sommet<T> *, Arete<S,T>* >

	for (l = lAretes, r = NULL; l; l = l->s)

		if (sommet == l->v->debut)
			r = new PElement< pair< Sommet<T> *, Arete<S, T>* > >(new pair< Sommet<T> *, Arete<S, T>* >(l->v->fin, l->v), r);
		else
			if (sommet == l->v->fin)
				r = new PElement< pair< Sommet<T> *, Arete<S, T>* > >(new pair< Sommet<T> *, Arete<S, T>* >(l->v->debut, l->v), r);

	return r;
}


template <class S, class T>
PElement< Arete<S, T> > *  Graphe<S, T>::aretesAdjacentes(const Sommet<T> * sommet) const
{
	PElement< pair< Sommet<T> *, Arete<S, T>* > > * ladj = this->adjacences(sommet);
	PElement< pair< Sommet<T> *, Arete<S, T>* > > * l;

	PElement< Arete<S, T> > * r;

	for (l = ladj, r = NULL; l; l = l->s)
		r = new PElement< Arete<S, T> >(l->v->second, r);

	PElement< pair< Sommet<T> *, Arete<S, T>* > >::efface2(ladj);

	return r;
}

template <class S, class T>
PElement< Sommet<T> > *  Graphe<S, T>::voisins(const Sommet<T> * sommet) const
{
	PElement< pair< Sommet<T> *, Arete<S, T>* > > * ladj = this->adjacences(sommet);
	PElement< pair< Sommet<T> *, Arete<S, T>* > > * l;

	PElement< Sommet<T> > * r;

	for (l = ladj, r = NULL; l; l = l->s)
		r = new PElement< Sommet<T> >(l->v->first, r);

	PElement< pair< Sommet<T> *, Arete<S, T>* > >::efface2(ladj);

	return r;
}

template <class S, class T>
Arete<S, T> * Graphe<S, T>::getAreteParSommets(const Sommet<T> * s1, const Sommet<T> * s2) const
{
	PElement<Arete<S, T> > * l;

	for (l = this->lAretes; l; l = l->s)
		if (l->v->estEgal(s1, s2))
			return l->v;

	return NULL;
}


template <class S, class T>
Graphe<S, T>::operator string() const
{
	ostringstream oss;
	oss << "Graphe( \n";
	oss << "prochaine clef = " << this->prochaineClef << endl;
	oss << "nombre de sommets = " << this->nombreSommets() << "\n";

	oss << PElement<Sommet<T> >::toString(lSommets, "", "\n", "\n");

	oss << "nombre d'arêtes = " << this->nombreAretes() << "\n";

	oss << PElement<Arete<S, T> >::toString(lAretes, "", "\n", "\n");
	oss << ")";
	return oss.str();
}

template <class S, class T>
template< class FENETRE>
bool Graphe<S, T>::dessineToutesAretes(FENETRE & fenetre) const
{

	// ------------------------ on dessine les arêtes --------------------------

	PElement< Arete<S, T>> * pA;
	for (pA = this->lAretes; pA; pA = pA->s)
		if (!fenetre.dessine(pA->v)) return false; // tente de dessiner puis retourne false en cas d'échec

	return true;
}

template <class S, class T>
template< class FENETRE>
bool Graphe<S, T>::dessineTousSommets(FENETRE & fenetre) const
{

	// ------------------------ on dessine les sommets --------------------------

	PElement< Sommet<T>> * pS;
	for (pS = this->lSommets; pS; pS = pS->s)
		if (!fenetre.dessine(pS->v)) return false;	// tente de dessiner puis retourne false en cas d'échec

	return true;
}

template <class S, class T>
template< class FENETRE>
bool Graphe<S, T>::dessine(FENETRE & fenetre) const
{

	// ------------------------ on dessine les arêtes --------------------------

	if (!this->dessineToutesAretes(fenetre)) return false;

	// ------------------------ on dessine les sommets --------------------------

	return this->dessineTousSommets(fenetre);
}

template <class T, class FENETRE>
bool dessine(const PElement<Sommet<T>> * chemin, FENETRE & fenetre, const unsigned int couleur)
{
	if (!(chemin && chemin->s)) // le chemin est vide ou ne contient qu'un sommet : il n'y  a rien à dessiner
		return true;

	else		// le chemin contient au moins une arête
	{
		// on dessine d'abord la 1ère arête

		fenetre.dessine(chemin->v, chemin->s->v, couleur);

		return dessine(chemin->s, fenetre, couleur);		// puis on dessine les arêtes suivantes
	}
}



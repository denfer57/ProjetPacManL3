#pragma once


#include <iostream>
#include <sstream>
#include <string>

using namespace std;

template <class T>
class PElement
{
public:
	T * v;				// valeur
	PElement<T> * s;	// suivant

	PElement(T * v, PElement<T> * s) :v(v), s(s) {}

	static const string toString(const PElement<T> * p, const char * debut = "( ", const char * separateur = ", ", const char * fin = ")");

	static int taille(const PElement<T> * l);

	static  PElement<T> * copie1(PElement<T> * l);

	static  PElement<T> * copie2(const PElement<T> * l);

	static PElement<T> * copie3(const PElement<T> * l);

	static void concat(PElement<T> * & l1, PElement<T> *  l2);

	static void efface1(PElement<T>* & l);

	static void efface2(PElement<T>* & l);

	static  PElement< T > * appartient(const T * a, PElement<T> * l);

	template <class FONCTEUR>
	static PElement< T > * appartient(PElement<T> * l, const FONCTEUR & condition);

	static void insertionOrdonnee(T * a, PElement<T> * & l, bool(*estPlusPetitOuEgal)(const T * a1, const T * a2));

	static bool retire(const T * a, PElement<T> * & l);

	static T * depiler(PElement<T> * & l);

	//-------------------------- PElement<T> ------------------------------
};

template<class T>
ostream& operator <<(ostream & os, const PElement<T> * p) { return os << PElement<T>::toString(p); }

template <class T>
/*static*/ const string PElement<T>::toString(const PElement<T> * p, const char * debut, const char * separateur, const char * fin)
{
	PElement<T> * r;
	ostringstream oss;

	for (r = (PElement<T>*) p, oss << debut; r; r = r->s)
		oss << *(r->v) << separateur;

	oss << fin;
	return oss.str();
}

template <class T>
/* static */ void PElement<T>::concat(PElement<T> * & l1, PElement<T> * l2)
{
	if (!l1)        /* l1 == liste vide */
		l1 = l2;

	else
		concat(l1->s, l2);
}

template <class T>
/* static */ int PElement<T>::taille(const PElement<T> * l)
{
	if (!l) return 0;
	else
		return 1 + PElement<T>::taille(l->s);
}

template <class T>
/* static */ PElement<T> * PElement<T>::copie1(PElement<T> * l)
{
	if (!l)
		return NULL;
	else
		return new PElement<T>(l->v, PElement<T>::copie1(l->s));
}

template <class T>
/* static */ PElement<T> * PElement<T>::copie2(const PElement<T> * l)
{
	if (!l)
		return NULL;
	else
		return new PElement<T>(new T(*(l->v)), PElement<T>::copie2(l->s));
}

template <class T>
/* static */ PElement<T> * PElement<T>::copie3(const PElement<T> * l)
{
	if (!l)
		return NULL;
	else
		return new PElement<T>(l->v->copie(), PElement<T>::copie3(l->s));
}

template <class T>
/* static */ void PElement<T>::efface1(PElement<T>* & l)
{
	if (l)
	{
		PElement<T>::efface1(l->s);
		delete l; l = NULL;
	}
}

template <class T>
/* static */ void PElement<T>::efface2(PElement<T>* & l)
{
	if (l)
	{
		PElement<T>::efface2(l->s);
		delete l->v; delete l; l = NULL;
	}
}

template <class T>
PElement< T > * PElement< T >::appartient(const T * a, PElement<T> * l)
{
	for (; l; l = l->s)
		if (a == l->v)
			return l;

	return l;
}

template <class T>
template <class FONCTEUR>
/*static*/ PElement< T > * PElement< T >::appartient(PElement<T> * l, const FONCTEUR & condition)
{
	for (; l; l = l->s)
		if (condition(l->v))
			return l;

	return l;
}

template<class T>
/*static*/ void PElement<T>::insertionOrdonnee(T * a, PElement<T> * & l, bool(*estPlusPetitOuEgal)(const T * a1, const T * a2))
{
	if (!l || estPlusPetitOuEgal(a, l->v))
		l = new PElement<T>(a, l);
	else
		PElement<T>::insertionOrdonnee(a, l->s, estPlusPetitOuEgal);
}

template<class T>
/*static*/ bool PElement<T>::retire(const T * a, PElement<T> * & l)
{
	if (!l)
		return false;
	else
		if (a == l->v)
		{
			PElement<T> * r = l; l = l->s; delete r;
			return true;
		}
		else
			return PElement<T>::retire(a, l->s);
}

template <class T>
/* static */ T * PElement<T>::depiler(PElement<T> * & l)
{
	if (!l) throw Erreur("impossible de dépiler une pile vide");
	T * a = l->v;
	PElement<T> * tete = l;

	l = l->s; delete tete;
	return a;

}

template <class T>
PElement<T> * reunion(PElement<T> * l1, PElement<T> * l2)
{
	PElement<T> * r = PElement<T>::copie1(l2);
	PElement<T> * pl1;

	for (pl1 = l1; pl1; pl1 = pl1->s)
		if (!PElement<T>::appartient(pl1->v, r))
			r = new PElement<T>(pl1->v, r);

	return r;
}

template <class T>
void partage(PElement<T> * & p, PElement<T> * & p1)
{
	if (p == NULL || p->s == NULL)
		p1 = NULL;
	else
	{
		PElement<T> *  r1, *r2;

		r1 = p->s;
		r2 = r1->s;

		partage(r2, p1);

		r1->s = p1;
		p->s = r2;
		p1 = r1;
	}
}

template <class T>
void fusion(PElement<T> * & p1, PElement<T> * & p2, bool(*estPlusPetitOuEgal)(const T * a1, const T * a2))
{
	if (!p2) return; // p2 est vide, il n'y a rien à faire

	if (!p1) // p1 est vide et p2 ne l'est pas
	{
		p1 = p2; p2 = NULL;
		return;
	}

	// à présent, p1 et p2 sont non vides

	if (estPlusPetitOuEgal(p1->v, p2->v)) // p1->v <= p2->v
	{
		PElement<T> * r;
		r = p1->s;
		fusion(r, p2, estPlusPetitOuEgal);
		p1->s = r;
	}
	else // p1->v > p2->v
	{
		PElement<T> * r;
		r = p2->s;
		fusion(p1, r, estPlusPetitOuEgal);
		p2->s = p1;
		p1 = p2;
		p2 = NULL;
	}
}

template <class T>
void tri(PElement<T>* & p, bool(*estPlusPetitOuEgal)(const T * a1, const T * a2))
{
	if (p != NULL && p->s != NULL)
	{
		PElement<T> * p1;

		partage(p, p1);

		tri(p, estPlusPetitOuEgal); tri(p1, estPlusPetitOuEgal);

		fusion(p, p1, estPlusPetitOuEgal);
	}
}





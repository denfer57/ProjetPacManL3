#pragma once
#include <iostream>
#include <string>
#include <sstream>

#include "AElement.h"
template <class T>
class GElement : public AElement
{
public:
	T v;				// valeur
	GElement(const int clef, const T & v) : AElement(clef), v(v) {};
	operator string() const { ostringstream o; o << this->AElement::operator string() << ", v = " << v; return o.str(); }
	friend ostream & operator << (ostream & os, const GElement<T>& gElement) { return os << (string)gElement; }
};

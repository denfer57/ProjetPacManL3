#include "InfoAStar.h"

const /*static*/ char *InfoAStar::ETATS[] = { "LIBRE","OUVERT","FERME" };

InfoAStar::operator string() const
{
	ostringstream oss;

	oss << "clef pere = ";

	if (pere)
		oss << pere->clef;
	else
		oss << "non d�finie";

	oss << ", �tat = " << ETATS[etat] << ", co�t = " << c << ", h = " << h << ", g = " << g;

	return oss.str();
}



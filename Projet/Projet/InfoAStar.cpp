#include "InfoAStar.h"

const /*static*/ char *InfoAStar::ETATS[] = { "LIBRE","OUVERT","FERME" };

InfoAStar::operator string() const
{
	ostringstream oss;

	oss << "clef pere = ";

	if (pere)
		oss << pere->clef;
	else
		oss << "non définie";

	oss << ", état = " << ETATS[etat] << ", coût = " << c << ", h = " << h << ", g = " << g;

	return oss.str();
}



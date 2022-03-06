
#include "valid.h"
#include <string.h>

int validateOffer(Offer oferta) {
	if (getID(oferta) <= 0)
		return 0;
	else if (getPret(oferta) < 0)
		return 0;
	else if (getSuprafata(oferta) < 0)
		return 0;
	else if (strcmp(getType(oferta), "Apartament")!=0 && strcmp(getType(oferta), "Teren")!=0 && strcmp(getType(oferta), "Casa"))
		return 0;
	else return 1;
}
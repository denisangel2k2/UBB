#include "compare_func.h"
#include <stdlib.h>
#include <string.h>

int comparePretAsc(double p1, double p2) {
	if (p1 > p2)
		return 1;
	return 0;
}
int comparePretDsc(double p1, double p2) {
	if (p1 < p2)
		return 1;
	return 0;
}

int compareTypeAsc(char* t1, char* t2) {
	if (strcmp(t1, t2) < 0)
		return 1;
	return 0;
	
}

int compareTypeDsc(char* t1, char* t2) {
	if (strcmp(t1, t2) < 0)
		return 0;
	return 1;
}

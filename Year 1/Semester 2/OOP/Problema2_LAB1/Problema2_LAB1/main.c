#include <stdio.h>
void factori(int n) {
	/*
	Functia care descompune in factori primi un numar
	pre: n - integer
	out: -
	*/
	int fact = 2;
	if (n == 1)
		printf("1 nu e prim.\n");
	else if (n == 0)
		printf("0 nu e prim.\n");

	while (n>1) {
		int putere = 0;
		while (n % fact == 0) {
			n /= fact;
			putere++;
		}
		if (putere > 0)
			printf("%d^%d\n", fact, putere);
		if (fact == 2)
			fact++;
		else fact += 2;
	}
}
void problema() {
	/*
	Functia care afiseaza descompunerea in factori primi
	pre: -
	post: -
	*/
		int n;
		printf("Introduceti un numar: ");
		scanf_s("%d", &n);
		printf("Descompunerea in factori primi este: \n");
		factori(n);
}
int main() {
	int cmd = 0;
	while (1) {
		printf("1-pentru iesire: ");
		scanf_s("%d", &cmd);
		if (cmd == 1)
			return;
		else problema();
	}
	
	
	
	problema();
	return 0;
}
#include <stdio.h>
#include <assert.h>
#include <string.h>


void ruleaza_teste();
void test_pow();
void test_Sin();
void test_factorial();


double pow(double a, int b) {
	/*
	Functie care returneaza a^b
	pre: a-numar baza (double), b-numar exponent (int)
	post: double, returneaza a^b
	*/
	if (b == 0)
		return 1;
	else if (b % 2)
		return a * pow(a, b - 1);
	else return pow(a, b / 2) * pow(a, b / 2);

}

double factorial(int n) {
	/*
	Functie care calculeaza si returneaza factorialul unui numar transmis ca parametru
	pre: n - integer
	post: n! - double
	*/
	if (n == 0)
		return 1;
	else if (n == 1)
		return 1;
	else return n * factorial(n - 1);
}
double Sin(double x) {
	/*
	Functie care calculeaza sinusul unui radian
	pre: x - double (radian)
	post: double - Sin(x)
	*/
	int k = 0;
	double SIN = 0;
	for (int i = 1; i <= 10; i++) 
		SIN += pow(-1, i+1) * (pow(x, 2*i-1) / (double)factorial(2*i-1));
	
	return SIN;
}
void Operatie() {
	/*
	Functionalitatea care efectueaza calculul functiei sin repetat
	pre : -
	post : -
	*/
	int x = 0;
	printf("x=");

	scanf_s("%d", &x);

	double radian = x * (3.14159 / 180.0);
	double h = Sin(radian);

	printf("SIN(%d)=%.5f\n", x, h);
}
int main() {
	ruleaza_teste();
	while(1) Operatie();
	
	return 0;
}
void ruleaza_teste() {
	test_pow();
	test_factorial();
	test_Sin();
}
void test_Sin() {
	double x = 90 * (3.14159 / 180.0);
	double sinus = Sin(x);
	assert(Sin(x)-1.000000<0.000001);
	assert(Sin(0)-0<0.00001);
	assert(Sin(30 * (3.14159 / 180.0)) - 0.500000<0.000001);
}

void test_factorial() {
	assert(factorial(0) == 1);
	assert(factorial(1) == 1);
	assert(factorial(2) == 2);
	assert(factorial(3) == 6);
	assert(factorial(4) == 24);
}

void test_pow() {
	assert(pow(-1, 1) == -1);
	assert(pow(2, 3) == 8);
	assert(pow(10, 0) == 1);
	assert(pow(0, 0) == 1);
	assert(pow(0, 2) == 0);
}

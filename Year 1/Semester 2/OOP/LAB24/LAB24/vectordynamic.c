#include <malloc.h>
#include "vectordynamic.h"

VectorDinamic* create(int cap) {
	
	VectorDinamic* v = (VectorDinamic*)malloc(sizeof(VectorDinamic));

	v->capacity = cap;

	v->elements = (Element*)malloc(cap * sizeof(Element));

	v->length = 0;

	return v;
}

void destroy(VectorDinamic* v) {

	free(v->elements);
	free(v);
}

void resize(VectorDinamic* v) {

	int newCap = 2 * v->capacity;
	Element* newE = (Element*)malloc(sizeof(Element) * newCap);

	for (int i = 0; i < v->length; i++) {
		newE[i]=v->elements[i];
	}

	free(v->elements);
	v->capacity = newCap;
	v->elements = newE;

}

void add(VectorDinamic* v, Element e) {
	if (v->length == v->capacity)
		resize(v);

	v->elements[v->length++] = e;
}

void del(VectorDinamic* v, int pos) {
	Element* newE = (Element*)malloc((v->length - 1) * sizeof(Element));
	int i = 0, j = 0;
	while (i < v->length) {
		if (i != pos) { 
			newE[j] = v->elements[i];
			j++;
		}
		i++;
	}
	free(v->elements);
	v->length--;
	v->elements = newE;
}

Element element(VectorDinamic* v, int pos) {
	return v->elements[pos];
}

int len(VectorDinamic* v) {
	return v->length;
}






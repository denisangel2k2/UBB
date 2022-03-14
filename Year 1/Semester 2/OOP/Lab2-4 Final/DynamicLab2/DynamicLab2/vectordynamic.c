#include "vectordynamic.h"
#include <malloc.h>

VectorDinamic* create(int cap) {
	VectorDinamic* v = (VectorDinamic*)malloc(sizeof(VectorDinamic));
	v->capacity = cap;
	v->lg = 0;
	v->elems = (Element*)malloc(sizeof(Element)*cap);
	return v;
}

void resize(VectorDinamic* v) {

	int newCap = v->capacity * 2;
	Element* newList = (Element*)malloc(sizeof(Element) * newCap);
	for (int i = 0; i < v->lg; i++)
		newList[i] = v->elems[i];

	free(v->elems);
	v->elems = newList;
	v->capacity = newCap;

}
void destroy(VectorDinamic** v) {
	free((*v)->elems);
	free(*v);
	*v = NULL;
}

void add(VectorDinamic* v, Element e) {
	if (v->lg == v->capacity)
		resize(v);
	v->elems[v->lg++] = e;
}

int del(VectorDinamic* v, int pos) {
	if (pos < 0 || pos >= v->lg || v->lg == 0)
		return 0;
	for (int i = pos; i < v->lg; i++)
		v->elems[i] = v->elems[i + 1];

	v->lg--;
	return 1;
}
int update(VectorDinamic* v, int pos, Element e) {

	if (pos < 0 || pos >= v->lg || v->lg == 0)
		return 0;


	v->elems[pos] = e; // possibly here memory leak cuz old v->elems[pos] still exists


	return 1;
}

Element getElement(VectorDinamic* v, int pos) {

	if (pos < 0 || pos >= v->lg || v->lg == 0)
		return 0;

	return v->elems[pos];
}

int len(VectorDinamic* v) {
	return v->lg;
}
VectorDinamic* copy(VectorDinamic* v) {
	VectorDinamic* copyv = create(v->capacity);
	for (int i = 0; i < v->lg; i++)
		copyv->elems[i] = v->elems[i];
	copyv->lg = v->lg;
	return copyv;
}
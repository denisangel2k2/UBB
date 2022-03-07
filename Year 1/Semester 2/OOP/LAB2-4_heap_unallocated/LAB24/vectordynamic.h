#pragma once

#include "domain.h"
typedef Offer Element;



typedef struct {

	int length;
	int capacity;
	Element* elements;

}VectorDinamic;

VectorDinamic* create(int init_capacity);


void destroy(VectorDinamic* v);

void resize(VectorDinamic* v);

void add(VectorDinamic* v, Element e);

void del(VectorDinamic* v, Element e);

Element element(VectorDinamic* v, int pos);

int len(VectorDinamic* v);

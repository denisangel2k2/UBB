#pragma once
#include <malloc.h>
#include "service.h"
#include "vectordynamic.h"

typedef struct {
	Service* service;
}UI;

UI* createUI(Service* serv);

void destroyUI(UI* ui);

void addUI(UI* ui);
void updateUI(UI* ui);
void printUI(UI* ui);

void UI_RUN(UI* ui);


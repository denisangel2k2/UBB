#pragma once
#include "Service.h"
#include <string>
#include "Domain.h"
class UI
{

private:
	Service srv;
	void filterUI();
	void sortUI();
	void showUI();
	void addUI();
	void delUI();
	void updateUI();
	void printUI();
	void findCarUI();
public:
	UI(const UI& ot) = delete;
	UI(const Service& srv) :srv{ srv } {}

	

	void run();
};


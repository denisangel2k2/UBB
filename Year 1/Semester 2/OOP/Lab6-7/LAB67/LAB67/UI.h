#pragma once
#include "Service.h"
#include <string>
#include "Domain.h"
class UI
{

private:
	Service& srv;
	void filterUI();
	void sortUI();
	void showUI();
	void addUI();
	void delUI();
	void updateUI();
	void printUI();
	void findCarUI();
	void addUI_nrInm();
	void clearUI();
	void addRandomUI();
public:
	UI(const UI& ot) = delete;
	UI(Service& srv) noexcept :srv{ srv } {}

	

	void run();
};


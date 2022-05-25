#pragma once
#include "Service.h"
#include <string>
#include "Domain.h"
#include "AdminService.h"
class UI
{

private:
	Service& srv;
	AdminService& srv2;

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


	void addRandomFictiv();
	void addNrInmFictiv();
	void printFictiv();
	void clearFictiv();
	void exporter();

	void batchmode();
	void undo();
public:
	UI(const UI& ot) = delete;
	UI(Service& srv, AdminService& _srv2) noexcept :srv{ srv }, srv2{ _srv2 } {}

	

	void run();
};


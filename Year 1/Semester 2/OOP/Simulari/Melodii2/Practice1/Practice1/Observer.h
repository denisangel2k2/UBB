#pragma once
#include <vector>
#include <algorithm>
using std::vector;
class Observer
{
public:
	virtual void update() = 0;
};
class Observable
{
private:
	vector<Observer*>observers;
public:
	void notify() { for (auto obs : observers) obs->update(); }
	void addObserver(Observer* o) { observers.push_back(o); }
	void removeObserver(Observer* o) { observers.erase(std::remove(observers.begin(), observers.end(), o), observers.end()); }
};
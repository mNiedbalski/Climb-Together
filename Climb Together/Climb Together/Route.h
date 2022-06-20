#pragma once
#include <string>
#include <iostream>
#include <memory>
#include <regex> //*
#include <list>
#include <filesystem> //*
#include <fstream>
#include <iterator>
#include <sstream>
#include <chrono>
#include <conio.h>
#include <Windows.h>
#include <thread> //*
#include <ctime>
#include <barrier> //*
#include <vector>
#include <ranges>
#include <iterator>


namespace fs = std::filesystem;
using namespace std;



class Route
{
protected:
	string routeSetter;
	string difficulty;
	string ID;
public:
	void saveToDatabase();
	void increaseScore();
	void setRouteSetter(const string& name) { this->routeSetter = name; }
	void setDifficulty(const string& diff) { this->difficulty = diff; }
	void setID(const string& _ID) { this->ID = _ID; }
	const string getRouteSetter() { return this->routeSetter; }
	const string getDifficulty() { return this->difficulty; }
	const string getID() { return this->ID; };
	double MeasureTime();
	static void Animation();

};

class CompletedRoute : public Route
{
protected:
	string date;
	double time;
public:

	void setDate(const string& _date) { this->date = _date; }
	void setTime(const double& _time) { this->time = _time; }
	const string getDate() { return this->date; }
	const double getTime() { return this->time; }
};

struct CountedRoute
{
	int counter;
	string ID;
};



#pragma once

#include "Route.h"

class User
{
protected:
	string email, password, name, surname;

public:
	virtual bool CheckWithDatabase() = 0;
	void LogIn();
	int Choice(const int last);
	virtual void Register() = 0;
	virtual bool Options(list <Route> & _routes, vector <string> & bestClimbers) = 0;
	virtual void Check() = 0;
	void RegisterEmailPassword();
	virtual void SaveToDatabase() = 0;
	virtual void Print() = 0;
	virtual void PrintUserProfile() = 0;
	virtual void LoadFromDatabase() = 0;
	virtual void SetPathForUser(fs::path & alteredPath) = 0;
	virtual string& getName() = 0;
	virtual string& getSurname() = 0;
	virtual bool FindMail(const string& mail)=0;
	void PrintAllRoutes(list <Route>& _routes);
	void setEmail(const string& _email) { this->email = _email; }
	void setPassword(const string& _password) { this->password = _password; }
	void setName(const string& _name) { this->name = _name; }
	void setSurname(const string& _surname) { this->surname = _surname; }
	void PrintTop3(vector <string> top3);
};

class Basic : public User
{
private:
	double height, weight;
	int age, score=0, level=0;
	char sex;
	list <CompletedRoute> routesCompleted;
	CompletedRoute bestRoute;
public:
	Basic() {};
	~Basic() {};
	void Register() override;
	bool Options(list <Route> & _routes, vector <string>& bestClimbers) override;
	void Check() override { cout << "*Basic*"; };
	void SaveToDatabase() override;
	void Print() override;
	void PrintUserProfile() override;
	void LoadFromDatabase() override;
	void SetPathForUser(fs::path& alteredPath) override;
	bool CheckWithDatabase() override;
	string& getName() override;
	string& getSurname() override;
	bool FindMail(const string& mail) override;
	double getScore() { return this->score; }
	void LoadRoutes();
	void PrintRoutes();
	void AttendRoute(const int & index, list <Route> & _routes);
	void SaveCompletedRoute(CompletedRoute& route);
	void CalculatingCompetetiveParameters();
	void AssignCompetetiveParameters();
	void UpdateScoreAndLevel(CompletedRoute& route);
	void FindBestRoute();
	void setHeight(const double& _height) { this->height = _height; }
	void setWeight(const double& _weight) { this->weight = _weight; }
	void setSex(const char& _sex) { this->sex = _sex; }
	void setAge(const int& _age) { this->age = _age; }
	void setRoutesCompleted(const list <CompletedRoute> _routesCompleted) { this->routesCompleted = _routesCompleted; }
	void setBestRoute(const CompletedRoute& _bestRoute) { this->bestRoute = _bestRoute; }
	void setScore(const int& _score) { this->score = _score; }
	void setLevel(const int& _level) { this->level = _level; }
	const int getAge() { return this->age; }
	const double getHeight() { return this->height; }
	const double getWeight() { return this->weight; }
	const char getSex() { return this->sex; }
	void clear();
};

class Admin : public User
{
private:
	list <Basic> users;
public:
	Admin() {};
	Admin(string& _email, string& _password)
	{
		this->email = _email;
		this->password = _password;
	};
	~Admin() {};
	void Register() override;
	bool Options(list <Route>& _routes, vector <string>& bestClimbers) override;
	void Check() override { cout << "*Admin*"; };
	void SaveToDatabase() override;
	void Print() override;
	void PrintUserProfile() override;
	void LoadFromDatabase() override;
	void SetPathForUser(fs::path& alteredPath) override;
	bool CheckWithDatabase() override;
	string& getName() override;
	string& getSurname() override;
	bool FindMail(const string& mail) override;
	void LoadBasicUsers();
	void PrintUsers();
	void DisplayStatistics();

};
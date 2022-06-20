#include "Interface.h"



bool Interface::LoginOrRegister()
{
	system("CLS");
	cout << "Please choose one option from two below: \n";
	cout << "1. Log in.\n2. Register.\n";
	bool correct = false;
	if (this->Choice(2, correct) == 1) {
		Route::Animation();
		return true; //log in
	}
	else {
		Route::Animation();
		return false; //register
	}
}
Interface::Interface(shared_ptr<User>& _user)
{
	list <Route> routes;
	list <Basic> users;
	vector <Basic> top3;
	vector <string> top3NamesAndScores;

	if (!this->LoadRoutes(routes)) {
		cerr << "There has been an error in loading routes from database. Please contact administrator.\n";
		system("PAUSE");
		return;
	}

	bool loggedIn = false;
	bool exit = false;
	this->LoadBasicUsers(users);
	this->FindBestClimbers(users, top3);
	this->GetNamesOfBestClimbers(top3NamesAndScores, top3);
	while (!exit) {
		if (!this->Beginning())
			_user = make_shared<Admin>();
		else
			_user = make_shared<Basic>();
		if (this->LoginOrRegister()) {
			_user->LogIn();
			loggedIn = true;
		}
		else
			_user->Register();

		if (!loggedIn) {
			_user->LogIn();
			loggedIn = true;
		}

		if (!_user->Options(routes, top3NamesAndScores)) {
			exit = true;
			break;
		}
		else {
			loggedIn = false;
			cout << "You have logged out. See You soon!\n";
			Sleep(1000);
			system("CLS");
		}
	}
	cout << "Goodbye! Thank You for using ClimbTogether! \n";
}
bool Interface::Beginning() // False if admin, true jesli user
{
	bool correct = false;
	int choice;
	while (!correct) {
		cout << "Choose one option:\n";
		cout << "1. User panel\n2. Admin panel\n";
		choice = this->Choice(2, correct);
	}
	Route::Animation();
	if (choice == 2)
		return false;
	else
		return true;
}
int Interface::Choice(const int last, bool& correct)
{
	int choice;
	while (!correct) {
		try {
			cin >> choice;
			if (choice > last || choice < 1)
				throw choice;
			else
				correct = true;
			system("CLS");
			return choice;
		}
		catch (int& choice) {
			cerr << "You have inputted wrong number. Make sure the number you choose has it's corresponding option.\n";
			system("pause");
			system("CLS");
		}
	}
}
bool Interface::LoadRoutes(list <Route> & _routes)
{
	fs::path myPath{ fs::current_path() };
	myPath /= "Routes/Routes.txt";
	ifstream file(myPath);
	Route tempRoute;
	string read;
	int sequence = 0;
	if (file.is_open()) {
		while (file >> read) {
			if (sequence % 3 == 0)
				tempRoute.setRouteSetter(read);
			else if (sequence % 3 == 1)
				tempRoute.setID(read);
			else if (sequence % 3 == 2) {
				tempRoute.setDifficulty(read);
				_routes.push_back(tempRoute);
			}
			sequence++;
		}
		return true;
	}
	else
		return false;
}
void Interface::LoadBasicUsers(list <Basic>& _users)
{
	fs::path myPath{ fs::current_path() };
	myPath /= "Users/Users.txt";
	ifstream file(myPath);
	string read;
	Basic tempUser;
	int sequence = 0;
	if (file.is_open()) {
		while (file >> read)
		{

			if (sequence % 8 == 0)
				tempUser.setName(read);
			else if (sequence % 8 == 1)
				tempUser.setSurname(read);
			else if (sequence % 8 == 2)
				tempUser.setEmail(read);
			else if (sequence % 8 == 3)
				tempUser.setPassword(read);
			else if (sequence % 8 == 4)
			{
				istringstream converted(read);
				double height;
				converted >> height;
				tempUser.setHeight(height);
			}
			else if (sequence % 8 == 5)
			{
				istringstream converted(read);
				int age;
				converted >> age;
				tempUser.setAge(age);
			}
			else if (sequence % 8 == 6)
			{
				istringstream converted(read);
				double weight;
				converted >> weight;
				tempUser.setWeight(weight);
			}
			else if (sequence % 8 == 7)
			{
				istringstream converted(read);
				char sex;
				converted >> sex;
				tempUser.setSex(sex);
				tempUser.LoadRoutes();
				//thread + barrier
				thread calculationThr(&Basic::CalculatingCompetetiveParameters, &tempUser);
				thread assigningThr(&Basic::AssignCompetetiveParameters, &tempUser);
				calculationThr.join();
				assigningThr.join();
				//thread + barrier

				tempUser.FindBestRoute();
				_users.push_back(tempUser);
				tempUser.clear();
			}
			sequence++;
		}
	}
	else {
		cout << "Application can't reach file from path: " << myPath << ".\nPlease contact administrator to resolve problems.\n";
		system("PAUSE");
		system("CLS");
	}
}
void Interface::FindBestClimbers(list <Basic>& _users, vector <Basic>& _top3)
{
	_users.sort([&](Basic t1, Basic t2) {return t1.getScore() > t2.getScore(); });
	list<Basic>::iterator iter = _users.begin();
	_top3.push_back(*iter++);
	_top3.push_back(*iter++);
	_top3.push_back(*iter++);
}
void Interface::GetNamesOfBestClimbers(vector <string>& top3Names, vector <Basic>& top3)
{
	for (auto& climber : top3) {
		string TempName(climber.getSurname());
		top3Names.push_back(climber.getName() + " " + TempName[0] + ". - Score: " + to_string(climber.getScore()));
	}
}

/*void Animation()
{
			
			cout << "     *\n";
			cout << "    * *\n";
			cout << "   *   *\n";
			cout << "  *     *\n";
			cout << " *       *\n";
			cout << "***********\n";
			cout << "- - Press any key to stop recording time - -\n";
			Sleep(500);
			system("CLS");
			cout << "     *\n";
			cout << "    * *\n";
			cout << "   *   *\n";
			cout << "  *     *\n";
			cout << " *********\n";
			cout << "***********\n";
			cout << "- - Press any key to stop recording time - -\n";
			Sleep(500);
			system("CLS");
			cout << "     *\n";
			cout << "    * *\n";
			cout << "   *   *\n";
			cout << "  *******\n";
			cout << " *********\n";
			cout << "***********\n";
			cout << "- - Press any key to stop recording time - -\n";
			Sleep(500);
			system("CLS");
			cout << "     *\n";
			cout << "    * *\n";
			cout << "   *****\n";
			cout << "  *******\n";
			cout << " *********\n";
			cout << "***********\n";
			cout << "- - Press any key to stop recording time - -\n";
			Sleep(500);
			system("CLS");
			cout << "     *\n";
			cout << "    ***\n";
			cout << "   *****\n";
			cout << "  *******\n";
			cout << " *********\n";
			cout << "***********\n";
			cout << "- - Press any key to stop recording time - -\n";
			Sleep(500);
			system("CLS");
}*/
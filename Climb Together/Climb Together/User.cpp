#include "User.h"
#pragma warning(disable : 4996)

void User::RegisterEmailPassword()
{
	regex Length("([A-Za-z0-9]{8,})");
	regex Uppercase("((\\w*)[A-Z]+(\\w*))");
	regex Number("((\\w*)[0-9]+(\\w*))");
	regex MailFormat("(\\w+)(\\.|_)?(\\w*)@(\\w+)(\\.(\\w+))+");
	bool correct = false;
	string email;
	string password;

	while (!correct) {
		cout << "Please enter your email and password: \n";
		cout << "Email: ";
		cin >> email;
		cout << "Password: ";
		cin >> password;

		if (!regex_match(email, MailFormat))
			cerr << "Incorrect email format. Please make sure email has been typed correctly." << endl;
		else if (!regex_match(password, Length))
			cerr << "Your password is not sufficiently long. It should contain at least 8 signs." << endl;
		else if (!regex_match(password, Uppercase))
			cerr << "Your password lacks uppercase." << endl;
		else if (!regex_match(password, Number))
			cerr << "Your password lacks numbers." << endl;
		else if (this->FindMail(email))
			cerr << "This email is already in database. Please check spelling or choose log in option.\n";
		else 
			correct = true;
		system("PAUSE");
		system("CLS");
	}
	this->email = email;
	this->password = password;
}
void User::LogIn()
{
	bool correct = false;
	while (!correct) {
		cout << "Please enter your email and password to log in: \n";
		cout << "Email: ";
		cin >> this->email;
		cout << "Password: ";
		cin >> this->password;
		if (this->CheckWithDatabase()) {
			this->LoadFromDatabase();
			cout << "You have logged in correctly! Welcome to ClimbTogether " << this->getName() << "!\n";
			system("PAUSE");
			Route::Animation();
			correct = true;
		}
		else {
			cout << endl << "Wrong password or account doesn't exist! Please try again and reassure your email and password are correct.\n";
			system("PAUSE");
			Route::Animation();
		}
	}
}
int User::Choice(const int last)
{
		int choice;
		try {
			cin >> choice;
			if (choice > last || choice < 1)
				throw choice;
			else {
				Route::Animation();
				return choice;
			}
		}
		catch (int& choice) {
			cerr << "You have inputted wrong number. Make sure the number you choose has it's corresponding option.\n";
			system("pause");
			return choice;
		}
}
void User::PrintAllRoutes(list <Route>& _routes)
{
	int counter = 1;
	for (auto& route : _routes) {
		cout << counter << ". " << route.getRouteSetter() << " " << route.getID() << " " << route.getDifficulty() << endl;
		counter++;
	}
}
void User::PrintTop3(vector <string> top3)
{
	cout << "Displaying best climbers: \n";
	cout << "#1. " << top3.at(0) << endl;
	cout << "#2. " << top3.at(1) << endl;
	cout << "#3. " << top3.at(2) << endl << endl;
	system("PAUSE");

}
//=============================================================================ADMIN========================================================================================
void Admin::Register()
{
	string code;
	cout << "In order to ensure You have the authorization to create admin account, please type in 8-digit code given by other administrator.\n";
	cin >> code;
	if (code != "$2MIT4C$")
	{
		cout << "Authorization failed.\n";
		system("PAUSE");
		system("CLS");
		return;
	}
	else
		system("CLS");
	this->RegisterEmailPassword();
	bool correct = false;
	int choice;
	while (!correct) {
		cout << "Please enter your name: ";
		cin >> this->name;
		cout << "Please enter your surname: ";
		cin >> this->surname;
		system("CLS");
		cout << "Is Your data correct?:\nName: " << this->name << "\nSurname: " << this->surname << "\nEmail address: " << email << "\nPassword: " << password << endl;
		cout << endl << "1. Yes\n2. No" << endl;
		try {
			cin >> choice;
			if (choice > 3 || choice < 1)
				throw choice;
			else if (choice == 1)
				correct = true;
			else
				system("CLS");
		}
		catch (...)
		{
			cerr << "You have inputted wrong number. Make sure the number you choose has it's corresponding option.\n";
			system("pause");
			system("CLS");
		}
	}
	this->SaveToDatabase();
}
bool Admin::Options(list <Route> & _routes, vector <string>& bestClimbers)
{
	this->LoadBasicUsers();
	bool logOut = false;
	int choice, choiceOfRoute;
	while (!logOut) {
		cout << "Please choose one from the following options: \n\n";
		cout << "1. My profile.\n";
		cout << "2. View all users.\n";
		cout << "3. Display statistics.\n";
		cout << "4. High scores.\n";
		cout << "5. Log out.\n";
		cout << "6. Exit program.\n";
		choice = this->Choice(6);
		Route::Animation();
		switch (choice) {
		case 1:
			this->PrintUserProfile();
			break;
		case 2:
			this->PrintUsers();
			break;
		case 3:
			this->DisplayStatistics();
			break;
		case 4:
			this->PrintTop3(bestClimbers);
			break;
		case 5:
			system("CLS");
			logOut = true;
			Route::Animation();
			return true;
			break;
		case 6:
			system("CLS");
			Route::Animation();
			return false;
			break;
		default:
			break;
		}
		Route::Animation();
	}
}
void Admin::SaveToDatabase()
{
	fs::path myPath{ fs::current_path() };
	this->SetPathForUser(myPath);
	ofstream file(myPath, ios::app);
	file << endl << this->name << " ";
	file << this->surname << " ";
	file << this->email << " ";
	file << this->password << endl;
	file.close();
}
void Admin::Print()
{
	system("CLS");
	cout << "Displaying information about user:\n";
	cout << "E-mail address: " << this->email;
	cout << "\nPassword: " << this->password;
	cout << "\nName: " << this->getName();
	cout << "\nSurname: " << this->getSurname() << endl;
	system("PAUSE");
	system("CLS");
}
void Admin::PrintUserProfile()
{
	cout << "Displaying admin profile\n";
	cout << "Name: " << this->name;
	cout << "\nSurname: " << this->surname << endl << endl;
	system("PAUSE");
}
void Admin::PrintUsers()
{
	cout << "Printing all climbers: \n\n";
	int counter = 1;
	for (auto& user : this->users) {
		cout << endl << counter << ". " << user.getName() << " " << user.getSurname() << " " << user.getSex() << " " << user.getAge() << " " << user.getWeight() << " " << user.getHeight() << "[m] ";
		counter++;
	}
	cout << endl << endl;
	system("PAUSE");
}
void Admin::LoadFromDatabase()
{
	fs::path myPath{ fs::current_path() };
	this->SetPathForUser(myPath);
	ifstream file(myPath);
	string read;
	Admin tempAdmin;
	int sequence = 0;
	bool stop = false;
	if (file.is_open()) {
		while (file >> read)
		{
			if (sequence % 4 == 0)
			{
				tempAdmin.name = read;
			}
			else if (sequence % 4 == 1)
				tempAdmin.surname = read;
			else if (sequence % 4 == 2)
				tempAdmin.email = read;
			else if (sequence % 4 == 3)
			{
				tempAdmin.password = read;
				stop = true;
			}
			sequence++;
			if (stop)
			{
				if (this->email == tempAdmin.email) {
					this->name = tempAdmin.name;
					this->surname = tempAdmin.surname;
					//this->Print();
					break;
				}
				else
					stop = false;
			}
		}
	}
	else {
		cout << "Application can't reach file from path: " << myPath << ".\nPlease contact administrator to resolve problems.\n";
		system("PAUSE");
		system("CLS");
	}


}
void Admin::SetPathForUser(fs::path& alteredPath)
{
	alteredPath /= "Users/Admins.txt";
}
bool Admin::CheckWithDatabase()
{
	fs::path myPath{ fs::current_path() };
	this->SetPathForUser(myPath);
	ifstream file(myPath);
	string read, tempMail, tempPassword;
	int sequence = 0;
	bool stop = false;
	if (file.is_open()) {
		while (file >> read) {
			if (sequence % 4 == 2)
				tempMail = read;
			else if (sequence % 4 == 3) {
				tempPassword = read;
				stop = true;
			}
			sequence++;

			if (stop) {
				if (tempMail == this->email && tempPassword != this->password)
					return false;
				else if (tempMail == this->email && tempPassword == this->password)
					return true;
				else
					stop = false;
			}
		}
		return false;
	}
	else {
		cout << "Application can't reach file from path: " << myPath << ".\nPlease contact administrator to resolve problems.\n";
		system("PAUSE");
		system("CLS");
	}
}
bool Admin::FindMail(const string& mail)
{
	fs::path myPath{ fs::current_path() };
	this->SetPathForUser(myPath);
	ifstream file(myPath);
	int sequence = 0;
	string read;
	if (file.is_open())
	{
		while (file >> read) {
			if (sequence % 4 == 2 && read == mail)
				return true;
			sequence++;
		}
		return false;
	}
}
string& Admin::getSurname()
{
	return this->surname;
}
string& Admin::getName()
{
	return this->name;
}
void Admin::LoadBasicUsers()
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
				this->users.push_back(tempUser);
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
void Admin::DisplayStatistics()
{
	cout << "Most attended route: ";
	//PrintMostAttended();
	cout << "\n\nRouteSetter whom routes are most attended: ";
	//PrintRouteSetter();
	cout << "\n\nDay of highest attendance: ";
	//PrintHighestAttendaceDay();
	cout << "\n\n";
	system("PAUSE");
}
//===========================================================================BASIC USER========================================================================================
void Basic::Register()
{
	this->RegisterEmailPassword();
	bool correct = false, correct2 = false;
	string TempName, TempSurname;
	double TempHeight, TempWeight;
	int TempAge, choice;
	char TempSex;
	while (!correct) {
		cout << "Please enter your name: ";
		cin >> TempName;
		cout << "Please enter your surname: ";
		cin >> TempSurname;
		cout << "Please enter your height: ";
		cin >> TempHeight;
		cout << "Please enter your weight: ";
		cin >> TempWeight;
		cout << "Please enter your age: ";
		cin >> TempAge;
		while (!correct2) 
		{
			try {
				cout << "Please enter your sex: \n";
				cout << "1. Male\n2. Female\n3. Other\n";
				cin >> choice;
				if (choice > 3 || choice < 1)
					throw choice;
				else
					correct2 = true;
			}
			catch (int& choice) {
				cerr << "You have inputted wrong number. Make sure the number you choose has it's corresponding option.\n";
				system("pause");
				system("CLS");
			}
		}
		switch (choice) {
		case 1:
			TempSex = 'M';
			break;
		case 2:
			TempSex = 'F';
			break;
		case 3:
			TempSex = 'O';
			break;
		}
		while (correct2) {
			system("CLS");
			cout << "Is Your data correct?:\nName: " << TempName << "\nSurname: " << TempSurname << "\nAge: " << TempAge << "\nHeight: " << TempHeight << "\nWeight: " << TempWeight << "\nSex: " << TempSex;
			cout << endl << endl << "1. Yes\n2. No" << endl;
			try {
				cin >> choice;
				if (choice > 2 || choice < 1)
					throw choice;
				else if (choice==1) {
					correct = true;
					correct2 = false;
				}
			}
			catch (...){
				cerr << "You have inputted wrong number. Make sure the number you choose has it's corresponding option.\n";
				system("pause");
				system("CLS");
			}
		}
	}
	this->name = TempName;
	this->surname = TempSurname;
	this->age = TempAge;
	this->height = TempHeight;
	this->weight = TempWeight;
	this->sex = TempSex;
	this->SaveToDatabase();
}
void Basic::LoadRoutes()
{
	fs::path myPath{ fs::current_path() };
	string altered = "Users/Users-Routes/" + this->email + ".txt";
	myPath /= altered;
	ifstream file(myPath);
	string read;
	CompletedRoute tempRoute;
	int sequence = 0;
	if (file.is_open()) {
		while (file >> read) {
			if (sequence % 5 == 0)
				tempRoute.setRouteSetter(read);
			else if (sequence % 5 == 1)
				tempRoute.setID(read);
			else if (sequence % 5 == 2)
				tempRoute.setDifficulty(read);
			else if (sequence % 5 == 3)
				tempRoute.setDate(read);
			else if (sequence % 5 == 4)
			{
				istringstream converted(read);
				double time;
				converted >> time;
				tempRoute.setTime(time);
				this->routesCompleted.push_back(tempRoute);
			}
			sequence++;
		}
	}
}
void Basic::LoadFromDatabase()
{
	fs::path myPath{ fs::current_path() };
	this->SetPathForUser(myPath);
	ifstream file(myPath);
	string read;
	Basic tempUser;
	int sequence = 0;
	bool stop = false;
	if (file.is_open()) {
		while (file >> read)
		{
			if (sequence % 8 == 0)
			{
				tempUser.name = read;
			}
			else if (sequence % 8 == 1)
				tempUser.surname = read;
			else if (sequence % 8 == 2)
				tempUser.email = read;
			else if (sequence % 8 == 3)
				tempUser.password = read;
			else if (sequence % 8 == 4)
			{
				istringstream converted(read);
				converted >> tempUser.height;
			}
			else if (sequence % 8 == 5)
			{
				istringstream converted(read);
				converted >> tempUser.age;
			}
			else if (sequence % 8 == 6)
			{
				istringstream converted(read);
				converted >> tempUser.weight;
			}
			else if (sequence % 8 == 7)
			{
				istringstream converted(read);
				converted >> tempUser.sex;
				stop = true;
			}
			sequence++;
			if (stop)
			{
				if (this->email == tempUser.email) {
					this->age = tempUser.age;
					this->height = tempUser.height;
					this->weight = tempUser.weight;
					this->sex = tempUser.sex;
					this->name = tempUser.name;
					this->surname = tempUser.surname;
					break;
				}
				else
					stop = false;
			}
		}
		this->LoadRoutes();
	}
	else {
		cout << "Application can't reach file from path: " << myPath << ".\nPlease contact administrator to resolve problems.\n";
		system("PAUSE");
		system("CLS");
	}
	//thread + barrier
	thread calculationThr(&Basic::CalculatingCompetetiveParameters, this);
	thread assigningThr(&Basic::AssignCompetetiveParameters, this);
	calculationThr.join();
	assigningThr.join();
	//thread + barrier
	this->FindBestRoute();
}
void Basic::PrintRoutes()
{
	for (auto& route : this->routesCompleted)
		cout << route.getID() << " " << route.getRouteSetter() << " " << route.getDifficulty() << " " << route.getDate() << " " << route.getTime() << endl;
	cout << endl << endl;
	system("PAUSE");
	system("CLS");
}
bool Basic::Options(list <Route> & _routes, vector <string>& bestClimbers)
{
	bool logOut = false;
	int choice, choiceOfRoute;
	bool correct = false;
	while (!logOut) {
		cout << "Please choose one from the following options: \n\n";
		cout << "1. My profile.\n";
		cout << "2. Routes history.\n";
		cout << "3. Attend a route.\n";
		cout << "4. High scores.\n";
		cout << "5. Log out.\n";
		cout << "6. Exit program.\n";
		choice = this->Choice(6);

		switch (choice) {
		case 1:
			this->PrintUserProfile();
			break;
		case 2:
			this->PrintRoutes();
			break;
		case 3:
			cout << "Please choose your route to attend: \n\n";
			this->PrintAllRoutes(_routes);
			this->AttendRoute(this->Choice(_routes.size()), _routes);
			break;
		case 4:
			this->PrintTop3(bestClimbers);
			break;
		case 5:
			logOut = true;
			return true;
			break;
		case 6:
			return false;
			break;
		default:
			break;
		}
		Route::Animation();
	}
}
void Basic::SaveToDatabase() 
{
	fs::path myPath{ fs::current_path() };
	this->SetPathForUser(myPath);
	ofstream file(myPath, ios::app);
	file << endl << this->name << " ";
	file << this->surname << " ";
	file << this->email << " ";
	file << this->password << " ";
	file << this->height << " ";
	file << this->age << " ";
	file << this->weight << " ";
	file << this->sex << endl;
	file.close();

}
void Basic::Print()
{
	system("CLS");
	cout << "Displaying information about user:\n";
	cout << "E-mail address: " << this->email;
	cout << "\nPassword: " << this->password;
	cout << "\nName: " << this->name;
	cout << "\nSurname: " << this->surname;
	cout << "\nAge: " << this->age;
	cout << "\nSex: " << this->sex;
	cout << "\nHeight: " << this->height;
	cout << "\nWeight: " << this->weight;
	system("PAUSE");
	system("CLS");
}
void Basic::PrintUserProfile()
{
	system("CLS");
	cout << "_ | - M y  P r o f i le - | _:\n";
	cout << "\nName: " << this->name;
	cout << "\nSurname: " << this->surname;
	cout << "\nLevel: " << this->level;
	cout << "\nScore: " << this->score;
	cout << "\nBest route: " << this->bestRoute.getID() << " " << this->bestRoute.getRouteSetter() << " " << this->bestRoute.getDifficulty() << " " << this->bestRoute.getTime() << "[ms]" << endl << endl;
	system("PAUSE");
	system("CLS");
}
void Basic::SetPathForUser(fs::path& alteredPath)
{
	alteredPath /= "Users/Users.txt";
}
bool Basic::CheckWithDatabase()
{
	fs::path myPath{ fs::current_path() };
	this->SetPathForUser(myPath);
	ifstream file(myPath);
	string read, tempMail, tempPassword;
	int sequence = 0;
	bool stop = false;
	if (file.is_open()) {
		while (file >> read) {
			if (sequence % 8 == 2)
				tempMail = read;
			else if (sequence % 8 == 3) {
				tempPassword = read;
				stop = true;
			}
			sequence++;

			if (stop) {
				if (tempMail == this->email && tempPassword != this->password)
					return false;
				else if (tempMail == this->email && tempPassword == this->password)
					return true;
				else
					stop = false;
			}
		}
		return false;
	}
	else {
		cout << "Application can't reach file from path: " << myPath << ".\nPlease contact administrator to resolve problems.\n";
		system("PAUSE");
		system("CLS");
	}
}
bool Basic::FindMail(const string & mail)
{
	fs::path myPath{ fs::current_path() };
	this->SetPathForUser(myPath);
	ifstream file(myPath);
	int sequence = 0;
	string read;
	if (file.is_open())
	{
		while (file >> read) {
			if (sequence % 8 == 2 && read == mail)
				return true;
			sequence++;
		}
		return false;
	}
}
string& Basic::getName()
{
	return this->name;
}
string& Basic::getSurname()
{
	return this->surname;
}
void Basic::AttendRoute(const int& index, list <Route>& _routes)
{
	CompletedRoute tempRoute;
	int counter=1;
	for (auto& route : _routes)
	{
		if (counter == index) {
			tempRoute.setRouteSetter(route.getRouteSetter());
			tempRoute.setID(route.getID());
			tempRoute.setDifficulty(route.getDifficulty());
			break;
		}
		counter++;
	}
	double tempTime = tempRoute.MeasureTime();
	if (tempTime != -1) {

		tempRoute.setTime(tempTime);
		time_t t = time(0);
		tm* now = localtime(&t);
		tempRoute.setDate(to_string(now->tm_year + 1900) + "-" + to_string(now->tm_mon + 1) + "-" + to_string(now->tm_mday));
		cout << "Your time: " << tempRoute.getTime() << " [ms]" << endl;
		this->SaveCompletedRoute(tempRoute);
		this->UpdateScoreAndLevel(tempRoute);
		system("PAUSE");
	}
	else {
		cout << "User has failed to complete the route. Try again after a rest!\n";
		Sleep(3000);
	}

}
void Basic::SaveCompletedRoute(CompletedRoute& route)
{
	this->routesCompleted.push_back(route);
	fs::path myPath{ fs::current_path() };
	string altered = "Users/Users-Routes/" + this->email + ".txt";
	myPath /= altered;
	ofstream file(myPath, ios::app);
	file << route.getRouteSetter() << " " << route.getID() << " " << route.getDifficulty() << " " << route.getDate() << " " << route.getTime() << endl;
}
barrier synchronizeCalculations(2);
void Basic::AssignCompetetiveParameters()
{
	synchronizeCalculations.arrive_and_wait();
	this->setLevel((this->score / 10) % 10);
}
void Basic::CalculatingCompetetiveParameters()
{
	int _score = 0;
	for (auto& route : this->routesCompleted) {
		if (route.getDifficulty() == "Green")
			_score++;
		else if (route.getDifficulty() == "Blue")
			_score += 2;
		else if (route.getDifficulty() == "Yellow")
			_score += 3;
		else if (route.getDifficulty() == "Red")
			_score += 4;
		else if (route.getDifficulty() == "Black")
			_score += 5;
	}
	this->setScore(_score);
	synchronizeCalculations.arrive_and_wait();
}
void Basic::UpdateScoreAndLevel(CompletedRoute& route)
{
	if (route.getDifficulty() == "Green")
		this->score++;
	else if (route.getDifficulty() == "Blue")
		this->score += 2;
	else if (route.getDifficulty() == "Yellow")
		this->score += 3;
	else if (route.getDifficulty() == "Red")
		this->score += 4;
	else if (route.getDifficulty() == "Black")
		this->score += 5;
	this->level = (this->score / 10) % 10;
}
void Basic::FindBestRoute() //Has to find max from 5 categories Green/Blue/Yellow/Red/Black.
{
	CompletedRoute Best;
	Best.setDifficulty(this->routesCompleted.begin()->getDifficulty());
	for (auto& route : this->routesCompleted) {
		if (Best.getDifficulty() == "Green" && (route.getDifficulty() == "Blue" || route.getDifficulty() == "Yellow" || route.getDifficulty() == "Red" || route.getDifficulty() == "Black"))
			Best = route;
		else if (Best.getDifficulty() == "Blue" && (route.getDifficulty() == "Yellow" || route.getDifficulty() == "Red" || route.getDifficulty() == "Black"))
			Best = route;
		else if (Best.getDifficulty() == "Yellow" && (route.getDifficulty() == "Red" || route.getDifficulty() == "Black"))
			Best = route;
		else if (Best.getDifficulty() == "Red" && (route.getDifficulty() == "Black"))
			Best = route;
	}
	this->bestRoute = Best;
}
void Basic::clear()
{
	this->age = 0;
	this->name = "";
	this->score = 0;
	this->email = "";
	this->password = "";
	this->level = 0;
	this->height = 0;
	this->weight = 0;
	this->routesCompleted.clear();
}

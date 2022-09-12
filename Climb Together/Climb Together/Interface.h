#pragma once
#include "User.h"
class Interface
{
private:
    shared_ptr <User> user;
public:
    Interface(shared_ptr<User>& _user);
    Interface() {};
    ~Interface() {};
    void ChangeView(shared_ptr<User>& _user);
    int Choice(const int last, bool& correct);
    bool Beginning();
    bool LoginOrRegister();
    bool LoadRoutes(list <Route> & _routes);
    void LoadBasicUsers(list <Basic>& _users);
    void FindBestClimbers(list <Basic>& _users, vector <Basic>& _top3);
    void GetNamesOfBestClimbers(vector <string>& top3Names, vector <Basic>& top3);
 
};



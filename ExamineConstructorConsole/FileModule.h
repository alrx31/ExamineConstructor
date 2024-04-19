#pragma once
#include "Structures.h"


int WriteToFile(string file_path, User user);
int WriteToFile(string file_path, Test test);
int WriteToFile(string file_pass, UserData user);
int WriteToFile(string file_pass, Test* test, User* user, int result, float mark);

UserData getUserData(int id, string file_path);
User FindUser(string file_path, string login);
int getLastId(string path);

TestsContainer* Read(string test_path, bool isPublic,User user);
<<<<<<< HEAD
Raiting* Read(string test_path,string test_name, string user_name);
=======
Raiting* Read(string test_path,Test* test, User user);
>>>>>>> df5a272 (b)

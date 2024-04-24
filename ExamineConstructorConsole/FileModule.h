#pragma once
#include "Structures.h"


int WriteToFile(string file_path, User user);
int WriteToFile(string file_path, Test test);
int WriteToFile(string file_pass, UserData user);
int WriteToFile(string file_pass, string test_name, string user_name, int result, float mark);

int UpdateTest(Test*test, Test test1,User user, string file_path);


UserData getUserData(int id, string file_path);
User FindUser(string file_path, string login);
int getLastId(string path);

TestsContainer* Read(string test_path, bool isPublic,User user);
Raiting* Read(string test_path, Test* test, User* user);
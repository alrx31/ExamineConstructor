#include <iostream>
#include <fstream>
#include "Structures.h"
using namespace std;



int WriteToFile(string file_path, User user){
	ofstream file(file_path, ios::app);
	if (!file.is_open()) return 1;

	file << user.id << " " << user.login << " " << user.password << " " << user.ruleLevel << endl;
	return 0;
}

int WriteToFile(string file_path, Test test) {
	ofstream file(file_path);
	if (!file.is_open()) return 1;
	return 0;
}
int WriteToFile(string file_pass, UserData user) {
	ofstream file(file_pass, ios::app);
	if (!file.is_open()) return 1;

	file << user.id << " " << user.name << " " << user.surname << " " << user.login << " " << user.age << " " << user.count_tests ;
	for (int i = 0; i < user.count_tests; i++) {
		file << "name";
	}
	file << endl;

	return 0;
}


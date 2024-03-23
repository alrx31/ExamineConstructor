#include <iostream>
#include <fstream>
#include "Structures.h"
using namespace std;



int WriteToFile(string file_path, User user){
	ofstream file(file_path);
	if (!file.is_open()) return 1;
	return 0;
}

int WriteToFile(string file_path, Test test) {
	ofstream file(file_path);
	if (!file.is_open()) return 1;
	return 0;
}
int WriteToFile(string file_pass, UserData user) {
	ofstream file(file_pass);
	if (!file.is_open()) return 1;
	return 0;
}


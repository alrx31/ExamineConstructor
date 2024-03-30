#include <iostream>
#include <fstream>
#include "Structures.h"
using namespace std;


// запись в файл пользователя
int WriteToFile(string file_path, User user){
	ofstream file(file_path, ios::app);
	if (!file.is_open()) return 1;

	file << user.id << " " << user.login << " " << user.password << " " << user.ruleLevel << endl;
	return 0;
}
// запись в файл теста
int WriteToFile(string file_path, Test test) {
	ofstream file(file_path,ios::app);
	if (!file.is_open()) return 1;
	file << test.name << test.author << test.difficulty << test.isPublic << test.count_q_standart;
	for (int i = 0; i < test.count_q_standart; i++) {
		///.....
	}

	return 0;
}
// запись в файл данных пользователя
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

// find user in file (login)
User FindUser(string file_path, string login) {
	ifstream file(file_path);
	if (!file.is_open()) {
		cout << "Ошибка открытия файла" << endl;
		return User();
	}
	User user;
	while (!file.eof()) {
		file >> user.id >> user.login >> user.password >> user.ruleLevel;
		if (user.login == login) {
			file.close();
			return user;
		}
	}
	file.close();
	return User();
}

UserData getUserData(int id,string file_path) {
	ifstream file(file_path);
	if (!file.is_open()) {
		cout << "Ошибка открытия файла" << endl;
		return UserData();
	}
	UserData userData;
	while (!file.eof()) {
		file >> userData.id >> userData.name >> userData.surname >> userData.login >> userData.age >> userData.count_tests;
		if (userData.id == id) {
			file.close();
			return userData;
		}
	}

}
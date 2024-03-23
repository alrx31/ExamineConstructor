#include <iostream>
#include "Structures.h"
#include "FileModule.h"
using namespace std;



void RegisterModule() {

	cout << "Регистрация" << endl;
	cout << "Введите логин: ";
	string login;
	cin >> login;
	cout << "Введите пароль: ";
	string password;
	cin >> password;
	cout << "Введите имя: ";
	string name;
	cin >> name;
	cout << "Введите фамилию: ";
	string surname;
	cin >> surname;
	cout << "Введите email: ";
	string email;
	cin >> email;
	cout << "Введите возраст: ";
	int age;
	cin >> age;

	string UserPath= "users/users.txt";
	string UserDataPath= "users/usersData.txt";
	
	User user = User(login, password, 1);
	UserData userData = UserData(name, login, surname, email, age);

	int status = WriteToFile(UserPath, user);
	if (status == 0)
		cout << "Пользователь успешно добавлен в базу" << endl;
	else
		cout << "Ошибка в работе в файлами" << endl;
	status = WriteToFile(UserDataPath, userData);
	if (status == 0)
		cout << "Успешная регистрация" << endl;
	else
		cout << "Ошибка в работе в файлами" << endl;

}

/*
int id;
	string name;
	string surname;
	string login;
	int age;
	string email;
*/
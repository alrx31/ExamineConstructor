#include <iostream>
#include "Structures.h"
#include "FileModule.h"
using namespace std;

string encrypt(string str) {
	string encrypted = "";
	for (int i = 0; i < str.length(); i++) {
		encrypted += str[i] + 1;
	}
	return encrypted;
}
string decrypt(string str) {
	string decrypted = "";
	for (int i = 0; i < str.length(); i++) {
		decrypted += str[i] - 1;
	}
	return decrypted;
}

void RegisterModule() {
	system("cls");
	cout << "Регистрация" << endl;
	cout << "Введите логин: ";
	string login;
	cin >> login;
	cout << "Введите пароль: ";
	string password;
	cin >> password;
	// Шифрование пароля
	password = encrypt(password);

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

	User::count_users = getLastId(UserPath);
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

User Login() {
	while (true) {
		cout << "================================" << endl;
		system("cls");
		cout << "Вход" << endl;
		string login;
		string password;
		cout << "Введите логин: ";
		cin >> login;
		cout << "Введите пароль: ";
		cin >> password;
		// Шифрование пароля
		password = encrypt(password);

		string UserPath = "users/users.txt";
		string UserDataPath = "users/usersData.txt";

		User user = FindUser(UserPath, login);
		cout << user.password << " " << password << endl;
		if (password != user.password) {
			cout << "Неверный пароль" << endl;
			continue;
		}
		else {
			UserData usd = getUserData(user.id, UserDataPath);
			cout << "Вход выполнен" << endl;
			cout << "Вы вошли как " << usd.name << endl;
			cout << "=========================" << endl;
			return user;
		}
	}

}






/*
int id;
	string name;
	string surname;
	string login;
	int age;
	string email;
*/
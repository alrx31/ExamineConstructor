#include <iostream>
#include <windows.h>
// Модули
#include "Structures.h"
#include "RegisterModule.h"
#include "ControlTestModule.h"


using namespace std;

// Главное меню
void Menu(User& user) {
	while (true) {
		cout << "Выберите действие:" << endl;
		cout << "1. Регистрация" << endl;
		cout << "2. Вход" << endl;
		cout << "3. Продолжить как гость" << endl;
		cout << "4. Выход" << endl;

		int choice;
		cin >> choice;
		switch (choice) {
		case 1:
			RegisterModule();
			user.ruleLevel = -1;
			break;
		case 2:
			user = Login();
			break;
		case 3:
			user = User();
			cout << "Продолжение как гость" << endl;
			break;
		case 4:
			cout << "До свидания!" << endl;
			return;
		}
		if (user.ruleLevel > -1) {
			system("cls");
			break;
		}
	}
}



int main() {
	SetConsoleCP(1251); // Ввод с консоли в кодировке 1251
	SetConsoleOutputCP(1251);
	setlocale(LC_ALL, "Russian");
	system("cls");
	cout << "Добро пожаловать в Конструктор экзаменационных билетов!" << endl << endl;
	User user;
	Menu(user);
	switch (user.ruleLevel) {
	case 0: {
		cout << user.ruleLevel;
		break;
	}
	case 1: {
		PersonUI(user);
		break;
	}
	case 2: {
		cout << user.ruleLevel;
		break;
	}
	default: {
		break;
	}


	}

	return 0;
}

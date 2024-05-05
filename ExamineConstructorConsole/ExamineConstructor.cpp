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
		system("cls");
		cout << "===========================" << endl;
		cout << "| Выберите действие:      |" << endl;
		cout << "| 1. Регистрация          |" << endl;
		cout << "| 2. Вход                 |" << endl;
		cout << "| 3. Продолжить как гость |" << endl;
		cout << "| 4. Выход                |" << endl;
		cout << "===========================" << endl;
		string temp;
		int choice;
		getline(cin, temp);
		try
		{
			choice = stoi(temp);
		}
		catch (const std::exception&)
		{
			cout << "Неверный ввод" << endl;
			continue;
		}

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
			cout << "Введите имя: ";
			getline(cin, user.login);
			break;
		case 4:
			cout << "До свидания!" << endl;
			return;
		default:
			cout << "Неверный ввод" << endl;
			continue;
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
	user.ruleLevel = -1;
	Menu(user);
	switch (user.ruleLevel) {
	case 0: {
		GuestUI(user);
		break;
	}
	case 1: {
		PersonUI(user);
		break;
	}
	case 2: {
		AdminUI(user);
		cout << user.ruleLevel;
		break;
	}
	default: {
		break;
	}

	}
	return 0;
}

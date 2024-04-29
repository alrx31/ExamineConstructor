#include "ExportModule.h"
#include <iostream>
#include <string>
#include "Structures.h"
#include <Windows.h>
#include "FileModule.h"
using namespace std;

void ExportTestMenu(Test test, User* user) {
	while (true) {
		system("cls");
		cout << "=====================" << endl;
		cout << "Экспорт теста: " << test.name << endl;
		cout << "=====================" << endl;
		cout << "Выберите действие:" << endl;
		cout << "1. Экспортировать с ответами" << endl;
		cout << "2. Экспортировать без ответов" << endl;
		cout << "3. Выйти" << endl;
		int choice;
		string temp_cin;
		getline(cin, temp_cin);
		try
		{
			choice = stoi(temp_cin);
		}
		catch (const std::exception&)
		{
			cout << "Неверный ввод" << endl;
			Sleep(500);
			continue;
		}
		if (choice < 1 || choice > 3) {
			cout << "Неверный ввод" << endl;
			Sleep(500);
			continue;
		}
		switch (choice) {
		case 1: {
			int res = ExportTest(test, user, "export/" + test.name + ".txt",true);
			if (res == 0) {
				cout << "Тест успешно экспортирован" << endl;
				Sleep(500);
			}
			else {
				cout << "Ошибка экспорта" << endl;
				Sleep(500);
			}
			break;
		}
		case 2: {
				int res = ExportTest(test, user, "export/" + test.name + ".txt", false);
				if (res == 0) {
				cout << "Тест успешно экспортирован" << endl;
				Sleep(500);
			}
						else {
				cout << "Ошибка экспорта" << endl;
				Sleep(500);
			}
				break;

		}
		case 3: {
			return;
		}
		}
	}
}
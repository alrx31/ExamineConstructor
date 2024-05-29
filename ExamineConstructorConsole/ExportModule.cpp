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
		cout << "=================================" << endl;
		cout << "| Экспорт теста: " << test.name << endl;
		cout << "=================================" << endl;
		cout << "| Выберите действие:            |" << endl;
		cout << "| 1. Экспортировать с ответами  |" << endl;
		cout << "| 2. Экспортировать без ответов |" << endl;
		cout << "| 3. Создать билеты             |" << endl;
		cout << "| 4. Выйти                      |" << endl;
		cout << "=================================" << endl;
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
		if (choice < 1 || choice > 4) {
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
			GerateBilets(test);
			break;
		}
		case 4: {
			return;
		}
		}
	}
}


void GerateBilets(Test test) {
	while (true) {
		system("cls");
		cout << "=================================" << endl;
		cout << "| Окно экспорта билетов:         |" << endl;
		cout << "=================================" << endl;
		cout << "| Введите количество билетов:    |" << endl;
		cout << "=================================" << endl;
		int count;
		string temp_cin;
		getline(cin, temp_cin);
		try
		{
			count = stoi(temp_cin);
		}
		catch (const std::exception&)
		{
			cout << "Неверный ввод" << endl;
			Sleep(500);
			continue;
		}
		if (count < 1 || count > 100) {
			cout << "Неверный ввод" << endl;
			Sleep(500);
			continue;
		}
		cout << "=================================" << endl;
		cout << "| Введиде количество вопросов:  |" << endl;
		cout << "=================================" << endl;
		int question_count;
		string temp_cin2;
		getline(cin, temp_cin2);
		try
		{
			question_count = stoi(temp_cin2);
		}
		catch (const std::exception&)
		{
			cout << "Неверный ввод" << endl;
			Sleep(500);
			continue;
		}
		if (question_count < 1 || question_count > 100) {
			cout << "Неверный ввод" << endl;
			Sleep(500);
			continue;
		}
		int res = GenerateBilets(test, count, question_count);
		if (res == 0) {
			cout << "Билеты успешно сгенерированы" << endl;
			Sleep(500);
		}
		else {
			cout << "Ошибка генерации" << endl;
			Sleep(500);
		
		}
		return;
	}
}

int GenerateBilets(Test test, int count_b, int count_q) {
	TestItem* bank = new TestItem[count_b];

	for (int i = 0; i < count_b; i++) {

		int num_q_st = 0;
		int num_q_gues = 0;
		Q_standart* q_st = new Q_standart[count_q];
		Q_guest* q_gues = new Q_guest[count_q];
		Q_standart temp_st;
		Q_guest temp_gues;
		if (test.count_q_guest == 0 || test.count_q_standart == 0) {
			cout << "Недостаочно вопросов в тесте" << endl;
			Sleep(1000);
			return 1;
		}

		for (int j = 0; j < count_q; j++) {
			if (rand() % 2 == 0) {
				temp_st = test.q_standart[rand() % test.count_q_standart];
				for (int k = 0; k < j; k++) {
					if (temp_st.question == q_st[k].question) {
						j--;
						continue;
					}
				}
				q_st[num_q_st] = temp_st;
				num_q_st++;
			}
			else {
				temp_gues = test.q_guest[rand() % test.count_q_guest];
				for (int k = 0; k < j; k++) {
					if (temp_gues.question == q_gues[k].question) {
						j--;
						continue;
					}
				}
				q_gues[num_q_gues] = temp_gues;

				num_q_gues++;
			}
		}
		bank[i] = TestItem(num_q_st, num_q_gues, q_st, q_gues);
		WriteToFile(bank[i], i+1, "export/"+test.name + "_" + to_string(i + 1) + "_bilet.txt");
	}

	string path = "export/" + test.name + "_bilets.txt";
	return 0;
}












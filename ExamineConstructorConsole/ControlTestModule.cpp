// Code for the ControlTestModule
#include <iostream>
#include "Structures.h"
#include "FileModule.h"
using namespace std;

void PersonUI(User user) {
	cout << "Добро пожаловать, " << user.login << "!" << endl << endl;
	while (true) {
		cout << "Выберите действие:" << endl;
		cout << "1. Создать тест" << endl;
		cout << "2. Просмотреть тесты" << endl;
		cout << "3. Пройти публичный тест" << endl;
		cout << "4. Выйти" << endl;
		int choice;
		cin >> choice;
		switch (choice) {
		case 1: {
			cout << "Меню создания теста" << endl;
			break;
		}
		case 2: {
			cout << "Меню просмотра тестов" << endl;
			break;
		}
		case 3: {
			cout << "Меню прохождения публичного теста" << endl;
			break;
		}
		case 4: {
			cout << "До свидания!" << endl;
			return;
		}
		}
	}
};


Test CreateTest(UserData user) {
	int userId = user.id;
	string TestPathPublic = "tests/publicTests.txt";
	string TestPath = "tests/" +to_string(userId) + "test.txt";

	cout << "Меню создания теста" << endl;
	cout << "Введите название теста: ";
	string name;
	getline(cin,name);
	cout << "введите сложность теста: ";
	int level;
	cin >> level;
	cout << "Сделать ли тест публично доступным? (1- да, 0 - нет): ";
	bool isPublic;
	cin >> isPublic;
	cout<< "Введите количество стандартных вопросов: " << endl;
	cout << "(вопросы с одним правильным ответом)" << endl;
	int count_q_standart;
	cin >> count_q_standart;
	Q_standart* q_standart = new Q_standart[count_q_standart];
	cout << "================" << endl;
	for (int i = 0; i < count_q_standart; i++) {
		cout << "Введите вопрос: ";
		string question;
		getline(cin,question);
		cout << "Введите ответ: ";
		string answer;
		getline(cin,answer);
		cout << "Введите сложность вопроса: ";
		int difficulty;
		cin >> difficulty;
		q_standart[i] = Q_standart(question, answer, difficulty);
	}
	cout << "Введите количество вопросов типа теста: " << endl;
	cout << "(вопросы с несколькими вариантами ответа (а,б,в,г)" << endl;
	int count_q_guest;
	cin >> count_q_guest;
	Q_guest* q_guest = new Q_guest[count_q_guest];
	cout << "================" << endl;
	for (int i = 0; i < count_q_guest; i++) {
		cout << "Введите вопрос: ";
		string question;
		getline(cin,question);
		cout << "Введите количество вариантов ответа: ";
		int count_answers;
		cin >> count_answers;
		string* answers = new string[count_answers];
		cout << "Введите варианты ответа: " << endl;
		for (int j = 0; j < count_answers; j++) {
			cout << j + 1 << ". ";
			getline(cin,answers[j]);
		}
		cout << "Введите номер правильного ответа: ";
		int right_answer;
		cin >> right_answer;
		cout << "Введите сложность вопроса: ";
		int difficulty;
		cin >> difficulty;
		q_guest[i] = Q_guest(question, answers, right_answer, difficulty);
	}
	Test test = Test(name, user.name, isPublic, level, count_q_standart, q_standart, count_q_guest, q_guest);

	if (isPublic) {
		WriteToFile(TestPathPublic, test);
	}
	else {
		WriteToFile(TestPath, test);
	}

};
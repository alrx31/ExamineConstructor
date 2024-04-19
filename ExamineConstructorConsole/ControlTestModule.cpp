// Code for the ControlTestModule
#include <iostream>
#include <string>
#include <windows.h>
#include "Structures.h"
#include "FileModule.h"
#include "ControlTestModule.h"

using namespace std;

// показать тесты (массива)
void ShowTests(TestsContainer* tests) {
	system("cls");
	cout << "Список тестов: " << endl;
	for (int i = 0; i < tests->count_tests; i++) {
		cout << i + 1 << ". Название\t" << tests->tests[i].name << "\nСложность:\t " << tests->tests[i].difficulty << endl << endl;
	}
	cout << endl <<"================" << endl << endl;
}



// создание теста
void CreateTest(UserData user) {
	try {
		int userId = user.id;
		string TestPathPublic = "tests/publicTests.txt";
		string TestPath = "tests/" + to_string(userId) + "test.txt";
		system("cls");
		cout << "Меню создания теста" << endl;
		cout << "Введите название теста: " << endl;
		string name;
		cin.ignore();
		getline(cin, name);
		cout << "введите сложность теста: ";
		int level;
		cin >> level;
		cout << "Сделать ли тест публично доступным? (1- да, 0 - нет): ";
		int isPublic;
		cin >> isPublic;
		cout << "Введите количество стандартных вопросов: " << endl;
		cout << "(вопросы с одним правильным ответом)" << endl;
		int count_q_standart;
		cin >> count_q_standart;
		Q_standart* q_standart = new Q_standart[count_q_standart];
		cout << "================" << endl;
		for (int i = 0; i < count_q_standart; i++) {
			cout << "Введите вопрос: ";
			string question;
			cin.ignore();
			getline(cin, question);
			cout << "Введите ответ: ";
			string answer;

			getline(cin, answer);
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
			cin.ignore();
			getline(cin, question);
			cout << "Введите количество вариантов ответа: ";
			int count_answers;
			cin >> count_answers;
			string* answers = new string[count_answers];
			cout << "Введите варианты ответа: " << endl;
			for (int j = 0; j < count_answers; j++) {
				cout << j + 1 << ". ";
				cin.ignore();
				getline(cin, answers[j]);
			}
			cout << "Введите номер правильного ответа: ";
			int right_answer;
			cin >> right_answer;
			cout << "Введите сложность вопроса: ";
			int difficulty;
			cin >> difficulty;
			q_guest[i] = Q_guest(question, answers, count_answers, right_answer, difficulty);
		}
		Test test = Test(name, user.name, isPublic, level, count_q_standart, q_standart, count_q_guest, q_guest);
		int res = 0;
		if (isPublic == 1) {
			res = WriteToFile(TestPathPublic, test);
		}
		else {
			res = WriteToFile(TestPath, test);
		}
		if (res == 1) {
			cout << "Ошибка при создании теста!" << endl;
		}
		else {
			cout << "Тест успешно создан!" << endl;
		}
	}
	catch (exception e) {
		cout << "Ошибка при создании теста!" << endl;
	}
};

// меню пользователя
void PersonUI(User user) {
	while (true) {
		system("cls");
		cout << "Добро пожаловать, " << user.login << "!" << endl << endl;
		cout << "Выберите действие:" << endl;
		cout << "1. Создать тест" << endl;
		cout << "2. Просмотреть тесты" << endl;
		cout << "3. Просмотреть публичные тест" << endl;
		cout << "4. Выйти" << endl;
		int choice;
		cin >> choice;
		Test test = Test();
		Test* temp = new Test();
		switch (choice) {
		case 1: {
			cout << "Меню создания теста" << endl;
			UserData data = getUserData(user.id, "users/usersData.txt");
			CreateTest(data);
			break;
		}
		case 2: {
			cout << "Меню просмотра тестов" << endl;
			TestsContainer* p = Read("tests/" + to_string(user.id) + "test.txt", false, user);
			while (true) {
				ShowTests(p);
				cout << " введите номер теста для прохождения" << endl;
				cout << " введите -1 для выхода" << endl;
				cout << " введите -2 для сортировки тестов (по возрастанию сложности)" << endl;
				cout << " введите -3 для сортировки тестов (по убыванию сложности)" << endl;
				cout << " введите -4 для сортировки тестов по названию (по возрастанию)" << endl;
				cout << " введите -5 для сортировки тестов по названию (по убыванию)" << endl;
				int choice;
				cin >> choice;
				if (choice == -1) {
					break;
				}
				if (choice == -2) {
					//temp = sortTests(p->tests, p->count_tests, 2);
					temp = InsertionSort(p->tests, p->count_tests);
					p->tests = temp;
					continue;
				}
				if (choice == -3) {
					temp = sortTests(p->tests, p->count_tests, 3);
					p->tests = temp;
					continue;
				}
				if (choice == -4) {
					temp = sortTests(p->tests, p->count_tests, 4);
					p->tests = temp;
					continue;
				}
				if (choice == -5) {
					temp = sortTests(p->tests, p->count_tests, 5);
					p->tests = temp;
					continue;
				}
				// cheah is valid number
				if (choice > p->count_tests || choice < 0) {
					cout << "Неверный номер теста!" << endl;
					continue;
				}

				for (int i = 0; i < p->count_tests; i++) {
					if (i == choice - 1) {
						test = p->tests[i];
						break;
					}
				}


				showTestMenu(test,&user);
			}

			break;
		}
		case 3: {
			cout << "Меню публичных тестов" << endl;
			TestsContainer * p = Read("tests/publicTests.txt", true, user);
			while (true) {
				ShowTests(p);
				cout << " введите -1 для выхода" << endl;
				cout << " введите -2 для сортировки тестов (по возрастанию сложности)" << endl;
				cout << " введите -3 для сортировки тестов (по убыванию сложности)" << endl;
				cout << " введите -4 для сортировки тестов по названию (по возрастанию)" << endl;
				cout << " введите -5 для сортировки тестов по названию (по убыванию)" << endl;
				int choice;
				cin >> choice;
				if (choice == -1) {
					break;
				}
				if (choice == -2) {
					//temp = sortTests(p->tests, p->count_tests, 2);
					temp = InsertionSort(p->tests, p->count_tests);
					p->tests = temp;
					continue;
				}
				if (choice == -3) {
					temp = sortTests(p->tests, p->count_tests, 3);
					p->tests = temp;
					continue;
				}
				if (choice == -4) {
					temp = sortTests(p->tests, p->count_tests, 4);
					p->tests = temp;
					continue;
				}
				if (choice == -5) {
					temp = sortTests(p->tests, p->count_tests, 5);
					p->tests = temp;
					continue;
				}
				// cheah is valid number
				if (choice > p->count_tests || choice < 0) {
					cout << "Неверный номер теста!" << endl;
					continue;
				}

				for (int i = 0; i < p->count_tests; i++) {
					if (i == choice - 1) {
						test = p->tests[i];
						break;
					}
				}


				showTestMenu(test,&user);
			}

			break;
		}
		case 4: {
			cout << "До свидания!" << endl;
			return;
		}
		}
	}
};

// меню гостя
void GuestUI(User user) {
	cout << "Добро пожаловать, гость!" << endl << endl;
	while (true) {
		system("cls");
		cout << "Выберите действие:" << endl;
		cout << "1. Просмотреть публичные тесты" << endl;
		cout << "2. Выйти" << endl;
		int choice;
		cin >> choice;
		Test test = Test();
		switch (choice) {
		case 1: {
			Test* temp = new Test();
			TestsContainer * p = Read("tests/publicTests.txt", true, user);
			cout << "Меню просмотра публичных тестов" << endl;
			while (true) {
				ShowTests(p);
				cout << " введите номер теста для прохождения" << endl;
				cout << " введите -1 для выхода" << endl;
				cout << " введите -2 для сортировки тестов (по возрастанию сложности)" << endl;
				cout << " введите -3 для сортировки тестов (по убыванию сложности)" << endl;
				cout << " введите -4 для сортировки тестов по названию (по возрастанию)" << endl;
				cout << " введите -5 для сортировки тестов по названию (по убыванию)" << endl;
				int choice;
				cin >> choice;
				if (choice == -1) {
					break;
				}
				if (choice == -2) {
					//temp = sortTests(p->tests, p->count_tests, 2);
					temp = InsertionSort(p->tests, p->count_tests);
					p->tests = temp;
					continue;
				}
				if (choice == -3) {
					temp = sortTests(p->tests, p->count_tests, 3);
					p->tests = temp;
					continue;
				}
				if (choice == -4) {
					temp = sortTests(p->tests, p->count_tests, 4);
					p->tests = temp;
					continue;
				}
				if (choice == -5) {
					temp = sortTests(p->tests, p->count_tests, 5);
					p->tests = temp;
					continue;
				}
				// cheah is valid number
				if (choice > p->count_tests || choice < 0) {
					cout << "Неверный номер теста!" << endl;
					continue;
				}
				
				for (int i = 0; i < p->count_tests; i++) {
					if (i == choice - 1) {
						test = p->tests[i];
						break;
					}
				}
				

				showTestMenu(test,&user);
			}

			break;
		}
		case 2: {
			cout << "До свидания!" << endl;
			return;
		}
		}
	}
};

// меню администратора
void AdminUI(User user) {}


// показать тест
void ShowTest(Test test) {
	system("cls");
	cout << "Название теста: " << test.name << endl;
	cout << "Автор: " << test.author << endl;
	cout << "Сложность: " << test.difficulty << endl;
	cout << "================" << endl;
	cout << "Стандартные вопросы: " << endl;
	for (int i = 0; i < test.count_q_standart; i++) {
		cout << i + 1 << ". " << test.q_standart[i].question << endl;
	}
	cout << "================" << endl;
	cout << "Вопросы тестого типа: " << endl;
	for (int i = 0; i < test.count_q_guest; i++) {
		cout << i + 1 << ". " << test.q_guest[i].question << endl;
	}
	cout << "================" << endl;

	cout << "Нажмите любую клавишу для продолжения..." << endl;
	cin.get();
	cin.get();
}

// показать меню теста
void showTestMenu(Test test, User*user) {
	if(test.author == user->login){
		while (true) {
			system("cls");
			cout << "�� ������� ����: " << test.name << endl;
			cout << "�������� ��������:" << endl;
			cout << "1. ������ ����" << endl;
			cout << "2. ����������� ����" << endl;
			cout << "3. ����������� �������" << endl;
			cout << "4. ������������� ����" << endl;
			cout << "5. ��������� �����" << endl;
			int choice;
			cin >> choice;
			switch (choice) {
			case 1: {
				int result = startTest(test);
				cout << "���� �������!" << endl;
				cout << "��� ���������: " << result << endl;
				float mark = getMark(result);
				cout << "���� ������: " << mark << endl;
				cout << "================" << endl;
				int res = WriteToFile("tests/raiting.txt", test.name, getUserData(user->id, "users/usersData.txt").name, result, mark);
				if (res == 1) {
					cout << "������ ��� ������ ��������!" << endl;
				}
				else {
					cout << "������� ������� �������!" << endl;
				}
				cout << "������� ����� ������� ��� �����������..." << endl;
				cin.get();
				break;
			}
			case 2: {
				ShowTest(test);
				break;
			}
			case 3: {
				Raiting* raiting = Read("tests/raiting.txt", &test, user);
				string user_name  = getUserData(user->id, "users/usersData.txt").name;
				showReiting(raiting,user, user_name);

				break;
			}
			case 4: {
				//EditTest();
			}
			case 5: {
				return;
			}
			}
		}
	}
	else {
		while (true) {
			system("cls");
			cout << "�� ������� ����: " << test.name << endl;
			cout << "�������� ��������:" << endl;
			cout << "1. ������ ����" << endl;
			cout << "2. ����������� ����" << endl;
			cout << "3. ����������� �������" << endl;
			cout << "4. ��������� �����" << endl;
			int choice;
			cin >> choice;
			switch (choice) {
			case 1: {
				int result = startTest(test);
				cout << "���� �������!" << endl;
				cout << "��� ���������: " << result << endl;
				float mark = getMark(result);
				cout << "���� ������: " << mark << endl;

				cout << "================" << endl;
				int res = WriteToFile("tests/raiting.txt", test.name, getUserData(user->id, "users/usersData.txt").name, result, mark);
				if (res == 1) {
					cout << "������ ��� ������ ��������!" << endl;
				}
				else {
					cout << "������� ������� �������!" << endl;
				}
				cout << "������� ����� ������� ��� �����������..." << endl;
				cin.get();
				break;
			}
			case 2: {
				ShowTest(test);
				break;
			}
			case 3: {
				return;
			}
			case 4: {
				return;
			}
			}
		}
	}
}




// начать тест
int startTest(Test test) {
	int result = 0;
	cout << "================" << endl;
	cout << "Тест начался!" << endl;
	cout << "================" << endl;
	cout << "Стандартные вопросы: " << endl;
	for (int i = 0; i < test.count_q_standart; i++) {
		cout << i + 1 << ". " << test.q_standart[i].question << endl;
		string answer;
		cout << "Введите ответ: ";
		cin.ignore();
		getline(cin, answer);
		if (answer == test.q_standart[i].answer) {
			result += test.q_standart[i].difficulty;
		}
	}
	cout << "================" << endl;
	cout << "Вопросы тестого типа: " << endl;
	for (int i = 0; i < test.count_q_guest; i++) {
		cout << i + 1 << ". " << test.q_guest[i].question << endl;
		cout << "Варианты ответа: " << endl;
		for (int j = 0; j < test.q_guest[i].count_answers; j++) {
			cout << j + 1 << ". " << test.q_guest[i].answer[j] << endl;
		}
		int answer; 
		cout << "Введите номер ответа: ";
		cin >> answer;
		cin >> answer;
		if (answer == test.q_guest[i].right_answer) {
			result += test.q_guest[i].difficulty;
		}
	}
	cout << "================" << endl;
	return result;
}

// �������� ������
float getMark(int result){
	if (result == 0) {
		return 0;
	}
	return result % 10;

}

// merge sort
Test* sortTests(Test* tests,int _size, int choice) {
	int size = _size;
	if (size == 1) {
		return tests;
	}
	int mid = size / 2;
	Test* left = new Test[mid];
	Test* right = new Test[size - mid];
	for (int i = 0; i < mid; i++) {
		left[i] = tests[i];
	}
	for (int i = mid; i < size; i++) {
		right[i - mid] = tests[i];
	}
	left = sortTests(left, mid,choice);
	right = sortTests(right,size-mid,choice);
	return merge(left, right, mid, size - mid, choice);
}
// merge
Test* merge(Test* left, Test* right, int l, int r, int choice) {
	// 2- по возрастанию сложности
	// 3 - по убыванию сложности
	// 4 - по названию (по возрастанию)
	// 5 - по названию (по убыванию)
	Test* result = new Test[l + r];
	int i = 0;
	int j = 0;
	int k = 0;
	while (i < l && j < r) {

		if (choice == 2) {
			if (left[i].difficulty < right[j].difficulty) {
				result[k] = left[i];
				i++;
			}
			else {
				result[k] = right[j];
				j++;
			}
		}
		else if (choice == 3) {
			if (left[i].difficulty > right[j].difficulty) {
				result[k] = left[i];
				i++;
			}
			else {
				result[k] = right[j];
				j++;
			}
		}
		else if (choice == 4) {
			if (left[i].name > right[j].name) {
				result[k] = left[i];
				i++;
			}
			else {
				result[k] = right[j];
				j++;
			}
		}
		else if (choice == 5) {
			if (left[i].name < right[j].name) {
				result[k] = left[i];
				i++;
			}
			else {
				result[k] = right[j];
				j++;
			}
		}

		k++;
	}
	
	while (i < l) {
		result[k] = left[i];
		i++;
		k++;
	}
	while (j < r) {
		result[k] = right[j];
		j++;
		k++;
	}
	return result;
}

<<<<<<< HEAD
// показать рейтинг
void showReiting(Raiting* raiting, User* user) {
	system("cls");
	cout << "Рейтинг теста: " << raiting->test_name << endl;
	cout << "Средний результат: " << raiting->middle_result << endl;
=======

void showReiting(Raiting* raiting, User * user,string user_name) {
	system("cls");
	cout << "������� �����: " << raiting->test_name << endl;
	cout << "������� ���������: " << raiting->middle_result << endl;
>>>>>>> df5a272 (b)
	cout << "================" << endl;
	cout << "Пользователи:" << endl;
	bool isGoten = false;
	Raiting_node* temp = raiting->head;
	while (temp != nullptr) {
		cout << temp->user_name<< " - " << temp->result << endl;
		if (temp->user_name == user_name) {
			isGoten = true;
		}
		temp = temp->next;
	}
	cout << "================" << endl;
	if (isGoten) {
		cout << "Ваш наивысший результат: " << LinearFind(raiting, user) << endl;
		cout << "================" << endl;
	}
	else {
		cout << "�� �� ��������� ������ ����" << endl;
	}
	cout << "������� ����� ������� ��� �����������..." << endl;
	cin.ignore();
	cin.get();
}
// линейный поиск
int LinearFind(Raiting* raiting, User* user) {
	int max = 0;
	Raiting_node* temp = raiting->head;
	while (temp != nullptr) {
		if (temp->user_name == getUserData(user->id, "users/usersData.txt").name && temp->result > max) {
			max = temp->result;
		}
		temp = temp->next;
	}
	return max;
}



// insertion sort tests by difficulty

Test* InsertionSort(Test* tests, int size) {
	Test temp;
	for (int i = 1; i < size; i++) {
		temp = tests[i];
		int j = i - 1;
		while (j >= 0 && tests[j].difficulty > temp.difficulty) {
			tests[j + 1] = tests[j];
			j--;
		}
		tests[j + 1] = temp;
	}
	return tests;
}
// Code for the ControlTestModule
#include <iostream>
#include <string>
#include <windows.h>
#include "Structures.h"
#include "FileModule.h"
#include "ControlTestModule.h"
#include "ExportModule.h"

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
		int userId = user.id;
		string TestPathPublic = "tests/publicTests.txt";
		string TestPath = "tests/" + to_string(userId) + "test.txt";
		system("cls");
		cout << "===================================================" << endl;
		cout << "| Меню создания теста                              " << endl;
		cout << "| Введите название теста: " << endl;
		string name;
		getline(cin, name);
		cout << "| Введите сложность теста от 1 до 100: ";
		int level;
		string temp_cin;
		getline(cin, temp_cin);
		try {
			level = stoi(temp_cin);
		}
		catch (const std::exception&)
		{
			cout << "| Неверный ввод" << endl;
			Sleep(500);
			return;
		}
		if (level < 1 || level > 100) {
			cout << "| Неверный ввод" << endl;
			Sleep(500);
			return;
		}
		cout << "| Сделать ли тест публично доступным? (1- да, 0 - нет): ";
		int isPublic;

		getline(cin, temp_cin);
		try {
			isPublic = stoi(temp_cin);
		}
		catch (const std::exception&)
		{
			cout << "Неверный ввод" << endl;
			Sleep(500);
			return;
		}
		if (isPublic != 0 && isPublic != 1) {
			cout << "Неверный ввод" << endl;
			Sleep(500);
			return;
		}
		cout << "| Введите количество стандартных вопросов до 1000: " << endl;
		cout << "| (вопросы с одним правильным ответом)" << endl;
		int count_q_standart;
		while (true) {
			getline(cin, temp_cin);
			try {
				count_q_standart = stoi(temp_cin);
				break;
			}
			catch (const std::exception&)
			{
				cout << "Неверный ввод" << endl;
				Sleep(500);
				continue;
			}
			if (count_q_standart < 0 || count_q_standart > 1000) {
				cout << "Неверное количество вопросов" << endl;
				Sleep(500);
				continue;
			}
		}
		
		Q_standart* q_standart = new Q_standart[count_q_standart];
		cout << "| ================" << endl;
		for (int i = 0; i < count_q_standart; i++) {
			cout << "| | Введите вопрос: " << i+1 << "." << endl;
			string question;
			getline(cin, question);
			if (question == "" || question == " ") {
				cout << "Вопрос не может быть пустым" << endl;
				Sleep(500);
				i--;
				continue;
			}
			cout << "| | Введите ответ: ";
			string answer;
			getline(cin, answer);
			if (answer == "" || answer == " ") {
				cout << "Ответ не может быть пустым" << endl;
				Sleep(500);
				i--;
				continue;
			}
			cout << "| | Введите сложность вопроса: ";
			int difficulty;
			getline(cin, temp_cin);
			try {
				difficulty = stoi(temp_cin);
			}
			catch (const std::exception&)
			{
				cout << "Неверный ввод" << endl;
				Sleep(500);
				i--;
				continue;
			}
			if (difficulty < 0 || difficulty > 100) {
				cout << "Неверная сложность вопроса" << endl;
				Sleep(500);
				i--;
				continue;
			}
			q_standart[i] = Q_standart(question, answer, difficulty);
		}
		cout << "| Введите количество вопросов типа теста до 1000: " << endl;
		cout << "| (вопросы с несколькими вариантами ответа (а,б,в,г)" << endl;
		int count_q_guest;
		while (true) {
			getline(cin, temp_cin);
			try {
				count_q_guest = stoi(temp_cin);
				break;
			}
			catch (const std::exception&)
			{
				cout << "Неверный ввод" << endl;
				Sleep(500);
				continue;
			}
			if (count_q_guest < 0 || count_q_guest > 1000) {
				cout << "Неверное количество вопросов" << endl;
				Sleep(500);
				continue;
			}
		}
		Q_guest* q_guest = new Q_guest[count_q_guest];
		cout << "| ================" << endl;
		for (int i = 0; i < count_q_guest; i++) {
			cout << "| | Введите вопрос: ";
			string question;
			getline(cin, question);
			if (question == "" || question == " ") {
				cout << "Вопрос не может быть пустым" << endl;
				Sleep(500);
				i--;
				continue;
			}
			cout << "| | Введите количество вариантов ответа до 20: ";
			int count_answers;
			while (true) {
				getline(cin, temp_cin);
				try {
					count_answers = stoi(temp_cin);
					break;
				}
				catch (const std::exception&)
				{
					cout << "Неверный ввод" << endl;
					Sleep(500);
					i--;
					continue;
				}
				if (count_answers < 1 || count_answers > 20) {
					cout << "Неверное количество вариантов ответа" << endl;
					Sleep(500);
					i--;
					continue;
				}
			}
			string* answers = new string[count_answers];
			cout << "| | Введите варианты ответа: " << endl;
			for (int j = 0; j < count_answers; j++) {
				cout << j + 1 << ". ";
				getline(cin, answers[j]);
				if (answers[j] == "" || answers[j] == " ") {
					cout << "Ответ не может быть пустым" << endl;
					Sleep(500);
					j--;
					continue;
				}
			}
			cout << "| | Введите номер правильного ответа: ";
			int right_answer;
			while (true) {
				getline(cin, temp_cin);
				try {
					right_answer = stoi(temp_cin);
					break;
				}
				catch (const std::exception&)
				{
					cout << "Неверный ввод" << endl;
					Sleep(500);
					i--;
					continue;
				}
				if (right_answer < 1 || right_answer > count_answers) {
					cout << "Неверный номер правильного ответа" << endl;
					Sleep(500);
					i--;
					continue;
				}
			}
			cout << "| | Введите сложность вопроса: ";
			int difficulty;
			while (true) {
				getline(cin, temp_cin);
				try {
					difficulty = stoi(temp_cin);
					break;
				}
				catch (const std::exception&)
				{
					cout << "Неверный ввод" << endl;
					Sleep(500);
					i--;
					continue;
				}
				if (difficulty < 0 || difficulty > 100) {
					cout << "Неверная сложность вопроса" << endl;
					Sleep(500);
					i--;
					continue;
				}
			}
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
		//create raiting file
		int res1 = CreateRaiting("raiting/" + test.name + ".txt", test.name, user.name);
			
		if (res1 == 1) {
			cout << "Ошибка при создании рейтинга!" << endl;
		}

		if (res == 1) {
			cout << "Ошибка при создании теста!" << endl;
		}
		else {
			cout << "Тест успешно создан!" << endl;
		}
};

// меню пользователя
void PersonUI(User user) {
	while (true) {
		system("cls");
		cout << "==================================" << endl;
		cout << "| Добро пожаловать, " << user.login << "!" << endl;
		cout << "| Выберите действие:             |" << endl;
		cout << "| 1. Создать тест                |" << endl;
		cout << "| 2. Просмотреть тесты           |" << endl;
		cout << "| 3. Просмотреть публичные тесты |" << endl;
		cout << "| 4. Выйти                       |" << endl;
		cout << "==================================" << endl;
		int choice;
		string temp_cin;
		//cin >> choice;
		getline(cin, temp_cin);
		try {
			choice = stoi(temp_cin);
		}
		catch (const std::exception&)
		{
			cout << "Неверный ввод" << endl;
			continue;
		}
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
			while (true) {
				TestsContainer* p = Read("tests/" + to_string(user.id) + "test.txt", false, user);
				
				if (p == nullptr) {
					cout << "У вас нет тестов!" << endl;
					Sleep(500);
					break;
				}

				ShowTests(p);
				 
				cout << " введите номер теста для его осмотра" << endl;
				cout << " введите (-1) для выхода" << endl;
				cout << " введите (-2) для сортировки тестов (по возрастанию сложности)" << endl;
				cout << " введите (-3) для сортировки тестов (по убыванию сложности)" << endl;
				cout << " введите (-4) для сортировки тестов по названию (по возрастанию)" << endl;
				cout << " введите (-5) для сортировки тестов по названию (по убыванию)" << endl;
				int choice;
				string temp_cin;
				//cin >> choice;
				getline(cin, temp_cin);
				try {
					choice = stoi(temp_cin);
				}
				catch (const std::exception&)
				{
					cout << "Неверный ввод" << endl;
					continue;
				}
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


				showTestMenu(test,&user,false);
			}

			break;
		}
		case 3: {
			cout << "Меню публичных тестов" << endl;
			TestsContainer * p = Read("tests/publicTests.txt", true, user);
			while (true) {
				ShowTests(p);
				cout << " введите (-1) для выхода" << endl;
				cout << " введите (-2) для сортировки тестов (по возрастанию сложности)" << endl;
				cout << " введите (-3) для сортировки тестов (по убыванию сложности)" << endl;
				cout << " введите (-4) для сортировки тестов по названию (по возрастанию)" << endl;
				cout << " введите (-5) для сортировки тестов по названию (по убыванию)" << endl;
				int choice;
				string temp_cin;
				//cin >> choice;
				getline(cin, temp_cin);
				try {
					choice = stoi(temp_cin);
				}
				catch (const std::exception&)
				{
					cout << "Неверный ввод" << endl;
					continue;
				}
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


				showTestMenu(test,&user,false);
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
		string temp_cin;
		int choice;
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
		Test test = Test();
		switch (choice) {
		case 1: {
			Test* temp = new Test();
			TestsContainer * p = Read("tests/publicTests.txt", true, user);
			if (p == nullptr) {
				cout << "Ошибка чтения тестов";
				Sleep(500);
				break;
			}

			cout << "Меню просмотра публичных тестов" << endl;
			while (true) {
				ShowTests(p);
				cout << " введите номер теста для его осмотра" << endl;
				cout << " введите (-1) для выхода" << endl;
				cout << " введите (-2) для сортировки тестов (по возрастанию сложности)" << endl;
				cout << " введите (-3) для сортировки тестов (по убыванию сложности)" << endl;
				cout << " введите (-4) для сортировки тестов по названию (по возрастанию)" << endl;
				cout << " введите (-5) для сортировки тестов по названию (по убыванию)" << endl;
				string temp_cin;
				int choice;
				getline(cin, temp_cin);
				try
				{
					choice = stoi(temp_cin);
				}
				catch (const std::exception&)
				{
					cout << "Неверный ввод" << endl;
					continue;
				}

				if (choice == -1) {
					break;
				}
				if (choice == -2) {
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
				// check is valid number
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
				

				showTestMenu(test,&user,true);
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
void AdminUI(User user) {
	while (true) {
		system("cls");
		cout << "=======================================" << endl;
		cout << "| Добро пожаловать, администратор " << user.login << "!" << endl;
		cout << "| Выберите действие:                  |" << endl;
		cout << "| 1. Просмотреть всех пользователей   |" << endl;
		cout << "| 2. Просмотреть публичные тесты      |" << endl;
		cout << "| 3. Выйти                            |" << endl;
		cout << "=======================================" << endl;
		int choice;
		string temp_cin;
		getline(cin, temp_cin);
		try {
			choice = stoi(temp_cin);
		}
		catch (const std::exception&)
		{
			cout << "Неверный ввод" << endl;
			continue;
		}
		if (choice < 1 || choice > 3) {
			cout << "Неверный ввод" << endl;
			continue;
		}
		switch (choice) {
		case 1: {
			system("cls");
			cout << "Список пользователей:" << endl;
			cout << "====================" << endl;
			ShowUsers();


			cout << "Нажмите любую кнопку для продолжения";
			cin.get();
			break;
		}
		case 2:{
			system("cls");
			Test test = Test();
			Test* temp = new Test();
			cout << "Меню просмотра публичных тестов" << endl;
			while (true) {
				TestsContainer* p = Read("tests/publicTests.txt", false, user);

				if (p == nullptr) {
					cout << "нет пуюличных тестов" << endl;
					Sleep(500);
					break;
				}

				ShowTests(p);

				cout << " введите номер теста для ого осмотра" << endl;
				cout << " введите -1 для выхода" << endl;
				cout << " введите -2 для сортировки тестов (по возрастанию сложности)" << endl;
				cout << " введите -3 для сортировки тестов (по убыванию сложности)" << endl;
				cout << " введите -4 для сортировки тестов по названию (по возрастанию)" << endl;
				cout << " введите -5 для сортировки тестов по названию (по убыванию)" << endl;
				int choice;
				string temp_cin;
				getline(cin, temp_cin);
				try {
					choice = stoi(temp_cin);
				}
				catch (const std::exception&)
				{
					cout << "Неверный ввод" << endl;
					continue;
				}
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


				showTestMenu(test, &user,false);
			}
			break;
		}
		case 3: {
			return;
		}
		}

	}

}

void ShowUsers() {
	UsersContainer* data = ReadUsers();
	if (data == nullptr) {
		cout << "Список пользователей пуст" << endl;
		return;
	}
	UserNode* temp = data->head;
	while (temp != nullptr) {

		cout << "| ID        " << temp->data.id<<"." << endl;
		cout << "| Login:    " << temp->data.login << endl;
		cout << "| Name:     " << temp->data.name << endl;	
		cout << "| Surname:  " << temp->data.surname << endl;
		cout << "| Email:    " << temp->data.email << endl;
		cout << "| Age:      " << temp->data.age << endl;
		cout << "==========================" << endl;
		temp = temp->next;
	}


}




// показать тест
void ShowTest(Test test,bool isPublic) {
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
	cin.clear();
	cin.ignore(32767, '\n');
	cin.get();
}

// показать меню теста
void showTestMenu(Test test, User*user, bool isPublic) {
	if(test.author == user->login){
		while (true) {
			system("cls");
			cout << "==============================" << endl;
			cout << "| Вы выбрали тест: " << test.name << endl;
			cout << "| Выберите действие:          |" << endl;
			cout << "| 1. Начать тест              |" << endl;
			cout << "| 2. Просмотреть тест         |" << endl;
			cout << "| 3. Просмотреть рейтинг      |" << endl;
			cout << "| 4. Редактировать тест       |" << endl;
			cout << "| 5. Вернуться назад          |" << endl;
			cout << "==============================" << endl;
			cout << "| 6. Экспортировать тест      |" << endl;
			cout << "==============================" << endl;

			string temp_cin;
			int choice;
			getline(cin, temp_cin);
			try
			{
				choice = stoi(temp_cin);
			}
			catch (const std::exception&)
			{
				cout << "Неверный ввод" << endl;
				continue;
			}

			switch (choice) {
			case 1: {
				int result = startTest(test);
				cout << "Тест пройден!" << endl;
				cout << "Ваш результат: " << result << endl;
				float mark = getMark(result);
				cout << "Ваша оценка: " << mark << endl;
				cout << "================" << endl;
				int res = WriteToFile("raiting/" + test.name + ".txt", test.name, getUserData(user->id, "users/usersData.txt").name, result);
				if (res == 1) {
					cout << "Ошибка при записи рейтинга!" << endl;
				}
				else {
					cout << "Рейтинг успешно записан!" << endl;
				}
				cout << "Нажмите любую клавишу для продолжения..." << endl;
				cin.get();
				break;
			}
			case 2: {
				ShowTest(test,isPublic);
				break;
			}
			case 3: {
				Raiting* raiting = Read("raiting/"+ test.name+".txt", &test, user);
				string user_name  = getUserData(user->id, "users/usersData.txt").name;
				showRaiting(raiting,user, user_name,isPublic);

				break;
			}
			case 4: {
				EditTest(&test, *user);
				return;
			}
			case 5: {
				return;
			}
			case 6: {
				ExportTestMenu(test,user);
			}
			}
		}
	}
	else if(!isPublic){
		while (true) {
			system("cls");
			cout << "Вы выбрали тест: " << test.name << endl;
			cout << "Выберите действие:" << endl;
			cout << "1. Начать тест" << endl;
			cout << "2. Просмотреть тест" << endl;
			cout << "3. Просмотреть рейтинг" << endl;
			cout << "4. Вернуться назад" << endl;
			
			string temp_cin;
			int choice;
			getline(cin, temp_cin);
			try
			{
				choice = stoi(temp_cin);
			}
			catch (const std::exception&)
			{
				cout << "Неверный ввод" << endl;
				continue;
			}
			switch (choice) {
			case 1: {
				int result = startTest(test);
				cout << "Тест пройден!" << endl;
				cout << "Ваш результат: " << result << endl;
				float mark = getMark(result);
				cout << "Ваша оценка: " << mark << endl;

				cout << "================" << endl;
				int res = WriteToFile("raiting/" + test.name + ".txt", test.name, getUserData(user->id, "users/usersData.txt").name, result);
				if (res == 1) {
					cout << "Ошибка при записи рейтинга!" << endl;
				}
				else {
					cout << "Рейтинг успешно записан!" << endl;
				}
				cout << "Нажмите любую клавишу для продолжения..." << endl;
				cin.get();
				break;
			}
			case 2: {
				ShowTest(test,isPublic);
				break;
			}
			case 3: {
				Raiting* raiting = Read("raiting/" + test.name + ".txt", &test, user);
				string user_name = getUserData(user->id, "users/usersData.txt").name;
				showRaiting(raiting, user, user_name,isPublic);
				break;
			}
			case 4: {
				return;
			}
			}
		}
	}
	else {
		while (true) {
			system("cls");
			cout << "Вы выбрали тест: " << test.name << endl;
			cout << "Выберите действие:" << endl;
			cout << "1. Начать тест" << endl;
			cout << "2. Просмотреть тест" << endl;
			cout << "3. Просмотреть рейтинг" << endl;
			cout << "4. Вернуться назад" << endl;
			string temp_cin;
			int choice;
			getline(cin, temp_cin);
			try
			{
				choice = stoi(temp_cin);
			}
			catch (const std::exception&)
			{
				cout << "Неверный ввод" << endl;
				continue;
			}
			switch (choice) {
			case 1: {
				int result = startTest(test);
				cout << "Тест пройден!" << endl;
				cout << "Ваш результат: " << result << endl;
				float mark = getMark(result);
				cout << "Ваша оценка: " << mark << endl;

				cout << "================" << endl;
				int res = WriteToFile("raiting/" + test.name + ".txt", test.name, user->login, result);
				if (res == 1) {
					cout << "Ошибка при записи рейтинга!" << endl;
				}
				else {
					cout << "Рейтинг успешно записан!" << endl;
				}
				cout << "Нажмите любую клавишу для продолжения..." << endl;
				cin.get();
				break;
			}
			case 2: {
				ShowTest(test,isPublic);
				break;
			}
			case 3: {
				Raiting* raiting = Read("raiting/" + test.name + ".txt", &test, user);
				string user_name = user->login;
				showRaiting(raiting, user, user_name,isPublic);
				break;
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
	cin.clear();
	cin.ignore(32767, '\n');
	int result = 0;
	system("cls");
	cout << "================" << endl;
	cout << "Тест "<< test.name<< " начался!" << endl;
	cout << "================" << endl;
	cout << "Стандартные вопросы: " << endl;
	for (int i = 0; i < test.count_q_standart; i++) {
		cout << i + 1 << ". " << test.q_standart[i].question << endl;
		string answer;
		cout << "Введите ответ: ";
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
		string temp_cin;
		getline(cin, temp_cin);
		try {
			answer = stoi(temp_cin);
		}
		catch (const exception) {
			answer = 0;
		}
		if (answer == test.q_guest[i].right_answer) {
			result += test.q_guest[i].difficulty;
		}
	}
	cout << "================" << endl;
	return result;
}

// получить оценку
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


void showRaiting(Raiting* raiting, User * user,string user_name, bool isPublic) {
	system("cls");
	cout << "Рейтинг теста: " << raiting->test_name << endl;
	cout << "Средний результат: " << raiting->middle_result << endl;
	cout << "================" << endl;
	raiting->BubleSort();
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
	if (!isPublic) {
		if (isGoten) {
			cout << "Ваш наивысший результат: " << LinearFind(raiting, user) << endl;
			cout << "================" << endl;
		}
		else {
			cout << "Вы не проходили данный тест" << endl;
		}
	}

	cout << "================" << endl;

	cout << "Нажмите любую клавишу для продолжения..." << endl;
	if (isPublic) {
		cin.ignore();
	}
	cin.get();
}

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



void EditTest(Test* test, User user) {
	TestsContainer* tests = Read("tests/" + to_string(getUserData(user.id, "users/usersData.txt").id) + "test.txt", false, user);
	Test temp = Test();

	for (int i = 0; i < tests->count_tests; i++) {
		if (test->name == tests->tests[i].name) {
			temp = tests->tests[i];
			break;
		}
	}
	if (temp.name == "") {
		cout << "Тест не найден!" << endl;
		return;
	}

	while (true) {
		system("cls");
		cout << "========================================" << endl;
		cout << "| Редактирование теста: " << temp.name << "Сложность: "<< temp.difficulty << endl;
		cout << "========================================" << endl;
		cout << "| Выберите действие:                   |" << endl;
		cout << "| 1. Изменить сложность                |" << endl;
		cout << "| 2. Изменить стандартные вопросы      |" << endl;
		cout << "| 3. Изменить вопросы тестового типа   |" << endl;
		cout << "| 4. Сохранить изменения               |" << endl;
		cout << "| 5. Удалить тест                      |" << endl;
		cout << "| 6. Выйти                             |" << endl;
		cout << "========================================" << endl;
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
		switch (choice) {
		case 1: {
			cout << "Введите новую сложность: ";
			int difficulty;
			string temp_cin;
			getline(cin, temp_cin);
			try
			{
				difficulty = stoi(temp_cin);
			}
			catch (const std::exception&)
			{
				cout << "Неверный ввод" << endl;
				Sleep(500);
				continue;
			}
			if (difficulty < 0 || difficulty > 100) {
				cout << "Сложность должна быть в диапазоне от 0 до 100" << endl;
				Sleep(500);
				continue;
			}

			temp.difficulty = difficulty;
			break;
		}
		case 2: {
			temp = edit_Q_standart(temp);
			break;
		}
		case 3: {
			temp = edit_Q_guest(temp);
			break;
		}
		case 4: {
			int res = UpdateTest(test,temp,user,"tests/" + to_string(user.id) + "test.txt");
			if (res == 1) {
				cout << "Ошибка при сохранении теста!" << endl;
			}
			else {
				cout << "Тест успешно сохранен!" << endl;
			}
			break;
		}
		case 5: {
			int res = DeleteTest(test, user, "tests/" + to_string(user.id) + "test.txt");
			int res2 = remove(("raiting/" + test->name + ".txt").c_str());
			if (res == 1) {
				cout << "Ошибка при удалении теста!" << endl;
			}
			else {
				cout << "Тест успешно удален!" << endl;
			}
			break;
		}
		case 6: {
			return;
		}


		}

	}




}


Test edit_Q_standart(Test temp1){
	Test temp = temp1;
	while (true) {
		system("cls");
		cout << "=====================" << endl;
		cout << "Стандартные вопросы: " << endl;
		for (int i = 0; i < temp.count_q_standart; i++) {
			cout << i + 1 << ". " << temp.q_standart[i].question << endl;
		}
		cout << "=====================" << endl;
		cout << "Выберите действие:" << endl;
		cout << "1. Добавить вопрос" << endl;
		if (temp.count_q_standart > 0) {
			cout << "2. Редактировать вопрос" << endl;
			cout << "3. Удалить вопрос" << endl;
		}
		cout << "4. Выйти" << endl;

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
		if (temp.count_q_standart == 0 && (choice == 2 || choice == 3)) {
			cout << "Нет вопросов для редактирования!" << endl;
			Sleep(500);
			continue;
		}
		switch (choice) {
		case 1: {
			cout << "Введите вопрос: ";
			string question;
			getline(cin, question);
			if (question == "") {
				cout << "Вопрос не может быть пустым!" << endl;
				Sleep(500);
				continue;
			}
			cout << "Введите ответ: ";
			string answer;
			getline(cin, answer);
			if (answer == "") {
				cout << "Ответ не может быть пустым!" << endl;
				Sleep(500);
				continue;
			}
			cout << "Введите сложность вопроса: ";
			int difficulty;
			string temp_cin;
			getline(cin, temp_cin);
			try
			{
				difficulty = stoi(temp_cin);
			}
			catch (const std::exception&)
			{
				cout << "Неверный ввод" << endl;
				Sleep(500);
				continue;
			}
			if (difficulty < 0 || difficulty > 100) {
				cout << "Сложность должна быть в диапазоне от 0 до 100" << endl;
				Sleep(500);
				continue;
			}
			
			Q_standart* q_standart = new Q_standart[temp.count_q_standart + 1];
			for (int i = 0; i < temp.count_q_standart; i++) {
				q_standart[i] = temp.q_standart[i];
			}
			q_standart[temp.count_q_standart] = Q_standart(question, answer, difficulty);
			temp.q_standart = q_standart;
			temp.count_q_standart++;
			break;
		}
		case 2: {
			cout << "Введите номер вопроса для редактирования: ";
			int number;
			string temp_cin;
			getline(cin, temp_cin);
			try
			{
				number = stoi(temp_cin);
			}
			catch (const std::exception&)
			{
				cout << "Неверный ввод" << endl;
				Sleep(500);
				continue;
			}
			if (number > temp.count_q_standart || number < 0) {
				cout << "Неверный номер вопроса!" << endl;
				Sleep(500);
				continue;
			}
			cout << "Введите новый вопрос: ";
			string question;
			getline(cin, question);
			if (question == "")
			{
				cout << "Вопрос не может быть пустым!" << endl;
				Sleep(500);
				continue;
			}
			cout << "Введите новый ответ: ";
			string answer;
			getline(cin, answer);
			if (answer == "")
			{
				cout << "Ответ не может быть пустым!" << endl;
				Sleep(500);
				continue;
			}
			cout << "Введите новую сложность: ";
			int difficulty;
			getline(cin, temp_cin);
			try
			{
				difficulty = stoi(temp_cin);
			}
			catch (const std::exception&)
			{
				cout << "Неверный ввод" << endl;
				Sleep(500);
				continue;
			}
			if (difficulty < 0 || difficulty > 100) {
				cout << "Сложность должна быть в диапазоне от 0 до 100" << endl;
				Sleep(500);
				continue;
			}
			Q_standart* q_standart = new Q_standart[temp.count_q_standart];
			for (int i = 0; i < temp.count_q_standart; i++) {
				if (i == number - 1) {
					q_standart[i] = Q_standart(question, answer, difficulty);
				}
				else {
					q_standart[i] = temp.q_standart[i];
				}
			}
			temp.q_standart = q_standart;
			break;
		}
		case 3: {
			cout << "Введите номер вопроса для удаления: ";
			int number;
			string temp_cin;
			getline(cin, temp_cin);
			try
			{
				number = stoi(temp_cin);
			}
			catch (const std::exception&)
			{
				cout << "Неверный ввод" << endl;
				Sleep(500);
				continue;
			}
			if (number > temp.count_q_standart || number < 1) {
				cout << "Неверный номер вопроса!" << endl;
				Sleep(500);
				continue;
			}
			Q_standart* q_standart = new Q_standart[temp.count_q_standart - 1];
			int k = 0;
			for (int i = 0; i < temp.count_q_standart; i++) {
				if (i == number - 1) {
					continue;
				}
				q_standart[k] = temp.q_standart[i];
				k++;
			}
			temp.q_standart = q_standart;
			temp.count_q_standart--;
			break;
		}
		case 4: {
			return temp;
		}
		}
	}

}



Test edit_Q_guest(Test temp1) {
	Test temp = temp1;
	while (true) {
		system("cls");
		cout << "=====================" << endl;
		cout << "Вопросы тестового типа: " << endl;
		for (int i = 0; i < temp.count_q_guest; i++) {
			cout << i + 1 << ". " << temp.q_guest[i].question << endl;
		}
		cout << "=====================" << endl;
		cout << "Выберите действие:" << endl;
		cout << "1. Добавить вопрос" << endl;
		if (temp.count_q_guest > 0) {
			cout << "2. Редактировать вопрос" << endl;
			cout << "3. Удалить вопрос" << endl;
		}
		cout << "4. Выйти" << endl;

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
		if (temp.count_q_guest == 0 && (choice == 2 || choice == 3)) {
			cout << "Нет вопросов для редактирования!" << endl;
			Sleep(500);
			continue;
		}
		switch (choice) {
		case 1: {
			cout << "Введите вопрос: ";
			string question;
			getline(cin, question);
			if (question == "") {
				cout << "Вопрос не может быть пустым!" << endl;
				Sleep(500);
				continue;
			}
			cout << "Введите количество вариантов ответа: ";
			int count_answers;
			getline(cin, temp_cin);
			try
			{
				count_answers = stoi(temp_cin);
			}
			catch (const std::exception&)
			{
				cout << "Неверный ввод" << endl;
				Sleep(500);
				continue;
			}
			if (count_answers < 1 || count_answers > 20) {
				cout << "Количество вариантов ответа должно быть в диапазоне от 1 до 20" << endl;
				Sleep(500);
				continue;
			}

			string* answers = new string[count_answers];
			cout << "Введите варианты ответа: " << endl;
			for (int j = 0; j < count_answers; j++) {
				cout << j + 1 << ". ";
				getline(cin, answers[j]);
				if (answers[j] == "") {
					cout << "Ответ не может быть пустым!" << endl;
					Sleep(500);
					j--;
					continue;
				}
			}
			
			cout << "Введите номер правильного ответа: ";
			int right_answer;
			getline(cin, temp_cin);
			try
			{
				right_answer = stoi(temp_cin);
			}
			catch (const std::exception&)
			{
				cout << "Неверный ввод" << endl;
				Sleep(500);
				continue;
			}
			if (right_answer < 1 || right_answer > count_answers) {
				cout << "Неверный номер правильного ответа!" << endl;
				Sleep(500);
				continue;
			}
			cout << "Введите сложность вопроса: ";
			int difficulty;
			getline(cin, temp_cin);
			try
			{
				difficulty = stoi(temp_cin);
			}
			catch (const std::exception&)
			{
				cout << "Неверный ввод" << endl;
				Sleep(500);
				continue;
			}
			if (difficulty < 0 || difficulty > 100) {
				cout << "Сложность должна быть в диапазоне от 0 до 100" << endl;
				Sleep(500);
				continue;
			}
			Q_guest* q_guest = new Q_guest[temp.count_q_guest + 1];
			for (int i = 0; i < temp.count_q_guest; i++) {
				q_guest[i] = temp.q_guest[i];
			}
			q_guest[temp.count_q_guest] = Q_guest(question, answers, count_answers, right_answer, difficulty);
			temp.q_guest = q_guest;
			temp.count_q_guest++;
			break;
		}
		case 2: {
			cout << "Введите номер вопроса для редактирования: ";
			int number;
			getline(cin, temp_cin);
			try
			{
				number = stoi(temp_cin);
			}
			catch (const std::exception&)
			{
				cout << "Неверный ввод" << endl;
				Sleep(500);
				continue;
			}
			if (number > temp.count_q_guest || number < 0) {
				cout << "Неверный номер вопроса!" << endl;
				Sleep(500);
				continue;
			}

			cout << "Введите новый вопрос: ";
			string question;
			getline(cin, question);
			if (question == "")
			{
				cout << "Вопрос не может быть пустым!" << endl;
				Sleep(500);
				continue;
			}
			cout << "Введите количество вариантов ответа: ";
			int count_answers;
			getline(cin, temp_cin);
			try
			{
				count_answers = stoi(temp_cin);
			}
			catch (const std::exception&)
			{
				cout << "Неверный ввод" << endl;
				Sleep(500);
				continue;
			}
			if (count_answers < 1 || count_answers > 20) {
				cout << "Количество вариантов ответа должно быть в диапазоне от 1 до 20" << endl;
				Sleep(500);
				continue;
			}
			string* answers = new string[count_answers];
			cout << "Введите варианты ответа: " << endl;
			for (int j = 0; j < count_answers; j++) {
				cout << j + 1 << ". ";
				getline(cin, answers[j]);
				if (answers[j] == "") {
					cout << "Ответ не может быть пустым!" << endl;
					Sleep(500);
					j--;
					continue;
				}
			}
			cout << "Введите номер правильного ответа: ";
			int right_answer;
			getline(cin, temp_cin);
			try
			{
				right_answer = stoi(temp_cin);
			}
			catch (const std::exception&)
			{
				cout << "Неверный ввод" << endl;
				Sleep(500);
				continue;
			}
			if (right_answer < 1 || right_answer > count_answers) {
				cout << "Неверный номер правильного ответа!" << endl;
				Sleep(500);
				continue;
			}
			cout << "Введите сложность вопроса: ";
			int difficulty;
			getline(cin, temp_cin);
			try
			{
				difficulty = stoi(temp_cin);
			}
			catch (const std::exception&)
			{
				cout << "Неверный ввод" << endl;
				Sleep(500);
				continue;
			}
			if (difficulty < 0 || difficulty > 100) {
				cout << "Сложность должна быть в диапазоне от 0 до 100" << endl;
				Sleep(500);
				continue;
			}
			Q_guest* q_guest = new Q_guest[temp.count_q_guest];
			for (int i = 0; i < temp.count_q_guest; i++) {
				if (i == number - 1) {
					q_guest[i] = Q_guest(question, answers, count_answers, right_answer, difficulty);
				}
				else {
					q_guest[i] = temp.q_guest[i];
				}
			}
			temp.q_guest = q_guest;
			break;
		}
		case 3: {
			cout << "Введите номер вопроса для удаления: ";
			int number;
			string temp_cin;
			getline(cin, temp_cin);
			try
			{
				number = stoi(temp_cin);
			}
			catch (const std::exception&)
			{
				cout << "Неверный ввод" << endl;
				Sleep(500);
				continue;
			}
			if (number > temp.count_q_guest || number < 1) {
				cout << "Неверный номер вопроса!" << endl;
				Sleep(500);
				continue;
			}
			Q_guest* q_guest = new Q_guest[temp.count_q_guest - 1];
			int k = 0;
			for (int i = 0; i < temp.count_q_guest; i++) {
				if (i == number - 1) {
					continue;
				}
				q_guest[k] = temp.q_guest[i];
				k++;
			}
			temp.q_guest = q_guest;
			temp.count_q_guest--;
			break;
		}
		case 4: {
			return temp;
		}
		}
	}
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
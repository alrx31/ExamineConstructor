#include <iostream>


// Модули
#include "Structures.h"
#include "RegisterModule.h"


using namespace std;

int main() {
	cout << "Добро пожаловать в Конструктор экзаменационных билетов!" << endl;
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
			break;
		case 2:
		case 4:
			cout << "До свидания!" << endl;
			break;
	}

	return 0;
}

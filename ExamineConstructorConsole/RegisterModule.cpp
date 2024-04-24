#include <iostream>
#include "Structures.h"
#include "FileModule.h"
#include <string>
#include <windows.h>
using namespace std;

string customHash(const string& input) {
	// Шаг 1: Инициализация начального значения хеша
	unsigned long long hash = 0;

	// Шаг 2: Перемешивание символов входной строки
	for (char c : input) {
		hash ^= static_cast<unsigned long long>(c);
		hash = (hash << 7) | (hash >> 57); // сдвиг влево на 7 бит и сдвиг вправо на 57 бит
		hash += 0xabcdef1234567890; // добавляем произвольное число
	}

	// Шаг 3: Применяем простую хеш-функцию
	hash ^= (hash << 13);
	hash ^= (hash >> 47);
	hash ^= (hash << 23);

	// Шаг 4: Повторяем преобразования несколько раз
	for (int i = 0; i < 10; ++i) {
		hash = ((hash << 5) ^ (hash >> 59)) * 2654435761;
	}

	// Шаг 5: Преобразуем значение хеша в строку и возвращаем
	return to_string(hash);
}

void RegisterModule() {
	while(true){
		system("cls");
		cout << "Регистрация" << endl;
		cout << "Введите логин: ";
		string login;
		cin >> login;
		cout << "Введите пароль: ";
		string password;
		cin.ignore();
		getline(cin, password);
		// Шифрование пароля
		password = customHash(password);

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
		string temp;
		cin.ignore();
		getline(cin, temp);
		try {
			age = stoi(temp);
		}
		catch (exception e) {
			cout << "Неверный ввод" << endl;
			Sleep(1000);
			continue;
		}
		string UserPath = "users/users.txt";
		string UserDataPath = "users/usersData.txt";

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
		Sleep(1000);
		break;
	}

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
		password = customHash(password);

		string UserPath = "users/users.txt";
		string UserDataPath = "users/usersData.txt";

		User user = FindUser(UserPath, login);
		if (password != user.password) {
			cout << "Неверный пароль" << endl;
			Sleep(1000);
			continue;
		}
		else {
			UserData usd = getUserData(user.id, UserDataPath);
			cout << "Вход выполнен" << endl;
			Sleep(1000);
			cout << "Вы вошли как " << usd.name << endl;
			cout << "=========================" << endl;
			return user;
		}
	}

}
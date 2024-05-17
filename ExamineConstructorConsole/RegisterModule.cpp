#include <iostream>
#include "Structures.h"
#include "FileModule.h"
#include <string>
#include <windows.h>
using namespace std;

bool HasSpace(string str) {
	for (int i = 0; i < str.length(); i++)
		if (str[i] == ' ' || str[i] == '\n') return true;
	return false;
}

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
	while (true) {
		system("cls");
		cout << "===========================" << endl;
		cout << "| Регистрация" << endl;
		cout << "| Введите логин: ";
		string login;
		getline(cin, login);
		if (HasSpace(login)) {
			cout << "Логин не должен содержать пробелов" << endl;
			Sleep(1000);
			continue;
		}
		if (login == "") {
			cout << "Логин не может быть пустым" << endl;
			Sleep(1000);
			continue;
		}
		cout << "| Введите пароль: ";
		string password;
		getline(cin, password);
		if (HasSpace(password)) {
			cout << "Пароль не должен содержать пробелов" << endl;
			Sleep(1000);
			continue;
		}
		if (password == "") {
			cout << "Пароль не может быть пустым" << endl;
			Sleep(1000);
			continue;
		}
		cout << "| Введите имя: ";
		string name;
		getline(cin, name);
		if (HasSpace(name)) {
			cout << "Имя не должно содержать пробелов" << endl;
			Sleep(1000);
			continue;
		}
		if (name == "") {
			cout << "Имя не может быть пустым" << endl;
			Sleep(1000);
			continue;
		}
		cout << "| Введите фамилию: ";
		string surname;
		getline(cin, surname);
		if (HasSpace(surname)) {
			cout << "Фамилия не должна содержать пробелов" << endl;
			Sleep(1000);
			continue;
		}
		if (surname == "") {
			cout << "Фамилия не может быть пустой" << endl;
			Sleep(1000);
			continue;
		}
		cout << "| Введите email: ";
		string email;
		getline(cin, email);
		if (HasSpace(email)) {
			cout << "Email не должен содержать пробелов" << endl;
			Sleep(1000);
			continue;
		}
		if (email == "") {
			cout << "Email не может быть пустым" << endl;
			Sleep(1000);
			continue;
		}
		cout << "| Введите возраст: ";
		int age;
		string temp;
		getline(cin, temp);
		try {
			age = stoi(temp);
		}
		catch (exception e) {
			cout << "Неверный ввод" << endl;
			Sleep(1000);
			continue;
		}

		if (age < 0 || age > 120) {
			cout << "Неверный возраст" << endl;
			Sleep(1000);
			continue;
		}

		// Шифрование пароля
		User get_user = FindUser("users/users.txt", login);
		if (get_user.id != -1) {
			cout << "Пользователь с таким логином уже существует" << endl;
			Sleep(1000);
			continue;
		}
		password = customHash(password);

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
		{
			cout << "Успешная регистрация" << endl;

			cout << "                                                                  " << endl;
			cout << "                                                                  " << endl;
			cout << "                                                                  " << endl;
			cout << "                                                                  " << endl;
			cout << "      =======     ||         ||   ||=====\\     ||=======    ||====\\            " << endl;
			cout << "    //            ||         ||   ||      \\\\   ||           ||     \\\\          " << endl;
			cout << "   ||             ||         ||   ||      ||   ||           ||     ||          " << endl;
			cout << "   \\\\             ||         ||   ||      //   ||           ||     //          " << endl;
			cout << "    \\======\\      ||         ||   ||=====/     ||=======    ||====/            " << endl;
			cout << "            \\\\    ||         ||   ||           ||           ||    \\\\          " << endl;
			cout << "            ||    ||         ||   ||           ||           ||     \\\\          " << endl;
			cout << "           //     \\\\        //    ||           ||           ||      \\\\         " << endl;
			cout << "     ======/        \\======/      ||           ||=======    ||       \\\\        " << endl;
			cout << "                                                                  " << endl;
			cout << "                                                                  " << endl;
			cout << "                                                                  " << endl;
			cout << "                                                                  " << endl;

			Sleep(1000);
		}
		else
			cout << "Ошибка в работе в файлами" << endl;
		Sleep(1000);
		break;
	}

}

User Login() {
	while (true) {
		system("cls");
		cout << "===========================" << endl;
		cout << "| Вход                    " << endl;
		string login;
		string password;
		cout << "| Введите логин:";
		getline(cin, login);
		cout << "| Введите пароль: ";
		getline(cin, password);
		if (login == "" || password == "") {
			cout << "| Логин или пароль не могут быть пустыми" << endl;
			Sleep(1000);
			continue;
		}
		if (HasSpace(login) || HasSpace(password)) {
			cout << "| Логин или пароль не могут содержать пробелы" << endl;
			Sleep(1000);
			continue;
		}
		// Шифрование пароля
		password = customHash(password);

		string UserPath = "users/users.txt";
		string UserDataPath = "users/usersData.txt";

		User user = FindUser(UserPath, login);
		if (password != user.password) {
			cout << "| Неверный логин или пароль" << endl;
			Sleep(1000);
			continue;
		}
		else {
			UserData usd = getUserData(user.id, UserDataPath);
			cout << "| Вход выполнен" << endl;
			Sleep(1000);
			return user;
		}
	}

}



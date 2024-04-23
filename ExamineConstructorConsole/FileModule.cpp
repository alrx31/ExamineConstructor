#include <iostream>
#include <string>
#include <fstream>
#include "Structures.h"
#include "ControlTestModule.h"
using namespace std;


// запись в файл пользователя
int WriteToFile(string file_path, User user){
	ofstream file(file_path, ios::app);
	if (!file.is_open()) return 1;

	file << user.id << " " << user.login << " " << user.password << " " << user.ruleLevel << endl;
	return 0;
}
// запись в файл теста
int WriteToFile(string file_path, Test test) {
	ofstream file(file_path,ios::app);
	if (!file.is_open()) return 1;
	file << test.name << endl << test.author<< endl << test.difficulty<< endl << test.isPublic << endl;
	file << test.count_q_standart<< endl;
	for (int i = 0; i < test.count_q_standart; i++) {
		file << test.q_standart[i].question << endl;
		file << test.q_standart[i].answer << endl;
		file << test.q_standart[i].difficulty<< endl;
	}
	file << test.count_q_guest<< endl;
	
	for (int i = 0; i < test.count_q_guest; i++) {
		file << test.q_guest[i].question<< endl;
		file << test.q_guest[i].right_answer<< endl;
		file << test.q_guest[i].count_answers << endl;
		for (int j = 0; j < test.q_guest[i].count_answers; j++) {
			file << test.q_guest[i].answer[j]<< endl;
		}
		file << test.q_guest[i].difficulty << endl;
	}
	file.close();


	return 0;
}
// запись в файл рейтинга
int WriteToFile(string file_pass, string test_name, string user_name, int result,float mark) {
	fstream file(file_pass, ios::in);
	if (!file.is_open()) {
		cout << "Ошибка открытия файла" << endl;
		return 1;
	}
	int count_tests = 0;
	Raiting * raiting = new Raiting[count_tests+1];
	int index = -1;
	while(!file.eof()){
		string temp;
		int count_users;
		file >> temp;
		file >> count_users;
		if(temp == test_name){
			index = count_tests;
		}
		Raiting * temp_raiting = new Raiting(test_name);
		for (int i = 0; i < count_users; i++) {
			string user;
			int result;
			file >> user;
			file >> result;
			temp_raiting->push(user, result, getMark(result));
		}
		// update array

		Raiting* temp_raiting1 = new Raiting[count_tests + 1];
		for (int i = 0; i < count_tests; i++) {
			temp_raiting1[i] = raiting[i];
		}
		raiting = temp_raiting1;
		raiting[count_tests++] = *temp_raiting;
		delete temp_raiting;
		delete[] temp_raiting1;
	}
	file.close();
	if (index == -1) {
		fstream file(file_pass, ios::out | ios::app);
		if(!file.is_open()) return 1;
		file << test_name << endl<< 1<< endl << user_name << endl<< result<<endl;
		file.close();
	}
	else {
		fstream file(file_pass, ios::out | ios::trunc);
		if (!file.is_open()) return 1;
		for (int i = 0; i < count_tests; i++) {
			if (i == index) {
				raiting[i].push(user_name, result, mark);
			}
			file << raiting[i].test_name << endl << raiting[i].count_users << endl;
			Raiting_node * temp = raiting[i].head;
			for(int j = 0; j < raiting[i].count_users; j++){
				file << temp->user_name << endl << temp->result << endl;
				temp = temp->next;
			}
		}
		file.close();
	}



	return 0;
	
}
// запись в файл данных пользователя
int WriteToFile(string file_pass, UserData user) {
	ofstream file(file_pass, ios::app);
	if (!file.is_open()) return 1;

	file << user.id << " " << user.name << " " << user.surname << " " << user.login << " " << user.age << " " << user.count_tests ;
	for (int i = 0; i < user.count_tests; i++) {
		file << "name";
	}
	file << endl;

	return 0;
}

// find user in file (login)
User FindUser(string file_path, string login) {
	ifstream file(file_path);
	if (!file.is_open()) {
		cout << "Ошибка открытия файла" << endl;
		return User();
	}
	User user;
	while (!file.eof()) {
		file >> user.id >> user.login >> user.password >> user.ruleLevel;
		if (user.login == login) {
			file.close();
			return user;
		}
	}
	file.close();
	return User();
}
// find user in file (id)
UserData getUserData(int id,string file_path) {
	ifstream file(file_path);
	if (!file.is_open()) {
		cout << "Ошибка открытия файла" << endl;
		return UserData();
	}
	UserData userData;
	while (!file.eof()) {
		file >> userData.id >> userData.name >> userData.surname >> userData.login >> userData.age >> userData.count_tests;
		if (userData.id == id) {
			file.close();
			return userData;
		}
	}
	return UserData();
}
// find test in file
int getLastId(string path) {
	ifstream file(path);
	if (!file.is_open()) {
		cout << "Ошибка открытия файла" << endl;
		return 0;
	}
	int id = 0;
	User user;
	while (!file.eof()) {
		file >> user.id >> user.login >> user.password >> user.ruleLevel;
		id = user.id;
	}
	return id;
}

//read test from file
TestsContainer* Read(string test_path,bool isPublict,User user) {
	
	
	ifstream file(test_path);
	
	if (!file.is_open()) {
		cout << "Ошибка открытия файла" << endl;
		return nullptr;
	}
	int size = 0;
	Test* tests = new Test[size+1];
	Test temp;
	string name;
	string author;
	string difficulty1;
	int difficulty;
	bool isPublic;
	string temp1;
	int count_q_standart;
	Q_standart* q_standart;

	int count_q_guest;
	Q_guest* q_guest;

	while (!file.eof()) {
		getline(file, name);
		getline(file, author);
		getline(file,difficulty1);
		difficulty = stoi(difficulty1);
		string p;
		getline(file,p);
		if (p == "1") isPublic = true;
		else isPublic = false;
		getline(file, temp1);
		count_q_standart = stoi(temp1);
		q_standart = new Q_standart[count_q_standart];
		for (int i = 0; i < count_q_standart; i++) {
			string question;
			string answer;
			int difficulty;
			getline(file, question);
			getline(file,answer);
			getline(file, temp1);
			difficulty = stoi(temp1);
			q_standart[i] = Q_standart(question, answer, difficulty);
		}
		getline(file, temp1);
		count_q_guest = stoi(temp1);
		q_guest = new Q_guest[count_q_guest];
		for (int i = 0; i < count_q_guest; i++) {
			string question;
			int right_answer;
			int count_answers;
			int difficulty;
			getline(file, question);
			getline(file, temp1);
			right_answer = stoi(temp1);
			getline(file, temp1);
			count_answers = stoi(temp1);
			string* answers = new string[count_answers];
			for (int j = 0; j < count_answers; j++) {
				getline(file, answers[j]);
			}
			getline(file, temp1);
			difficulty = stoi(temp1);
			q_guest[i] = Q_guest(question, answers, count_answers, right_answer, difficulty);
		}
		temp = Test(name, author, isPublic, difficulty, count_q_standart, q_standart, count_q_guest, q_guest);
		tests[size++] = temp;
		// update array
		Test* temp_tests = new Test[size + 1];
		for (int i = 0; i < size; i++) {
			temp_tests[i] = tests[i];
		}
		delete[] tests;
		tests = temp_tests;

	}
	file.close();
	return new TestsContainer(tests,size-1);

}
//read raiting from file
Raiting* Read(string test_path, Test* test, User* user) {
	
	Raiting* raiting = new Raiting();

	fstream file(test_path, ios::in);
	if (!file.is_open()) {
		cout << "Ошибка открытия файла рейтинга" << endl;
		return raiting;
	}

	string test_name;
	int count_user;
	string user_name;
	int result;

	while (!file.eof()) {
		file >> test_name >> count_user;


		raiting = new Raiting(test_name);
		for (int i = 0; i < count_user; i++) {
			file >> user_name >> result;
			raiting->push(user_name, result, getMark(result));
		}
		if(test_name == test->name) break;
	}

	file.close();
	return raiting;
}

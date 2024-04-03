#include "Structures.h"
#include <string>
#include <iostream>
using namespace std;


Q_guest::Q_guest() {}
Q_guest::Q_guest(string question, string* answer,int count_answers, int right_answer, int difficulty) {
	this->question = question;
	this->answer = answer;
	this->count_answers = count_answers;
	this->right_answer = right_answer;
	this->difficulty = difficulty;
}

Q_standart::Q_standart() {}
Q_standart::Q_standart(string question, string answer, int difficulty) {
	this->question = question;
	this->answer = answer;
	this->difficulty = difficulty;
};



Test::Test() {}
Test::Test(int size) {
	this->count_q_standart = size;
	this->q_standart = new Q_standart[size];
	this->count_q_guest = size;
	this->q_guest = new Q_guest[size];
	this->isPublic = false;
	this->difficulty = 0;
	this->name = "";
	this->author = "";
}

Test::Test(string name, string author, bool isPublic, int difficulty, int count_q_standart, Q_standart* q_standart, int count_q_guest, Q_guest* q_guest) {
    this->name = name;
    this->author = author;
    this->isPublic = isPublic;
    this->difficulty = difficulty;
    this->count_q_standart = count_q_standart;
    this->q_standart = q_standart;
    this->count_q_guest = count_q_guest;
    this->q_guest = q_guest;
}
User::User() { this->ruleLevel = 0; }
User::User(string login, string password, int ruleLevel) {
	this->login = login;
	this->password = password;
	this->ruleLevel = ruleLevel;
	this->id = ++count_users;
}

int User::count_users = 0;
UserData::UserData() {}
UserData::UserData(string name, string login, string surname, string email ,int age) {
	this->name = name;
	this->surname = surname;
	this->login = login;
	this->age = age;
	this->email = email;
	this->count_tests = 0;
	this->tests = new Test[count_tests];
	this->id = User::count_users;
}
void UserData::addtest(Test test) {
	tests[this->count_tests++] = test;
};

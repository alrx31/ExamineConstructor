#include "Structures.h"
#include <string>
#include <iostream>
using namespace std;


Q_guest::Q_guest() {
	this->question = "";
	this->answer = new string[0];
	this->count_answers = 0;
	this->right_answer = 0;
	this->difficulty = 0;
}
Q_guest::Q_guest(string question, string* answer,int count_answers, int right_answer, int difficulty) {
	this->question = question;
	this->answer = answer;
	this->count_answers = count_answers;
	this->right_answer = right_answer;
	this->difficulty = difficulty;
}

Q_standart::Q_standart() {
	this->question = "";
	this->answer = "";
	this->difficulty = 0;
}
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
User::User() { 
	this->ruleLevel = 0;
	this->login = "";
	this->password = "";
	this->id = -1;
}
User::User(string login, string password, int ruleLevel) {
	this->login = login;
	this->password = password;
	this->ruleLevel = ruleLevel;
	this->id = ++count_users;
}

int User::count_users = 0;
UserData::UserData() {
	this->name = "";
	this->surname = "";
	this->login = "";
	this->age = 0;
	this->email = "";
	this->count_tests = 0;
	this->tests = new Test[count_tests];
	this->id = User::count_users;
}
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


Raiting::Raiting() {}
Raiting::Raiting(Test* test) {
	this->test = test;
	this->count_users = 0;
	this->middle_result = 0;
	this->head = nullptr;
}
<<<<<<< HEAD
void Raiting::push(string user_name, int mark, int result) {
	Raiting_node * new_node = new Raiting_node(user_name, mark, result, head);
=======
void Raiting::push(User* user, int mark, int result) {
	Raiting_node * new_node = new Raiting_node(user, mark, result, head);
>>>>>>> df5a272 (b)
	this->head = new_node;
	this->count_users++;
	this->middle_result = (middle_result*(count_users-1) + result) / count_users;
}

void Raiting::swap(Raiting_node* prev, Raiting_node* curr, Raiting_node* next, Raiting_node* H) {
	if (curr != nullptr && next != nullptr && curr->result < next->result) {
		if (prev == nullptr) {
			Raiting_node* temp = curr;
			curr->next = next->next;
			next->next = temp;
			head = next;
		}
		else {
			Raiting_node* temp = curr;
			prev->next = curr->next;
			temp->next = temp->next->next;
			prev->next->next = temp;
		}
	}
	else {
		return;
	}

}
// шейкерная сортировка
void Raiting::BubleSort() {
	if (head == nullptr) return;
	Raiting_node* prev;
	Raiting_node* curr;

	for (int i = 0; i < count_users; i++) {
		prev = nullptr;
		curr = head;

		for (int j = 0; j < count_users; j++) {
			if (curr == nullptr) break;
			swap(prev, curr, curr->next, head);
			prev = curr;
			curr = curr->next;
		}

		for(int j = count_users; j > 0; j--) {
			if (curr == nullptr) break;
			swap(prev, curr, curr->next, head);
			prev = curr;
			curr = curr->next;
		}
	}
}


Raiting_node::Raiting_node() {}
<<<<<<< HEAD
Raiting_node::Raiting_node(string user_name, int mark , int reuslt, Raiting_node *next) {
	this->user_name = user_name;
=======
Raiting_node::Raiting_node(User* user, int mark , int reuslt, Raiting_node *next) {
	this->user = user;
>>>>>>> df5a272 (b)
	this->mark = mark;
	this->result = reuslt;
	this->next = next;
}




TestsContainer::TestsContainer() {}
TestsContainer::TestsContainer(Test* tests, int size) {
	this->tests = tests;
	this->count_tests = size;
}


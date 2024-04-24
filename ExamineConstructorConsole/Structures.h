// Structures.h

#pragma once

#include <string>
using namespace std;
#include <iostream>

// type of questions
class Q_standart {
public:
    string question;
    string answer;
    int difficulty;
    Q_standart();
    Q_standart(string question, string answer, int difficulty);
};

class Q_guest {
public:
    string question;
    string* answer;
    int count_answers;
    int right_answer;
    int difficulty;
    Q_guest();
    Q_guest(string question, string* answer,int count_answers, int right_answer, int difficulty);
};

class Test {
public:
    string name;
    string author;
    int difficulty;
    bool isPublic;

    int count_q_standart;
    Q_standart* q_standart;

    int count_q_guest;
    Q_guest* q_guest;

    Test();
    Test(int size);
    Test(string name, string author, bool isPublic, int difficulty, int count_q_standart, Q_standart* q_standart, int count_q_guest, Q_guest* q_guest);

};

class User {
public:
    int id;
    string login;
    string password;
    int ruleLevel;
    static int count_users;
    User();
    User(string login, string password, int ruleLevel);
    
};

class UserData{
    
public:
    int id;
    string name;
    string surname;
    string login;
    int age;
    string email;

    Test* tests;
    int count_tests;
    UserData();
    UserData(string name, string login, string surname, string email, int age);
    void addtest(Test test);
};

class Bilet {
    string name;
    string theme;
    string author;
    string viewer;
    string date;
    string difficulty;
    int id;

    int count_q_standart;
    Q_standart* q_standart;

    int count_q_guest;
    Q_guest* q_guest;
};

// Definition of BiletsContainer is moved here
class BiletsContainer {
    Bilet* bilets;
    int count_bilets;
};

class Raiting_node {
public:
    string user_name;
    int mark;
    int result;
    Raiting_node* next;
    Raiting_node();
    Raiting_node(string user_name, int result, int mark);
    Raiting_node(string user_name, int mark, int result, Raiting_node* node);
};
    
class Raiting {
public:
    string test_name;
    int count_users;
    Raiting_node* head;
    int middle_result;
    Raiting();
    Raiting(string test_name);
    void push(string user_name, int mark, int result);
    void BubleSort();
    void swap(Raiting_node* prev, Raiting_node* curr, Raiting_node* next, Raiting_node* H);
    void print();
};

class RaitingFileModule {
public:
    string user_name;
    int result;
    RaitingFileModule();
    RaitingFileModule(string user_name, int result);
};



class TestsContainer {
public:
    Test* tests;
	int count_tests;
    TestsContainer();
    TestsContainer(Test* tests, int size);
};
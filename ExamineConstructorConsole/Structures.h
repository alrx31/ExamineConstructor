// Structures.h

#pragma once

#include <string>
using namespace std;
#include <iostream>

// type of questions
class Q_standart {
    string question;
    string answer;
    int difficulty;
public:
    Q_standart();
};

class Q_guest {
    string question;
    string* answer;
    int right_answer;
    int difficulty;
public:
    Q_guest();
};

class Test {
    string name;
    string author;
    int difficulty;
    bool isPublic;

    int count_q_standart;
    Q_standart* q_standart;

    int count_q_guest;
    Q_guest* q_guest;

public:
    Test();
    Test(int size);
    Test(string name, string author, bool isPublic, int difficulty, int count_q_standart, Q_standart* q_standart, int count_q_guest, Q_guest* q_guest);

};

class User {
    int id;
    string login;
    string password;
    int ruleLevel;
public:
    static int count_users;
    User();
    User(string login, string password, int ruleLevel);
};

class UserData {
    int id;
    string name;
    string surname;
    string login;
    int age;
    string email;

    Test* tests;
    int count_tests;

public:
    UserData();
    UserData(string name, string login, string surname, string email, int age);
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

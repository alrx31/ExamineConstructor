#pragma once
#include "Structures.h"
#include <iostream>

void PersonUI( User user);
void GuestUI(User user);
void AdminUI(User user);

void CreateTest(UserData user);
int startTest(Test test);
float getMark(int result);

void ShowTest(Test test);
void ShowTests(TestsContainer* tests);
void showTestMenu(Test test);
void showReiting(Raiting* raiting);

Test* sortTests(Test* tests,int size, int choice);
Test* merge(Test* left, Test* right, int l, int r, int choice);


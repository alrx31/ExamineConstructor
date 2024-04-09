#pragma once
#include "Structures.h"
#include <iostream>

void PersonUI( User user);
void GuestUI(User user);

void CreateTest(UserData user);
void ShowTest(Test test);
void ShowTests(Test* tests);
int startTest(Test test);
void showTestMenu(Test test);
float getMark(int result);


Test* sortTests(Test* tests,int size, int choice);
Test* merge(Test* left, Test* right, int l, int r, int choice);
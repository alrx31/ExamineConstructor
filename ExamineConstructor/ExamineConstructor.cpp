#include <iostream>
#include <fstream>

using namespace std;

class User {
private:
	string name;
	string login;
	string password;
public:
	User(){
		name = "Guest";
		login = "guest";
		password = "guest";
	}
	User(string name, string login, string password) {
		this->name = name;
		this->login = login;
		this->password = password;
	}
	string getName() {
		return name;
	}
	string getLogin() {
		return login;
	}
	string getPassword() {
		return password;
	}
	void setName(string name) {
		this->name = name;
	}
	void setLogin(string login) {
		this->login = login;
	}
	void setPassword(string password) {
		this->password = password;
	}
	void print() {
		cout << "Name: " << name << endl;
		cout << "Login: " << login << endl;
		cout << "Password: " << password << endl;
	}
};

class UserList {
private:
	User* users;
	int size;
public:
	UserList() {
		users = new User[10];
		size = 0;
	}
	~UserList() {
		delete[] users;
	}
	void addUser(User user) {
		users[size] = user;
		size++;
	}
	void print() {
		for (int i = 0; i < size; i++) {
			users[i].print();
		}
	}
	int getSize() {
		return size;
	}
	User* getUsers() {
		return users;
	}
};





//get all users from file and add them to the 

UserList getUsersFromFile() {
	UserList userList;
	ifstream file("./users/users.txt");
	string name;
	string login;
	string password;
	while (file >> name >> login >> password) {
		userList.addUser(User(name, login, password));
	}
	file.close();
	return userList;
}




class QuestionStandart {
	string question;
	string* answers;
	string comment;
public:
	QuestionStandart() {}
	QuestionStandart(string question, string* answers, string comment) {
		this->question = question;
		this->answers = answers;
		this->comment = comment;
	}
	void Print() {
		cout << question << endl;
		for (int i = 0; i < 4; i++) {
			cout << i + 1 << ". " << answers[i] << endl;
		}
	}
	string getQuestion() {
		return question;
	}
	string getAnswers() {
		return answers[0];
	}
	string getComment() {
		return comment;
	}


};


class QuestionTypeGuest {
	string question;
	string* answers;
	int rightAnswer;
	string comment;
public:
	QuestionTypeGuest() {}
	QuestionTypeGuest(string question, string* answers, int rightAnswer, string comment) {
		this->question = question;
		this->answers = answers;
		this->rightAnswer = rightAnswer;
		this->comment = comment;
	}
	void Print() {
		cout << question << endl;
		for (int i = 0; i < 4; i++) {
			cout << i + 1 << ". " << answers[i] << endl;
		}
	}
	string getQuestion() {
		return question;
	}
	string* getAnswers() {
		return answers;
	}

	string getRightAnswer() {
		return answers[rightAnswer];
	}
	string getComment() {
		return comment;
	}

};



class Test {
	string name;
	string description;
	string author;


	QuestionStandart* questionsStandart;
	QuestionTypeGuest* questionsTypeGuest;
	int sizeStandart;
	int sizeTypeGuest;
public:
	Test() {}
	Test(string name, string description, string author) {
		this->name = name;
		this->description = description;
		this->author = author;
		questionsStandart = new QuestionStandart[10];
		questionsTypeGuest = new QuestionTypeGuest[10];
		sizeStandart = 0;
		sizeTypeGuest = 0;
	}
	Test(string name, string description, string author, QuestionStandart* questionsStandart, QuestionTypeGuest* questionsTypeGuest, int sizeStandart, int sizeTypeGuest) {
		this->name = name;
		this->description = description;
		this->author = author;
		this->questionsStandart = questionsStandart;
		this->questionsTypeGuest = questionsTypeGuest;
		this->sizeStandart = sizeStandart;
		this->sizeTypeGuest = sizeTypeGuest;
	}

	QuestionStandart* getQuestionsStandart() {
		return questionsStandart;
	}
	QuestionTypeGuest* getQuestionsTypeGuest() {
		return questionsTypeGuest;
	}
	int getSizeStandart() {
		return sizeStandart;
	}
	int getSizeTypeGuest() {
		return sizeTypeGuest;
	}
	void addQuestionsStandart(QuestionStandart * question, int size) {
		questionsStandart = question;
		this->sizeStandart = size;
	}
	void addQuestionsTypeGuest(QuestionTypeGuest* question, int size) {
		questionsTypeGuest = question;
		this->sizeTypeGuest = size;
	}
	void Print() {
		cout << "Name: " << name << endl;
		cout << "Description: " << description << endl;
		cout << "Author: " << author << endl;
		cout << "Questions Standart: " << endl;
		for (int i = 0; i < sizeStandart; i++) {
			questionsStandart[i].Print();
		}
		cout << "Questions Type Guest: " << endl;
		for (int i = 0; i < sizeTypeGuest; i++) {
			questionsTypeGuest[i].Print();
		}
	}
};


class TestsContainer {
	Test* tests;
	int size;
public:
	TestsContainer() {
		tests = new Test[10];
		size = 0;
	}
	TestContainer(Test* tests, int size) {
		this->tests = tests;
		this->size = size;
	}
	~TestsContainer() {
		delete[] tests;
	}
	void addTest(Test test) {
		tests[size] = test;
		size++;
	}
	void print() {
		for (int i = 0; i < size; i++) {
			tests[i].Print();
		}
	}
	int getSize() {
		return size;
	}
	Test* getTests() {
		return tests;
	}
	Test getTest(int index) {
		return tests[index];
	}

};


// 1 - guest
// 2 - user
// 3 - admin
int getChoice(int leverOfRule) {
	
}




// get all public tests from file
Test* GetPublicTests() {
	
}
int main() {
	UserList userList = getUsersFromFile();
	
	int ruleLevel = 0;

	while (true) {
		cout << "Enter a number for your choice: \n 1 - Test yourself as guest \n 2 - Login \n 3 - Register \n 4 - Exit" << endl;
		int choice;
		cin >> choice;
		string password;
		string name;
		string login;
		User guest;

		switch (choice) {
		case 1:
			guest.print();
			ruleLevel = 1;
			break;
		case 2:
			cout << "Enter your login: ";
			cin >> login;
			cout << "Enter your password: ";
			cin >> password;
			for (int i = 0; i < userList.getSize(); i++) {
				if (userList.getUsers()[i].getLogin() == login && userList.getUsers()[i].getPassword() == password) {
					cout << "You have been logged in as " << userList.getUsers()[i].getName() << endl;
					if (userList.getUsers()[i].getName() == "admin") {
						ruleLevel = 3;
						break;
					}
					ruleLevel = 2;
					break;
				}
				else {
					cout << "Invalid login or password\n" << endl;
				}
			}
			break;
		case 3:
			cout << "Enter your name: ";
			cin >> name;
			cout << "Enter your login: ";
			cin >> login;
			cout << "Enter your password: ";
			cin >> password;
			userList.addUser(User(name, login, password));
			cout << "You have been registered \n Try to login\n" << endl;
			continue;
		case 4:
			return;
		default:
			cout << "Invalid choice" << endl;
			continue;
		}
	}
	cout << "=========================================" << endl;


	switch (ruleLevel) {
	case 0:
		cout << "You are not logged in" << endl;
		break;
	case 1:
		cout << "You are logged in as guest" << endl;
		cout << "Choice your Test from public tests" << endl;
		int testChoice = getChoice();

		break;
	case 2:
		cout << "You are logged in as user" << endl;
		cout << "Choice your Test from public tests" << endl;
		int testChoice = getChoice();
		break;
	}
	case 3:
		cout << "You are logged in as admin" << endl;
		cout << "Choice your Test from public tests" << endl;
		int testChoice = getChoice();
		break;
	}


	


	return 0;
}




#include <iostream>
#include <fstream>
#include <string>

using namespace std;


// is the array has the element
bool isHas(string* arr, string an) {
	for (int i = 0; i < 4; i++) {
		if (arr[i] == an) return true;
	}
	return false;
}


string Encrypt(string s) {
	string special = ",./<>?[]{}\|!@#$%^&*()_-=+;':\"`~";
	string alphabet_en = "qwertyuiopasdfghjklzxcvbnm";
	string alphabet_ru = "йцукенгшщзхъфывапролджэячсмитьбю";

	return s;
}


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
	User getUserByIndex(int index) {
		return users[index];
	}
};



// types of questions
class QuestionStandart {
	string question;
	string* answers;
	string comment;
	int difficulty;
public:
	QuestionStandart() {}
	QuestionStandart(string question, string* answers, string comment, int difficulty) {
		this->question = question;
		this->answers = answers;
		this->comment = comment;
		this->difficulty = difficulty;
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
	string getAnswer() {
		return answers[0];
	}
	string getComment() {
		return comment;
	}
	int getDifficulty(){
		return difficulty;
	}



};
class QuestionTypeGuest {
	string question;
	string* answers;
	int rightAnswer;
	string comment;
	int difficulty;
public:
	QuestionTypeGuest() {}
	QuestionTypeGuest(string question, string* answers, int rightAnswer, string comment, int difficulty) {
		this->question = question;
		this->answers = answers;
		this->rightAnswer = rightAnswer;
		this->comment = comment;
		this->difficulty = difficulty;
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
	int getDifficulty() {
		return difficulty;
	}

};


// test
class Test {
	string name;
	string description;
	string author;
	bool isPublic;

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
		isPublic = false;
	}
	Test(string name, string description, string author, QuestionStandart* questionsStandart, QuestionTypeGuest* questionsTypeGuest, int sizeStandart, int sizeTypeGuest, bool isPublic) {
		this->name = name;
		this->description = description;
		this->author = author;
		this->questionsStandart = questionsStandart;
		this->questionsTypeGuest = questionsTypeGuest;
		this->sizeStandart = sizeStandart;
		this->sizeTypeGuest = sizeTypeGuest;
		this->isPublic = isPublic;
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
	string getName() {
		return name;
	}
	string getDescription() {
		return description;
	}
	string getAuthor() {
		return author;
	}
	bool getIsPublic() {
		return isPublic;
	}
	void setIsPublic(bool isPublic) {
		this->isPublic = isPublic;
	}

	int Play() {
		int reting = 0;
		int index_question = 1;
		cout << "Start test: " << name;
		for (int i = 0; i < sizeStandart; i++) {
			cout << "Question " << index_question << " : " << endl;
			cout << questionsStandart[i].getQuestion() << endl;
			for (int j = 0; j < 4; j++) {
				cout << j << ". " << questionsStandart[i].getAnswers()[j];
			}
			cout << "Your answer: ";
			string answer;
			cin >> answer;

			if (isHas(questionsStandart[i].getAnswers(), answer)) {
				reting += questionsStandart[i].getDifficulty();
			}

		}
		cout << "==========================================";
		return reting;
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
	TestsContainer(Test* tests, int size) {
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
	void PrintNames() {
		for (int i = 0; i < size; i++) {
			cout << i + 1 << ". " << tests[i].getName() << endl;
		}
	}

};


// get all public tests from file
TestsContainer getAllPublicTests() {
	TestsContainer testsContainer;
	ifstream file("./tests/publicTests.txt");
	cout << "File try to open" << endl;
	cout << "File is Open" << endl;
	string name, description, author, isPublic;
	int num_of_q_standart, num_of_q_guest, diff, right_q;
	QuestionStandart* questionsStandart;
	QuestionTypeGuest* questionsTypeGuest;
	string question, answer1, answer2, answer3, answer4, comment;
	
	while (file >> name >> description >> author >> isPublic >> num_of_q_standart >> num_of_q_guest) {
		cout << name << " " << description << " " << author <<" " << isPublic << " " << num_of_q_standart << " " << num_of_q_guest << endl;
		questionsStandart = new QuestionStandart[num_of_q_standart];
		questionsTypeGuest = new QuestionTypeGuest[num_of_q_guest];
		for (int i = 0; i < num_of_q_standart; i++) {
			file >> question >> answer1 >> answer2 >> answer3 >> answer4>> comment >> diff;
			questionsStandart[i] = QuestionStandart(question, new string[4]{ answer1, answer2, answer3, answer4 }, comment, diff);
			cout << question << " " << answer1 << " " << answer2 << " " << answer3 << " " << answer4 << " " << comment << " " << diff << endl;
		}
		for (int i = 0; i < num_of_q_guest;i++) {
			file >> question >> answer1 >> answer2 >> answer3 >> answer4 >>right_q>> comment >> diff;
			questionsTypeGuest[i] = QuestionTypeGuest(question, new string[4]{ answer1, answer2, answer3, answer4 }, right_q, comment, diff);
			cout << question << " " << answer1 << " " << answer2 << " " << answer3 << " " << answer4 << " " << right_q << " " << comment << " " << diff << endl;
		}
	}


	file.close();
	return testsContainer;

}

//
//1
//0
//AreYouAMan
//Yes
//Yes
//Yes
//No
//PiPipi
//10
// 1 - guest
// 2 - user
// 3 - admin
int getChoice(int leverOfRule, TestsContainer& testsContainer) {
	
	switch (leverOfRule) {
	case 1:
		testsContainer.PrintNames();
		int choice;
		cout << endl << endl << "Enter the number of the test you want" << endl;

		for (int i = 0; i < testsContainer.getSize(); i++) {
			cout << i + 1 << ".  - " << testsContainer.getTest(i).getName() << endl;
		}
		cin >> choice;

		return choice;
		break;
	default:
		return 0;
		break;
	}
}
void StartTest(int choice, TestsContainer testsContainer) {
	int raiting = 0;
	Test current_test = testsContainer.getTest(choice);
	raiting = current_test.Play();
	cout << "You are passed the Test : " << current_test.getName() << endl;
	cout << "With finish score: " << raiting;
	return;
}



// get all public tests from file
//Test* GetPublicTests() {
//	
//}
int main() {
	setlocale(LC_ALL, "Russian");
	cout << " Привет мир!!";
	string p;
	cin >> p;
	cout << p;
	return 0;
}
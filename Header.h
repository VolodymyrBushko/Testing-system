#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <fstream>
#include <cstdio>
using namespace std;

class Question;
class Test;
class Subject;
class Testing;

////////////////////////////////////////////////////////////////////////////////
class Account
{
protected:
	string login, password, pathTests = "_tests.txt";
	string name, mail; int number;
	fstream file; string path;
	void SetDataInRegister(string name, string mail, int number, string login, string password);
	bool CheckFile(string name);
	bool CorrectData(string loginTmp, string passwordTmp, string login, string password);
	string Encryption(string value);
	string Decryption(string value);
public:
	int Register(string name, string mail, int number, string login, string password);
	bool Enter(string login, string password);
};
////////////////////////////////////////////////////////////////////////////////
class User :public Account
{
public:
	void StartTest(Testing& test, string nameCategory, string nameTest);
	void ShowTests();
	void Menu();
};
////////////////////////////////////////////////////////////////////////////////
class Admin :public Account
{
	string pathUsers = "_users.txt";
	string ReadWithFile();
public:
	void RegisterUser(string name, string mail, int number, string login, string password);
	void DeleteUser(string loginUser);
	void EditDataOfUser(string name, string mail, int number, string login, string newLogin, string password);
	void ShowTestsUser(string login, string password);
	void ShowTestByCategory(string nameCategory);
	void ShowAllTests();
	void PushCategory(Testing& testing, string nameCategory);
	void PushTestInCategory(Testing& testing, string nameCategory, string nameTest);
	void PushQuestionInTest(Testing& testing, string nameCategory, string nameTest, string question, string answer);
	void Menu();
};
////////////////////////////////////////////////////////////////////////////////
class Testing
{
	string nameCategory, nameTest;
	vector<Subject> categories;
public:
	Testing() {}
	Testing(string nameCategory, string nameTest);
	void PushCategory(Subject value);
	void PushTestInCategory(string nameCategory,Test value);
	void PushQuestionInTest(string nameCategory, string nameTest, Question value);
	void ShowData();
	int GetCheck(string nameCategory, string nameTest);
	int StartTest(string nameCategory, string nameTest);
};
//
class Subject
{
	string name;
	vector<Test> tests;
public:
	Subject(string name);
	void PushTest(Test value);
	void PushQuestion(string nameTest, Question value);
	void ShowData();
	string GetName();
	int GetSizeTest();
	vector<Test>::iterator FindTest(string nameTest);
	int GetCheck(string nameTest);
	int StartTest(string nameTest);
};
//
class Test
{
	string name;
	int position, check, counter;
	vector<Question> tests;
public:
	Test();
	Test(string name);
	void PushQuestion(Question value);
	void ShowData();
	void SetCheck(int check);
	string GetName();
	int GetCheck();
	int GetPosition();
	int GetSizeTest();
	int StartTest();
	int CheckStop(int check);
};
//
class Question
{
	string question, answer;
public:
	Question(string question, string answer);
	void SetData(string question, string answer);
	void ShowData();
	bool GiveAnswer(string answer);
	string GetQuestion() { return question; }
	string GetAnswer() { return answer; }
};
////////////////////////////////////////////////////////////////////////////////
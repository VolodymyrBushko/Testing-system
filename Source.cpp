#include "Header.h"
//CLASS Admin
////////////////////////////////////////////////////////////////////////////////
void Admin::RegisterUser(string name, string mail, int number, string login, string password)
{
	User newUser;
	file.open(pathUsers, fstream::app);
	if (newUser.Register(name, mail, number, login, password) != -1)
		file << Encryption(login) << "\n";
	file.close();
}
void Admin::ShowTestByCategory(string nameCategory)
{
	string tmp;
	file.open(pathTests);
	while (file >> tmp)
	{
		if (tmp == nameCategory)
		{
			cout << tmp << "\t";
			file >> tmp;
			cout << tmp << "\n";
		}
		else
			file >> tmp;
	}
	file.close();
}
void Admin::PushCategory(Testing& testing, string nameCategory)
{
	testing.PushCategory(Subject(nameCategory));
}
void Admin::PushTestInCategory(Testing& testing, string nameCategory, string nameTest)
{
	testing.PushTestInCategory(nameCategory, Test(nameTest));
}
void Admin::PushQuestionInTest(Testing& testing, string nameCategory, string nameTest, string question, string answer)
{
	testing.PushQuestionInTest(nameCategory, nameTest, Question(question, answer));
}
void Admin::ShowAllTests()
{
	string tmp;
	file.open(pathTests);
	while (file >> tmp)
	{
		cout << tmp << "\t";
		file >> tmp;
		cout << tmp << "\n";
	}
	file.close();
}
void Admin::EditDataOfUser(string name, string mail, int number, string login, string newLogin, string newPassword)
{
	DeleteUser(login);
	RegisterUser(name, mail, number, newLogin, newPassword);
}
void Admin::ShowTestsUser(string login, string password)
{
	User user;
	if (user.Enter(login, password) == 1)
		user.ShowTests();
}
string Admin::ReadWithFile()
{
	string tmp, returnStr;
	file.open(pathUsers);
	while (getline(file, tmp))
	{
		returnStr += Decryption(tmp);
		returnStr += ' ';
	}
	file.close();
	return returnStr;
}
void Admin::DeleteUser(string loginUser)
{
	string data, tmp; ofstream clear;
	int posB = 0, posE = 0;
	data = ReadWithFile();
	posB = posE = data.find(loginUser);
	while (data[posE++] != ' ') {}
	data.erase(posB, posE - posB);
	clear.open(pathUsers, ofstream::trunc);
	clear.close();
	file.open(pathUsers);
	for (int i = 0; i < data.size(); ++i)
	{
		if (data[i] != ' ')
			tmp += data[i];
		else
		{
			file << Encryption(tmp);
			file << '\n';
			tmp = "";
		}
	}
	file.close();
	loginUser += ".txt";
	remove(loginUser.c_str());
}
void Admin::Menu()
{
	cout << "\n\n\n0) ¬ихiд."
		<< "\n1) ƒодати предметну область."
		<< "\n2) ƒодати тест в предметну область."
		<< "\n3) ƒодати питанн¤ в тест."
		<< "\n4) ƒодати тестера."
		<< "\n5) ¬идалити тестера."
		<< "\n6) «мiнити данi тестера."
		<< "\n7) ѕерегл¤нути всi результати тест≥в."
		<< "\n8) ѕерегл¤нути результати по конкретнiй областi."
		<< "\n9) ѕерегл¤нути результати окремого тестера.\n\n\n"
		;
}
//CLASS User
////////////////////////////////////////////////////////////////////////////////
void User::StartTest(Testing& test, string nameCategory, string nameTest)
{
	int tmpInt;
	file.open(path, fstream::app);
	tmpInt = test.StartTest(nameCategory, nameTest);
	if (tmpInt != -1)
		file << "\n" << nameCategory << "\t" << tmpInt;
	file.close();
	file.open(pathTests, fstream::app);
	if (tmpInt != -1)
		file << "\n" << nameCategory << "\t" << tmpInt;
	file.close();
}
void User::ShowTests()
{
	string tmp; int i = 0;
	this->path += this->login;
	file.open(path);
	while (getline(file, tmp))
	{
		if (i > 1)
			cout << tmp << "\n";
		i++;
	}
	file.close();
}
void User::Menu()
{
	cout << "\n\n\n0) ¬ихiд."
		<<"\n1) ѕройти тест."
		<<"\n2) ѕодивитис¤ результати своiх тестувань."
		;
}
//CLASS Account
////////////////////////////////////////////////////////////////////////////////
void Account::SetDataInRegister(string name, string mail, int number, string login, string password)
{
	this->name = name;
	this->mail = mail;
	this->number = number;
	this->login = login;
	this->password = password;
}
bool Account::CheckFile(string login)
{
	path = login + ".txt";
	file.open(path);
	if (file.is_open())
	{
		file.close();
		return 1;
	}
	file.close();
	return 0;
}
int Account::Register(string name, string mail, int number, string login, string password)
{
	if (CheckFile(login))
	{
		cout << "\n“акий аккаунт вже зареЇстрований.\n";
		system("pause");
		return -1;
	}
	SetDataInRegister(name, mail, number, login, password);
	file.open(path, fstream::app);
	file << Encryption(login) << "\t" << Encryption(password) << "\n" << name << "\t" << mail << "\t" << number << "\n";
	file.close();
	return 0;
}
bool Account::CorrectData(string loginTmp, string passwordTmp, string login, string password)
{
	return (login == loginTmp) && (password == passwordTmp);
}
bool Account::Enter(string login, string password)
{
	path += login;
	path += ".txt";
	string loginTmp, passwordTmp;
	if (!CheckFile(login))
	{
		cout << "\n“акого аккаунта немаЇ.\n";
		system("pause");
		return 0;
	}
	file.open(path);
	file >> loginTmp;
	file >> passwordTmp;
	if (CorrectData(Decryption(loginTmp), Decryption(passwordTmp), login, password))
	{
		file.close();
		cout << "\n¬и успiшно увiйшли.\n";
		return 1;
	}
	file.close();
	cout << "\nЌекоректнi данi.\n";
	return 0;
}
string Account::Encryption(string value)
{
	string tmp, returnStr; int tmpInt;
	for (int i = 0; i < value.size(); ++i)
	{
		tmp += value[i];
		tmp += '-';
	}
	for (int i = 0; i < tmp.size(); ++i)
	{
		if (tmp[i] != '-')
		{
			tmpInt = tmp[i];
			returnStr += to_string(tmpInt);
		}
		else
			returnStr += tmp[i];
	}
	reverse(begin(value), end(value));
	return returnStr;
}
string Account::Decryption(string value)
{
	string returnStr, tmp; int tmpInt;
	for (int i = 0; i < value.size(); ++i)
	{
		if (value[i] != '-')
			tmp += value[i];
		else
		{
			tmpInt = atoi(tmp.c_str());
			returnStr += tmpInt;
			tmp = "";
		}
	}
	return returnStr;
}
//CLASS Testing
////////////////////////////////////////////////////////////////////////////////
Testing::Testing(string nameCategory, string nameTest)
{
	this->nameCategory = nameCategory;
	this->nameTest = nameTest;
}
void Testing::PushCategory(Subject value)
{
	categories.push_back(value);
}
void Testing::ShowData()
{
	for_each(begin(categories), end(categories), [](Subject value)
	{value.ShowData(); });
}
int Testing::StartTest(string nameCategory, string nameTest)
{
	return find_if(begin(categories), end(categories), [nameCategory, nameTest](Subject value)
	{return value.GetName() == nameCategory; })->StartTest(nameTest);
}
void Testing::PushTestInCategory(string nameCategory, Test value)
{
	find_if(begin(categories), end(categories), [nameCategory, value](Subject valueSubject)
	{return valueSubject.GetName() == nameCategory; })->PushTest(value);
}
void Testing::PushQuestionInTest(string nameCategory, string nameTest, Question value)
{
	find_if(begin(categories), end(categories), [nameCategory](Subject valueSubject)
	{return valueSubject.GetName() == nameCategory; })->PushQuestion(nameTest, value);
}
int Testing::GetCheck(string nameCategory, string nameTest)
{
	auto category = find_if(begin(categories), end(categories), [nameCategory](Subject valueSubject)
	{return valueSubject.GetName() == nameCategory; });
	return category->FindTest(nameTest)->GetCheck();
}
//CLASS Subject
////////////////////////////////////////////////////////////////////////////////
Subject::Subject(string name)
{
	this->name = name;
}
vector<Test>::iterator Subject::FindTest(string nameTest)
{
	return find_if(begin(tests), end(tests), [nameTest](Test valueTest)
	{return valueTest.GetName() == nameTest; });
}
int Subject::GetCheck(string nameTest)
{
	return find_if(begin(tests), end(tests), [nameTest](Test value)
	{return value.GetName() == nameTest; })->GetCheck();
}
void Subject::PushTest(Test value)
{
	tests.push_back(value);
}
void Subject::ShowData()
{
	for_each(begin(tests), end(tests), [](Test value)
	{value.ShowData(); });
}
string Subject::GetName()
{
	return name;
}
int Subject::GetSizeTest()
{
	return tests.size();
}
int Subject::StartTest(string nameTest)
{
	return find_if(begin(tests), end(tests), [nameTest](Test value)
	{return value.GetName() == nameTest; })->StartTest();
}
void Subject::PushQuestion(string nameTest, Question value)
{
	find_if(begin(tests), end(tests), [nameTest](Test valueTest)
	{return valueTest.GetName() == nameTest; })->PushQuestion(value);
}
//CLASS TEST
////////////////////////////////////////////////////////////////////////////////
Test::Test()
{
	this->position = check = counter = 0;
}
Test::Test(string name)
{
	this->name = name;
	this->counter = position = check = 0;
}
void Test::PushQuestion(Question value)
{
	tests.push_back(value);
}
void Test::ShowData()
{
	for_each(begin(tests), end(tests), [](Question value)
	{value.ShowData(); });
}
string Test::GetName()
{
	return name;
}
int Test::GetSizeTest()
{
	return tests.size();
}
int Test::GetCheck()
{
	return check;
}
int Test::GetPosition()
{
	return position;
}
void Test::SetCheck(int check)
{
	this->check = -1;
}
int Test::CheckStop(int check)
{
	if (check == -1)
		return this->position;
	return 0;
}
int Test::StartTest()
{
	int rating; string answer;
	for (int i = CheckStop(check); i < tests.size(); ++i)
	{
		cout << tests[i].GetQuestion()
			<< "\n¬ведiть вiдповiдь: "; getline(cin, answer);
		if (answer == "Stop")
		{
			SetCheck(-1);
			return -1;
		}
		else if (tests[i].GiveAnswer(answer))
			this->counter++;
		this->position++;
	}
	rating = 12 * (((double)counter / (double)tests.size()) * 100) / 100;
	cout << "\n¬и дали вiдповiдь на " << counter << " запитанн¤ з " << tests.size()
		<< "\n¬и здали тест на " << ((double)counter / (double)tests.size()) * 100 << "%"
		<< "\n¬аша оцiнка: " << rating << "\n";
	position = counter = 0;
	return  rating;
}
//CLASS Question
////////////////////////////////////////////////////////////////////////////////
Question::Question(string question, string answer)
{
	this->question = question;
	this->answer = answer;
}
void Question::ShowData()
{
	cout << "\nQuestion: " << question << "\nAnswer: " << answer << "\n\n";
}
bool Question::GiveAnswer(string answer)
{
	return this->answer == answer;
}
void Question::SetData(string question, string answer)
{
	this->question = question;
	this->answer = answer;
}
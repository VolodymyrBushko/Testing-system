#include "Header.h"
int main()
{
	setlocale(LC_ALL, ("ukr"));
	Testing testing; int choise; bool run = false, runIn = false, runMain = true;
	Admin admin; User user;
	string name, mail, login, password, line1, line2; int number;
	string nameCategory, nameTest, question, answer;
	do
	{
		cout << "1)–егiстрацi¤. \n"
			<< "2)¬хiд. \n"
			<< "3)ѕовний вихiд. \n";
		(cin >> choise).get();
		if (choise == 1)
		{
			cout << "\n¬ведiть iм¤: "; getline(cin, name);
			cout << "\n¬ведiть пошту: "; getline(cin, mail);
			cout << "\n¬ведiть номер: "; (cin >> number).get();
			cout << "\n¬ведiть логiн: "; getline(cin, login);
			cout << "\n¬ведiть пароль: "; getline(cin, password);
			if (admin.Register(name, mail, number, login, password) != -1)
				run = true;
		}
		else if (choise == 2)
		{
			cout << "\n¬ведiть логiн: "; getline(cin, login);
			cout << "\n¬ведiть пароль: "; getline(cin, password);
			if (admin.Enter(login, password) != 0)
				run = runIn = true;
		}
		else if (choise == 3)
			return 0;
		if (run == false)
			return 0;
		cout << "\n1)–ежим дл¤ адмiна."
			<< "\n2)–ежим дл¤ тестера.";
		cout << "\n¬аш вибiр: ";
		(cin >> choise).get();
		if (choise == 1)
		{
			admin.Menu();
			while (runIn)
			{
				cout << "\n¬аш вибiр: ";
				(cin >> choise).get();
				switch (choise)
				{
				case 0:
				{
					runIn = false;
					break;
				}
				case 1:
				{
					cout << "\n¬ведiть предметну область: "; getline(cin, nameCategory);
					admin.PushCategory(testing, nameCategory);
					break;
				}
				case 2:
				{
					cout << "\n¬ведiть предметну область: "; getline(cin, nameCategory);
					cout << "\n¬ведiть назву тесту: "; getline(cin, nameTest);
					admin.PushTestInCategory(testing, nameCategory, nameTest);
					break;
				}
				case 3:
				{
					cout << "\n¬ведiть предметну область: "; getline(cin, nameCategory);
					cout << "\n¬ведiть назву тесту: "; getline(cin, nameTest);
					cout << "\n¬ведiть запитанн¤: "; getline(cin, question);
					cout << "\n¬ведiть правельну вiдповiдь: "; getline(cin, answer);
					admin.PushQuestionInTest(testing, nameCategory, nameTest, question, answer);
					break;
				}
				case 4:
				{
					cout << "\n¬ведiть iм¤: "; getline(cin, name);
					cout << "\n¬ведiть пошту: "; getline(cin, mail);
					cout << "\n¬ведiть номер: "; (cin >> number).get();
					cout << "\n¬ведiть логiн: "; getline(cin, login);
					cout << "\n¬ведiть пароль: "; getline(cin, password);
					admin.RegisterUser(name, mail, number, login, password);
					break;
				}
				case 5:
				{
					cout << "\n¬ведiть логiн: "; getline(cin, login);
					admin.DeleteUser(login);
					break;
				}
				case 6:
				{
					cout << "\n¬ведiть старий логiн: "; getline(cin, login);
					cout << "\n¬ведiть новий логiн: "; getline(cin, line1);
					cout << "\n¬ведiть новий пароль: "; getline(cin, password);
					cout << "\n¬ведiть нове iм¤: "; getline(cin, name);
					cout << "\n¬ведiть нову пошту: "; getline(cin, mail);
					cout << "\n¬ведiть новий номер: "; (cin >> number).get();
					admin.EditDataOfUser(name, mail, number, login, line1, password);
					break;
				}
				case 7:
				{
					admin.ShowAllTests();
					break;
				}
				case 8:
				{
					cout << "\n¬ведiть предметну область: "; getline(cin, nameCategory);
					admin.ShowTestByCategory(nameCategory);
					break;
				}
				case 9:
				{
					cout << "\n¬ведiть логiн: "; getline(cin, login);
					cout << "\n¬ведiть пароль: "; getline(cin, password);
					admin.ShowTestsUser(login, password);
					break;
				}
				}
			}
		}
		else if (choise == 2)
		{
			while (run)
			{

				cout << "1)¬хiд тестера.\n"
					<< "2)¬ихiд.\n";
				(cin >> choise).get();
				if (choise == 1)
				{
					cout << "\n¬ведiть логiн: "; getline(cin, login);
					cout << "\n¬ведiть пароль: "; getline(cin, password);
					if (user.Enter(login, password) != 0)
						runIn = true;
				}
				else if (choise == 0)
					runIn = run = false;
				while (runIn)
				{
					user.Menu();
					cout << "\n¬аш вибiр: ";
					(cin >> choise).get();
					switch (choise)
					{
					case 0:
					{
						run = runIn = false;
						break;
					}
					case 1:
					{
						cout << "\n¬иберiть предметну область: "; getline(cin, nameCategory);
						cout << "\n¬иберiть тест: "; getline(cin, nameTest);
						user.StartTest(testing, nameCategory, nameTest);
						break;
					}
					case 2:
					{
						user.ShowTests();
						break;
					}
					}
				}
			}
		}
	} while (runMain);
	return 0;
}
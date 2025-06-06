#include <iostream>
#include "../headers/console_helper.h"

void ConsoleHelper::ShowMessageAndPauseThenClear(const string& message)
{
	cout << message;
	system("pause>nul");
	ClearScreen();
}
void ConsoleHelper::ShowScreenHeader(const string& screenName) {
	cout << "\n==================================================\n\n";
	cout << "\t" << screenName << endl;
	cout << "\n==================================================\n\n";
}

void ConsoleHelper::ClearBuffer()
{
	cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

bool ConsoleHelper::AreYouSure(const string& Message)
{
	cout << Message;
	char areYouSure = 'N';
	cin >> areYouSure;
	ClearBuffer();
	return toupper(areYouSure) == 'Y';
}

void ConsoleHelper::PauseAndClearScreen(){
	system("pause>nul");
	ClearScreen();
}

void ConsoleHelper::ClearScreen()
{
	system("cls");
}
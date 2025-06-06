#pragma once
#include <string>
using namespace std;
class ConsoleHelper
{
public:

	 static void ShowMessageAndPauseThenClear(const string& message);

	 static void ShowScreenHeader(const string& screenName);

	 static void ClearBuffer();

	 static bool AreYouSure(const string& Message);

	 static void PauseAndClearScreen();

	 static void ClearScreen();

};


#pragma once
#include <string>
using namespace std;

class InputValidatorUtils
{
public:

	static bool IsValidPinCode(const string& PinCode);

	static bool IsValidAccountNumber(const string& AccountNumber);

	static bool IsValidName(const string& name);

	static bool IsValidAccountNumberAndPinCode(const string& AccountNumber, const string& PinCode);
};




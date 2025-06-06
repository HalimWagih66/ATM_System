#include "../headers/input_validator_utils.h"
#include "../headers/string_operations.h"
#include <iostream>

// Checks if a PIN code is valid based on:
// - Length must be either 4 or 6 digits
// - Must consist only of digits
bool InputValidatorUtils::IsValidPinCode(const string& PinCode)
{
	if (PinCode.length() != 4 && PinCode.length() != 6) {
		return false;
	}
	if (!StringOperations::IsWordAllDigits(PinCode))
	{
		return false;
	}
	return true;
}

// Checks if an account number is valid based on:
bool InputValidatorUtils::IsValidAccountNumber(const string& accountNumber)
{
	if (accountNumber.size() != 10 || !(StringOperations::IsWordAllDigits(accountNumber))) { // Check length and if all characters are digits
		return false; 
	}
	return true; // All checks passed
}

bool InputValidatorUtils::IsValidName(const string& fullName)
{
	// Check length between 7 and 50 characters
	if (fullName.length() < 7 || fullName.length() > 50) {
		return false;
	}
	// Check that the name contains at least two words
	if (StringOperations::CountEachWordInTheString(fullName) < 2)
	{
		return false;
	}
	// Check that the name contains only letters and spaces
	if (!StringOperations::ContainsOnlyLettersAndSpaces(fullName))
	{
		return false;
	}
	return true;
}

bool InputValidatorUtils::IsValidAccountNumberAndPinCode(const string& AccountNumber,const string& PinCode)
{
	return (IsValidAccountNumber(AccountNumber) && IsValidPinCode(PinCode));
}


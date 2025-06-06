#pragma once
#include "features/atm/models/client info/client_info.h"
#include <vector>
using namespace std;

enum enMainMenuOptions
{
	eQuickWithdraw = 1, eNormalWithdraw, eDeposit, eCheckBalance, eLogout
};
class ATM
{
private:

	ClientInfo LoggedClient; // Information of the logged-in client

	int LoggedClientIndex; // Index of the logged-in client in the Clients vector

	vector<ClientInfo> LoadClientsFromFile(const string& filename)const; // Loads client information from a file and returns a vector of ClientInfo objects

	int GetClientIndexByAccountNumberAndPinCode(const string& AccountNumber, const string& PinCode, const vector<ClientInfo>& Clients) const; // Gets the index of a client by account number and pin code, returns -1 if not found

	bool FindClientByAccountNumberAndPinCode(const string& AccountNumber, const string& PinCode, ClientInfo& LoggedClient, int& LoggedClientReference, const vector<ClientInfo>& Clients); // Finds a client by account number and pin code, returns true if found

	void SaveClientChanges(const string& filePath)const; // Saves changes made to the client information back to the file

	vector<string> ConvertClientsToString(const vector<ClientInfo>& Clients)const; // Converts vector of ClientInfo to vector of strings for saving to file 

	void ShowMainMenuOptions()const; // Displays the main menu options for the logged-in client

	void ShowWithdrawOptions(const vector<short>& WithdrawOptions)const; // Displays the withdrawal options available to the client

	void ProcessWithdrawalIfPossible(const int& amount); // Processes the withdrawal if the amount is valid and available in the account

	short ReadValidChoiceQuickWithdraw(const short& numberOfOptions)const;// Reads a valid choice for quick withdrawal from user input

	void ShowQuickWithdrawScreen(); // Displays the quick withdrawal screen for the logged-in client

	void ShowNormalWithdrawScreen(); // Displays the normal withdrawal screen for the logged-in client

	int ReadAmountForDeposit()const;		 // Reads the amount to be deposited from user input and returns it

	void ShowDepositScreen(); // Displays the deposit screen for the logged-in client

	void ShowAccountBalance()const; // Displays the account balance of the logged-in client

	void ShowCheckBalanceScreen()const; // Displays the account balance of the logged-in client

	void PerformMainMenuOption(const enMainMenuOptions& enMainMenuOption); // Performs the action corresponding to the selected main menu option

	void GoBackToMainMenu()const; // Returns to the main menu after performing an action

	void ShowMainMenuScreen(); // Displays the main menu after successful login

public:
	~ATM();

	void LoginScreen(); // Displays the login screen and handles user input for logging in 
};


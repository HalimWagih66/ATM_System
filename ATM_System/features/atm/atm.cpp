#include "atm.h"
#include <iostream>
#include <array>
#include <iomanip>
#include "../../core/constants/file_pathes.h"
#include "../../core/utils/headers/console_helper.h"
#include "../../core/utils/headers/data_reader.h"
#include "../../core/utils/headers/input_validator_utils.h"
#include "../../core/utils/headers/file_operations.h"

enum class IndexResult {
	NotFound = -1
};

// Destructor: Save any changes made to the logged-in client before destroying the ATM object
ATM::~ATM(){}

// Displays the login screen and handles user authentication
void ATM::LoginScreen()
{
	bool isUserFound = false;
	bool isValidInput = false;
	string AccountNumber, PinCode;
	vector<ClientInfo> clients = LoadClientsFromFile(FilePathes::Clients); // Load clients from file

	do
	{
		ConsoleHelper::ClearScreen();
		ConsoleHelper::ShowScreenHeader("ATM Login Screen");

		AccountNumber = DataReader::PromptAndReadLine("Please enter your account number: ");
		PinCode = DataReader::PromptAndReadLine("Please enter your pin code: "); // Read account number and pin code from user input

		isValidInput = InputValidatorUtils::IsValidAccountNumberAndPinCode(AccountNumber, PinCode); // Validate the input format

		if (!isValidInput) {
			ConsoleHelper::ShowMessageAndPauseThenClear("Invalid input. Please enter a valid account number and pin code.");
			continue;
		}

		isUserFound = LoadClientInfo(AccountNumber, PinCode, clients); // Attempt to find the client using the provided account number and pin code

		if (!isUserFound) {
			ConsoleHelper::ShowMessageAndPauseThenClear("Client not found. Please check your account number and pin code."); // If client is not found, show an error message and prompt again
			continue;
		}

		break; // Successful login
	} while (true);

	ShowMainMenuScreen(); // Show main ATM menu after successful login

	SaveClientChanges(FilePathes::Clients); // Save any changes made to the logged-in client
}

// Loads clients from a file and returns a vector of ClientInfo objects
vector<ClientInfo> ATM::LoadClientsFromFile(const string& filename)const
{
	vector<string> Records = FileOperations::RestoreDataFromFile(filename); // Read records from the file
	vector<ClientInfo> Clients;

	for (string Record : Records)
	{
		Clients.push_back(ClientInfo::ConvertFromRecordString(Record));  // Convert each record to ClientInfo object
	}
	return Clients;
}

// Finds the index of a client using their account number and pin code
int ATM::GetClientIndexByAccountNumberAndPinCode(const string& AccountNumber, const string& PinCode, const vector<ClientInfo>& Clients)const
{
	for (size_t i = 0; i < Clients.size(); i++)
	{
		if (Clients[i].getAccountNumber() == AccountNumber && Clients[i].getPinCode() == PinCode) // Check if both account number and pin code match
			return i;
	}
	return (int)IndexResult::NotFound; // Not found
}

// Finds and returns a client if account number and pin match; also returns index
bool ATM::FindClientByAccountNumberAndPinCode(const string& AccountNumber, const string& PinCode, ClientInfo& LoggedClient, int& LoggedClientReference, const vector<ClientInfo>& Clients)
{
	int ClientIndex = GetClientIndexByAccountNumberAndPinCode(AccountNumber, PinCode, Clients); // Get the index of the client
	LoggedClientReference = ClientIndex;

	if (ClientIndex != (int)IndexResult::NotFound) {
		LoggedClient = Clients[ClientIndex];
		return true;
	}
	return false;
}

// Saves changes to the logged-in client back to the file
void ATM::SaveClientChanges(const string& filePath)const
{
	vector<ClientInfo> vClients = LoadClientsFromFile(filePath);
	vClients[LoggedClientIndex] = LoggedClient; // Update the logged-in client's data
	vector<string> vRecords = ConvertClientsToString(vClients); // Convert the updated client data to string records
	FileOperations::SaveRecordsInFile(vRecords, filePath); // Save the updated records back to the file
}

// Converts a list of ClientInfo objects to their string representations
vector<string> ATM::ConvertClientsToString(const vector<ClientInfo>& vClients)const
{
	vector<string> vRecords;
	for (const ClientInfo& clientInfo : vClients)
	{
		vRecords.push_back(ClientInfo::ConvertToRecordString(clientInfo));
	}
	return vRecords;
}

// Displays ATM main menu options
void ATM::ShowMainMenuOptions()const
{
	cout << "\t[1] Quick Withdraw.\n";
	cout << "\t[2] Normal Withdraw.\n";
	cout << "\t[3] Deposit.\n";
	cout << "\t[4] Check Balance.\n";
	cout << "\t[5] Logout.\n";
}
short ATM::getQuickWithDrawAmount(const short& QuickWithDrawOption)
{
	switch (QuickWithDrawOption)
	{
	case 1:
		return 20;
	case 2:
		return 50;
	case 3:
		return 100;
	case 4:
		return 200;
	case 5:
		return 400;
	case 6:
		return 600;
	case 7:
		return 800;
	case 8:
		return 1000;
	default:
		return 0;
	}
}

// Displays quick withdrawal options in two columns
void ATM::ShowWithdrawOptions(const vector<short>& WithdrawOptions)const {
	for (size_t i = 0; i < WithdrawOptions.size(); i += 2)
	{
		cout << "\n" << left << setw(19) << "[" + to_string(i + 1) + "] " + to_string(WithdrawOptions[i]);
		if (i + 1 < WithdrawOptions.size())
			cout << "[" + to_string(i + 2) + "] " + to_string(WithdrawOptions[i + 1]) << "\n";
	}
	cout << "\n[" << WithdrawOptions.size() + 1 << "] Exit\n\n";
	cout << "===================================================\n";
}

// Reads a valid option from the user for quick withdrawal
short ATM::ReadQuickWithdrawOption(const short& numberOfOptions) const{
	short choice;
	do {
		choice = DataReader::PromptAndReadNumber("Choose What to Withdraw from [1 ~ 9] : ");
	} while (choice < 1 || choice > numberOfOptions + 1);
	return choice;
}

void ATM::PerformQuickWithdrawOpiton(const short& quickWithdrawOption)
{
	if (quickWithdrawOption == 9) return; // Exit

	ProcessWithdrawalIfPossible(getQuickWithDrawAmount(quickWithdrawOption)); // Process the withdrawal if the choice is valid
}
// Displays quick withdrawal screen and handles selection
void ATM::ShowQuickWithdrawScreen() {
	ConsoleHelper::ShowScreenHeader("Quick Withdraw");

	vector<short> WithdrawOptions = { 20, 50, 100, 200, 400, 600, 800, 1000 };

	ShowWithdrawOptions(WithdrawOptions); // Display the withdrawal options

	cout << "Your Balance is : " << LoggedClient.getAccountBalance() << "\n\n\n";

	short quickWithdrawOption = ReadQuickWithdrawOption(WithdrawOptions.size()); // Read a valid choice from the user
	cout << "\n\n";

	PerformQuickWithdrawOpiton(quickWithdrawOption);
}

// Performs withdrawal if balance is sufficient
void ATM::ProcessWithdrawalIfPossible(const int& amount)
{
	if (LoggedClient.getAccountBalance() >= amount)
	{
		if (ConsoleHelper::AreYouSure("Are you sure you want perform this transaction? [Y/N]? ")) {
			LoggedClient.setAccountBalance(LoggedClient.getAccountBalance() - amount);
			cout << "\n\nDone Successfully. New Balance is : " << LoggedClient.getAccountBalance() << endl;
		}
		else {
			cout << "The transaction was not completed. Your balance remains the same.\n";
		}
	}
	else {
		cout << "The amount exceeds your balance, please make another choice.\n";
	}
}

// Reads a valid amount that is a multiple of 5
int ReadAmountMultipleOfFive() {
	int amount = 0;
	do {
		amount = DataReader::PromptAndReadNumber("Enter an amount (must be a multiple of 5): ");
		if (amount % 5 != 0) {
			cout << "Invalid amount. Please enter a value that's a multiple of 5.\n";
		}
	} while (amount % 5 != 0);
	return amount;
}

void ATM::PerfromNormalWithdrawOption(const int& amount)
{
	ProcessWithdrawalIfPossible(amount); // Process the withdrawal if the amount is valid
}

// Displays the normal withdrawal screen
void ATM::ShowNormalWithdrawScreen() {
	ConsoleHelper::ShowScreenHeader("Normal Withdraw Screen");
	cout << "\n";
	int amount = ReadAmountMultipleOfFive(); // Read a valid amount that is a multiple of 5
	cout << "\n\n";
	ProcessWithdrawalIfPossible(amount); // Process the withdrawal if possible
}

// Reads a valid amount for deposit (must be positive)
int ATM::ReadAmountForDeposit()const {
	int amount = 0;
	do {
		amount = DataReader::PromptAndReadNumber("Please enter the amount you want to deposit must be positive : ");
		if (amount <= 0) {
			cout << "Invalid amount. Please enter a positive value.\n";
		}
	} while (amount <= 0);
	return amount;
}

void ATM::PerformDepositOption(const int& amount)
{
	if (ConsoleHelper::AreYouSure("Are you sure you want to deposit " + to_string(amount) + " ? [Y/N]? ")) {
		LoggedClient.setAccountBalance(LoggedClient.getAccountBalance() + amount); // Update the account balance
		cout << "\n\nDeposit successful! New Balance is : " << LoggedClient.getAccountBalance() << endl;
	}
	else {
		cout << "The deposit was not completed. Your balance remains the same.\n"; // If user cancels, show a message
	}
}

// Displays deposit screen and processes deposit
void ATM::ShowDepositScreen() {
	ConsoleHelper::ShowScreenHeader("Deposit Screen"); // Show the deposit screen header

	int amount = ReadAmountForDeposit(); // Read a valid amount for deposit

	cout << "\n\n";

	PerformDepositOption(amount); // Perform the deposit operation with the entered amount
}

// Shows client's current balance
void ATM::ShowAccountBalance() const{
	cout << "Your Balance is : " << LoggedClient.getAccountBalance() << endl;
}

// Displays balance checking screen
void ATM::ShowCheckBalanceScreen() const{
	ConsoleHelper::ShowScreenHeader("Check Balance Screen");
	ShowAccountBalance();
}

// Executes the selected main menu option
void ATM::PerformMainMenuOption(const enMainMenuOptions& enMainMenuOption) {
	switch (enMainMenuOption) {
	case eQuickWithdraw:
		ConsoleHelper::ClearScreen(); // Clear the screen before showing quick withdraw options
		ShowQuickWithdrawScreen(); // Show the quick withdraw screen
		GoBackToMainMenu();
		break;
	case eNormalWithdraw:
		ConsoleHelper::ClearScreen(); // Clear the screen before showing normal withdraw options
		ShowNormalWithdrawScreen(); // Show the normal withdraw screen
		GoBackToMainMenu();
		break;
	case eDeposit:
		ConsoleHelper::ClearScreen(); // Clear the screen before showing deposit options
		ShowDepositScreen(); // Show the deposit screen
		GoBackToMainMenu();
		break;
	case eCheckBalance:
		ConsoleHelper::ClearScreen(); // Clear the screen before showing balance
		ShowCheckBalanceScreen(); // Show the current account balance
		GoBackToMainMenu();
		break;
	case eLogout:
		ConsoleHelper::ClearScreen();
		break;
	}
}

// Pauses until the user presses a key to return to the main menu
void ATM::GoBackToMainMenu() const{
	cout << "\n\n";
	cout << "\nPress any key to return to main menu...";
	system("pause>nul");
}

// Displays the main ATM menu loop
void ATM::ShowMainMenuScreen() {
	int choice;
	do
	{
		ConsoleHelper::ClearScreen(); // Clear the screen before showing the menu

		ConsoleHelper::ShowScreenHeader("ATM Main Menu Screen");

		ShowMainMenuOptions(); // Display main menu options

		cout << "=====================================\n";

		choice = DataReader::PromptAndReadNumber("Please enter your choice [1 - 5]: "); // Read user choice

		PerformMainMenuOption((enMainMenuOptions)choice); // Perform the action based on user choice

	} while (choice != 5); // Exit on logout
}

bool ATM::LoadClientInfo(const string& AccountNumber, const string& PinCode, const vector<ClientInfo>& clients) // Attempts to load client information based on account number and pin code
{

	return FindClientByAccountNumberAndPinCode(AccountNumber, PinCode, LoggedClient, LoggedClientIndex, clients) ? true : false; // Attempt to find the client using the provided account number and pin code
}



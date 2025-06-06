#pragma once
#include <string>
using namespace std;
class ClientInfo {

private:
	std::string accountNumber;
	std::string pinCode;
	std::string name;
	std::string phoneNumber;
	int accountBalance;

	static constexpr const char* RECORD_DELIMITER = "#//#";
public:

	// Constructor to initialize ClientInfo with parameters
	ClientInfo(const string& accountNumber, const string& pinCode, const string& name, const string& phoneNumber,const int& accountBalance);

	// Default constructor initializes with empty strings and zero balance
	ClientInfo();

	// Setter only for account balance to allow controlled modifications
	void setAccountBalance(const int& accountBalance) { this->accountBalance = accountBalance; }

	const string& getAccountNumber() const { return accountNumber; }

	const string& getPinCode() const { return pinCode; }

	const string& getName() const { return name; }

	const string& getPhoneNumber() const { return phoneNumber; }

	const int& getAccountBalance() const { return accountBalance; }

	// Static methods for serialization/deserialization
	static string ConvertToRecordString(ClientInfo ClientInfo, const string& separator = "#//#"); // Converts a ClientInfo object to a string record

	static ClientInfo ConvertFromRecordString(const string& ClientRecord);  // Converts a string record to a ClientInfo object
};




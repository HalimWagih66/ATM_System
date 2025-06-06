#include "client_info.h"
#include <string>
#include <iostream>
#include <iomanip>
#include <vector>
#include "../../../../core/utils/headers/input_validator_utils.h"
#include "../../../../core/utils/headers/string_operations.h"
#include "../../../../core/utils/headers/data_reader.h"

ClientInfo::ClientInfo(const string& accountNumber, const string& pinCode, const string& name, const string& phoneNumber,const int& accountBalance)
{
    this->accountNumber = accountNumber;
    this->pinCode = pinCode;
    this->name = name;
    this->phoneNumber = phoneNumber;
    this->accountBalance = accountBalance;
}

ClientInfo::ClientInfo() {
	accountNumber = "";
	pinCode = "";
	name = "";
	phoneNumber = "";
	accountBalance = 0;
}
// Converts a ClientInfo object into a string record with fields separated by 'separator' string
string ClientInfo::ConvertToRecordString(ClientInfo ClientInfo,const string& separator) {
    string stClientRecord = "";
    stClientRecord += ClientInfo.accountNumber + separator;
    stClientRecord += ClientInfo.pinCode + separator;
    stClientRecord += ClientInfo.name + separator;
    stClientRecord += ClientInfo.phoneNumber + separator;
    stClientRecord += to_string(ClientInfo.accountBalance);
    return stClientRecord;
}

// Converts a string record back into a ClientInfo object by splitting the record using "#//#" delimiter
ClientInfo ClientInfo::ConvertFromRecordString(const string& ClientRecord) {
    vector<string> ClientInfoFromFile = StringOperations::SplitString(ClientRecord, "#//#");

    ClientInfo client;
    client.accountNumber = ClientInfoFromFile[0];
    client.pinCode = ClientInfoFromFile[1];
    client.name = ClientInfoFromFile[2];
    client.phoneNumber = ClientInfoFromFile[3];
    try {
        client.accountBalance = stod(ClientInfoFromFile[4]);
    }
    catch (...) {
        // If conversion fails, default account balance to 0
        client.accountBalance = 0;
    }
    return client;
}
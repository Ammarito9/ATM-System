#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <iomanip>
#include <limits>
using namespace std;

const string clientFileName = "clients.txt";

struct stClient
{
  string accountNumber;
  string pinCode;
  string fullName;
  string phone;
  double accountBalance = 0;
  bool markDelete = false;
};

enum AtmMainMenu
{
  _quickWithdraw = 1,
  _normalWithdraw,
  _deposit,
  _checkBalance,
  _logOut
};

enum QuickWithdrawMenuOptions
{
  _20 = 1,
  _50,
  _100,
  _200,
  _400,
  _600,
  _800,
  _1000,
  _exit,
};

stClient currentClient;

// Declarations :

void logIn();

void atmMainMenu();

// -+-+-+-+-+-+-+-+-+-+-+--+-+-+-+-+-+-+-+-

int main()
{
    logIn();

    return 0;
}

short getDividerLength(string mainStr)
{
  return 30 + mainStr.length();
}

void printHeader(string mainStr)
{

  string formattedStr = mainStr;

  short dividerLength = getDividerLength(mainStr);

  for (int i = 0; i < (dividerLength - mainStr.length()) / 2; i++)
  {

    formattedStr = i >= 5 ? '=' + formattedStr + '=' : i == 2 ? '+' + formattedStr + '+' : ' ' + formattedStr + ' ';
  }

  cout << string(dividerLength, '=') << endl;
  cout << formattedStr << endl;
  cout << string(dividerLength, '=') << endl;
}

string recordToLine(stClient clientData, string separator = "#//#")
{

  string dataLine;

  dataLine = clientData.accountNumber + separator;
  dataLine += clientData.pinCode + separator;
  dataLine += clientData.fullName + separator;
  dataLine += clientData.phone + separator;
  dataLine += to_string(clientData.accountBalance);

  return dataLine;
}

void saveClientDataToFile(const vector<stClient> &clientsData, bool append = false)
{

  fstream clientFile;

  ios::openmode mode = append ? (ios::out | ios::app) : ios::out;
  clientFile.open(clientFileName, mode);

  if (clientFile.is_open())
  {

    for (const stClient &client : clientsData)
    {
      if (!client.markDelete)
        clientFile << recordToLine(client) << endl;
    }

    clientFile.close();
  }
}

vector<string> splitString(string str, string delimeter = "#//#")
{

  vector<string> stringSeparated;
  int pos = 0;

  while ((pos = str.find(delimeter)) != string::npos)
  {

    stringSeparated.push_back(str.substr(0, pos));

    str.erase(0, pos + delimeter.length());
  }

  // adds the last word since the string doest end with the delimeter.
  stringSeparated.push_back(str);

  return stringSeparated;
}

stClient ClientDataLineToRecord(string dataline, string delimeter = "#//#")
{

  stClient ClientData;

  vector<string> dataLineSeparated = splitString(dataline);

  ClientData.accountNumber = dataLineSeparated.at(0);
  ClientData.pinCode = dataLineSeparated.at(1);
  ClientData.fullName = dataLineSeparated.at(2);
  ClientData.phone = dataLineSeparated.at(3);
  ClientData.accountBalance = stod(dataLineSeparated.at(4));

  return ClientData;
}

vector<stClient> loadClientsFromFile(string clientFileName)
{

  vector<stClient> clientsData;

  fstream clientFile;
  clientFile.open(clientFileName, ios::in);

  if (clientFile.is_open())
  {

    string dataLine;

    while (getline(clientFile, dataLine))
    {
      clientsData.push_back(ClientDataLineToRecord(dataLine));
    }

    clientFile.close();
  }

  return clientsData;
}

int readNumber(string message, int from, int to, bool printRangeInMessage = false, string messageAfterTheRange = " : ")
{

  int number;
  
  if(printRangeInMessage)
  {
    message = message + "[" + to_string(from) + "-" + to_string(to) +"]" + messageAfterTheRange;
  }
  
  cout << message << endl;

  cin >> number;

  while (cin.fail() || (number < from || number > to))
  {

    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "Invalid input, please enter a valid number : " << endl;
    cin >> number;
  }

  return number;
}

int readNumber(string message)
{

  int number;

  cout << message << endl;

  cin >> number;

  while (cin.fail())
  {

    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "Invalid input, please enter a valid number : " << endl;
    cin >> number;
  }

  return number;
}

string readString(string message)
{
  string input;

  cout << message;
  cin >> input;

  return input;
}

char readChar(string message)
{

  char character;

  cout << message;
  cin >> character;

  return character;
}

bool findClientByAccountNumber(string accountNumber, const vector<stClient> &clientsData, stClient &foundClient)
{
  for (const stClient &client : clientsData)
  {
    if (client.accountNumber == accountNumber)
    {
      foundClient = client;
      return true;
    }
  }
  return false;
}

bool findClientByAccountNumberAndPinCode(string accountNumber, string pinCode, const vector<stClient> &clientsData, stClient &foundClient)
{
  for (const stClient &client : clientsData)
  {
    if (client.accountNumber == accountNumber)
    {
      if(client.pinCode == pinCode)
      {
        foundClient = client;
        return true;
      }
    }
  }
  return false;
}

bool isAmountExceedBalance(stClient client, int amount)
{
  return client.accountBalance < amount;
}

void printAmountExceedsYourBalance()
{
  printHeader("Amount exceeds your balance");
  cout << "   The amount exceeds your balance, make another choice." << endl;
}

bool withDrawFormClient(vector<stClient>& clientsData,const stClient client, int amount)
{
  for(stClient& c : clientsData)
  {
    if(c.accountNumber == client.accountNumber)
    {
      c.accountBalance -= amount;
      return true;
    }
  }
  return false;
}

bool depositForClient(vector<stClient>& clientsData,const stClient client, int amount)
{
  for(stClient& c : clientsData)
  {
    if(c.accountNumber == client.accountNumber)
    {
      c.accountBalance += amount;
      return true;
    }
  }
  return false;
}

void printQuickWithdrawMenu()
{
  system("cls");
  string menuName = "Quick Withdraw";
  int setwSpace = 20;

  printHeader(menuName);

  cout << "       " << left << setw(setwSpace) << "[1] 20." << "[2] 50." << endl;
  cout << "       " << left << setw(setwSpace) << "[3] 100."  << "[4] 200." << endl;
  cout << "       " << left << setw(setwSpace) << "[5] 400."  << "[6] 600." << endl;
  cout << "       " << left << setw(setwSpace) << "[7] 800."  << "[8] 1000." << endl;
  cout << "       " << "[9] Exit." << endl;

  cout << string(getDividerLength(menuName),'=') << endl;
}

void quickWithdraw(vector<stClient>& clientsData)
{
  int menuChoice, amount;

  printQuickWithdrawMenu();

  menuChoice = readNumber("Please choose a amount ",QuickWithdrawMenuOptions::_20,QuickWithdrawMenuOptions::_exit,true,", or press [9] to exit : ");

  switch(static_cast<QuickWithdrawMenuOptions>(menuChoice))
  {
    case QuickWithdrawMenuOptions::_20:
      amount = 20;
    break;
    
    case QuickWithdrawMenuOptions::_50:
      amount = 50;
    break;

    case QuickWithdrawMenuOptions::_100:
      amount = 100;
    break;

    case QuickWithdrawMenuOptions::_200:
      amount = 200;
    break;

    case QuickWithdrawMenuOptions::_400:
      amount = 400;
    break;

    case QuickWithdrawMenuOptions::_600:
      amount = 600;
    break;

    case QuickWithdrawMenuOptions::_800:
      amount = 800;
    break;

    case QuickWithdrawMenuOptions::_1000:
      amount = 1000;
    break;

    case QuickWithdrawMenuOptions::_exit:
      atmMainMenu();
    break;
    
    default:
      atmMainMenu();
    break;
  }

  if(isAmountExceedBalance(currentClient,amount)) 
  {
    printAmountExceedsYourBalance();
    system("cls");
    quickWithdraw(clientsData);
  }

  if(withDrawFormClient(clientsData,currentClient,amount))
  {
    cout << "Withdraw done successfully! Your balance is " << currentClient.accountBalance << "."; 
    saveClientDataToFile(clientsData);
  }
  else
  {
    cout << "Withdraw done unsuccessfully!"; 
  }
}

void normalWithdraw(vector<stClient>& clientsData)
{
  int amount;

  printHeader("Normal withdraw");

  amount = readNumber("Please enter the amount to withdraw (must be multiple of 5) : ");
  
  if(isAmountExceedBalance(currentClient,amount))
  {
    printAmountExceedsYourBalance();
    system("cls");
    normalWithdraw(clientsData);
  }

  while(amount % 5 != 0)
  {
    cout << "must be multiple of 5, please make sure to enter a valid amount.";
    amount = readNumber("Please enter the amount to withdraw (must be multiple of 5) : ");
  }

  if(withDrawFormClient(clientsData,currentClient,amount))
  {
    cout << "Withdraw done successfully! Your balance is " << currentClient.accountBalance << "."; 
    saveClientDataToFile(clientsData);
  }
  else
  {
    cout << "Withdraw done unsuccessfully!"; 
  }
}

void deposit(vector<stClient>& clientsData)
{
  int amount;

  printHeader("Deposit");

  amount = readNumber("Please enter the amount to withdraw (must be multiple of 5) : ");
  
  while(amount <= 0)
  {
    cout << "Amount must be positive and bigger then 0!" << endl;
    amount = readNumber("Please enter the amount to withdraw (must be multiple of 5) : ");
  }

  if(depositForClient(clientsData,currentClient,amount))
  {
    cout << "Deposit done successfully! Your balance is " << currentClient.accountBalance << "."; 
    saveClientDataToFile(clientsData);
  }
  else
  {
    cout << "Deposit done unsuccessfully!"; 
  }
}

void checkBalance()
{
  cout << "Your balance is " << currentClient.accountBalance << ".";
}

void logOut()
{
  logIn();
}

void printAtmMenu()
{
  system("cls");
  string menuName = "ATM main menu";

  printHeader(menuName);

  cout << "[1] Quick withdraw." << endl;
  cout << "[2] Normal withdraw." << endl;
  cout << "[3] Deposit." << endl;
  cout << "[4] Check balance." << endl;
  cout << "[5] Log out." << endl;

  cout << string(getDividerLength(menuName),'=') << endl;
}

void goBackToAtmMenu()
{
  cout << "Press any key to go back to atm menu screen..." << endl;
  system("pause > 0");
  atmMainMenu();
}

void atmMainMenu()
{
  vector<stClient> clientsData = loadClientsFromFile(clientFileName);
  int menuChoice;

  printAtmMenu();

  menuChoice = readNumber("Please choose a number ",AtmMainMenu::_quickWithdraw,AtmMainMenu::_logOut,true);

  switch(static_cast<AtmMainMenu>(menuChoice))
  {
    case AtmMainMenu::_quickWithdraw:
      system("cls");
      quickWithdraw(clientsData);
      goBackToAtmMenu();
    break;

    case AtmMainMenu::_normalWithdraw:
      system("cls");
      normalWithdraw(clientsData);
      goBackToAtmMenu();
    break;

    case AtmMainMenu::_deposit:
      system("cls");
      deposit(clientsData);
      goBackToAtmMenu();
    break;

    case AtmMainMenu::_checkBalance:
      system("cls");
      checkBalance();
      goBackToAtmMenu();
    break;

    case AtmMainMenu::_logOut:
      system("cls");
      logOut();
    break;

    default:
      cout << "Invalid input!";
    break;
  }
}

void logIn()
{
  vector <stClient> clientsData = loadClientsFromFile(clientFileName);
  string clientAccountNumber, pinCode;
  printHeader("Log in Screen");

  clientAccountNumber = readString("Please enter the account number : ");
  pinCode = readString("Please enter the pin code : ");

  while(!findClientByAccountNumberAndPinCode(clientAccountNumber,pinCode,clientsData,currentClient))
  {
    cout << "Incorrect account number or pin code!" << endl;

    clientAccountNumber = readString("Please enter the account number : ");
    pinCode = readString("Please enter the pin code : ");
  }

  atmMainMenu();
}

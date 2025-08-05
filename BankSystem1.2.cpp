#include <iostream>
#include <string>
#include <iomanip>
#include <vector>
#include <fstream>
#include <limits>
using namespace std;

enum enManageClients { ClientsList = 1, AddClient = 2, DeleteClient = 3, UpdateClientData = 4, FindClient = 5, Transactions = 6, ManageUsers = 7, Logout = 8};
enum enManageTransactions { Deposit = 1, WithDraw = 2, TotalBalance = 3, MainMenu = 4};
enum enManageUsers {UsersList = 1, AddUser = 2, DeleteUser = 3, UpdateUser = 4,FindUser = 5, UserToMainMenu = 6};
enum enMainMenuPermissions {pAll = -1, pListClients = 1, pAddNewClient = 2, pDeleteClient = 4, pUpdateClients = 8, pFindClient = 16, pTranactions = 32, pManageUsers = 64};

struct stClient {

    string AccountNumber;
    string PinCode;
    string ClientName;
    string PhoneNumber;
    double AccountBalance;
    bool DeleteClient = false;
};

struct stUser {

    string UserName;
    string Password;
    int Permission = 0;
    bool DeleteUser = false;
};


const string ClientsDataFile = "Clients_data_file.txt";
const string UsersDataFile = "Users_data_file.txt";
stUser CurrentUser;

void ShowMainMenu();
void ShowTransactionsMenu();
void ShowUsersMenu();

vector<string> SplitString(string Data, string Separator = "#//#") {

    vector<string> vClient;
    string Word = "";
    short Pos = 0;

    while ((Pos = Data.find(Separator)) != Separator.npos) {

        Word = Data.substr(0, Pos);

        if (Word != "") {
            vClient.push_back(Word);
        }
        Data.erase(0, Pos + Separator.length());
    }
    if (!Data.empty()) {
        vClient.push_back(Data);
    }
    return vClient;
}

stClient ConvertLineToRecord(string Line, string Separator = "#//#") {

    stClient Client;
    vector<string> vClient;
    vClient = SplitString(Line);

    Client.AccountNumber = vClient[0];
    Client.PinCode = vClient[1];
    Client.ClientName = vClient[2];
    Client.PhoneNumber = vClient[3];
    Client.AccountBalance = stod(vClient[4]); //cast string to double.
    return Client;
}

string ConvertRecordToLine(stClient ClientData, string Separator = "#//#") {

    string ClientRecord = "";
    ClientRecord += ClientData.AccountNumber + Separator;
    ClientRecord += ClientData.PinCode + Separator;
    ClientRecord += ClientData.ClientName + Separator;
    ClientRecord += ClientData.PhoneNumber + Separator;
    ClientRecord += to_string(ClientData.AccountBalance);
    return ClientRecord;
}

bool IsClientExistsByAccountNumber(string FileName, string AccountNumber) {

    vector<stClient> vClients;
    fstream DataFile;
    DataFile.open(FileName, ios::in);

    if (DataFile.is_open()) {

        string Line;
        stClient Client;

        while(getline(DataFile, Line)) {

            Client = ConvertLineToRecord(Line);

            if (Client.AccountNumber == AccountNumber) {
                DataFile.close();
                return true;
            }
        }
        DataFile.close();
    }
    return false;
}

stClient ReadNewClient () {

    stClient NewClient;

    cout << "Enter the account number:   ";
    getline(cin >> ws, NewClient.AccountNumber);

    while (IsClientExistsByAccountNumber(ClientsDataFile, NewClient.AccountNumber)) {

        cout << "Client with [" << NewClient.AccountNumber << "] is already exists, enter another number:  ";
        getline(cin >> ws, NewClient.AccountNumber);
    }

    cout << "Enter the PIN code:  ";
    getline(cin , NewClient.PinCode);

    cout << "Enter the client name:  ";
    getline(cin , NewClient.ClientName);

    cout << "Enter the phone number:  ";
    getline(cin , NewClient.PhoneNumber);

    cout << "Enter the account balance:  ";
    cin >> NewClient.AccountBalance;

    return NewClient;
}

vector<stClient> LoadClientDataFromFile(string FileName, string Separator = "#//#") {

    vector<stClient> vClients;
    fstream DataFile;
    DataFile.open(FileName, ios::in);

    if (DataFile.is_open()) {

        stClient Client;
        string Line;

        while (getline(DataFile, Line)) {

            Client = ConvertLineToRecord(Line);
            vClients.push_back(Client);
        }
        DataFile.close();
    }
    return vClients;
}

void PrintClientRecordLine(stClient Data) {

    cout << "| " << setw(15) << left << Data.AccountNumber;
    cout << " | " << setw(10) << left << Data.PinCode;
    cout << " | " << setw(40) << left << Data.ClientName;
    cout << " | " << setw(15) << left << Data.PhoneNumber;
    cout << " | " << setw(10) << left << Data.AccountBalance << " |";
}

void PrintAllClientData() {

    vector<stClient> vClients = LoadClientDataFromFile(ClientsDataFile);
    printf("\t\t\t\tClient List (%d) Client(s)\n", vClients.size());
    cout << "----------------------------------------------------------------------------------------------------------\n";
    cout << "| " << setw(15) << left << "Account Number";
    cout << " | " << setw(10) << left << "Pin Code";
    cout << " | " << setw(40) << left << "Client Name";
    cout << " | " << setw(15) << left << "Phone";
    cout << " | " << setw(10) << left << "Balance" << " |" << endl;
    cout << "----------------------------------------------------------------------------------------------------------\n";
    
    if (vClients.size() == 0) {
        cout << "\t\t\t\tNo clients availsble in the system\n";
    }

    for (stClient & Client : vClients) {
        PrintClientRecordLine(Client);
        cout << endl;
    }
    cout << "----------------------------------------------------------------------------------------------------------\n";
}

void PrintClientCard(stClient Client) {

    cout << "\n\nThe following are the client details:\n";
    cout << "----------------------------------------\n";
    cout << "Account number  : " << Client.AccountNumber << endl;
    cout << "PIN code        : " << Client.PinCode << endl;
    cout << "Client name     : " << Client.ClientName << endl;
    cout << "Phone number    : " << Client.PhoneNumber << endl;
    cout << "Account Balance : " << Client.AccountBalance << endl;
    cout << "----------------------------------------\n\n";
}

bool FindClientByAccountNumber(string AccountNumber, vector<stClient>& vClients, stClient& Client) {

    for (stClient& C : vClients) {

        if (C.AccountNumber == AccountNumber) {
            Client = C;
            return true;
        }
    }
    return false;
}

stClient ChangeClientRecord(string AccountNumber) {

    stClient NewClient;

    NewClient.AccountNumber = AccountNumber;

    cout << "\n\n   Enter the PIN code:  ";
    getline(cin >> ws , NewClient.PinCode);

    cout << "Enter the client name:  ";
    getline(cin , NewClient.ClientName);

    cout << "Enter the phone number:  ";
    getline(cin , NewClient.PhoneNumber);

    cout << "Enter the account balance:  ";
    cin >> NewClient.AccountBalance;

    return NewClient;
}

bool MarkClientForDeleteByAccountNumber(string AccountNumber, vector<stClient>& vClients) {

    for (stClient& Client : vClients) {

        if (Client.AccountNumber == AccountNumber) {
            Client.DeleteClient = true;
            return true;
        }
    }
    return false;
}

vector<stClient> SaveClientDataToFile(string FileName, vector<stClient>& vClients, string Separator = "#//#") {

    fstream DataFile;
    DataFile.open(FileName, ios::out);
    string DataLine;

    if (DataFile.is_open()) {

        for (stClient & Client : vClients) {

            if (Client.DeleteClient == false) {
                DataLine = ConvertRecordToLine(Client);
                DataFile << DataLine << endl;
            }
        }
        DataFile.close();
    }
    return vClients;
}

void AddDataLineToFile(string FileName, string NewClientData) {

    fstream DataFile;
    DataFile.open(FileName, ios::out | ios::app);

    if (DataFile.is_open()) {
        DataFile << NewClientData << endl;
        DataFile.close();
    }
}

void AddNewClient() {

    stClient NewClient;
    NewClient = ReadNewClient();
    AddDataLineToFile(ClientsDataFile, ConvertRecordToLine(NewClient));
}

void AddNewClients() {

    char ConfirmAdding = 'Y';
    do {
        cout << "Adding new client:\n\n";
        AddNewClient();

        cout << "Client added successfully, do you want to add more clients [Y/N]:  ";
        cin >> ConfirmAdding;
    } while (toupper(ConfirmAdding) == 'Y');
}

bool DeleteClientByAccountNumber(vector<stClient>& vClients, string AccountNumber) {

    stClient Client;
    char ConfirmDeleting = 'N';
    if (FindClientByAccountNumber(AccountNumber, vClients, Client)) {

        PrintClientCard(Client);

        cout << "Are you sure you want to delete this client [Y/N]:  ";
        cin >>ConfirmDeleting;

        if(toupper(ConfirmDeleting) == 'Y') {

            MarkClientForDeleteByAccountNumber(AccountNumber, vClients);
            SaveClientDataToFile(ClientsDataFile, vClients);
            vClients = LoadClientDataFromFile(ClientsDataFile);

            cout << "Client deleted successfully\n.";
            return true;
        }
    }
    else {
        cout << "Client with account number [" << AccountNumber << "] is not found.\n";
    }
    return false;
}

bool UpdateClientByAccountNumber(string AccountNumber, vector<stClient>& vClients) {

    stClient Client;
    char ConfirmUpdating = 'N';

    if (FindClientByAccountNumber(AccountNumber, vClients, Client)) {

        PrintClientCard(Client);

        cout << "\nAre you sure you want to update this client [Y/N]:  ";
        cin >>ConfirmUpdating;

        if (toupper(ConfirmUpdating) == 'Y') {

            for (stClient C : vClients) {

                if (C.AccountNumber == AccountNumber) {
                    C = ChangeClientRecord(AccountNumber);
                    break;
                }
            }
            SaveClientDataToFile(ClientsDataFile, vClients);
            cout << "client Updated successfully.\n";
            return true;
        }
    }
    else {
        cout << "Client with account number [" << AccountNumber << "] is not found.\n";
    }
    return false;
}

double ReadNewAmount(string Message) {

    double Amount = 0;
    cout << Message;
    cin >> Amount;

    while (cin.fail()) {

        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Innvalid Input, " << Message;
        cin >> Amount;
    }
    return Amount;
}

bool DepositToAccount(string AccountNumber, vector<stClient>& vClients, stClient Client) {

    char ConfirmDeposit = 'Y';
    double NewAmount = 0;

    PrintClientCard(Client);
    NewAmount = ReadNewAmount("Enter deposit amount:  ");

    cout << "\nAre you sure you want perform this transaction [Y/N]:  ";
    cin >> ConfirmDeposit;

    if (toupper(ConfirmDeposit) == 'Y') {

        for (stClient & C : vClients) {
            
            if (C.AccountNumber == AccountNumber) {
                C.AccountBalance += NewAmount;

                cout << "\nDeposit done successfully, the new balance is " << C.AccountBalance << endl;
                SaveClientDataToFile(ClientsDataFile, vClients);
                return true;
            }
        }
    }
    return false;
}

double ReadWithdrawAmount(stClient Client) {

    double NewAmount = 0;

    NewAmount = ReadNewAmount("Enter withdraw amount:  ");
    while (NewAmount > Client.AccountBalance) {
        cout << "\nAmount exceeds the balance, you can withdraw up to " << Client.AccountBalance << endl;
        NewAmount = ReadNewAmount("Enter anothr amount:  ");
    }
    return NewAmount;
}

bool WithdrawFromAccount(string AccountNumber, vector<stClient>& vClients, stClient Client) {

    char ConfirmDeposit = 'Y';
    double NewAmount = 0;

    PrintClientCard(Client);

    NewAmount = ReadWithdrawAmount(Client);

    cout << "\nAre you sure you want perform this transaction [Y/N]:  ";
    cin >> ConfirmDeposit;

    if (toupper(ConfirmDeposit) == 'Y') {

        for (stClient & C : vClients) {
            
            if (C.AccountNumber == AccountNumber) {
                C.AccountBalance -= NewAmount;

                cout << "\nwithdraw done successfully, the new balance is " << C.AccountBalance << endl;
                SaveClientDataToFile(ClientsDataFile, vClients);
                return true;
            }
        }
    }
    return false;
}

void PrintClientBalance(stClient Data) {

    cout << "| " << setw(15) << left << Data.AccountNumber;
    cout << " | " << setw(40) << left << Data.ClientName;
    cout << " | " << setw(10) << left << Data.AccountBalance << " |";
}

double CalculateTotalBalance(vector<stClient>& vClients) {

    double Total = 0;
    for (stClient & Client : vClients) {
        Total += Client.AccountBalance;
    }
    return Total;
}

void PrintTotalBalance() {

    double TotalBalance = 0;
    vector<stClient> vClients = LoadClientDataFromFile(ClientsDataFile);
    printf("\t\t\t\tBalance List (%d) Client(s)\n", vClients.size());
    cout << "---------------------------------------------------------------------------\n";
    cout << "| " << setw(15) << left << "Account Number";
    cout << " | " << setw(40) << left << "Client Name";
    cout << " | " << setw(10) << left << "Balance" << " |" << endl;
    cout << "---------------------------------------------------------------------------\n";
    
    if (vClients.size() == 0) {
        cout << "\t\t\t\tNo clients availsble in the system\n";
    }

    for (stClient & Client : vClients) {
        PrintClientBalance(Client);
        cout << endl;
    }
    cout << "---------------------------------------------------------------------------\n";

    TotalBalance = CalculateTotalBalance(vClients);
    cout << "\t\t\t\t\t\tTotal balance = " << TotalBalance << "\n\n";
}

void PrintUsersData(stUser Data) {

    cout << "| " << setw(15) << left << Data.UserName;
    cout << " | " << setw(40) << left << Data.Password;
    cout << " | " << setw(10) << left << Data.Permission << " |";
}

stUser ConvertUserLineToRecord(string Line, string Separator = "#//#") {

    stUser User;
    vector<string> vUser;
    vUser = SplitString(Line);

    User.UserName = vUser[0];
    User.Password = vUser[1];
    User.Permission = stod(vUser[2]); //cast string to double.
    return User;
}

vector<stUser> LoadUserDataFromFile(string FileName, string Separator = "#//#") {

    vector<stUser> vUser;
    fstream DataFile;
    DataFile.open(FileName, ios::in);

    if (DataFile.is_open()) {

        stUser User;
        string Line;

        while (getline(DataFile, Line)) {

            User = ConvertUserLineToRecord(Line);
            vUser.push_back(User);
        }
        DataFile.close();
    }
    return vUser;
}

void PrintUsersList() {

    vector<stUser> vUser = LoadUserDataFromFile(UsersDataFile);
    printf("\t\t\t\tUsers List (%d) Client(s)\n", vUser.size());
    cout << "---------------------------------------------------------------------------\n";
    cout << "| " << setw(15) << left << "User Name";
    cout << " | " << setw(40) << left << "Password";
    cout << " | " << setw(10) << left << "Permissions" << " |" << endl;
    cout << "---------------------------------------------------------------------------\n";
    for (stUser & User : vUser) {
        PrintUsersData(User);
        cout << endl;
    }
    cout << "---------------------------------------------------------------------------\n";
}

bool IsUserExistsByUserName(string FileName, string UserName) {

    vector<stUser> vUser;
    fstream DataFile;
    DataFile.open(FileName, ios::in);

    if (DataFile.is_open()) {

        string Line;
        stUser User;

        while(getline(DataFile, Line)) {

            User = ConvertUserLineToRecord(Line);

            if (User.UserName == UserName) {
                DataFile.close();
                return true;
            }
        }
        DataFile.close();
    }
    return false;
}

int ReadPermissionsToSet() {

    int Permissions = 0;
    char Answer = 'N';

    cout << "\nDo you want to give full access? y/n? ";
    cin >> Answer;
    if (toupper(Answer) == 'Y') {
    return -1;
    }

    cout << "\nDo you want to give access to : \n ";

    cout << "\nShow Client List? y/n? ";
    cin >> Answer;
    if (toupper(Answer) == 'Y') {
        Permissions += enMainMenuPermissions::pListClients;
    }

    cout << "\nAdd New Client? y/n? ";
    cin >> Answer;
    if (toupper(Answer) == 'Y') {
        Permissions += enMainMenuPermissions::pAddNewClient;
    }

    cout << "\nDelete Client? y/n? ";
    cin >> Answer;
    if (toupper(Answer) == 'Y') {
        Permissions += enMainMenuPermissions::pDeleteClient;
    }

    cout << "\nUpdate Client? y/n? ";
    cin >> Answer;
    if (toupper(Answer) == 'Y') {
        Permissions += enMainMenuPermissions::pUpdateClients;
    }

    cout << "\nFind Client? y/n? ";
    cin >> Answer;
    if (toupper(Answer) == 'Y') {
        Permissions += enMainMenuPermissions::pFindClient;
    }

    cout << "\nTransactions? y/n? ";
    cin >> Answer;
    if (toupper(Answer) == 'Y') {
    Permissions += enMainMenuPermissions::pTranactions;
    }

    cout << "\nManage Users? y/n? ";
    cin >> Answer;
    if (toupper(Answer) == 'Y') {
        Permissions += enMainMenuPermissions::pManageUsers;
    }

    return Permissions;
}

stUser ReadNewUser() {

    stUser User;

    cout << "Enter UserName:  ";
    getline(cin >> ws, User.UserName);

    while (IsUserExistsByUserName(UsersDataFile, User.UserName)) {
        cout << "\nUser name iS alreasy exists,\n Enter another user name:  ";
        getline(cin , User.UserName);
    }

    cout << "\nEnter Password:  ";
    getline(cin , User.Password);
    
    User.Permission = ReadPermissionsToSet();

    return User;
}

string ConvertUserRecordToLine(stUser UserData, string Separator = "#//#") {

    string UserRecord = "";
    UserRecord += UserData.UserName + Separator;
    UserRecord += UserData.Password + Separator;
    UserRecord += to_string(UserData.Permission);
    return UserRecord;
}

void AddNewUser() {

    stUser NewUser;
    NewUser = ReadNewUser();
    AddDataLineToFile(UsersDataFile, ConvertUserRecordToLine(NewUser));
}

void AddNewUsers() {

    char ConfirmAdding = 'Y';
    do {
        cout << "Adding new User:\n\n";
        AddNewUser();

        cout << "User added successfully, do you want to add more Users [Y/N]:  ";
        cin >> ConfirmAdding;
    } while (toupper(ConfirmAdding) == 'Y');
}

bool FindUserByUserName(string UserName, vector<stUser>& vUser, stUser& User) {

    for (stUser& U : vUser) {

        if (U.UserName == UserName) {
            User = U;
            return true;
        }
    }
    return false;
}

void PrintUserCard(stUser User) {

    cout << "\n\nThe following are the User details:\n";
    cout << "----------------------------------------\n";
    cout << "User Name       : " << User.UserName << endl;
    cout << "Password        : " << User.Password << endl;
    cout << "Permissions     : " << User.Permission << endl;
    cout << "----------------------------------------\n\n";
}

bool MarkUserForDeleteByUserName(string UserName, vector<stUser>& vUser) {

    for (stUser& User : vUser) {

        if (User.UserName == UserName) {
            User.DeleteUser = true;
            return true;
        }
    }
    return false;
}

vector<stUser> SaveUserDataToFile(string FileName, vector<stUser>& vUser, string Separator = "#//#") {

    fstream DataFile;
    DataFile.open(FileName, ios::out);
    string DataLine;

    if (DataFile.is_open()) {

        for (stUser & User : vUser) {

            if (User.DeleteUser == false) {
                DataLine = ConvertUserRecordToLine(User);
                DataFile << DataLine << endl;
            }
        }
        DataFile.close();
    }
    return vUser;
}

bool DeleteUserByAccountNumber(vector<stUser>& vUser, string UserName) {

    stUser User;
    char ConfirmDeleting = 'N';
    if (FindUserByUserName(UserName, vUser, User)) {

        PrintUserCard(User);

        cout << "Are you sure you want to delete this User [Y/N]:  ";
        cin >>ConfirmDeleting;

        if(toupper(ConfirmDeleting) == 'Y') {

            MarkUserForDeleteByUserName(UserName, vUser);
            SaveUserDataToFile(UsersDataFile, vUser);
            vUser = LoadUserDataFromFile(UsersDataFile);

            cout << "User deleted successfully\n.";
            return true;
        }
    }
    else {
        cout << "User with user name [" << UserName << "] is not found.\n";
    }
    return false;
}

stUser ChangeUserRecord(string UserName) {

    stUser User;

    User.UserName = UserName;

    cout << "Enter Password:  ";
    getline(cin , User.Password);

    User.Permission = ReadPermissionsToSet();

    return User;
}

bool UpdateUserByUserName(string UserName, vector<stUser>& vUser) {

    stUser User;
    char ConfirmUpdating = 'N';

    if (FindUserByUserName(UserName, vUser, User)) {

        PrintUserCard(User);

        cout << "\nAre you sure you want to update this user [Y/N]:  ";
        cin >>ConfirmUpdating;

        if (toupper(ConfirmUpdating) == 'Y') {

            for (stUser U : vUser) {

                if (U.UserName == UserName) {
                    U = ChangeUserRecord(UserName);
                    break;
                }
            }
            SaveUserDataToFile(UsersDataFile, vUser);
            cout << "\nUser Updated successfully.\n";
            return true;
        }
    }
    else {
        cout << "User with user name [" << UserName << "] is not found.\n";
    }
    return false;
}

bool ReadUserLogin(vector<stUser> vUser, stUser& CurrentUser) {

    string UserName = "";
    string Password = "";

    cout << "Enter Username:  ";
    getline(cin >> ws, UserName);
    cout << "Enter Password:  ";
    getline (cin, Password);

    for (stUser& User : vUser) {
        if (User.UserName == UserName && User.Password == Password) {
            CurrentUser.UserName = User.UserName;
            CurrentUser.Password = User.Password;
            CurrentUser.Permission = User.Permission;
            return true;
        }
    }
    return false;
}

bool CheckAccessPermission(enMainMenuPermissions Permission) {

    if (CurrentUser.Permission == enMainMenuPermissions::pAll) {
        return true;
    }

    if ((Permission & CurrentUser.Permission) == Permission) {
        return true;
    }

    else {
        return false;
    }
}

string ReadUsername() {

    string UserName = "";
    cout << "\nEnter the User Name:  ";
    getline(cin >> ws, UserName);
    return UserName;
}

string ReadAccountNumber() {

    string AccountNumber = "";
    cout << "\nEnter the account numbrt:  ";
    cin >> AccountNumber;
    return AccountNumber;
}

void ShowDepositScreen() {

    cout << "----------------------------------------\n";
    cout << "            Deposit screen:\n";
    cout << "----------------------------------------\n\n";

    vector<stClient> vClients = LoadClientDataFromFile(ClientsDataFile);
    string AccountNumber = ReadAccountNumber();
    stClient Client;

    while (!FindClientByAccountNumber(AccountNumber, vClients, Client)) {

        cout << "\nClient with account number [" << AccountNumber << "] is not found.\n";
        AccountNumber = ReadAccountNumber();
    }
    DepositToAccount(AccountNumber, vClients, Client);
}

void ShowWithdrawScreen() {

    cout << "----------------------------------------\n";
    cout << "            Withdraw screen:\n";
    cout << "----------------------------------------\n\n";

    vector<stClient> vClients = LoadClientDataFromFile(ClientsDataFile);
    string AccountNumber = ReadAccountNumber();
    stClient Client;

    while (!FindClientByAccountNumber(AccountNumber, vClients, Client)) {

        cout << "\nClient with account number [" << AccountNumber << "] is not found.\n";
        AccountNumber = ReadAccountNumber();
    }
    WithdrawFromAccount(AccountNumber, vClients, Client);
}

void ShowAddUserScreen() {

    cout << "----------------------------------------\n";
    cout << "           New User screen:\n";
    cout << "----------------------------------------\n\n";

    AddNewUsers();
}

void ShowDeleteUserScreen() {

    cout << "----------------------------------------\n";
    cout << "          Delete User screen:\n";
    cout << "----------------------------------------\n\n";

    vector<stUser> vUser = LoadUserDataFromFile(UsersDataFile);
    string UserName = ReadUsername();

    if (UserName == "Admin") {
        cout << "Admin Is non-deletable.\n";
    }
    else {
        DeleteUserByAccountNumber(vUser, UserName);
    }
}

void ShowUpdateUserScreen() {

    cout << "----------------------------------------\n";
    cout << "          Update User screen:\n";
    cout << "----------------------------------------\n\n";

    vector<stUser> vUser = LoadUserDataFromFile(UsersDataFile);
    string UserName = ReadUsername();

    UpdateUserByUserName(UserName, vUser);
}

void ShowFindUserScreen() {

    cout << "----------------------------------------\n";
    cout << "          Find User screen:\n";
    cout << "----------------------------------------\n\n";

    vector<stUser> vUser = LoadUserDataFromFile(UsersDataFile);
    string UserName = ReadUsername();
    stUser User;

    if (FindUserByUserName(UserName, vUser, User)) {
        PrintUserCard(User);
    }
    else {
        cout << "\nUser with User Uame [" << UserName << "] is not found.";
    }
}

short ReadMUsersMenuOption() {
    
    short Choice;
    cout << "Choose what do you want to do [1:6]:  ";
    cin >> Choice;

    while (Choice < 1 && Choice > 6) {
        cout << "Invalid input, choose what do you want to do [1:6]:  ";
        cin >> Choice;
    }
    return Choice;
}

void GoBackToUserMenu() {

    cout << "\nPress any key to go back to the user menu...";
    system("pause>0");
    ShowUsersMenu();
}

void PerformUserMenuOption(enManageUsers choice) {

    switch (choice) {

        case enManageUsers::UsersList:
        system("cls");
        PrintUsersList(); 
        GoBackToUserMenu();
        break;
    
        case enManageUsers::AddUser:
        system("cls");
        ShowAddUserScreen();
        GoBackToUserMenu();
        break;
        
        case enManageUsers::DeleteUser:
        system("cls");
        ShowDeleteUserScreen();
        GoBackToUserMenu();
        break;

        case enManageUsers::UpdateUser:
        system("cls");
        ShowUpdateUserScreen();
        GoBackToUserMenu();
        break;

        case enManageUsers::FindUser:
        system("cls");
        ShowFindUserScreen();
        GoBackToUserMenu();
        break;

        default:
        ShowMainMenu();
    }
}

void ShowAddClientScreen() {

    cout << "----------------------------------------\n";
    cout << "           New client screen:\n";
    cout << "----------------------------------------\n\n";

    AddNewClients();
}

void ShowDeleteClientScreen() {

    cout << "----------------------------------------\n";
    cout << "          Delete client screen:\n";
    cout << "----------------------------------------\n\n";

    vector<stClient> vClients = LoadClientDataFromFile(ClientsDataFile);
    string AccountNumber = ReadAccountNumber();

    DeleteClientByAccountNumber(vClients, AccountNumber);
}

void ShowUpdateClientScreen() {

    cout << "----------------------------------------\n";
    cout << "          Update client screen:\n";
    cout << "----------------------------------------\n\n";

    vector<stClient> vClients = LoadClientDataFromFile(ClientsDataFile);
    string AccountNumber = ReadAccountNumber();

    UpdateClientByAccountNumber(AccountNumber, vClients);
}

void ShowFindClientScreen() {

    cout << "----------------------------------------\n";
    cout << "          Find client screen:\n";
    cout << "----------------------------------------\n\n";

    vector<stClient> vClients = LoadClientDataFromFile(ClientsDataFile);
    string AccountNumber = ReadAccountNumber();
    stClient Client;

    if (FindClientByAccountNumber(AccountNumber, vClients, Client)) {
        PrintClientCard(Client);
    }
    else {
        cout << "\nClient with account number [" << AccountNumber << "] is not found.";
    }
}

void ShowLoginScreen() {

    cout << "----------------------------------------\n";
    cout << "           Login screeen:\n";
    cout << "----------------------------------------\n\n";

    vector<stUser> vUser = LoadUserDataFromFile(UsersDataFile);

    while (!ReadUserLogin(vUser, CurrentUser)) {
        system("cls");
        cout << "----------------------------------------\n";
        cout << "           Login screeen:\n";
        cout << "----------------------------------------\n\n";

        cout << "Invalid Username/Password!\n\n";
    }
    ShowMainMenu();
}

void GoBackToMainMenu() {

    cout << "\nPress any key to go back to the main menu...";
    system("pause>0");
    ShowMainMenu();
}

void GoBackToTransactionsMenu() {

    cout << "\nPress any key to go back to the transactions menu...";
    system("pause>0");
    ShowTransactionsMenu();
}

short ReadMainMenuOption() {
    
    short Choice;
    cout << "Choose what do you want to do [1:8]:  ";
    cin >> Choice;

    while (Choice < 1 && Choice > 8) {
        cout << "Invalid input, choose what do you want to do [1:8]:  ";
        cin >> Choice;
    }
    return Choice;
}

short ReadTransactionsMenuOption() {
    
    short Choice;
    cout << "Choose what do you want to do [1:4]:  ";
    cin >> Choice;

    while (Choice < 1 && Choice > 4) {
        cout << "Invalid input, choose what do you want to do [1:4]:  ";
        cin >> Choice;
    }
    return Choice;
}

void PerformTransactionsMenuOption(enManageTransactions choice) {

    switch (choice) {

    case enManageTransactions::Deposit:
        system("cls");
        ShowDepositScreen();
        GoBackToTransactionsMenu();
        break;
    
    case enManageTransactions::WithDraw:
        system("cls");
        ShowWithdrawScreen();
        GoBackToTransactionsMenu();
        break;
    
    case enManageTransactions::TotalBalance:
        system("cls");
        PrintTotalBalance();
        GoBackToTransactionsMenu();
        break;

    default:
        ShowMainMenu();
    }
}

void ShowAccessDeniedScreen() {

    cout << "----------------------------------------\n";
    cout << "Access denied,\n";
    cout << "you don't have permission to do this,\n";
    cout << "please contact your admin.\n";
    cout << "----------------------------------------\n\n";
}

void PerformMainMenuOption(enManageClients choice) {

    switch (choice) {

        case enManageClients::ClientsList:
        system("cls");
        if (!CheckAccessPermission(enMainMenuPermissions::pListClients)) {
            ShowAccessDeniedScreen();
        }
        else {
            PrintAllClientData();
        }
        GoBackToMainMenu();
        break;
    
        case enManageClients::AddClient:
        system("cls");
        if (!CheckAccessPermission(enMainMenuPermissions::pAddNewClient)) {
            ShowAccessDeniedScreen();
        }
        else {
            ShowAddClientScreen();
        }
        GoBackToMainMenu();
        break;
    
        case enManageClients::DeleteClient:
        system("cls");
        if (!CheckAccessPermission(enMainMenuPermissions::pDeleteClient)) {
            ShowAccessDeniedScreen();
        }
        else {
            ShowDeleteClientScreen();
        }
        GoBackToMainMenu();
        break;

        case enManageClients::UpdateClientData:
        system("cls");
        if (!CheckAccessPermission(enMainMenuPermissions::pUpdateClients)) {
            ShowAccessDeniedScreen();
        }
        else {
            ShowUpdateClientScreen();
        }
        GoBackToMainMenu();
        break;
    
        case enManageClients::FindClient:
        system("cls");
        if (!CheckAccessPermission(enMainMenuPermissions::pFindClient)) {
            ShowAccessDeniedScreen();
        }
        else {
            ShowFindClientScreen();
        }
        GoBackToMainMenu();
        break;

        case enManageClients::Transactions:
        system("cls");
        if (!CheckAccessPermission(enMainMenuPermissions::pTranactions)) {
            ShowAccessDeniedScreen();
        }
        else {
            ShowTransactionsMenu();
        }
        GoBackToMainMenu();
        break;

        case enManageClients::ManageUsers:
        system("cls");
        if (!CheckAccessPermission(enMainMenuPermissions::pManageUsers)) {
            ShowAccessDeniedScreen();
        }
        else {
            ShowUsersMenu();
        }
        GoBackToMainMenu();
        break;

        default:
        system("cls");
        ShowLoginScreen();
    }
}

void ShowTransactionsMenu() {

    system("cls");
    cout << "=============================================\n";
    cout << "           Transactions Menu Screen\n";
    cout << "=============================================\n";
    cout << "\t[1] Deposit.\n";
    cout << "\t[2] Withdraw.\n";
    cout << "\t[3] Total balance.\n";
    cout << "\t[4] Main menu.\n";
    cout << "=============================================\n";
    PerformTransactionsMenuOption((enManageTransactions)ReadTransactionsMenuOption());
}

void ShowUsersMenu() {

    system("cls");
    cout << "=============================================\n";
    cout << "               User Menu Screen\n";
    cout << "=============================================\n";
    cout << "\t[1] Show users list.\n";
    cout << "\t[2] Add new user.\n";
    cout << "\t[3] Delete user.\n";
    cout << "\t[4] Update user.\n";
    cout << "\t[5] Find user.\n";
    cout << "\t[6] Main menu.\n";
    cout << "=============================================\n";
    PerformUserMenuOption((enManageUsers)ReadMUsersMenuOption());
}

void ShowMainMenu() {

    system("cls");
    cout << "=============================================\n";
    cout << "               Main Menu Screen\n";
    cout << "=============================================\n";
    cout << "\t[1] Show clients list.\n";
    cout << "\t[2] Add new client.\n";
    cout << "\t[3] Delete client.\n";
    cout << "\t[4] Update client info.\n";
    cout << "\t[5] Find client.\n";
    cout << "\t[6] Transactions.\n";
    cout << "\t[7] Manage Users.\n";
    cout << "\t[8] Logout.\n";
    cout << "=============================================\n";
    PerformMainMenuOption((enManageClients)ReadMainMenuOption());

}

int main() {

    ShowLoginScreen();
    system("pause>0");
    return 0;
}

/*

bool CheckUserPermissions(enManageClients choice) {
    switch (choice) {

        case enManageClients::ClientsList:
        return (((CurrentUser.Permission & 1) != 0) || CurrentUser.Permission == -1)? true : false;

        case enManageClients::AddClient:
        return (((CurrentUser.Permission & 2) != 0) || CurrentUser.Permission == -1)? true : false;

        case enManageClients::DeleteClient:
        return (((CurrentUser.Permission & 4) != 0) || CurrentUser.Permission == -1)? true : false;

        case enManageClients::UpdateClientData:
        return (((CurrentUser.Permission & 8) != 0) || CurrentUser.Permission == -1)? true : false;

        case enManageClients::FindClient:
        return (((CurrentUser.Permission & 16) != 0) || CurrentUser.Permission == -1)? true : false;

        case enManageClients::Transactions:
        return (((CurrentUser.Permission & 32) != 0) || CurrentUser.Permission == -1)? true : false;

        case enManageClients::ManageUsers:
        return (((CurrentUser.Permission & 64) != 0) || CurrentUser.Permission == -1)? true : false;

        default:
        return false;
    }
}

*/
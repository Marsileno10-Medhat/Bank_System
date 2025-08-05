#include <iostream>
#include <string>
#include <iomanip>
#include <vector>
#include <cctype>
#include <fstream>
#include <limits>
using namespace std;

enum en_ManageClientsData { Print = 1, Add = 2, Delete = 3, Update = 4, Find = 5, Exit = 6};

const string ClientsDataFileName = "Clients_data_file.txt";

struct st_AccountDetails
{
    string AccountNumber;
    string PinCode;
    string Name;
    string Phone;
    double Balance;
    bool DeleteClient = false;
};

short read_int(string Message) {

    short Num = 0;
    cout << Message;
    cin >> Num;

    while (cin.fail()) {

        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Innvalid Input, " << Message;
        cin >> Num;
    }
    return Num;
}

vector<string> split_string(string Data, string Separator = "#//#") {

    vector<string> vClientData;
    string Word = "";
    short pos = 0;

    while ((pos = Data.find(Separator)) != Separator.npos) {

        Word = Data.substr(0, pos);
        vClientData.push_back(Word);
        Data.erase(0, pos + Separator.length());
    }
    if (!Data.empty()) {
        vClientData.push_back(Data);
    }
    return vClientData;
}

st_AccountDetails convert_line_to_record(vector<string> ClientData) {

    st_AccountDetails Client;
    Client.AccountNumber = ClientData[0];
    Client.PinCode = ClientData[1];
    Client.Name = ClientData[2];
    Client.Phone = ClientData[3];
    Client.Balance = stod(ClientData[4]);
    return Client;
}

vector<st_AccountDetails> load_data_from_file(string FileName, string Separator) {

    fstream ClientsDataFile;
    ClientsDataFile.open(FileName, ios::in);

    vector<st_AccountDetails> vClientsData;
    st_AccountDetails Client;
    string Line;

    if (ClientsDataFile.is_open()) {

        while (getline(ClientsDataFile, Line)) {

            Client = convert_line_to_record(split_string(Line, Separator));
            vClientsData.push_back(Client);
        }
        ClientsDataFile.close();
    }
    return vClientsData;
}

void print_main_menu() {

    cout << "=============================================\n";
    cout << "               Main Menu Screen\n";
    cout << "=============================================\n";
    cout << "\t[1] Show clients list.\n";
    cout << "\t[2] Add new client.\n";
    cout << "\t[3] Delete client.\n";
    cout << "\t[4] Update client info.\n";
    cout << "\t[5] Find client.\n";
    cout << "\t[6] Exit.\n";
    cout << "=============================================\n";
}

void back_to_main_menu() {

    cout << "\n\nPress any key to go back to the main menu...";
    system("pause>0");
}

short main_menu_choice() {
    
    short Choice;
    system("cls");
    print_main_menu();
    Choice = read_int("what you want to do? [1:6]:  ");

    while (Choice != 1 && Choice != 2 && Choice != 3 && Choice != 4 && Choice != 5 && Choice != 6) {
        cout << "Invalid input, ";
        Choice = read_int("what you want to do? [1:6]:  ");
    }
    return Choice;
}

void print_client(st_AccountDetails Data) {

    cout << "| " << left << setw(15) << Data.AccountNumber;
    cout << " | " << left << setw(10) << Data.PinCode;
    cout << " | " << left << setw(40) << Data.Name;
    cout << " | " << left << setw(15) << Data.Phone;
    cout << " | " << left << setw(10) << Data.Balance << " |" << endl;
}

void print_clients_data(vector<st_AccountDetails>& vClientsData) {

    printf("                                       Client List (%d) Client(s)\n", vClientsData.size());
    cout << "----------------------------------------------------------------------------------------------------------\n";
    cout << "| " << left << setw(15) << "Account Number";
    cout << " | " << left << setw(10) << "Pin Code";
    cout << " | " << left << setw(40) << "Client Name";
    cout << " | " << left << setw(15) << "Phone";
    cout << " | " << left << setw(10) << "Balance" << " |" << endl;
    cout << "----------------------------------------------------------------------------------------------------------\n";
    
    if (vClientsData.size() == 0) {
        cout << "\t\t\t\tNo clients availsble in the system\n";
    }

    for (st_AccountDetails & C : vClientsData) {
        print_client(C);
    }
    cout << "----------------------------------------------------------------------------------------------------------\n";
}

string read_account_number(string Message) {

    string AccountNumber;

    cout << Message;
    getline(cin >> ws, AccountNumber);

    return AccountNumber;
}

bool is_account_in_the_file(vector<st_AccountDetails>& vClientsData, string AccountNumber) {

    for (st_AccountDetails & C : vClientsData) {

        if (C.AccountNumber == AccountNumber) {
            return true;
        }
    }
    return false;
}

char confirm_system_action(string Message) {

    char C;
    cout << Message;
    cin >> C;

    while (toupper(C) != 'Y' && toupper(C) != 'N') {
        cout << "Invalid input, " << Message;
        cin >> C;
    }
    return toupper(C); 
}

st_AccountDetails read_client_data (string AccountNumber) {

    st_AccountDetails NewClient;

    NewClient.AccountNumber = AccountNumber;

    cout << "Enter the PIN code:  ";
    getline(cin >> ws , NewClient.PinCode);

    cout << "Enter the client name:  ";
    getline(cin , NewClient.Name);

    cout << "Enter the phone number:  ";
    getline(cin , NewClient.Phone);

    cout << "Enter the account balance:  ";
    cin >> NewClient.Balance;

    return NewClient;
}

string convert_record_to_line(st_AccountDetails& ClientData, string Separator) {

    string ClientDataLine;

    ClientDataLine += ClientData.AccountNumber + Separator;
    ClientDataLine += ClientData.PinCode + Separator;
    ClientDataLine += ClientData.Name + Separator;
    ClientDataLine += ClientData.Phone + Separator;
    ClientDataLine += to_string(ClientData.Balance);

    return ClientDataLine;
}

void add_new_client_to_file(string FileName, string NewClientData) {

    fstream ClientsDataFile;
    ClientsDataFile.open(FileName, ios::out | ios::app);

    if (ClientsDataFile.is_open()) {
        ClientsDataFile << NewClientData << endl;
    }
    ClientsDataFile.close();
}

void add_new_client(string FileName, vector<st_AccountDetails>& vClientsData, string Separator) {

    char AddNewClient = 'Y';
    st_AccountDetails NewClient;

    string AccountNumber = read_account_number("Enter the account number you want to add:  ");
    do {
        while (is_account_in_the_file(vClientsData, AccountNumber)) {

            cout << "\nClient with [" << AccountNumber << "] already exists, ";
            AccountNumber = read_account_number("Enter the account number you want to add:  "); 
        }

        cout << endl;
        NewClient = read_client_data(AccountNumber);

        vClientsData.push_back(NewClient);
        add_new_client_to_file(FileName, convert_record_to_line(NewClient,  Separator));
        
        cout << "\n\nClient added successfully, ";
        AddNewClient = confirm_system_action("Do you want to add new clients? [Y/N]:  ");
    } while (AddNewClient == 'Y');
}

void print_client_data(st_AccountDetails Client) {

    cout << "\n\nThe following are the client details:\n";
    cout << "----------------------------------------\n";
    cout << "Account number  : " << Client.AccountNumber << endl;
    cout << "PIN code        : " << Client.PinCode << endl;
    cout << "Client name     : " << Client.Name << endl;
    cout << "Phone number    : " << Client.Phone << endl;
    cout << "Account Balance : " << Client.Balance << endl;
    cout << "----------------------------------------\n\n";
}

void print_account_details(vector<st_AccountDetails>& vClientsData, string AccountNumber) {

    for (st_AccountDetails & C : vClientsData) {

        if (C.AccountNumber == AccountNumber) {
            print_client_data(C);
            break;
        }
    }
}

bool mark_deleting_account(vector<st_AccountDetails>& vClientsData, string AccountNumber) {

    for (st_AccountDetails & C : vClientsData) {

        if (C.AccountNumber == AccountNumber) {
            C.DeleteClient = true;
            return true;
        }
    }
    return false;
}

void delete_client_from_file(string FileName, vector<st_AccountDetails>& vClientsData, string Separator) {

    fstream ClientsDataFile(FileName, ios::out);
    string DataLine;
    
    if (ClientsDataFile.is_open()) {

        for (st_AccountDetails & C : vClientsData) {

            if (C.DeleteClient != true) {

                DataLine = convert_record_to_line(C, Separator);
                ClientsDataFile << DataLine << endl;
            }
        }
        vClientsData = load_data_from_file(FileName, Separator);
        ClientsDataFile.close();
    }
}

void delete_client(string FileName, vector<st_AccountDetails>& vClientsData, string Separator) {

    char ConfirmDeletion;
    string AccountNumber = read_account_number("Enter the accout number you want to delete:  ");

    if (!is_account_in_the_file(vClientsData, AccountNumber)) {

        cout << "Client with [" << AccountNumber << "]does not exists.";
    }
    else {
        print_account_details(vClientsData, AccountNumber);
        ConfirmDeletion = confirm_system_action("Are you sure you want to delete [Y/N]:  ");

        if (ConfirmDeletion == 'Y') {

            mark_deleting_account(vClientsData, AccountNumber);
            delete_client_from_file(FileName, vClientsData, Separator);
            cout << "Client deleted successfully.\n";
        }
    }
}

void update_client_data(vector<st_AccountDetails>& vClientsData, string AccountNumber) {

    for (st_AccountDetails & C : vClientsData) {

        if (C.AccountNumber == AccountNumber) {

            C = read_client_data(AccountNumber);
            break;
        }
    }
}

void save_data_to_file(string FileName, vector<st_AccountDetails>& vClientsData, string Separator) {

    fstream ClientsDataFile;
    ClientsDataFile.open(FileName, ios::out);
    string DataLine;

    if (ClientsDataFile.is_open()) {

        for (st_AccountDetails & C : vClientsData) {

            DataLine = convert_record_to_line(C, Separator);
            ClientsDataFile << DataLine << endl;
        }
        ClientsDataFile.close();
    }
}

void update_data(string FileName, vector<st_AccountDetails>& vClientsData, string Separator) {

    char ConfirmUpdate = 'Y';
    string AccountNumber = read_account_number("Enter the account number you want to update:  ");
    
    if (!is_account_in_the_file(vClientsData, AccountNumber)) {
        cout << "\nClient with [" << AccountNumber << "]does not exists.";
    }
    else {
        print_account_details(vClientsData, AccountNumber);

        ConfirmUpdate = confirm_system_action("Do you want to add update the client's data? [Y/N]:  ");

        if (ConfirmUpdate == 'Y') {

            update_client_data(vClientsData, AccountNumber);
            save_data_to_file(FileName, vClientsData, Separator);
            cout << "Client data updated successfully\n";
        }
    }
}


void find_Client(string FileName, vector<st_AccountDetails>& vClientsData, string Separator) {

    string AccountNumber = read_account_number("Enter the account number you want to search for:  ");

    if (!is_account_in_the_file(vClientsData, AccountNumber)) {
        cout << "\nClient with [" << AccountNumber << "]does not exists.";
    }
    else {
        print_account_details(vClientsData, AccountNumber);
    }
}

void show_add_screen(vector<st_AccountDetails>& vClientsData, string Separator) {

    cout << "----------------------------------------\n";
    cout << "           New client screen:\n";
    cout << "----------------------------------------\n\n";
    add_new_client(ClientsDataFileName, vClientsData, Separator);
}

void show_delete_screen(vector<st_AccountDetails>& vClientsData, string Separator) {

    cout << "----------------------------------------\n";
    cout << "          Delete client screen:\n";
    cout << "----------------------------------------\n\n";
    delete_client(ClientsDataFileName, vClientsData, Separator);
}

void show_update_screen(vector<st_AccountDetails>& vClientsData, string Separator) {

    cout << "----------------------------------------\n";
    cout << "          Update client screen:\n";
    cout << "----------------------------------------\n\n";
    update_data(ClientsDataFileName, vClientsData, Separator);
}

void show_find_screen(vector<st_AccountDetails>& vClientsData, string Separator) {

    cout << "----------------------------------------\n";
    cout << "          Find client screen:\n";
    cout << "----------------------------------------\n\n";
    find_Client(ClientsDataFileName, vClientsData, Separator);
}

void show_exit_screen(vector<st_AccountDetails>& vClientsData, string Separator) {

    cout << "----------------------------------------\n";
    cout << "           Program ends :-)\n";
    cout << "----------------------------------------\n\n";
}

void main_menu_controller(vector<st_AccountDetails>& vClientsData, string Separator) {

    en_ManageClientsData choice;
    do {
    system("cls");
    choice = (en_ManageClientsData)main_menu_choice();
    switch (choice){

        case en_ManageClientsData::Print:
            system("cls");
            print_clients_data(vClientsData);
            back_to_main_menu();
            break;
    
        case en_ManageClientsData::Add:
            system("cls");
            show_add_screen(vClientsData, Separator);
            back_to_main_menu();
            break;
    
        case en_ManageClientsData::Delete:
            system("cls");
            show_delete_screen(vClientsData, Separator);
            back_to_main_menu();
            break;

        case en_ManageClientsData::Update:
            system("cls");
            show_update_screen(vClientsData, Separator);
            back_to_main_menu();
            break;
    
        case en_ManageClientsData::Find:
            system("cls");
            show_find_screen(vClientsData, Separator);
            back_to_main_menu();
            break;
        default:
            system("cls");
            show_exit_screen(vClientsData, Separator);
    }
    } while (choice != en_ManageClientsData::Exit);
}

int main() {

    string Separator = "#//#";
    vector<st_AccountDetails> vClientsData = load_data_from_file(ClientsDataFileName, Separator);
    main_menu_controller(vClientsData, Separator);

    system("pause>0");
    return 0;
}
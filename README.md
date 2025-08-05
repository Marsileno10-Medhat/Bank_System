# Bank_System
A simple C++ console-based banking system for managing client records (add, delete, update, find, and display).
=======
# Bank System Project

This project is a C++ console-based banking system designed to manage client accounts and perform basic banking operations. Below is an overview of the different versions of the codebase, starting with version 1.0, followed by the enhancements introduced in versions 1.1 and 1.2.

## Version 1.0

The initial version of the bank system provides core functionality for managing client accounts stored in a text file (`Clients_data_file.txt`). Key features include:

- **Client Management**:
  - View a list of all clients.
  - Add new clients with details such as account number, PIN code, name, phone number, and balance.
  - Delete clients by marking them for deletion and updating the file.
  - Update client information.
  - Search for clients by account number.
- **Data Storage**:
  - Client data is stored in a text file with fields separated by a delimiter (`#//#`).
  - Data is loaded from and saved to the file for persistence.
- **User Interface**:
  - A console-based main menu allows users to select operations (Show Clients, Add Client, Delete Client, Update Client, Find Client, Exit).
  - Input validation ensures robust handling of user inputs.
- **Implementation Details**:
  - Uses a `struct st_AccountDetails` to store client information.
  - Employs a `vector` to manage client data in memory.
  - File operations are performed using `fstream` for reading and writing client data.
  - The system ensures unique account numbers and provides confirmation prompts for critical actions like deletion.

### Usage
- Compile and run `BankSystem1.0.cpp`.
- Ensure the `Clients_data_file.txt` is in the same directory as the executable.
- Interact with the console menu to perform operations.

## Version 1.1

This version builds upon version 1.0 by introducing transaction-related functionality and improving code structure. New features and changes include:

- **New Transaction Menu**:
  - Added a transactions menu with options for Deposit, Withdraw, and Total Balance.
  - **Deposit**: Allows users to add funds to a client's account.
  - **Withdraw**: Enables withdrawal from a client's account with balance validation to prevent overdrafts.
  - **Total Balance**: Displays a summary of all clients' balances and the total sum.
- **Code Improvements**:
  - Renamed the client structure to `stClient` and fields to be more descriptive (e.g., `Name` to `ClientName`, `Phone` to `PhoneNumber`).
  - Improved function naming for clarity (e.g., `add_new_client` to `AddNewClient`).
  - Enhanced input handling for transactions with validation for numeric inputs and balance checks.
  - Streamlined menu navigation with a dedicated `ShowMainMenu` function and a separate `ShowTransactionsMenu`.
- **Structural Changes**:
  - Introduced new enums (`enManageClients` and `enManageTransactions`) for better menu option management.
  - Refactored code to reduce redundancy and improve modularity (e.g., separate functions for deposit and withdraw operations).
  - Improved file handling by reloading client data before critical operations to ensure data consistency.

### Usage
- Compile and run `BankSystem1.1.cpp`.
- Ensure `Clients_data_file.txt` is present.
- Access the transactions menu via the main menu to perform a deposit, withdrawal, or view total balances.

## Version 1.2

Version 1.2 introduces user authentication and permission-based access control, along with user management features, making the system more secure and suitable for multi-user environments. Key enhancements include:

- **User Authentication**:
  - Added a login screen requiring a username and password.
  - User data is stored in a new file (`Users_data_file.txt`) with fields for username, password, and permissions.
- **User Management**:
  - New menu for managing users with options to list, add, delete, update, and find users.
  - Users can have specific permissions controlling access to features like client list, add client, delete client, update client, find client, transactions, and user management.
  - Permissions are managed using a bit-field approach (`enMainMenuPermissions`), allowing fine-grained access control.
  - The `Admin` user is protected from deletion to ensure system integrity.
- **Permission-Based Access**:
  - Each menu option checks the current user's permissions before execution.
  - A `ShowAccessDeniedScreen` is displayed if the user lacks the required permission.
  - Full access can be granted to a user with a permission value of `-1`.
- **Code Enhancements**:
  - Added a `stUser` structure to store user data (username, password, permissions).
  - Implemented functions for user data management, similar to client data handling (e.g., `LoadUserDataFromFile`, `ConvertUserLineToRecord`).
  - Introduced a global `CurrentUser` variable to track the logged-in user.
  - Enhanced the main menu to include options for managing users and logging out.
- **Security Features**:
  - Ensures unique usernames and validates login credentials.
  - Prevents unauthorized access to sensitive operations based on permissions.

### Usage
- Compile and run `BankSystem1.2.cpp`.
- Ensure both `Clients_data_file.txt` and `Users_data_file.txt` are in the same directory.
- Log in with a valid username and password (create users in `Users_data_file.txt` with the format `username#//#password#//#permissions`).
- Navigate the main menu, which now includes user management and logout options, with access controlled by permissions.

## General Notes
- **File Format**: Both client and user data files use the `#//#` delimiter to separate fields.
- **Dependencies**: The code uses standard C++ libraries (`iostream`, `string`, `iomanip`, `vector`, `fstream`, `limits`).
- **Error Handling**: All versions include input validation to handle invalid inputs gracefully.
- **Extensibility**: The system is designed to be modular, allowing for future enhancements like additional transaction types or user roles.

## Running the Program
1. Ensure a C++ compiler (e.g., g++) is installed.
2. Compile the desired version (e.g., `g++ BankSystem1.2.cpp -o BankSystem`).
3. Create or ensure the presence of `Clients_data_file.txt` (and `Users_data_file.txt` for version 1.2).
4. Run the executable and follow the console prompts.

## Future Improvements
- Add transaction history logging.
- Implement data encryption for sensitive information.
- Support for multiple sessions or concurrent users.
- Add input validation for phone numbers and PIN codes.

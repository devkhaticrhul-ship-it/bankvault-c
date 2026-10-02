# BankVault

BankVault is a console-based Bank Management System written in C.

The project is built around a simple banking workflow where users can create
accounts, log in using a PIN, manage their balance, transfer money, and view
their transaction history. It also includes a separate admin panel for
managing and viewing bank information.

The main goal of this project was to build a practical C application using
multiple source files, structures, file handling, input validation, and
modular programming instead of keeping everything inside one large C file.

## Features

### Customer Features

- Create a new bank account
- Automatically generate account numbers
- PIN-based account login
- Maximum login attempt limit
- View account details
- Deposit money
- Withdraw money
- Transfer money between accounts
- View transaction history
- View account statement
- Change account PIN
- Close account
- Search for an account
- Closed account status handling

### Transaction Features

- Deposit transaction records
- Withdrawal transaction records
- Transfer Out records
- Transfer In records
- Unique transaction IDs
- Balance recorded after each transaction
- Transaction receipts for deposits, withdrawals, and transfers

### Admin Features

- Admin login
- View all accounts
- Search accounts
- View bank statistics
- View all transactions

### Input Validation

The program validates several types of user input:

- Account numbers
- Four-digit PINs
- PIN strength during creation/change
- Login PIN format
- Phone numbers
- Names
- Transaction amounts
- Yes/No confirmations
- Invalid menu choices

## Project Structure

```text
Bank MS/
│
├── main.c
├── account.c
├── account.h
├── transaction.c
├── transaction.h
├── bank.c
├── bank.h
├── admin.c
├── admin.h
├── file_manager.c
├── file_manager.h
├── input.c
├── input.h
│
├── data/
│   ├── account.dat
│   ├── accounts.dat
│   └── transactions.dat
│
├── screenshots
├── README.md
└── .gitignore

How It Works

The program starts with the main BankVault menu.

========================================
              BANKVAULT
        Simple Banking System
========================================
1. Create Account
2. Login
3. Search Account
4. Admin Panel
5. Exit
========================================

A customer can create an account and receive an automatically generated
account number.

After logging in, the customer gets access to the account menu:

========== ACCOUNT MENU ==========
1. Account Details
2. Deposit Money
3. Withdraw Money
4. Transfer Money
5. Transaction History
6. Account Statement
7. Change PIN
8. Close Account
9. Logout
==================================
Data Storage

BankVault uses binary files to store account and transaction information.

The files are stored inside the data directory:

data/accounts.dat
data/transactions.dat

The program uses C file handling functions such as:

fopen()
fread()
fwrite()
fseek()
fclose()

This allows account and transaction information to remain available after
the program is closed.

Account Management

Each account stores information such as:

Account number
Customer name
Phone number
PIN
Account balance
Account status

Accounts are represented using a C structure:

typedef struct
{
    int account_no;
    char name[NAME_SIZE];
    char phone[PHONE_SIZE];
    int pin;
    double balance;
    int active;
} Account;

The active field is used to distinguish between active and closed accounts.

Transaction Management

Transactions are stored separately from account information.

Each transaction contains:

Transaction ID
Account number
Transaction type
Amount
Balance after transaction

Examples of transaction types are:

Deposit
Withdrawal
Transfer Out
Transfer In
PIN Handling

BankVault uses different validation rules depending on the operation.

When creating or changing a PIN:

The PIN must contain exactly four digits.
Some very simple PINs are rejected.

During login:

The PIN must contain exactly four digits.
The program compares it with the stored account PIN.
The user gets a limited number of login attempts.

This keeps PIN creation rules separate from normal login verification.

Admin Panel

The admin section provides an overview of the bank data.

Admin functionality includes:

Viewing all accounts
Searching for accounts
Viewing bank statistics
Viewing all stored transactions

The admin section is separate from the normal customer account menu.

Requirements

To compile and run BankVault, you need:

Windows
GCC / MinGW
Command Prompt or VS Code

Compilation

Open Command Prompt in the project directory:

cd /d "D:\MyCproj\Intermidiate\Bank MS"

Compile all source files together:

gcc main.c account.c transaction.c file_manager.c input.c bank.c admin.c -o bankvault.exe

Run the program:

bankvault.exe
Example Workflow

A normal customer workflow can be:

Create Account
      ↓
Receive Account Number
      ↓
Login
      ↓
Account Details
      ↓
Deposit / Withdraw
      ↓
Transfer Money
      ↓
View Transaction History
      ↓
View Account Statement
      ↓
Logout

Screenshots

Screenshots from the project are stored in the project directory.

They show different parts of the BankVault console application such as account
management, transactions, and administrative features.

What I Practiced

This project helped me work with several C programming concepts together:

Structures

Functions
Header files
Multiple source files
File handling
Binary file storage
fread() and fwrite()
Searching records
Updating records
Input validation
Modular programming
Menu-driven programs
Basic authentication logic
Transaction processing
Git and GitHub
 
 Future Improvements

Some possible improvements for future versions are:

Better transaction rollback handling
More detailed transaction timestamps
Password/PIN encryption or hashing
More advanced admin controls
Account deletion/archive handling
Improved reporting
Better command-line interface
Database-based storage instead of binary files

Author

Built as an intermediate-level C programming project to practice
modular programming, file handling, structures, validation, and GitHub
project management.
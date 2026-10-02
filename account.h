#ifndef ACCOUNT_H
#define ACCOUNT_H

#define NAME_SIZE 50
#define PHONE_SIZE 15

typedef struct
{
    int account_no;
    char name[NAME_SIZE];
    char phone[PHONE_SIZE];
    int pin;
    double balance;
    int active;
} Account;

void createAccount(void);
void loginAccount(void);
void searchAccount(void);
void showAccountDetails(int account_no);
void depositMoney(int account_no);
void withdrawMoney(int account_no);
void transferMoney(int account_no);
void changePin(int account_no);
void closeAccount(int account_no);

int findAccount(int account_no, Account *account);
int updateAccount(Account account);

#endif
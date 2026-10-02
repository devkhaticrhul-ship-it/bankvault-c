#include <stdio.h>
#include "account.h"
#include "transaction.h"
#include "input.h"

#define ACCOUNT_FILE "data/accounts.dat"
#define MAX_LOGIN_ATTEMPTS 3

static int getNextAccountNumber(void)
{
    FILE *file;
    Account account;
    int highest = 1000;

    file = fopen(ACCOUNT_FILE, "rb");

    if (file == NULL)
        return highest + 1;

    while (fread(&account, sizeof(Account), 1, file) == 1)
    {
        if (account.account_no > highest)
            highest = account.account_no;
    }

    fclose(file);

    return highest + 1;
}

int findAccount(int account_no, Account *account)
{
    FILE *file;

    file = fopen(ACCOUNT_FILE, "rb");

    if (file == NULL)
        return 0;

    while (fread(account, sizeof(Account), 1, file) == 1)
    {
        if (account->account_no == account_no && account->active)
        {
            fclose(file);
            return 1;
        }
    }

    fclose(file);
    return 0;
}

static int findAnyAccount(int account_no, Account *account)
{
    FILE *file;

    file = fopen(ACCOUNT_FILE, "rb");

    if (file == NULL)
        return 0;

    while (fread(account, sizeof(Account), 1, file) == 1)
    {
        if (account->account_no == account_no)
        {
            fclose(file);
            return 1;
        }
    }

    fclose(file);
    return 0;
}

int updateAccount(Account account)
{
    FILE *file;
    Account current;

    file = fopen(ACCOUNT_FILE, "rb+");

    if (file == NULL)
        return 0;

    while (fread(&current, sizeof(Account), 1, file) == 1)
    {
        if (current.account_no == account.account_no)
        {
            fseek(file, -(long)sizeof(Account), SEEK_CUR);
            fwrite(&account, sizeof(Account), 1, file);

            fclose(file);
            return 1;
        }
    }

    fclose(file);
    return 0;
}

void createAccount(void)
{
    FILE *file;
    Account account;

    account.account_no = getNextAccountNumber();

    printf("\n========== CREATE ACCOUNT ==========\n");

    readName("Enter your name: ", account.name, NAME_SIZE);

    readPhone("Enter phone number: ", account.phone, PHONE_SIZE);

    account.pin = readPin("Create a 4-digit PIN: ");

    account.balance = 0.0;
    account.active = 1;

    file = fopen(ACCOUNT_FILE, "ab");

    if (file == NULL)
    {
        printf("\nUnable to open account file.\n");
        return;
    }

    if (fwrite(&account, sizeof(Account), 1, file) != 1)
    {
        fclose(file);
        printf("\nUnable to save account.\n");
        return;
    }

    fclose(file);

    printf("\nAccount created successfully.\n");
    printf("Your account number is: %d\n", account.account_no);
}

void loginAccount(void)
{
    int account_no;
    int pin;
    int choice;
    int attempt;
    int login_successful = 0;
    Account account;

    printf("\n========== ACCOUNT LOGIN ==========\n");

    account_no = readInt("Account number: ");

    if (!findAccount(account_no, &account))
    {
        printf("\nAccount not found or account is closed.\n");
        return;
    }

    for (attempt = 1; attempt <= MAX_LOGIN_ATTEMPTS; attempt++)
    {
        pin = readLoginPin("PIN: ");

        if (account.pin == pin)
        {
            login_successful = 1;
            break;
        }

        if (attempt < MAX_LOGIN_ATTEMPTS)
        {
            printf("\nIncorrect PIN. Attempts remaining: %d\n",
                   MAX_LOGIN_ATTEMPTS - attempt);
        }
    }

    if (!login_successful)
    {
        printf("\nToo many incorrect PIN attempts.\n");
        printf("Login cancelled.\n");
        return;
    }

    printf("\nWelcome, %s!\n", account.name);

    while (1)
    {
        printf("\n========== ACCOUNT MENU ==========\n");
        printf("1. Account Details\n");
        printf("2. Deposit Money\n");
        printf("3. Withdraw Money\n");
        printf("4. Transfer Money\n");
        printf("5. Transaction History\n");
        printf("6. Account Statement\n");
        printf("7. Change PIN\n");
        printf("8. Close Account\n");
        printf("9. Logout\n");
        printf("==================================\n");

        choice = readInt("Enter your choice: ");

        switch (choice)
        {
            case 1:
                showAccountDetails(account_no);
                break;

            case 2:
                depositMoney(account_no);
                break;

            case 3:
                withdrawMoney(account_no);
                break;

            case 4:
                transferMoney(account_no);
                break;

            case 5:
                showTransactions(account_no);
                break;

            case 6:
                showAccountStatement(account_no);
                break;

            case 7:
                changePin(account_no);
                break;

            case 8:
                closeAccount(account_no);
                return;

            case 9:
                printf("\nLogged out successfully.\n");
                return;

            default:
                printf("\nInvalid choice. Try again.\n");
        }
    }
}

void searchAccount(void)
{
    int account_no;
    Account account;

    printf("\n========== ACCOUNT SEARCH ==========\n");

    account_no = readInt("Enter account number: ");

    if (!findAnyAccount(account_no, &account))
    {
        printf("\nAccount not found.\n");
        return;
    }

    printf("\nAccount Number : %d\n", account.account_no);
    printf("Name           : %s\n", account.name);
    printf("Phone          : %s\n", account.phone);
    printf("Balance        : %.2f\n", account.balance);

    if (account.active)
        printf("Status         : Active\n");
    else
        printf("Status         : Closed\n");
}

void showAccountDetails(int account_no)
{
    Account account;

    if (!findAccount(account_no, &account))
    {
        printf("\nAccount not found.\n");
        return;
    }

    printf("\n========== ACCOUNT DETAILS ==========\n");
    printf("Account Number : %d\n", account.account_no);
    printf("Name           : %s\n", account.name);
    printf("Phone          : %s\n", account.phone);
    printf("Balance        : %.2f\n", account.balance);
}

void depositMoney(int account_no)
{
    Account account;
    double amount;
    int transaction_id;

    if (!findAccount(account_no, &account))
    {
        printf("\nAccount not found.\n");
        return;
    }

    amount = readAmount("\nEnter amount to deposit: ");

    account.balance += amount;

    if (!updateAccount(account))
    {
        printf("\nUnable to update account.\n");
        return;
    }

    transaction_id = saveTransaction(
        account.account_no,
        "Deposit",
        amount,
        account.balance
    );

    printf("\nDeposit successful.\n");
    printf("New balance: %.2f\n", account.balance);

    if (transaction_id != 0)
    {
        showDepositReceipt(
            transaction_id,
            account.account_no,
            amount,
            account.balance
        );
    }
}

void withdrawMoney(int account_no)
{
    Account account;
    double amount;
    int transaction_id;

    if (!findAccount(account_no, &account))
    {
        printf("\nAccount not found.\n");
        return;
    }

    amount = readAmount("\nEnter amount to withdraw: ");

    if (amount > account.balance)
    {
        printf("\nInsufficient balance.\n");
        return;
    }

    account.balance -= amount;

    if (!updateAccount(account))
    {
        printf("\nUnable to update account.\n");
        return;
    }

    transaction_id = saveTransaction(
        account.account_no,
        "Withdrawal",
        amount,
        account.balance
    );

    printf("\nWithdrawal successful.\n");
    printf("New balance: %.2f\n", account.balance);

    if (transaction_id != 0)
    {
        showWithdrawalReceipt(
            transaction_id,
            account.account_no,
            amount,
            account.balance
        );
    }
}

void transferMoney(int account_no)
{
    Account sender;
    Account receiver;
    int receiver_no;
    double amount;
    int transaction_id;

    if (!findAccount(account_no, &sender))
    {
        printf("\nSender account not found.\n");
        return;
    }

    receiver_no = readInt("\nEnter receiver account number: ");

    if (receiver_no == account_no)
    {
        printf("\nYou cannot transfer money to the same account.\n");
        return;
    }

    if (!findAccount(receiver_no, &receiver))
    {
        printf("\nReceiver account not found or account is closed.\n");
        return;
    }

    amount = readAmount("Enter amount to transfer: ");

    if (amount > sender.balance)
    {
        printf("\nInsufficient balance.\n");
        return;
    }

    sender.balance -= amount;
    receiver.balance += amount;

    if (!updateAccount(sender))
    {
        printf("\nUnable to update sender account.\n");
        return;
    }

    if (!updateAccount(receiver))
    {
        printf("\nUnable to update receiver account.\n");
        return;
    }

    transaction_id = saveTransaction(
        sender.account_no,
        "Transfer Out",
        amount,
        sender.balance
    );

    saveTransaction(
        receiver.account_no,
        "Transfer In",
        amount,
        receiver.balance
    );

    printf("\nTransfer successful.\n");
    printf("Amount transferred: %.2f\n", amount);
    printf("Your new balance: %.2f\n", sender.balance);

    if (transaction_id != 0)
    {
        showTransferReceipt(
            transaction_id,
            sender.account_no,
            receiver.account_no,
            amount,
            sender.balance
        );
    }
}

void changePin(int account_no)
{
    Account account;
    int old_pin;
    int new_pin;
    int confirm_pin;

    if (!findAccount(account_no, &account))
    {
        printf("\nAccount not found.\n");
        return;
    }

    old_pin = readLoginPin("\nEnter current PIN: ");

    if (old_pin != account.pin)
    {
        printf("\nIncorrect current PIN.\n");
        return;
    }

    new_pin = readPin("Enter new 4-digit PIN: ");

    if (new_pin == old_pin)
    {
        printf("\nNew PIN must be different from your current PIN.\n");
        return;
    }

    confirm_pin = readLoginPin("Confirm new 4-digit PIN: ");

    if (new_pin != confirm_pin)
    {
        printf("\nPIN confirmation does not match.\n");
        return;
    }

    account.pin = new_pin;

    if (updateAccount(account))
        printf("\nPIN changed successfully.\n");
    else
        printf("\nUnable to change PIN.\n");
}

void closeAccount(int account_no)
{
    Account account;

    if (!findAccount(account_no, &account))
    {
        printf("\nAccount not found.\n");
        return;
    }

    printf("\nCurrent balance: %.2f\n", account.balance);

    if (account.balance != 0)
    {
        printf("Please withdraw or transfer your remaining balance first.\n");
        return;
    }

    if (readYesNo("Are you sure you want to close this account? (Y/N): "))
    {
        account.active = 0;

        if (updateAccount(account))
            printf("\nAccount closed successfully.\n");
        else
            printf("\nUnable to close account.\n");
    }
    else
    {
        printf("\nAccount closing cancelled.\n");
    }
}
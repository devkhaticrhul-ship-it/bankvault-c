#include <stdio.h>
#include <string.h>

#include "admin.h"
#include "account.h"
#include "transaction.h"
#include "input.h"

#define ACCOUNT_FILE "data/accounts.dat"
#define TRANSACTION_FILE "data/transactions.dat"

#define ADMIN_USERNAME "admin"
#define ADMIN_PASSWORD "1234"

static void showAdminMenu(void)
{
    printf("\n========================================\n");
    printf("             BANKVAULT ADMIN\n");
    printf("========================================\n");
    printf("1. View All Accounts\n");
    printf("2. Search Account\n");
    printf("3. Bank Statistics\n");
    printf("4. View All Transactions\n");
    printf("5. Logout\n");
    printf("========================================\n");
}

static void viewAllAccounts(void)
{
    FILE *file;
    Account account;
    int found = 0;

    file = fopen(ACCOUNT_FILE, "rb");

    if (file == NULL)
    {
        printf("\nNo account records found.\n");
        return;
    }

    printf("\n================ ALL ACCOUNTS ================\n");
    printf("%-8s %-20s %-15s %-12s %-10s\n",
           "ACC NO", "NAME", "PHONE", "BALANCE", "STATUS");

    printf("---------------------------------------------------------------\n");

    while (fread(&account, sizeof(Account), 1, file) == 1)
    {
        printf("%-8d %-20s %-15s %-12.2f %-10s\n",
               account.account_no,
               account.name,
               account.phone,
               account.balance,
               account.active ? "Active" : "Closed");

        found = 1;
    }

    fclose(file);

    if (!found)
        printf("No accounts available.\n");
}

static void searchAccountAdmin(void)
{
    int account_no;
    Account account;
    FILE *file;

    printf("\n========== ADMIN ACCOUNT SEARCH ==========\n");

    account_no = readInt("Enter account number: ");

    file = fopen(ACCOUNT_FILE, "rb");

    if (file == NULL)
    {
        printf("\nUnable to open account records.\n");
        return;
    }

    while (fread(&account, sizeof(Account), 1, file) == 1)
    {
        if (account.account_no == account_no)
        {
            printf("\nAccount Number : %d\n", account.account_no);
            printf("Name           : %s\n", account.name);
            printf("Phone          : %s\n", account.phone);
            printf("Balance        : %.2f\n", account.balance);

            if (account.active)
                printf("Status         : Active\n");
            else
                printf("Status         : Closed\n");

            fclose(file);
            return;
        }
    }

    fclose(file);

    printf("\nAccount not found.\n");
}

static void showBankStatistics(void)
{
    FILE *file;
    Account account;

    int total_accounts = 0;
    int active_accounts = 0;
    int closed_accounts = 0;

    double total_balance = 0.0;

    file = fopen(ACCOUNT_FILE, "rb");

    if (file == NULL)
    {
        printf("\nNo account records found.\n");
        return;
    }

    while (fread(&account, sizeof(Account), 1, file) == 1)
    {
        total_accounts++;

        if (account.active)
        {
            active_accounts++;
            total_balance += account.balance;
        }
        else
        {
            closed_accounts++;
        }
    }

    fclose(file);

    printf("\n========== BANK STATISTICS ==========\n");
    printf("Total Accounts     : %d\n", total_accounts);
    printf("Active Accounts    : %d\n", active_accounts);
    printf("Closed Accounts    : %d\n", closed_accounts);
    printf("Total Bank Balance : %.2f\n", total_balance);
}

static void viewAllTransactions(void)
{
    FILE *file;
    Transaction transaction;
    int found = 0;

    file = fopen(TRANSACTION_FILE, "rb");

    if (file == NULL)
    {
        printf("\nNo transaction records found.\n");
        return;
    }

    printf("\n================ ALL TRANSACTIONS ================\n");
    printf("%-8s %-10s %-16s %-12s %-12s\n",
           "ID", "ACC NO", "TYPE", "AMOUNT", "BALANCE");

    printf("----------------------------------------------------------------\n");

    while (fread(&transaction, sizeof(Transaction), 1, file) == 1)
    {
        printf("%-8d %-10d %-16s %-12.2f %-12.2f\n",
               transaction.transaction_id,
               transaction.account_no,
               transaction.type,
               transaction.amount,
               transaction.balance_after);

        found = 1;
    }

    fclose(file);

    if (!found)
        printf("No transactions available.\n");
}

void adminLogin(void)
{
    char username[30];
    char password[30];
    int choice;

    printf("\n========== ADMIN LOGIN ==========\n");

    printf("Username: ");
    scanf("%29s", username);

    printf("Password: ");
    scanf("%29s", password);

    if (strcmp(username, ADMIN_USERNAME) != 0 ||
        strcmp(password, ADMIN_PASSWORD) != 0)
    {
        printf("\nInvalid admin credentials.\n");
        return;
    }

    printf("\nAdmin login successful.\n");

    while (1)
    {
        showAdminMenu();

        choice = readInt("Enter your choice: ");

        switch (choice)
        {
            case 1:
                viewAllAccounts();
                break;

            case 2:
                searchAccountAdmin();
                break;

            case 3:
                showBankStatistics();
                break;

            case 4:
                viewAllTransactions();
                break;

            case 5:
                printf("\nAdmin logged out successfully.\n");
                return;

            default:
                printf("\nInvalid choice. Try again.\n");
        }
    }
}
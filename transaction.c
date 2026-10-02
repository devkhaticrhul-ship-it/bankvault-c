#include <stdio.h>
#include <string.h>
#include "transaction.h"

#define TRANSACTION_FILE "data/transactions.dat"

static int getNextTransactionId(void)
{
    FILE *file;
    Transaction transaction;
    int last_id = 1000;

    file = fopen(TRANSACTION_FILE, "rb");

    if (file == NULL)
        return last_id + 1;

    while (fread(&transaction, sizeof(Transaction), 1, file) == 1)
    {
        if (transaction.transaction_id > last_id)
            last_id = transaction.transaction_id;
    }

    fclose(file);

    return last_id + 1;
}

int saveTransaction(int account_no, const char *type,
                    double amount, double balance_after)
{
    FILE *file;
    Transaction transaction;

    transaction.transaction_id = getNextTransactionId();
    transaction.account_no = account_no;
    transaction.amount = amount;
    transaction.balance_after = balance_after;

    strcpy(transaction.type, type);

    file = fopen(TRANSACTION_FILE, "ab");

    if (file == NULL)
    {
        printf("\nUnable to save transaction.\n");
        return 0;
    }

    fwrite(&transaction, sizeof(Transaction), 1, file);
    fclose(file);

    return transaction.transaction_id;
}

void showTransactions(int account_no)
{
    FILE *file;
    Transaction transaction;
    int found = 0;

    file = fopen(TRANSACTION_FILE, "rb");

    if (file == NULL)
    {
        printf("\nNo transaction history found.\n");
        return;
    }

    printf("\n========== TRANSACTION HISTORY ==========\n");
    printf("%-8s %-16s %-12s %-12s\n",
           "ID", "TYPE", "AMOUNT", "BALANCE");

    printf("-----------------------------------------------\n");

    while (fread(&transaction, sizeof(Transaction), 1, file) == 1)
    {
        if (transaction.account_no == account_no)
        {
            printf("%-8d %-16s %-12.2f %-12.2f\n",
                   transaction.transaction_id,
                   transaction.type,
                   transaction.amount,
                   transaction.balance_after);

            found = 1;
        }
    }

    fclose(file);

    if (!found)
        printf("No transactions available for this account.\n");
}

void showAccountStatement(int account_no)
{
    FILE *file;
    Transaction transaction;
    int found = 0;
    int count = 0;

    file = fopen(TRANSACTION_FILE, "rb");

    if (file == NULL)
    {
        printf("\nNo transaction history found.\n");
        return;
    }

    printf("\n========== ACCOUNT STATEMENT ==========\n");
    printf("Account Number : %d\n", account_no);
    printf("-----------------------------------------------\n");
    printf("%-8s %-16s %-12s %-12s\n",
           "ID", "TYPE", "AMOUNT", "BALANCE");

    printf("-----------------------------------------------\n");

    while (fread(&transaction, sizeof(Transaction), 1, file) == 1)
    {
        if (transaction.account_no == account_no)
        {
            printf("%-8d %-16s %-12.2f %-12.2f\n",
                   transaction.transaction_id,
                   transaction.type,
                   transaction.amount,
                   transaction.balance_after);

            found = 1;
            count++;
        }
    }

    fclose(file);

    printf("-----------------------------------------------\n");

    if (!found)
    {
        printf("No transactions available for this account.\n");
        return;
    }

    printf("Total Transactions : %d\n", count);
}

void showDepositReceipt(int transaction_id, int account_no,
                        double amount, double balance_after)
{
    printf("\n========================================\n");
    printf("          TRANSACTION RECEIPT\n");
    printf("========================================\n");
    printf("Transaction ID : %d\n", transaction_id);
    printf("Account Number : %d\n", account_no);
    printf("Transaction    : Deposit\n");
    printf("Amount         : %.2f\n", amount);
    printf("Balance        : %.2f\n", balance_after);
    printf("========================================\n");
    printf("Transaction completed successfully.\n");
}

void showWithdrawalReceipt(int transaction_id, int account_no,
                           double amount, double balance_after)
{
    printf("\n========================================\n");
    printf("          TRANSACTION RECEIPT\n");
    printf("========================================\n");
    printf("Transaction ID : %d\n", transaction_id);
    printf("Account Number : %d\n", account_no);
    printf("Transaction    : Withdrawal\n");
    printf("Amount         : %.2f\n", amount);
    printf("Balance        : %.2f\n", balance_after);
    printf("========================================\n");
    printf("Transaction completed successfully.\n");
}

void showTransferReceipt(int transaction_id, int from_account,
                         int to_account, double amount,
                         double balance_after)
{
    printf("\n========================================\n");
    printf("           TRANSFER RECEIPT\n");
    printf("========================================\n");
    printf("Transaction ID : %d\n", transaction_id);
    printf("From Account   : %d\n", from_account);
    printf("To Account     : %d\n", to_account);
    printf("Amount         : %.2f\n", amount);
    printf("New Balance    : %.2f\n", balance_after);
    printf("========================================\n");
    printf("Transfer completed successfully.\n");
}
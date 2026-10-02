#ifndef TRANSACTION_H
#define TRANSACTION_H

#define TRANSACTION_TYPE_SIZE 20

typedef struct
{
    int transaction_id;
    int account_no;
    char type[TRANSACTION_TYPE_SIZE];
    double amount;
    double balance_after;
} Transaction;

int saveTransaction(int account_no, const char *type, double amount, double balance_after);
void showTransactions(int account_no);
void showAccountStatement(int account_no);

void showDepositReceipt(int transaction_id, int account_no,
                        double amount, double balance_after);

void showWithdrawalReceipt(int transaction_id, int account_no,
                           double amount, double balance_after);

void showTransferReceipt(int transaction_id, int from_account,
                         int to_account, double amount,
                         double balance_after);

#endif
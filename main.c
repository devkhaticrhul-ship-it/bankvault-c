#include <stdio.h>

#include "account.h"
#include "admin.h"
#include "file_manager.h"
#include "input.h"

static void showMainMenu(void)
{
    printf("\n========================================\n");
    printf("              BANKVAULT\n");
    printf("        Simple Banking System\n");
    printf("========================================\n");
    printf("1. Create Account\n");
    printf("2. Login\n");
    printf("3. Search Account\n");
    printf("4. Admin Panel\n");
    printf("5. Exit\n");
    printf("========================================\n");
}

int main(void)
{
    int choice;

    if (!prepareDataFolder())
    {
        printf("Unable to prepare the data folder.\n");
        return 1;
    }

    while (1)
    {
        showMainMenu();

        choice = readInt("Enter your choice: ");

        switch (choice)
        {
            case 1:
                createAccount();
                break;

            case 2:
                loginAccount();
                break;

            case 3:
                searchAccount();
                break;

            case 4:
                adminLogin();
                break;

            case 5:
                printf("\nThank you for using BankVault.\n");
                return 0;

            default:
                printf("\nInvalid choice. Try again.\n");
        }
    }
}
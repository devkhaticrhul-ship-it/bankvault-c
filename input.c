#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "input.h"

int readInt(const char *message)
{
    int value;
    int result;

    while (1)
    {
        printf("%s", message);

        result = scanf("%d", &value);

        if (result == 1)
        {
            while (getchar() != '\n')
            {
            }

            return value;
        }

        while (getchar() != '\n')
        {
        }

        printf("Invalid input. Please enter a number.\n");
    }
}

double readAmount(const char *message)
{
    double amount;
    int result;

    while (1)
    {
        printf("%s", message);

        result = scanf("%lf", &amount);

        if (result == 1)
        {
            while (getchar() != '\n')
            {
            }

            if (amount > 0)
                return amount;

            printf("Amount must be greater than zero.\n");
            continue;
        }

        while (getchar() != '\n')
        {
        }

        printf("Enter a valid amount.\n");
    }
}

int readPin(const char *message)
{
    int pin;
    int result;

    while (1)
    {
        printf("%s", message);

        result = scanf("%d", &pin);

        if (result == 1)
        {
            while (getchar() != '\n')
            {
            }

            if (pin < 1000 || pin > 9999)
            {
                printf("PIN must contain exactly 4 digits.\n");
                continue;
            }

            if (pin == 1111 ||
                pin == 2222 ||
                pin == 3333 ||
                pin == 4444 ||
                pin == 5555 ||
                pin == 6666 ||
                pin == 7777 ||
                pin == 8888 ||
                pin == 9999 ||
                pin == 1234 ||
                pin == 4321)
            {
                printf("This PIN is too easy to guess. Choose another PIN.\n");
                continue;
            }

            return pin;
        }

        while (getchar() != '\n')
        {
        }

        printf("Enter a valid 4-digit PIN.\n");
    }
}

int readLoginPin(const char *message)
{
    int pin;
    int result;

    while (1)
    {
        printf("%s", message);

        result = scanf("%d", &pin);

        if (result == 1)
        {
            while (getchar() != '\n')
            {
            }

            if (pin < 1000 || pin > 9999)
            {
                printf("PIN must contain exactly 4 digits.\n");
                continue;
            }

            return pin;
        }

        while (getchar() != '\n')
        {
        }

        printf("Enter a valid 4-digit PIN.\n");
    }
}

void readName(const char *message, char *name, int size)
{
    int valid;

    while (1)
    {
        valid = 1;

        printf("%s", message);

        if (fgets(name, size, stdin) == NULL)
        {
            name[0] = '\0';
            continue;
        }

        name[strcspn(name, "\n")] = '\0';

        if (strlen(name) == 0)
        {
            printf("Name cannot be empty.\n");
            continue;
        }

        for (int i = 0; name[i] != '\0'; i++)
        {
            if (isdigit((unsigned char)name[i]))
            {
                valid = 0;
                break;
            }
        }

        if (!valid)
        {
            printf("Name cannot contain numbers.\n");
            continue;
        }

        return;
    }
}

void readPhone(const char *message, char *phone, int size)
{
    int valid;
    int length;

    while (1)
    {
        valid = 1;

        printf("%s", message);

        if (fgets(phone, size, stdin) == NULL)
        {
            phone[0] = '\0';
            continue;
        }

        phone[strcspn(phone, "\n")] = '\0';

        length = strlen(phone);

        if (length != 10)
        {
            printf("Phone number must contain exactly 10 digits.\n");
            continue;
        }

        for (int i = 0; phone[i] != '\0'; i++)
        {
            if (!isdigit((unsigned char)phone[i]))
            {
                valid = 0;
                break;
            }
        }

        if (!valid)
        {
            printf("Phone number can contain digits only.\n");
            continue;
        }

        return;
    }
}

int readYesNo(const char *message)
{
    char answer;

    while (1)
    {
        printf("%s", message);

        scanf(" %c", &answer);

        while (getchar() != '\n')
        {
        }

        if (answer == 'Y' || answer == 'y')
            return 1;

        if (answer == 'N' || answer == 'n')
            return 0;

        printf("Please enter Y or N.\n");
    }
}
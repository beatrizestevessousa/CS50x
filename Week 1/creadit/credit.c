#include <stdio.h>
#include <cs50.h>
#include <math.h>

long long creditcard_number(void);
int check_number(long long number);

long long long_pow(long long a, long long b)
{
    long long res = 1;

    for (long long i = 0; i < b; i++)
    {
        res *= a;
    }

    return res;
}

int main()
{
    long long number = creditcard_number();
    int check = check_number(number);
    for (long long i = 0; i <= 16; i++)
    {
        // See the lenght of the number
        if ((number >= long_pow(10, i) && (number < long_pow(10, i + 1))) || number == 0)
        {
            long long lenght = i + 1;

            //Check first digit
            long digit = (long)(number / pow(10, floor(log10(number))));

            //Removing first digit
            long remaining = number % (long) pow(10, floor(log10(number)));

            //Check second digit
            long second = (long)(remaining / pow(10, floor(log10(remaining))));
            if ((lenght == 13 || lenght == 16) && check == 1 && digit == 4)
            {
                printf("VISA\n");
            }
            else if (lenght == 15 && check == 1 && digit == 3 && (second == 4 || second == 7))
            {
                printf("AMEX\n");
            }
            else if (lenght == 16 && check == 1 && digit == 5 && (second == 1 || second == 2 || second == 3 || second == 4 || second == 5))
            {
                printf("MASTERCARD\n");
            }
            else
            {
                printf("INVALID\n");
            }
            break;
        }
    }
}

//Ask for the credit card number
long long creditcard_number(void)
{
    long long number;
    do
    {
        number = get_long_long("Number: ");
    }
    while (number < 1);
    return number;
}

//Check if it is valid
int check_number(long long number)
{
    int count = 0;
    int sum = 0;

    do
    {
        //Check the last digit of the credit card number
        int digit = number % 10;

        //Removes the last digit
        number /= 10;
        count++;

        //Doubles every second digit
        if (count % 2 == 0)
        {
            digit *= 2;

            //Sums the digits of the doubled number if it's greater than 9
            if (digit > 9)
            {
                digit = digit % 10 + digit / 10;
            }
        }

        //Adds the digit (or the sum of digits) to the total sum
        sum += digit;
    }
    while (number > 0);

    if (sum % 10 == 0)
    {
        int n = 1;
        return n;
    }
    else
    {
        int n = 2;
        return n;
    }
}

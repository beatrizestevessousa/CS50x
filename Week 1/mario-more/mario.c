#include <cs50.h>
#include <stdio.h>

int get_size(void);
void left_pyramid(int n);

int main(void)
{
    int n = get_size();
    left_pyramid(n);
}

int get_size(void)
{
    int n;
    do
    {
        n = get_int("Height: ");
    }
    while (n < 1 || n > 8);
    return n;
}

void left_pyramid(int n)
{
    //Left-centered pyramid
    for (int i = 1; i <= n; i++)
    {
        //Calculates how much space is needed in that row
        for (int space = 1; space <= n - i; space++)
        {
            printf(" ");
        }

        //Prints the hashes
        for (int j = 0; j < i; j++)
        {
            printf("#");
        }

        //Two spaces between
        printf("  ");

        //Right-centered pyramid
        for (int m = 1; m <= i; m++)
        {
            //Calculates how much space is needed in that row
            for (int space = n - 2; space < n - 2; space++)
            {
                printf(" ");
            }

            //Prints the hashes
            for (int z = n - 1; z < n; z++)
            {
                printf("#");
            }
        }
        printf("\n");
    }
}

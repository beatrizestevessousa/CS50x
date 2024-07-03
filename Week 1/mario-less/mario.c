#include <cs50.h>
#include <stdio.h>

int get_size(void);
void print_pyramid(int n);

int main(void)
{
    int n = get_size();
    print_pyramid(n);
}

//Get pyramid size
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


//Print the pyramid
void print_pyramid(int n)
{
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
        printf("\n");
    }
}

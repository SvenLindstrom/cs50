#include <cs50.h>
#include <stdio.h>


void print_wall(int i);

int main(void)
{

    int height;
    do
    {
        height =  get_int("Height: ");

    }
    while (height > 8 || height < 1);


    for (int i = 0; i < height; i++)
    {

        for (int x = 1; x < height - i; x++)
        {
            printf(" ");
        }

        print_wall(i);

        printf("  ");

        print_wall(i);

        printf("\n");
    }

}

void print_wall(int i)
{
    for (int j = 0; j <= i; j++)
    {
        printf("#");
    }
}




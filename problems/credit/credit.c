#include <cs50.h>
#include <stdio.h>

int numLength(long num);
int cardName(long num, int length);
long power(int exponent);
void toName(int n);
bool testNumber(long num, int leangth);
int main(void)
{
    long number = get_long("Number: ");
    int length = numLength(number);

    if (length > 12 && length < 17)
    {
        int card_Name = cardName(number, length);

        if (card_Name != 0)
        {
            if (testNumber(number, length))
            {
                toName(card_Name);
            }
            else
            {
                toName(0);
            }
        }
        else
        {
            toName(0);
        }

    }
    else
    {
        toName(0);
    }
    
}

int numLength(long num)
{
    int length = 0;
    while (num > 0)
    {
        num = num / 10;
        length ++;
    }
    return length;
}

int cardName(long num, int length)
{
    int firstNum = num / power(length - 1);
    if (firstNum == 4)
    {
        return 1;
    }
    else
    {
        int secondNum = num / power(length - 2);

        if (length == 15 && (secondNum == 34 || secondNum == 37))
        {
            return 2;
        }
        else if (length == 16 && (secondNum >= 51 && secondNum <= 55))
        {
            return 3;
        }
    }
    return 0;
}

long power(int exponent)
{
    long n = 1;
    for (int i = 0; i < exponent; i++)
    {
        n = n * 10;
    }
    return n;
}
void toName(int n)
{
    if (n == 1)
    {
        printf("VISA\n");
    }
    else if (n == 2)
    {
        printf("AMEX\n");
    }
    else if (n == 3)
    {
        printf("MASTERCARD\n");
    }
    else
    {
        printf("INVALID\n");
    }

}

bool testNumber(long num, int leangth)
{
    int sumOdd = 0;
    int sumEven = 0;
    for (int i = 1; i <= leangth; i++)
    {
        long int_upto_i = num % power(i);
        int int_pos_i = int_upto_i / power(i - 1);

        if ((i) % 2 == 0)
        {
            int_pos_i = int_pos_i * 2;
            if (int_pos_i >= 10)
            {
                sumEven += (int_pos_i % 10) + 1;
            }
            else
            {
                sumEven += int_pos_i;
            }
        }
        else
        {
            sumOdd += int_pos_i;
        }


    }

    if ((sumOdd + sumEven) % 10 == 0)
    {
        return true;
    }

    return false;
}



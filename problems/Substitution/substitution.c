#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>


int main(int argc, string argv[])
{
    string cipher = argv[1];
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
    else if (strlen(argv[1]) != 26)
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }
    else
    {
        for (int i = 0;  i < 26; i++)
        {
            char check = tolower(cipher[i]);
            if (!isalpha(check))
            {
                printf("cipher must only contain letters\n");
                return 1;
            }

            for (int j = i + 1; j < 26; j++)
            {

                if (check == cipher[j] || (check - 32) == cipher[j])
                {
                    printf("no douplicat letters\n");
                    return 1;
                }
            }

        }
    }
    string to_cipher = get_string("plaintext: ");

    for (int i = 0, length = strlen(to_cipher); i < length; i++)
    {
        char incode = to_cipher[i];
        if (isalpha(incode))
        {
            if (isupper(incode))
            {
                to_cipher[i] = toupper(cipher[incode - 65]);
            }
            else
            {
                to_cipher[i] = tolower(cipher[incode - 97]);
            }
        }

    }

    printf("ciphertext: %s\n", to_cipher);
    return 0;

}
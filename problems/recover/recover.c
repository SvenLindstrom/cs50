#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>


int main(int argc, char *argv[])
{
    if (argc != 1)
    {
        printf("Usage: ./recover file_name");
    }

    FILE *infile = fopen(argv[1], "r");

    if (infile == NULL)
    {
        printf("invaled file");
        return 1;
    }
    typedef uint8_t BYTE;

    BYTE *buffer = malloc(512);
    char *name = malloc(8);
    int num_jpg = 0;
    sprintf(name, "00%i.jpg", num_jpg);

    FILE *outfile = fopen(name, "w");

    while (fread(buffer, 1, 512, infile) == 512)
    {

        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff)
        {
            fclose(outfile);

            if (num_jpg < 10)
            {
                sprintf(name, "00%i.jpg", num_jpg);
            }
            else
            {
                sprintf(name, "0%i.jpg", num_jpg);
            }

            num_jpg++;

            outfile = fopen(name, "w");
        }

        fwrite(buffer, 1, 512, outfile);

    }

    free(buffer);
    free(name);
    fclose(infile);
    fclose(outfile);
}
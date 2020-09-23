#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{

    if (argc != 2)
    {
        printf("Usage: %s image\n", argv[0]);
        return 1;
    }


    FILE *inptr = fopen(argv[1], "r");

    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", argv[1]);
        return 4;
    }


    unsigned char buffer[512] = { 0 };
    char filename[50] = {0};
    int fileNameCounter = 0;
    FILE *outptr = NULL;
    int resultRead = 0;

    for (int i = 0; ; i++)
    {
        // read data from input file
        resultRead = fread(&buffer, 1, 512, inptr);

        if (resultRead <= 0)
            break;

        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && ((buffer[3] & 0xf0) == 0xe0))
        {

            sprintf(filename, "%03i.jpg", fileNameCounter);


            // close current output file
            if (outptr != NULL)
            {
                fclose(outptr);
            }

            // Open output file
            outptr = fopen(filename, "w");
            fileNameCounter++;

            if (outptr == NULL)
            {
                fclose(outptr);
                fprintf(stderr, "Could not create %s.\n", filename);
                return 5;
            }

            fwrite(&buffer, 1, resultRead, outptr);


        }
        else
        {
            if (outptr != NULL)
            {
                fwrite(&buffer, 1, resultRead, outptr);
            }
        }


    }


    // close files
    fclose(outptr);
    fclose(inptr);

}

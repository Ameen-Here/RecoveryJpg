#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
typedef uint8_t BYTE;

int main(int argc, char* argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./recover image ");
        return 1;
    }
    BYTE buffer[512];
    int count = 0;
    FILE* file = fopen(argv[1], "r");
    if (file == NULL)
    {
        printf("Could not open .\n");
        return 1;
    }
    FILE* file_out = NULL;
    char filename[8];
    while (fread(&buffer, 512, 1, file) == 1)
    {
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            if (!(count == 0))
            {
                fclose(file_out);
            }
            sprintf(filename, "%03i.jpg", count);
            file_out = fopen(filename, "w");
            count++;
        }
        if (!(count == 0))
        {
            fwrite(&buffer, 512, 1, file_out);
        }
    }
    fclose(file);
    fclose(file_out);
    return 0;

}
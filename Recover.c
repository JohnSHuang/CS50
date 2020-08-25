#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <cs50.h>
#define block_size 512

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./recover image\n");
        return 1;
    }
    FILE *file = fopen(argv[1], "r");
    if (file == NULL)
    {
        printf("File not found\n");
        return 1;
    }

    BYTE buffer[block_size];
    FILE *recovered_file;
    char filename[8];
    int count = 0;

    bool first_jpg = false;
    while (fread(buffer, block_size, 1, file))
    {
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            if (first_jpg == false)
            {
                first_jpg = true;
            }
            else
            {
                fclose(recovered_file);
            }
            sprintf(filename, "%03i.jpg", count);
            count++;
            recovered_file = fopen(filename, "w");
            fwrite(buffer, block_size, 1, recovered_file);
        }
        else if (first_jpg == true)
        {
            fwrite(buffer, block_size, 1, recovered_file);
        }
    }
    fclose(recovered_file);
    fclose(file);
}

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

const int BLOCK_SIZE = 512;

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./recover IMAGE");
        return 1;
    }

    FILE *file = fopen(argv[1], "rb");
    if (file == NULL)
    {
        printf("Could not open file");
        return 1;
    }

    uint8_t buffer[BLOCK_SIZE];
    int counter = 0;
    char filename[8];

    FILE *image = NULL;

    while (fread(buffer, BLOCK_SIZE, 1, file) == 1)
    {
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            if (image != NULL)
            {
                fclose(image);
            }

            sprintf(filename, "%03d.jpg", counter);
            image = fopen(filename, "wb");
            counter++;
        }

        if (image != NULL)
        {
            fwrite(buffer, BLOCK_SIZE, 1, image);
        }
    }

    if (image != NULL)
    {
        fclose(image);
    }

    fclose(file);

    return 0;
}

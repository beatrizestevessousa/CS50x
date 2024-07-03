#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./recover IMAGE \n");
        return 1;
    }

    char *f = argv[1];
    FILE *file = fopen(f, "r");
    if (file == NULL)
    {
        printf("Could not open %s.\n", f);
        return 1;
    }

    // List to store every 512 bytes of the memory card we want to recover
    BYTE buffer[512];

    // Counts the amount of jpeg files
    int counter = 0;

    // Set a pointer to NULL
    FILE *new_file = NULL;

    // String to filename
    char filename [8] = {0};

    while (fread(buffer, sizeof(BYTE) * 512, 1, file) == 1)
    {
        // Check if it is a jpeg file
        if ((buffer[0] == 0xff) && (buffer[1] == 0xd8) && (buffer[2] == 0xff) && ((buffer[3] & 0xf0) == 0xe0))
        {

            // Check if there is a file already open to close it
            if (new_file != NULL)
            {
                fclose(new_file);
            }

            // Create a new file and update the counter
            sprintf(filename, "%03i.jpg", counter);
            new_file = fopen(filename, "w");
            counter++;
        }

        // Write in the new file
        if (new_file != NULL)
        {
            fwrite(buffer, sizeof(BYTE) * 512, 1, new_file);
        }
    }

    // Close all files
    if (new_file != NULL)
    {
        fclose(new_file);
    }

    fclose(file);
}

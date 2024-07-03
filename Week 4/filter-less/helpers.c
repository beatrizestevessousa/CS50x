#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            BYTE originalRed = image[i][j].rgbtRed;
            BYTE originalGreen = image[i][j].rgbtGreen;
            BYTE originalBlue = image[i][j].rgbtBlue;

            // Check if the pixel is not in grayscale
            if (!(originalRed == originalGreen && originalGreen == originalBlue))
            {

                // Change to grayscale
                int value = round((originalRed + originalGreen + originalBlue) / 3.0);
                image[i][j].rgbtRed = value;
                image[i][j].rgbtGreen = value;
                image[i][j].rgbtBlue = value;
            }
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Temp variables
            BYTE originalRed = image[i][j].rgbtRed;
            BYTE originalGreen = image[i][j].rgbtGreen;
            BYTE originalBlue = image[i][j].rgbtBlue;

            // Conversion to sepia
            int sepiaRed = round(.393 * originalRed + .769 * originalGreen + .189 * originalBlue);
            if (sepiaRed > 255)
            {
                sepiaRed = 255;
            }

            int sepiaGreen = round(.349 * originalRed + .686 * originalGreen + .168 * originalBlue);
            if (sepiaGreen > 255)
            {
                sepiaGreen = 255;
            }

            int sepiaBlue = round(.272 * originalRed + .534 * originalGreen + .131 * originalBlue);
            if (sepiaBlue > 255)
            {
                sepiaBlue = 255;
            }

            // Store the values in the image
            image[i][j].rgbtRed = sepiaRed;
            image[i][j].rgbtGreen = sepiaGreen;
            image[i][j].rgbtBlue = sepiaBlue;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            // Temp variables
            BYTE originalRed = image[i][j].rgbtRed;
            BYTE originalGreen = image[i][j].rgbtGreen;
            BYTE originalBlue = image[i][j].rgbtBlue;

            // Switch values
            image[i][j].rgbtRed = image[i][width - (j + 1)].rgbtRed;
            image[i][j].rgbtGreen = image[i][width - (j + 1)].rgbtGreen;
            image[i][j].rgbtBlue = image[i][width - (j + 1)].rgbtBlue;

            image[i][width - (j + 1)].rgbtRed = originalRed;
            image[i][width - (j + 1)].rgbtGreen = originalGreen;
            image[i][width - (j + 1)].rgbtBlue = originalBlue;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copy[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
        }
    }

    for (int n = 0; n < height; n++)
    {
        for (int k = 0; k < width; k++)
        {
            int red = 0;
            int green = 0;
            int blue = 0;
            int counter = 0;

            // Center pixel
            if (n >= 0 && k >= 0)
            {
                red += copy[n][k].rgbtRed;
                green += copy[n][k].rgbtGreen;
                blue += copy[n][k].rgbtBlue;
                counter++;
            }

            // Left pixel
            if (n >= 0 && k - 1 >= 0)
            {
                red += copy[n][k - 1].rgbtRed;
                green += copy[n][k - 1].rgbtGreen;
                blue += copy[n][k - 1].rgbtBlue;
                counter++;
            }

            // Right pixel
            if ((n >= 0 && k + 1 >= 0) && (n >= 0 && k + 1 < width))
            {
                red += copy[n][k + 1].rgbtRed;
                green += copy[n][k + 1].rgbtGreen;
                blue += copy[n][k + 1].rgbtBlue;
                counter++;
            }

            // Upper pixel
            if (n - 1 >= 0 && k >= 0)
            {
                red += copy[n - 1][k].rgbtRed;
                green += copy[n - 1][k].rgbtGreen;
                blue += copy[n - 1][k].rgbtBlue;
                counter++;
            }

            // Upper left pixel
            if (n - 1 >= 0 && k - 1 >= 0)
            {
                red += copy[n - 1][k - 1].rgbtRed;
                green += copy[n - 1][k - 1].rgbtGreen;
                blue += copy[n - 1][k - 1].rgbtBlue;
                counter++;
            }

            // Upper right pixel
            if ((n - 1 >= 0 && k + 1 >= 0) && (n - 1 >= 0 && k + 1 < width))
            {
                red += copy[n - 1][k + 1].rgbtRed;
                green += copy[n - 1][k + 1].rgbtGreen;
                blue += copy[n - 1][k + 1].rgbtBlue;
                counter++;
            }

            // Below pixel
            if ((n + 1 >= 0 && k >= 0) && (n + 1 < height && k >= 0))
            {
                red += copy[n + 1][k].rgbtRed;
                green += copy[n + 1][k].rgbtGreen;
                blue += copy[n + 1][k].rgbtBlue;
                counter++;
            }

            // Below left pixel
            if ((n + 1 >= 0 && k - 1 >= 0) && (n + 1 < height && k - 1 >= 0))
            {
                red += copy[n + 1][k - 1].rgbtRed;
                green += copy[n + 1][k - 1].rgbtGreen;
                blue += copy[n + 1][k - 1].rgbtBlue;
                counter++;
            }

            // Below right pixel
            if ((n + 1 >= 0 && k + 1 >= 0) && (n + 1 < height && k + 1 < width))
            {
                red += copy[n + 1][k + 1].rgbtRed;
                green += copy[n + 1][k + 1].rgbtGreen;
                blue += copy[n + 1][k + 1].rgbtBlue;
                counter++;
            }

            // Tranfer to the image
            image[n][k].rgbtRed = round(red / (float)counter);
            image[n][k].rgbtGreen = round(green / (float)counter);
            image[n][k].rgbtBlue = round(blue / (float)counter);
        }
    }
    return;
}

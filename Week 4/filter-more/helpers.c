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

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    int Gx [3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int Gy [3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

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
            // Variables to store the sum
            int redGx = 0;
            int redGy = 0;
            int greenGx = 0;
            int greenGy = 0;
            int blueGx = 0;
            int blueGy = 0;

            // Center pixel
            if (n >= 0 && k >= 0)
            {
                redGx += copy[n][k].rgbtRed * Gx[1][1];
                redGy += copy[n][k].rgbtRed * Gy[1][1];
                greenGx += copy[n][k].rgbtGreen * Gx[1][1];
                greenGy += copy[n][k].rgbtGreen * Gy[1][1];
                blueGx += copy[n][k].rgbtBlue * Gx[1][1];
                blueGy += copy[n][k].rgbtBlue * Gy[1][1];
            }

            // Left pixel
            if (n >= 0 && k - 1 >= 0)
            {
                redGx += copy[n][k - 1].rgbtRed * Gx[1][0];
                redGy += copy[n][k - 1].rgbtRed * Gy[1][0];
                greenGx += copy[n][k - 1].rgbtGreen * Gx[1][0];
                greenGy += copy[n][k - 1].rgbtGreen * Gy[1][0];
                blueGx += copy[n][k - 1].rgbtBlue * Gx[1][0];
                blueGy += copy[n][k - 1].rgbtBlue * Gy[1][0];
            }

            // Right pixel
            if ((n >= 0 && k + 1 >= 0) && (n >= 0 && k + 1 < width))
            {
                redGx += copy[n][k + 1].rgbtRed * Gx[1][2];
                redGy += copy[n][k + 1].rgbtRed * Gy[1][2];
                greenGx += copy[n][k + 1].rgbtGreen * Gx[1][2];
                greenGy += copy[n][k + 1].rgbtGreen * Gy[1][2];
                blueGx += copy[n][k + 1].rgbtBlue * Gx[1][2];
                blueGy += copy[n][k + 1].rgbtBlue * Gy[1][2];
            }

            // Upper pixel
            if (n - 1 >= 0 && k >= 0)
            {
                redGx += copy[n - 1][k].rgbtRed * Gx[0][1];
                redGy += copy[n - 1][k].rgbtRed * Gy[0][1];
                greenGx += copy[n - 1][k].rgbtGreen * Gx[0][1];
                greenGy += copy[n - 1][k].rgbtGreen * Gy[0][1];
                blueGx += copy[n - 1][k].rgbtBlue * Gx[0][1];
                blueGy += copy[n - 1][k].rgbtBlue * Gy[0][1];
            }

            // Upper left pixel
            if (n - 1 >= 0 && k - 1 >= 0)
            {
                redGx += copy[n - 1][k - 1].rgbtRed * Gx[0][0];
                redGy += copy[n - 1][k - 1].rgbtRed * Gy[0][0];
                greenGx += copy[n - 1][k - 1].rgbtGreen * Gx[0][0];
                greenGy += copy[n - 1][k - 1].rgbtGreen * Gy[0][0];
                blueGx += copy[n - 1][k - 1].rgbtBlue * Gx[0][0];
                blueGy += copy[n - 1][k - 1].rgbtBlue * Gy[0][0];
            }

            // Upper right pixel
            if ((n - 1 >= 0 && k + 1 >= 0) && (n - 1 >= 0 && k + 1 < width))
            {
                redGx += copy[n - 1][k + 1].rgbtRed * Gx[0][2];
                redGy += copy[n - 1][k + 1].rgbtRed * Gy[0][2];
                greenGx += copy[n - 1][k + 1].rgbtGreen * Gx[0][2];
                greenGy += copy[n - 1][k + 1].rgbtGreen * Gy[0][2];
                blueGx += copy[n - 1][k + 1].rgbtBlue * Gx[0][2];
                blueGy += copy[n - 1][k + 1].rgbtBlue * Gy[0][2];
            }

            // Below pixel
            if ((n + 1 >= 0 && k >= 0) && (n + 1 < height && k >= 0))
            {
                redGx += copy[n + 1][k].rgbtRed * Gx[2][1];
                redGy += copy[n + 1][k].rgbtRed * Gy[2][1];
                greenGx += copy[n + 1][k].rgbtGreen * Gx[2][1];
                greenGy += copy[n + 1][k].rgbtGreen * Gy[2][1];
                blueGx += copy[n + 1][k].rgbtBlue * Gx[2][1];
                blueGy += copy[n + 1][k].rgbtBlue * Gy[2][1];
            }

            // Below left pixel
            if ((n + 1 >= 0 && k - 1 >= 0) && (n + 1 < height && k - 1 >= 0))
            {
                redGx += copy[n + 1][k - 1].rgbtRed * Gx[2][0];
                redGy += copy[n + 1][k - 1].rgbtRed * Gy[2][0];
                greenGx += copy[n + 1][k - 1].rgbtGreen * Gx[2][0];
                greenGy += copy[n + 1][k - 1].rgbtGreen * Gy[2][0];
                blueGx += copy[n + 1][k - 1].rgbtBlue * Gx[2][0];
                blueGy += copy[n + 1][k - 1].rgbtBlue * Gy[2][0];
            }

            // Below right pixel
            if ((n + 1 >= 0 && k + 1 >= 0) && (n + 1 < height && k + 1 < width))
            {
                redGx += copy[n + 1][k + 1].rgbtRed * Gx[2][2];
                redGy += copy[n + 1][k + 1].rgbtRed * Gy[2][2];
                greenGx += copy[n + 1][k + 1].rgbtGreen * Gx[2][2];
                greenGy += copy[n + 1][k + 1].rgbtGreen * Gy[2][2];
                blueGx += copy[n + 1][k + 1].rgbtBlue * Gx[2][2];
                blueGy += copy[n + 1][k + 1].rgbtBlue * Gy[2][2];
            }

            // Calculate the sobel value of each pixel
            int sobelRed = round(sqrt(pow(redGx, 2) + pow(redGy, 2)));
            if (sobelRed > 255)
            {
                sobelRed = 255;
            }
            int sobelGreen = round(sqrt(pow(greenGx, 2) + pow(greenGy, 2)));
            if (sobelGreen > 255)
            {
                sobelGreen = 255;
            }
            int sobelBlue = round(sqrt(pow(blueGx, 2) + pow(blueGy, 2)));
            if (sobelBlue > 255)
            {
                sobelBlue = 255;
            }

            // Transfer to the image
            image[n][k].rgbtRed = sobelRed;
            image[n][k].rgbtGreen = sobelGreen;
            image[n][k].rgbtBlue = sobelBlue;
        }
    }
    return;
}

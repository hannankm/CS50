#include "helpers.h"
#include <math.h>
int min(int a, int b);
//file -- helper.c

// Convert image to grayscale - done
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int avg = round((image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3.0);
            image[i][j].rgbtRed = image[i][j].rgbtGreen = image[i][j].rgbtBlue = avg;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    //check for values greater than 255 and int values
    RGBTRIPLE copy[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j].rgbtRed = image[i][j].rgbtRed;
            copy[i][j].rgbtGreen = image[i][j].rgbtGreen;
            copy[i][j].rgbtBlue = image[i][j].rgbtBlue;

            image[i][j].rgbtRed = min(round(.393 * copy[i][j].rgbtRed + .769 * copy[i][j].rgbtGreen + .189 * copy[i][j].rgbtBlue), 255);
            image[i][j].rgbtGreen = min(round(.349 * copy[i][j].rgbtRed + .686 * copy[i][j].rgbtGreen + .168 * copy[i][j].rgbtBlue), 255);
            image[i][j].rgbtBlue = min(round(.272 * copy[i][j].rgbtRed + .534 * copy[i][j].rgbtGreen + .131 * copy[i][j].rgbtBlue), 255);

        }
    }
    return;
}

// Reflect image horizontally -done
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        int right = 0;
        int left = width - 1;
        while (left > right)
        {
            // swap red values of the pixel
            RGBTRIPLE pixel = image[i][left];
            image[i][left].rgbtRed = image[i][right].rgbtRed;
            image[i][right].rgbtRed = pixel.rgbtRed;

            // green logic
            pixel.rgbtGreen = image[i][left].rgbtGreen;
            image[i][left].rgbtGreen = image[i][right].rgbtGreen;
            image[i][right].rgbtGreen = pixel.rgbtGreen;

            //blue logic
            pixel.rgbtBlue = image[i][left].rgbtBlue;
            image[i][left].rgbtBlue = image[i][right].rgbtBlue;
            image[i][right].rgbtBlue = pixel.rgbtBlue;
            left -= 1;
            right += 1;
        }
    }
    return;
}

int min(int a, int b)
{
    if (a <= b)
    {
        return a;
    }

    return b;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copy[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j].rgbtRed = image[i][j].rgbtRed;
            copy[i][j].rgbtGreen = image[i][j].rgbtGreen;
            copy[i][j].rgbtBlue = image[i][j].rgbtBlue;
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            //the actual pixel
            int sumRed = copy[i][j].rgbtRed;
            int sumGreen = copy[i][j].rgbtGreen;
            int sumBlue = copy[i][j].rgbtBlue;
            int count = 1;

            //same column to the right
            if (j - 1 >= 0)
            {
                sumRed += copy[i][j - 1].rgbtRed;
                sumBlue += copy[i][j - 1].rgbtBlue;
                sumGreen += copy[i][j - 1].rgbtGreen;
                count += 1;

            }

            //same column to the left
            if (j + 1 < width)
            {
                sumRed += copy[i][j + 1].rgbtRed;
                sumBlue += copy[i][j + 1].rgbtBlue;
                sumGreen += copy[i][j + 1].rgbtGreen;
                count += 1;

            }

            //on column up
            if (i - 1 >= 0)
            {
                sumRed += copy[i - 1][j].rgbtRed;
                sumBlue += copy[i - 1][j].rgbtBlue;
                sumGreen += copy[i - 1][j].rgbtGreen;

                count += 1;
                if (j - 1 >= 0)
                {
                    sumRed += copy[i - 1][j - 1].rgbtRed;
                    sumBlue += copy[i - 1][j - 1].rgbtBlue;
                    sumGreen += copy[i - 1][j - 1].rgbtGreen;

                    count += 1;
                }
                if (j + 1 < width)
                {
                    sumRed += copy[i - 1][j + 1].rgbtRed;
                    sumBlue += copy[i - 1][j + 1].rgbtBlue;
                    sumGreen += copy[i - 1][j + 1].rgbtGreen;

                    count += 1;
                }
            }

            //one column down
            if (i + 1 < height)
            {
                sumRed += copy[i + 1][j].rgbtRed;
                sumBlue += copy[i + 1][j].rgbtBlue;
                sumGreen += copy[i + 1][j].rgbtGreen;

                count += 1;
                if (j - 1 >= 0)
                {
                    sumRed += copy[i + 1][j - 1].rgbtRed;
                    sumBlue += copy[i + 1][j - 1].rgbtBlue;
                    sumGreen += copy[i + 1][j - 1].rgbtGreen;

                    count += 1;
                }
                if (j + 1 < width)
                {
                    sumRed += copy[i + 1][j + 1].rgbtRed;
                    sumBlue += copy[i + 1][j + 1].rgbtBlue;
                    sumGreen += copy[i + 1][j + 1].rgbtGreen;

                    count += 1;
                }
            }

// calculate avgs
            int avgRed = round(sumRed / (float)count);
            int avgBlue = round(sumBlue / (float)count);
            int avgGreen = round(sumGreen / (float)count);


//set values
            image[i][j].rgbtRed = avgRed;
            image[i][j].rgbtBlue = avgBlue;
            image[i][j].rgbtGreen = avgGreen;

        }
    }
    return;
}

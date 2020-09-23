#include "helpers.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int roundResult = round((float) (image[i][j].rgbtRed + image[i][j].rgbtBlue + image[i][j].rgbtGreen) / 3);
            image[i][j].rgbtRed = image[i][j].rgbtBlue = image[i][j].rgbtGreen = roundResult;
        }
    }

    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{

    // make temporary array
    RGBTRIPLE(*tempImage)[width] = calloc(height, width * sizeof(RGBTRIPLE));

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            tempImage[i][j].rgbtRed = image[i][j].rgbtRed;
            tempImage[i][j].rgbtGreen = image[i][j].rgbtGreen;
            tempImage[i][j].rgbtBlue = image[i][j].rgbtBlue;
        }
    }

    // write result images
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][width - j - 1].rgbtRed = tempImage[i][j].rgbtRed;
            image[i][width - j - 1].rgbtGreen = tempImage[i][j].rgbtGreen;
            image[i][width - j - 1].rgbtBlue = tempImage[i][j].rgbtBlue;
        }
    }


    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{

    // make temporary array
    RGBTRIPLE(*tempImage)[width] = calloc(height, width * sizeof(RGBTRIPLE));

    // process image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int tempRed = 0;
            int countRed = 0;
            int tempGreen = 0;
            int countGreen = 0;
            int tempBlue = 0;
            int countBlue = 0;

            // count around pixels
            //    ------> x j
            //    |
            //   \/ y i

            for (int y = -1; y < 2; y++)
            {
                for (int x = -1; x < 2; x++)
                {
                    // check if the pixel is out of array bound
                    if (((i + y) >= 0) && ((i + y) < height) && ((j + x) >= 0) && ((j + x) < width))
                    {
                        // add value to result pixel and count it
                        tempRed += image[i + y][j + x].rgbtRed;
                        tempGreen += image[i + y][j + x].rgbtGreen;
                        tempBlue += image[i + y][j + x].rgbtBlue;
                        countRed++;
                        countGreen++;
                        countBlue++;
                    }
                }
            }

            // write result pixel with avarage calculation
            tempImage[i][j].rgbtRed = round((float) tempRed / countRed);
            tempImage[i][j].rgbtGreen = round((float) tempGreen / countGreen);
            tempImage[i][j].rgbtBlue = round((float) tempBlue / countBlue);

        }

    }

    // write result array
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtRed = tempImage[i][j].rgbtRed;
            image[i][j].rgbtGreen = tempImage[i][j].rgbtGreen;
            image[i][j].rgbtBlue = tempImage[i][j].rgbtBlue;
        }
    }

    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    // make temporary array for edges
    RGBTRIPLE(*tempImage)[width] = calloc(height, width * sizeof(RGBTRIPLE));

    // init kernels
    int Gx[3][3] = {
        { -1, 0, 1 },
        { -2, 0, 2 },
        { -1, 0, 1 },
        };

    int Gy[3][3] = {
        { -1, -2, -1 },
        { 0, 0, 0 },
        { 1, 2, 1 },
        };

    // process image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int GxRed = 0;
            int GyRed = 0;
            //int countRed = 0;
            int GxGreen = 0;
            int GyGreen = 0;
            //int countGreen = 0;
            int GxBlue = 0;
            int GyBlue = 0;
            //int countBlue = 0;

            // count around pixels
            //    ------> x j
            //    |
            //   \/ y i

            for (int y = -1; y < 2; y++)
            {
                for (int x = -1; x < 2; x++)
                {
                    // check if the pixel is out of array bound
                    if (((i + y) >= 0) && ((i + y) < height) && ((j + x) >= 0) && ((j + x) < width))
                    {
                        // add value to result pixel and count it
                        GxRed += image[i + y][j + x].rgbtRed * Gx[y + 1][x + 1];
                        GxGreen += image[i + y][j + x].rgbtGreen * Gx[y + 1][x + 1];
                        GxBlue += image[i + y][j + x].rgbtBlue * Gx[y + 1][x + 1];
                        //countRed++;
                        //countGreen++;
                        //countBlue++;

                        GyRed += image[i + y][j + x].rgbtRed * Gy[y + 1][x + 1];
                        GyGreen += image[i + y][j + x].rgbtGreen * Gy[y + 1][x + 1];
                        GyBlue += image[i + y][j + x].rgbtBlue * Gy[y + 1][x + 1];
                    }
                    else
                    {
                        // solid black pixel
                    }
                }
            }

            tempImage[i][j].rgbtRed = 0;
            tempImage[i][j].rgbtGreen = 0;
            tempImage[i][j].rgbtBlue = 0;

            // write result pixel with avarage calculation

            // chech is sqrt value is positive
            if ((GxRed * GxRed + GyRed * GyRed) > 0 && (GxRed * GxRed + GyRed * GyRed) <= 65025)
            {
                tempImage[i][j].rgbtRed = round(sqrt(GxRed * GxRed + GyRed * GyRed));
            }

            if ((GxGreen * GxGreen + GyGreen * GyGreen)  > 0 && (GxGreen * GxGreen + GyGreen * GyGreen) <= 65025)
            {
                tempImage[i][j].rgbtGreen = round(sqrt(GxGreen * GxGreen + GyGreen * GyGreen));
            }

            if ((GxBlue * GxBlue + GyBlue * GyBlue) > 0 && (GxBlue * GxBlue + GyBlue * GyBlue) <= 65025)
            {
                tempImage[i][j].rgbtBlue = round(sqrt(GxBlue * GxBlue + GyBlue * GyBlue));
            }

            // chech is result value is higher then 255
            if ((GxRed * GxRed + GyRed * GyRed) > 65025) tempImage[i][j].rgbtRed = 255;
            if ((GxGreen * GxGreen + GyGreen * GyGreen) > 65025) tempImage[i][j].rgbtGreen = 255;
            if ((GxBlue * GxBlue + GyBlue * GyBlue) > 65025) tempImage[i][j].rgbtBlue = 255;

        }

    }

    // write result array
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtRed = tempImage[i][j].rgbtRed;
            image[i][j].rgbtGreen = tempImage[i][j].rgbtGreen;
            image[i][j].rgbtBlue = tempImage[i][j].rgbtBlue;
        }
    }

    return;
}

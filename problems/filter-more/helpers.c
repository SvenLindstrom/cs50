#include "helpers.h"
#include "math.h"
#include "stdlib.h"


// Convert image to grayscale
int get_factor(int center_primery, int center_secondery, int checking_primery, int cheakinc_secondary);
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            RGBTRIPLE pixel = image[i][j];
            int blue = pixel.rgbtBlue;
            int green = pixel.rgbtGreen;
            int red = pixel.rgbtRed;

            int average = round((blue + green + red) / 3.0);

            pixel.rgbtBlue = average;
            pixel.rgbtGreen = average;
            pixel.rgbtRed = average;
            image[i][j] = pixel;
        }
    }

    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{

    for (int i = 0; i < height; i++)
    {
        for (int j = 0, half_width = width / 2; j < half_width; j++)
        {
            RGBTRIPLE temp_Pixel = image[i][j];
            image[i][j] = image[i][width - 1 - j];
            image[i][width - 1 - j] = temp_Pixel;
        }
    }

    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE(*temp)[width] = calloc(height, width * sizeof(RGBTRIPLE));

    for (int i = 0; i < height; i++)
    {
        int y_stard = i - 1;
        int y_end = i + 1;

        if (i == 0)
        {
            y_stard = i;
        }
        else if (i == height - 1)
        {
            y_end = i;
        }

        for (int j = 0; j < width; j++)
        {
            int x_stard = j - 1;
            int x_end = j + 1;

            if (j == 0)
            {
                x_stard = j;
            }
            else if (j == width - 1)
            {
                x_end = j;
            }

            int blue_sum = 0;
            int green_sum = 0;
            int red_sum = 0;
            float num_sum = 0.0;

            for (int y = y_stard; y <= y_end; y++)
            {
                for (int x = x_stard; x <= x_end; x++)
                {
                    RGBTRIPLE pixel = image[y][x];
                    num_sum++;

                    blue_sum += pixel.rgbtBlue;
                    green_sum += pixel.rgbtGreen;
                    red_sum += pixel.rgbtRed;
                }
            }

            temp[i][j].rgbtBlue = (int) round(blue_sum / num_sum);
            temp[i][j].rgbtGreen = (int) round(green_sum / num_sum);
            temp[i][j].rgbtRed = (int) round(red_sum / num_sum);
        }
    }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = temp[i][j];
        }
    }


    free(temp);
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE(*temp)[width] = calloc(height, width * sizeof(RGBTRIPLE));

    for (int i = 0; i < height; i++)
    {
        int y_stard = i - 1;
        int y_end = i + 1;

        for (int j = 0; j < width; j++)
        {
            int x_stard = j - 1;
            int x_end = j + 1;

            int blue_sum_x = 0;
            int green_sum_x = 0;
            int red_sum_x = 0;

            int blue_sum_y = 0;
            int green_sum_y = 0;
            int red_sum_y = 0;

            for (int y = y_stard; y <= y_end; y++)
            {

                for (int x = x_stard; x <= x_end; x++)
                {
                    if (!(y < 0 || y == height || x < 0 || x == width))
                    {
                        int factor_x = get_factor(j, i, x, y);
                        int factor_y = get_factor(i, j, y, x);

                        RGBTRIPLE pixel = image[y][x];
                        blue_sum_x += (pixel.rgbtBlue * factor_x);
                        green_sum_x += (pixel.rgbtGreen * factor_x);
                        red_sum_x += (pixel.rgbtRed * factor_x);

                        blue_sum_y += (pixel.rgbtBlue * factor_y);
                        green_sum_y += (pixel.rgbtGreen * factor_y);
                        red_sum_y += (pixel.rgbtRed * factor_y);
                    }
                }
            }

            int blue = round(sqrt((blue_sum_x * blue_sum_x) + (blue_sum_y * blue_sum_y)));
            int green = round(sqrt((green_sum_x * green_sum_x) + (green_sum_y * green_sum_y)));
            int red = round(sqrt((red_sum_x * red_sum_x) + (red_sum_y * red_sum_y)));

            if (blue > 255)
            {
                blue = 255;
            }
            if (green > 255)
            {
                green = 255;
            }
            if (red > 255)
            {
                red = 255;
            }
            temp[i][j].rgbtBlue = blue;
            temp[i][j].rgbtGreen = green;
            temp[i][j].rgbtRed = red;
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = temp[i][j];
        }
    }
    free(temp);
    return;
}



int get_factor(int center_primery, int center_secondery, int checking_primery, int cheakinc_secondary)
{
    int factor = 1;
    if (cheakinc_secondary == center_secondery && checking_primery != center_primery)
    {
        factor = 2;
    }
    if (checking_primery < center_primery)
    {
        factor *= -1;
    }
    if (checking_primery == center_primery)
    {
        factor = 0;
    }
    return factor;
}


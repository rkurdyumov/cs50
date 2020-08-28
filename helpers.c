#include <math.h>
#include <stdio.h>
#include <string.h>
#include "helpers.h"

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            RGBTRIPLE *p = &image[i][j];
            double avg = round((p->rgbtBlue + p->rgbtGreen + p->rgbtRed) / 3.);
            p->rgbtBlue = p->rgbtGreen = p->rgbtRed = avg;
        }
    }
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width / 2; j++) {
            RGBTRIPLE temp = image[i][j];
            image[i][j] = image[i][width - 1 - j];
            image[i][width - 1 - j] = temp;
        }
    }
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE blurred[height][width];
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            int num_pixels = 0;
            double sum[3] = {0, 0, 0};  // {B, G, R}
            for (int dy = -1; dy <= 1; dy++) {
                if (i + dy < 0 || i + dy >= height) continue;
                for (int dx = -1; dx <= 1; dx++) {
                    if (j + dx < 0 || j + dx >= width) continue;
                    sum[0] += image[i + dy][j + dx].rgbtBlue;
                    sum[1] += image[i + dy][j + dx].rgbtGreen;
                    sum[2] += image[i + dy][j + dx].rgbtRed;
                    num_pixels++;
                }
            }
            blurred[i][j].rgbtBlue = round(sum[0] / num_pixels);
            blurred[i][j].rgbtGreen = round(sum[1] / num_pixels);
            blurred[i][j].rgbtRed = round(sum[2] / num_pixels);
        }
    }
    memcpy(image, blurred, sizeof(RGBTRIPLE) * height * width);
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE edges[height][width];
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            double sum_gx[3] = {0, 0, 0};  // {B, G, R}
            double sum_gy[3] = {0, 0, 0};
            int sobel_gx[3][3] = {{-1, 0, 1},
                                  {-2, 0, 2},
                                  {-1, 0, 1}};
            int sobel_gy[3][3] = {{-1, -2, -1},
                                  {0, 0, 0},
                                  {1, 2, 1}};
            for (int dy = -1; dy <= 1; dy++) {
                if (i + dy < 0 || i + dy >= height) continue;
                for (int dx = -1; dx <= 1; dx++) {
                    if (j + dx < 0 || j + dx >= width) continue;
                    RGBTRIPLE p = image[i + dy][j + dx];
                    sum_gx[0] += sobel_gx[dy + 1][dx + 1] * p.rgbtBlue;
                    sum_gx[1] += sobel_gx[dy + 1][dx + 1] * p.rgbtGreen;
                    sum_gx[2] += sobel_gx[dy + 1][dx + 1] * p.rgbtRed;
                    sum_gy[0] += sobel_gy[dy + 1][dx + 1] * p.rgbtBlue;
                    sum_gy[1] += sobel_gy[dy + 1][dx + 1] * p.rgbtGreen;
                    sum_gy[2] += sobel_gy[dy + 1][dx + 1] * p.rgbtRed;
                }
            }
            int g[3];
            g[0] = round(sqrt(sum_gx[0] * sum_gx[0] + sum_gy[0] * sum_gy[0]));
            g[1] = round(sqrt(sum_gx[1] * sum_gx[1] + sum_gy[1] * sum_gy[1]));
            g[2] = round(sqrt(sum_gx[2] * sum_gx[2] + sum_gy[2] * sum_gy[2]));
            edges[i][j].rgbtBlue = g[0] > 255 ? 255 : g[0];
            edges[i][j].rgbtGreen = g[1] > 255 ? 255 : g[1];
            edges[i][j].rgbtRed = g[2] > 255 ? 255 : g[2];
        }
    }
    memcpy(image, edges, sizeof(RGBTRIPLE) * height * width);
}

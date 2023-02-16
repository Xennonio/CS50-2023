#include "helpers.h"
#include <stdio.h>
#include <math.h>

//Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
  for(int i = 0; i < height; i++)
  {
    for(int j = 0; j < width; j++)
    {
      int newcolor = round((image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed)/3.0);
      if(newcolor > 255)
        newcolor = 255;
      image[i][j].rgbtBlue = newcolor;
      image[i][j].rgbtGreen = newcolor;
      image[i][j].rgbtRed = newcolor;
    }
  }
}

//Sepia effect
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
  for(int i = 0; i < height; i++)
  {
    for(int j = 0; j < width; j++)
    {
      int sepiaRed = round(.393*image[i][j].rgbtRed + .769*image[i][j].rgbtGreen + .189*image[i][j].rgbtBlue),
          sepiaGreen = round(.349*image[i][j].rgbtRed + .686*image[i][j].rgbtGreen + .168*image[i][j].rgbtBlue),
          sepiaBlue = round(.272*image[i][j].rgbtRed + .534*image[i][j].rgbtGreen + .131*image[i][j].rgbtBlue);
      if(sepiaRed > 255)
        sepiaRed = 255;
      if(sepiaGreen > 255)
        sepiaGreen = 255;
      if(sepiaBlue > 255)
        sepiaBlue = 255;
      image[i][j].rgbtBlue = sepiaBlue;
      image[i][j].rgbtGreen = sepiaGreen;
      image[i][j].rgbtRed = sepiaRed;
    }
  }
}

//Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
  for(int i = 0; i < height; i++)
  {
    for(int j = 0; j < width/2; j++)
    {
      RGBTRIPLE tmp = image[i][j];

      image[i][j] = image[i][width - 1 - j];

      image[i][width - 1 - j] = tmp;
    }
  }
}

//Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
  RGBTRIPLE tmp[height][width];

  tmp[0][0].rgbtBlue = round((image[0][0].rgbtBlue + image[0][1].rgbtBlue + image[1][0].rgbtBlue + image[1][1].rgbtBlue)/4.0);
  tmp[0][0].rgbtGreen = round((image[0][0].rgbtGreen + image[0][1].rgbtGreen + image[1][0].rgbtGreen + image[1][1].rgbtGreen)/4.0);
  tmp[0][0].rgbtRed = round((image[0][0].rgbtRed + image[0][1].rgbtRed + image[1][0].rgbtRed + image[1][1].rgbtRed)/4.0);

  tmp[0][width - 1].rgbtBlue = round((image[0][width - 1].rgbtBlue + image[0][width - 2].rgbtBlue + image[1][width - 1].rgbtBlue + image[1][width - 2].rgbtBlue)/4.0);
  tmp[0][width - 1].rgbtGreen = round((image[0][width - 1].rgbtGreen + image[0][width - 2].rgbtGreen + image[1][width - 1].rgbtGreen + image[1][width - 2].rgbtGreen)/4.0);
  tmp[0][width - 1].rgbtRed = round((image[0][width - 1].rgbtRed + image[0][width - 2].rgbtRed + image[1][width - 1].rgbtRed + image[1][width - 2].rgbtRed)/4.0);

  tmp[height - 1][0].rgbtBlue = round((image[height - 1][0].rgbtBlue + image[height - 2][0].rgbtBlue + image[height - 1][1].rgbtBlue + image[height - 2][1].rgbtBlue)/4.0);
  tmp[height - 1][0].rgbtGreen = round((image[height - 1][0].rgbtGreen + image[height - 2][0].rgbtGreen + image[height - 1][1].rgbtGreen + image[height - 2][1].rgbtGreen)/4.0);
  tmp[height - 1][0].rgbtRed = round((image[height - 1][0].rgbtRed + image[height - 2][0].rgbtRed + image[height - 1][1].rgbtRed + image[height - 2][1].rgbtRed)/4.0);

  tmp[height - 1][width - 1].rgbtBlue = round((image[height - 1][width - 1].rgbtBlue + image[height - 2][width - 1].rgbtBlue + image[height - 1][width - 2].rgbtBlue + image[height - 2][width - 2].rgbtBlue)/4.0);
  tmp[height - 1][width - 1].rgbtGreen = round((image[height - 1][width - 1].rgbtGreen + image[height - 2][width - 1].rgbtGreen + image[height - 1][width - 2].rgbtGreen + image[height - 2][width - 2].rgbtGreen)/4.0);
  tmp[height - 1][width - 1].rgbtRed = round((image[height - 1][width - 1].rgbtRed + image[height - 2][width - 1].rgbtRed + image[height - 1][width - 2].rgbtRed + image[height - 2][width - 2].rgbtRed)/4.0);

  for(int i = 0; i < height; i++)
  {
    for(int j = 0; j < width; j++)
    {
      if(i == 0 && 0 < j && j < width - 1)
      {
        tmp[i][j].rgbtBlue = round((image[i][j - 1].rgbtBlue + image[i][j].rgbtBlue + image[i][j + 1].rgbtBlue + image[i + 1][j - 1].rgbtBlue + image[i + 1][j].rgbtBlue + image[i + 1][j + 1].rgbtBlue)/6.0);
        tmp[i][j].rgbtGreen = round((image[i][j - 1].rgbtGreen + image[i][j].rgbtGreen + image[i][j + 1].rgbtGreen + image[i + 1][j - 1].rgbtGreen + image[i + 1][j].rgbtGreen + image[i + 1][j + 1].rgbtGreen)/6.0);
        tmp[i][j].rgbtRed = round((image[i][j - 1].rgbtRed + image[i][j].rgbtRed + image[i][j + 1].rgbtRed + image[i + 1][j - 1].rgbtRed + image[i + 1][j].rgbtRed + image[i + 1][j + 1].rgbtRed)/6.0);
      }
      if(i == height - 1 && 0 < j && j < width - 1)
      {
        tmp[i][j].rgbtBlue = round((image[i][j - 1].rgbtBlue + image[i][j].rgbtBlue + image[i][j + 1].rgbtBlue + image[i - 1][j - 1].rgbtBlue + image[i - 1][j].rgbtBlue + image[i - 1][j + 1].rgbtBlue)/6.0);
        tmp[i][j].rgbtGreen = round((image[i][j - 1].rgbtGreen + image[i][j].rgbtGreen + image[i][j + 1].rgbtGreen + image[i - 1][j - 1].rgbtGreen + image[i - 1][j].rgbtGreen + image[i - 1][j + 1].rgbtGreen)/6.0);
        tmp[i][j].rgbtRed = round((image[i][j - 1].rgbtRed + image[i][j].rgbtRed + image[i][j + 1].rgbtRed + image[i - 1][j - 1].rgbtRed + image[i - 1][j].rgbtRed + image[i - 1][j + 1].rgbtRed)/6.0);
      }
      if(0 < i && i < height - 1 && j == 0)
      {
        tmp[i][j].rgbtBlue = round((image[i - 1][j].rgbtBlue + image[i][j].rgbtBlue + image[i + 1][j].rgbtBlue + image[i - 1][j + 1].rgbtBlue + image[i][j + 1].rgbtBlue + image[i + 1][j + 1].rgbtBlue)/6.0);
        tmp[i][j].rgbtGreen = round((image[i - 1][j].rgbtGreen + image[i][j].rgbtGreen + image[i + 1][j].rgbtGreen + image[i - 1][j + 1].rgbtGreen + image[i][j + 1].rgbtGreen + image[i + 1][j + 1].rgbtGreen)/6.0);
        tmp[i][j].rgbtRed = round((image[i - 1][j].rgbtRed + image[i][j].rgbtRed + image[i + 1][j].rgbtRed + image[i - 1][j + 1].rgbtRed + image[i][j + 1].rgbtRed + image[i + 1][j + 1].rgbtRed)/6.0);
      }
      if(0 < i && i < height - 1 && j == width - 1)
      {
        tmp[i][j].rgbtBlue = round((image[i - 1][j].rgbtBlue + image[i][j].rgbtBlue + image[i + 1][j].rgbtBlue + image[i - 1][j - 1].rgbtBlue + image[i][j - 1].rgbtBlue + image[i + 1][j - 1].rgbtBlue)/6.0);
        tmp[i][j].rgbtGreen = round((image[i - 1][j].rgbtGreen + image[i][j].rgbtGreen + image[i + 1][j].rgbtGreen + image[i - 1][j - 1].rgbtGreen + image[i][j - 1].rgbtGreen + image[i + 1][j - 1].rgbtGreen)/6.0);
        tmp[i][j].rgbtRed = round((image[i - 1][j].rgbtRed + image[i][j].rgbtRed + image[i + 1][j].rgbtRed + image[i - 1][j - 1].rgbtRed + image[i][j - 1].rgbtRed + image[i + 1][j - 1].rgbtRed)/6.0);
      }
      if(0 < i && i < height - 1 && 0 < j && j < width - 1)
      {
        tmp[i][j].rgbtBlue = round((image[i - 1][j - 1].rgbtBlue + image[i - 1][j].rgbtBlue + image[i - 1][j + 1].rgbtBlue + image[i][j - 1].rgbtBlue + image[i][j].rgbtBlue + image[i][j + 1].rgbtBlue + image[i + 1][j - 1].rgbtBlue + image[i + 1][j].rgbtBlue + image[i + 1][j + 1].rgbtBlue)/9.0);
        tmp[i][j].rgbtGreen = round((image[i - 1][j - 1].rgbtGreen + image[i - 1][j].rgbtGreen + image[i - 1][j + 1].rgbtGreen + image[i][j - 1].rgbtGreen + image[i][j].rgbtGreen + image[i][j + 1].rgbtGreen + image[i + 1][j - 1].rgbtGreen + image[i + 1][j].rgbtGreen + image[i + 1][j + 1].rgbtGreen)/9.0);
        tmp[i][j].rgbtRed = round((image[i - 1][j - 1].rgbtRed + image[i - 1][j].rgbtRed + image[i - 1][j + 1].rgbtRed + image[i][j - 1].rgbtRed + image[i][j].rgbtRed + image[i][j + 1].rgbtRed + image[i + 1][j - 1].rgbtRed + image[i + 1][j].rgbtRed + image[i + 1][j + 1].rgbtRed)/9.0);
      }
    }
  }
  for(int i = 0; i < height; i++)
  {
    for(int j = 0; j < width; j++)
    {
      image[i][j].rgbtBlue = tmp[i][j].rgbtBlue;
      image[i][j].rgbtGreen = tmp[i][j].rgbtGreen;
      image[i][j].rgbtRed = tmp[i][j].rgbtRed;
    }
  }
}

//Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
  int GxBlue, GxRed, GxGreen, GyBlue, GyRed, GyGreen;
  RGBTRIPLE tmp[height][width];

  GxBlue = (2*image[0][1].rgbtBlue + image[1][1].rgbtBlue);
  GxGreen = (2*image[0][1].rgbtGreen + image[1][1].rgbtGreen);
  GxRed = (2*image[0][1].rgbtRed + image[1][1].rgbtRed);
  GyBlue = (2*image[1][0].rgbtBlue + image[1][1].rgbtBlue);
  GyGreen = (2*image[1][0].rgbtGreen + image[1][1].rgbtGreen);
  GyRed = (2*image[1][0].rgbtRed + image[1][1].rgbtRed);
  tmp[0][0].rgbtBlue = fmin(round((float)sqrt(pow(GxBlue, 2) + pow(GyBlue, 2))), 255);
  tmp[0][0].rgbtGreen = fmin(round((float)sqrt(pow(GxGreen, 2) + pow(GyGreen, 2))), 255);
  tmp[0][0].rgbtRed = fmin(round((float)sqrt(pow(GxRed, 2) + pow(GyRed, 2))), 255);

  GxBlue = (-2*image[0][width - 2].rgbtBlue - image[1][width - 2].rgbtBlue);
  GxGreen = (-2*image[0][width - 2].rgbtGreen - image[1][width - 2].rgbtGreen);
  GxRed = (-2*image[0][width - 2].rgbtRed - image[1][width - 2].rgbtRed);
  GyBlue = (image[1][width - 2].rgbtBlue + 2*image[1][width - 1].rgbtBlue);
  GyGreen = (image[1][width - 2].rgbtGreen + 2*image[1][width - 1].rgbtGreen);
  GyRed = (image[1][width - 2].rgbtRed + 2*image[1][width - 1].rgbtRed);
  tmp[0][width - 1].rgbtBlue = fmin(round((float)sqrt(pow(GxBlue, 2) + pow(GyBlue, 2))), 255);
  tmp[0][width - 1].rgbtGreen = fmin(round((float)sqrt(pow(GxGreen, 2) + pow(GyGreen, 2))), 255);
  tmp[0][width - 1].rgbtRed = fmin(round((float)sqrt(pow(GxRed, 2) + pow(GyRed, 2))), 255);

  GxBlue = (2*image[height - 1][1].rgbtBlue + image[height - 2][1].rgbtBlue);
  GxGreen = (2*image[height - 1][1].rgbtGreen + image[height - 2][1].rgbtGreen);
  GxRed = (2*image[height - 1][1].rgbtRed + image[height - 2][1].rgbtRed);
  GyBlue = (-2*image[height - 2][0].rgbtBlue - image[height - 2][1].rgbtBlue);
  GyGreen = (-2*image[height - 2][0].rgbtGreen - image[height - 2][1].rgbtGreen);
  GyRed = (-2*image[height - 2][0].rgbtRed - image[height - 2][1].rgbtRed);
  tmp[height - 1][0].rgbtBlue = fmin(round((float)sqrt(pow(GxBlue, 2) + pow(GyBlue, 2))), 255);
  tmp[height - 1][0].rgbtGreen = fmin(round((float)sqrt(pow(GxGreen, 2) + pow(GyGreen, 2))), 255);
  tmp[height - 1][0].rgbtRed = fmin(round((float)sqrt(pow(GxRed, 2) + pow(GyRed, 2))), 255);

  GxBlue = (-2*image[height - 1][width - 2].rgbtBlue - image[height - 2][width - 2].rgbtBlue);
  GxGreen = (-2*image[height - 1][width - 2].rgbtGreen - image[height - 2][width - 2].rgbtGreen);
  GxRed = (-2*image[height - 1][width - 2].rgbtRed - image[height - 2][width - 2].rgbtRed);
  GyBlue = (-2*image[height - 2][width - 1].rgbtBlue - image[height - 2][width - 2].rgbtBlue);
  GyGreen = (-2*image[height - 2][width - 1].rgbtGreen - image[height - 2][width - 2].rgbtGreen);
  GyRed = (-2*image[height - 2][width - 1].rgbtRed - image[height - 2][width - 2].rgbtRed);
  tmp[height - 1][width - 1].rgbtBlue = fmin(round((float)sqrt(pow(GxBlue, 2) + pow(GyBlue, 2))), 255);
  tmp[height - 1][width - 1].rgbtGreen = fmin(round((float)sqrt(pow(GxGreen, 2) + pow(GyGreen, 2))), 255);
  tmp[height - 1][width - 1].rgbtRed = fmin(round((float)sqrt(pow(GxRed, 2) + pow(GyRed, 2))), 255);

  for(int i = 0; i < height; i++)
  {
    for(int j = 0; j < width; j++)
    {
      if(i == 0 && 0 < j && j < width - 1)
      {
        GxBlue = (-2*image[i][j - 1].rgbtBlue + 2*image[i][j + 1].rgbtBlue - image[i + 1][j - 1].rgbtBlue + image[i + 1][j + 1].rgbtBlue);
        GxGreen = (-2*image[i][j - 1].rgbtGreen + 2*image[i][j + 1].rgbtGreen - image[i + 1][j - 1].rgbtGreen + image[i + 1][j + 1].rgbtGreen);
        GxRed = (-2*image[i][j - 1].rgbtRed + 2*image[i][j + 1].rgbtRed - image[i + 1][j - 1].rgbtRed + image[i + 1][j + 1].rgbtRed);
        GyBlue = (image[i + 1][j - 1].rgbtBlue + 2*image[i + 1][j].rgbtBlue + image[i + 1][j + 1].rgbtBlue);
        GyGreen = (image[i + 1][j - 1].rgbtGreen + 2*image[i + 1][j].rgbtGreen + image[i + 1][j + 1].rgbtGreen);
        GyRed = (image[i + 1][j - 1].rgbtRed + 2*image[i + 1][j].rgbtRed + image[i + 1][j + 1].rgbtRed);
        tmp[i][j].rgbtBlue = fmin(round((float)sqrt(pow(GxBlue, 2) + pow(GyBlue, 2))), 255);
        tmp[i][j].rgbtGreen = fmin(round((float)sqrt(pow(GxGreen, 2) + pow(GyGreen, 2))), 255);
        tmp[i][j].rgbtRed = fmin(round((float)sqrt(pow(GxRed, 2) + pow(GyRed, 2))), 255);
      }
      if(i == height - 1 && 0 < j && j < width - 1)
      {
        GxBlue = (-image[i - 1][j - 1].rgbtBlue + image[i - 1][j + 1].rgbtBlue -2*image[i][j - 1].rgbtBlue + 2*image[i][j + 1].rgbtBlue);
        GxGreen = (-image[i - 1][j - 1].rgbtGreen + image[i - 1][j + 1].rgbtGreen -2*image[i][j - 1].rgbtGreen + 2*image[i][j + 1].rgbtGreen);
        GxRed = (-image[i - 1][j - 1].rgbtRed + image[i - 1][j + 1].rgbtRed -2*image[i][j - 1].rgbtRed + 2*image[i][j + 1].rgbtRed);
        GyBlue = (-image[i - 1][j - 1].rgbtBlue - 2*image[i - 1][j].rgbtBlue - image[i - 1][j + 1].rgbtBlue);
        GyGreen = (-image[i - 1][j - 1].rgbtGreen - 2*image[i - 1][j].rgbtGreen - image[i - 1][j + 1].rgbtGreen);
        GyRed = (-image[i - 1][j - 1].rgbtRed - 2*image[i - 1][j].rgbtRed - image[i - 1][j + 1].rgbtRed);
        tmp[i][j].rgbtBlue = fmin(round((float)sqrt(pow(GxBlue, 2) + pow(GyBlue, 2))), 255);
        tmp[i][j].rgbtGreen = fmin(round((float)sqrt(pow(GxGreen, 2) + pow(GyGreen, 2))), 255);
        tmp[i][j].rgbtRed = fmin(round((float)sqrt(pow(GxRed, 2) + pow(GyRed, 2))), 255);
      }
      if(0 < i && i < height - 1 && j == 0)
      {
        GxBlue = (image[i - 1][j + 1].rgbtBlue + 2*image[i][j + 1].rgbtBlue + image[i + 1][j + 1].rgbtBlue);
        GxGreen = (image[i - 1][j + 1].rgbtGreen + 2*image[i][j + 1].rgbtGreen + image[i + 1][j + 1].rgbtGreen);
        GxRed = (image[i - 1][j + 1].rgbtRed + 2*image[i][j + 1].rgbtRed + image[i + 1][j + 1].rgbtRed);
        GyBlue = (-2*image[i - 1][j].rgbtBlue - image[i - 1][j + 1].rgbtBlue + 2*image[i + 1][j].rgbtBlue + image[i + 1][j + 1].rgbtBlue);
        GyGreen = (-2*image[i - 1][j].rgbtGreen - image[i - 1][j + 1].rgbtGreen + 2*image[i + 1][j].rgbtGreen + image[i + 1][j + 1].rgbtGreen);
        GyRed = (-2*image[i - 1][j].rgbtRed - image[i - 1][j + 1].rgbtRed + 2*image[i + 1][j].rgbtRed + image[i + 1][j + 1].rgbtRed);
        tmp[i][j].rgbtBlue = fmin(round((float)sqrt(pow(GxBlue, 2) + pow(GyBlue, 2))), 255);
        tmp[i][j].rgbtGreen = fmin(round((float)sqrt(pow(GxGreen, 2) + pow(GyGreen, 2))), 255);
        tmp[i][j].rgbtRed = fmin(round((float)sqrt(pow(GxRed, 2) + pow(GyRed, 2))), 255);
      }
      if(0 < i && i < height - 1 && j == width - 1)
      {
        GxBlue = (-image[i - 1][j - 1].rgbtBlue - 2*image[i][j - 1].rgbtBlue - image[i + 1][j - 1].rgbtBlue);
        GxGreen = (-image[i - 1][j - 1].rgbtGreen - 2*image[i][j - 1].rgbtGreen - image[i + 1][j - 1].rgbtGreen);
        GxRed = (-image[i - 1][j - 1].rgbtRed - 2*image[i][j - 1].rgbtRed - image[i + 1][j - 1].rgbtRed);
        GyBlue = (-image[i - 1][j - 1].rgbtBlue - 2*image[i - 1][j].rgbtBlue + image[i + 1][j - 1].rgbtBlue + 2*image[i + 1][j].rgbtBlue);
        GyGreen = (-image[i - 1][j - 1].rgbtGreen - 2*image[i - 1][j].rgbtGreen + image[i + 1][j - 1].rgbtGreen + 2*image[i + 1][j].rgbtGreen);
        GyRed = (-image[i - 1][j - 1].rgbtRed - 2*image[i - 1][j].rgbtRed + image[i + 1][j - 1].rgbtRed + 2*image[i + 1][j].rgbtRed);
        tmp[i][j].rgbtBlue = fmin(round((float)sqrt(pow(GxBlue, 2) + pow(GyBlue, 2))), 255);
        tmp[i][j].rgbtGreen = fmin(round((float)sqrt(pow(GxGreen, 2) + pow(GyGreen, 2))), 255);
        tmp[i][j].rgbtRed = fmin(round((float)sqrt(pow(GxRed, 2) + pow(GyRed, 2))), 255);
      }
      if(0 < i && i < height - 1 && 0 < j && j < width - 1)
      {
        GxBlue = (-image[i - 1][j - 1].rgbtBlue + image[i - 1][j + 1].rgbtBlue -2*image[i][j - 1].rgbtBlue + 2*image[i][j + 1].rgbtBlue - image[i + 1][j - 1].rgbtBlue + image[i + 1][j + 1].rgbtBlue);
        GxGreen = (-image[i - 1][j - 1].rgbtGreen + image[i - 1][j + 1].rgbtGreen -2*image[i][j - 1].rgbtGreen + 2*image[i][j + 1].rgbtGreen - image[i + 1][j - 1].rgbtGreen + image[i + 1][j + 1].rgbtGreen);
        GxRed = (-image[i - 1][j - 1].rgbtRed + image[i - 1][j + 1].rgbtRed -2*image[i][j - 1].rgbtRed + 2*image[i][j + 1].rgbtRed - image[i + 1][j - 1].rgbtRed + image[i + 1][j + 1].rgbtRed);
        GyBlue = (-image[i - 1][j - 1].rgbtBlue - 2*image[i - 1][j].rgbtBlue - image[i - 1][j + 1].rgbtBlue + image[i + 1][j - 1].rgbtBlue + 2*image[i + 1][j].rgbtBlue + image[i + 1][j + 1].rgbtBlue);
        GyGreen = (-image[i - 1][j - 1].rgbtGreen - 2*image[i - 1][j].rgbtGreen - image[i - 1][j + 1].rgbtGreen + image[i + 1][j - 1].rgbtGreen + 2*image[i + 1][j].rgbtGreen + image[i + 1][j + 1].rgbtGreen);
        GyRed = (-image[i - 1][j - 1].rgbtRed - 2*image[i - 1][j].rgbtRed - image[i - 1][j + 1].rgbtRed + image[i + 1][j - 1].rgbtRed + 2*image[i + 1][j].rgbtRed + image[i + 1][j + 1].rgbtRed);
        tmp[i][j].rgbtBlue = fmin(round((float)sqrt(pow(GxBlue, 2) + pow(GyBlue, 2))), 255);
        tmp[i][j].rgbtGreen = fmin(round((float)sqrt(pow(GxGreen, 2) + pow(GyGreen, 2))), 255);
        tmp[i][j].rgbtRed = fmin(round((float)sqrt(pow(GxRed, 2) + pow(GyRed, 2))), 255);
      }
    }
  }
  for(int i = 0; i < height; i++)
  {
    for(int j = 0; j < width; j++)
    {
      image[i][j].rgbtBlue = tmp[i][j].rgbtBlue;
      image[i][j].rgbtGreen = tmp[i][j].rgbtGreen;
      image[i][j].rgbtRed = tmp[i][j].rgbtRed;
    }
  }
}
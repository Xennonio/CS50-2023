#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "wav.h"

int check_format(WAVHEADER header);
int get_block_size(WAVHEADER header);

int main(int argc, char *argv[])
{
  // Ensure proper usage
  if(argc != 3)
  {
    printf("Usage: ./reverse input.wav output.wav\n");
    return 1;
  }

  // Open input file for reading
  FILE *file = fopen(argv[1], "r");

  if(file == NULL)
  {
    printf("Could not open file\n");
    return 1;
  }

  // Read header
  WAVHEADER buffer;

  fread(&buffer, sizeof(WAVHEADER), 1, file);

  // Use check_format to ensure WAV format
  if(!check_format(buffer))
  {
    printf("Input is not a WAV file.\n");
    return 2;
  }

  // Open output file for writing
  FILE *output = fopen(argv[2], "w");

  if(output == NULL)
  {
    printf("Could not open file");
    return 1;
  }

  // Write header to file
  fwrite(&buffer, sizeof(WAVHEADER), 1, output);

  // Use get_block_size to calculate size of block
  int block_size = get_block_size(buffer);

  // Write reversed audio to file
  int data[block_size];

  // Start seeking from the end
  fseek(file, block_size, SEEK_END);

  // Read everything after the header
  while(ftell(file) - block_size > sizeof(WAVHEADER))
  {
    // After fread(file) in data we take 2 block_size steps back
    fseek(file, -2*block_size, SEEK_CUR);
    fread(&data, block_size, 1, file);
    fwrite(&data, block_size, 1, output);
  }

  printf("%ld\n", ftell(file));

  // Close open files
  fclose(file);
  fclose(output);
}

int check_format(WAVHEADER header)
{
  if(header.format[0] == 'W' && header.format[1] == 'A' && header.format[2] == 'V' && header.format[3] == 'E')
  {
    return 1;
  }
  return 0;
}

int get_block_size(WAVHEADER header)
{
  // header.bitsPerSample returns the number of bits, as we want the bytes we divide it by 8
  return header.numChannels * (header.bitsPerSample / 8);
}
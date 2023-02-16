#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
  if(argc != 2)
  {
    printf("Usage: ./recover card.raw");
    return 1;
  }

  FILE *file = fopen(argv[1], "r");

  if(file == NULL)
  {
    printf("Could not open file");
    return 2;
  }

  unsigned char buffer[512];
  int count_image = 0;
  FILE *output = NULL;
  char *filename = malloc(8*sizeof(char));

  while(fread(buffer, sizeof(char), 512, file))
  {
    if(buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && ((buffer[3] & 0xf0) == 0xe0))
    {
      sprintf(filename, "%03i.jpg", count_image);
      output = fopen(filename, "w");
      count_image++;
    }
    if(output != NULL)
    {
      fwrite(buffer, sizeof(char), 512, output);
    }
  }
  free(filename);
  fclose(output);
  fclose(file);

  return 0;
}
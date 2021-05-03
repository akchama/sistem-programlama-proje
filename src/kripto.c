#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include "fields.h"
#include <cJSON.h>

void encrypt(IS is_input);
void decrypt();

int main(int argc, char **argv)
{
  IS is_input;
  is_input = new_inputstruct("data/istiklal_marsi/istiklal_marsi.txt");

  encrypt(is_input);
  decrypt();

  return 0;
}

void decrypt() 
{
  FILE *f = fopen ("data/istiklal_marsi/decrypted_test.txt", "w+");
}

void encrypt(IS is_input)
{
  FILE *fp;
  int i, j;
  char *buffer = 0;
  long length;
  FILE *f = fopen ("data/istiklal_marsi/.kilit", "rb");
  cJSON *json;
  cJSON *name = NULL;

  if (is_input == NULL) {
    perror("Hata: ");
    exit(1);
  }

  fp = fopen("data/istiklal_marsi/encripted_test", "w+");
  if (fp < 0) { perror("data/hata.txt"); exit(1); }

  if (f)
  {
    fseek (f, 0, SEEK_END);
    length = ftell (f);
    fseek (f, 0, SEEK_SET);
    buffer = malloc (length);
    if (buffer)
    {
      fread (buffer, 1, length, f);
    }
    fclose (f);
  }

  if (buffer)
  {
    json = cJSON_Parse(buffer);
    while(get_line(is_input) >= 0) {
      for (i = 0; i < is_input->NF; i++) {
        name = cJSON_GetObjectItemCaseSensitive(json, is_input->fields[i]);
        fprintf(fp, "%s ", name->valuestring);
        // printf("%d: %s: ", is_input->line, is_input->fields[i]);
        // printf("%s\n", name->valuestring);
      }
    }
  }

  jettison_inputstruct(is_input);
  fclose(fp);
  return;
}
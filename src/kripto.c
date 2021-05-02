#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include "fields.h"
#include <cJSON.h>

int main(int argc, char **argv)
{
  IS is;
  int i, j;
  FILE *fp;
  cJSON *name = NULL;
  char *buffer = 0;
  long length;
  cJSON *json;
  FILE *f = fopen ("data/istiklal_marsi/.kilit", "rb");
  is = new_inputstruct("data/istiklal_marsi/istiklal_marsi.txt");

  if (is == NULL) {
    perror(argv[1]);
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
    while(get_line(is) >= 0) {
      for (i = 0; i < is->NF; i++) {
        name = cJSON_GetObjectItemCaseSensitive(json, is->fields[i]);
        fprintf(fp, "%s ", name->valuestring);
        // printf("%d: %s: ", is->line, is->fields[i]);
        // printf("%s\n", name->valuestring);
      }
    }
  }

  jettison_inputstruct(is);
  fclose(fp);
  return 0;
}
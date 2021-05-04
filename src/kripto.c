#include <fcntl.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "fields.h"
#include <cJSON.h>
#include "jrb.h"

void encrypt();
void decrypt();

int main(int argc, char **argv)
{
  // encrypt();
  decrypt();

  return 0;
}

void decrypt()
{
    FILE* fp;
    int i, j;
    char* buffer = 0;
    char* str = 0;
    long length;
    FILE* f = fopen("data/istiklal_marsi/.kilit", "rb");
    cJSON* json;
    JRB b, tmp;
    b = make_jrb();
    tmp = make_jrb();

    fp = fopen("data/istiklal_marsi/decrypted_test.txt", "w+");
    if (fp < 0) { perror("Error: "); exit(1); }

    if (f)
    {
        fseek(f, 0, SEEK_END);
        length = ftell(f);
        fseek(f, 0, SEEK_SET);
        buffer = malloc(length);
        if (buffer)
        {
            fread(buffer, 1, length, f);
        }
        fclose(f);
    }

    if (buffer)
    {
        json = cJSON_Parse(buffer);
        cJSON* current_element = NULL;
        char* current_key = NULL;

        cJSON_ArrayForEach(current_element, json)
        {
            current_key = current_element->string;
            if (current_key != NULL)
            {
                // printf("%s ", current_element->valuestring);
                (void)jrb_insert_str(b, strdup(current_element->valuestring), new_jval_v(current_key));
            }
        }
    }

    fclose(fp);
    return;
}

void encrypt()
{
  IS is_input;
  FILE *fp;
  int i, j;
  char *buffer = 0;
  long length;
  FILE *f = fopen ("data/istiklal_marsi/.kilit", "r");
  cJSON *json;
  cJSON *name = NULL;
  JRB b, tmp;
  b = make_jrb();
  tmp = make_jrb();
  is_input = new_inputstruct("data/istiklal_marsi/istiklal_marsi.txt");

  if (is_input == NULL) {
    perror("Hata: ");
    exit(1);
  }

  fp = fopen("data/istiklal_marsi/encrypted_test", "w+");
  if (fp < 0) { perror("Error: "); exit(1); }

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
    cJSON *current_element = NULL;
    char *current_key = NULL;

    cJSON_ArrayForEach(current_element, json)
    {
        current_key = current_element->string;
        if (current_key != NULL)
        {
            // printf("%s ", current_element->valuestring);
            (void) jrb_insert_str(b, strdup(current_key), new_jval_v(current_element->valuestring));
        }
    }

    while(get_line(is_input) >= 0) {
      for (i = 0; i < is_input->NF; i++) {
        tmp = jrb_find_str(b, is_input->fields[i]);
        fprintf(fp, "%s ", tmp->val.s);
      }
    }
  }

  jettison_inputstruct(is_input);
  fclose(fp);
  jrb_free_tree(b);
  return;
}
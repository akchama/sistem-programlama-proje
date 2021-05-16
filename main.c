#include <fcntl.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "fields.h"
#include <cJSON.h>
#include "jrb.h"

void encrypt();
void decrypt();

int main(int argc, char *argv[])
{
  if (argc != 4) 
  { 
    fprintf(stderr, "Kullanım: kripto -e [giris dosyasi] [cikis dosyasi]\n"); 
    exit(1); 
  }

  if (strcmp(argv[1], "-e") == 0) 
  {
    encrypt(argv);
  }
  else if (strcmp(argv[1], "-d") == 0)
  {
    decrypt(argv);
  }
  else
  {
    printf("Hatalı giriş\n");
  }
  return 0;
}

void decrypt(char **argv)
{
  IS is_input;
  FILE *fp;
  int i, j;
  char *buffer = 0;
  char *str = 0;
  long length;
  FILE *f = fopen (".kilit", "r");
  cJSON *json;
  JRB b, tmp;
  b = make_jrb();
  tmp = make_jrb();
  is_input = new_inputstruct(argv[2]);

  if (is_input == NULL) {
    perror("Hata");
    exit(1);
  }

  fp = fopen(argv[3], "w+");
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
  else
  {
    printf("Kilit dosyası açılamıyor\n");
    exit(1);
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
            (void) jrb_insert_str(b, strdup(current_element->valuestring), new_jval_v(current_key));
        }
    }
    while(get_line(is_input) >= 0) {
      for (i = 0; i < is_input->NF; i++) {
        str = strdup(is_input->fields[i]);
        // printf("%s ", str);
        tmp = jrb_find_str(b, str);
        if (tmp == NULL) {
          printf("| %s Bulunamadi | (1000 karakter hatasi)\n", str);
        }
        else {
          fprintf(fp, "%s ", tmp->val.s);
        }
      }
    }
    printf("***\nDecoding işlemi tamamlandı.\n***\n");
  }

  jettison_inputstruct(is_input);
  fclose(fp);
  return;
}

void encrypt(char **argv)
{
  IS is_input;
  FILE *fp;
  int i, j;
  char *buffer = 0;
  long length;
  FILE *f = fopen (".kilit", "r");
  cJSON *json;
  cJSON *name = NULL;
  JRB b, tmp;
  b = make_jrb();
  tmp = make_jrb();
  is_input = new_inputstruct(argv[2]);
  if (is_input == NULL) {
    perror(argv[2]);
    exit(1);
  }

  fp = fopen(argv[3], "w+");
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
  else
  {
    printf(".kilit dosyası açılamıyor\n");
    exit(1);
  }

  if (buffer)
  {
    printf(".kilit dosyası okunuyor...\n");
    json = cJSON_Parse(buffer);
    cJSON *current_element = NULL;
    char *current_key = NULL;

    if (json == NULL) {
      printf("Gecersiz json");
    }
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
    printf("Şifrelenen dosya: %s\n", argv[3]);
  }
  else
  {
    printf("Buffer hatası\n");
  }

  jettison_inputstruct(is_input);
  fclose(fp);
  jrb_free_tree(b);
  return;
}
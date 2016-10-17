#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdarg.h>
#include <openssl/md5.h>
#include <string.h>

#define COUNT 1024
#define DEBUG

struct sumInfo {
  unsigned char data[MD5_DIGEST_LENGTH];
  unsigned char match;
};

int main(int argc, const char *argv[]) {
  int ret = -1;
  MD5_CTX mdContext;
  uint32_t i, j;
  uint64_t argsAmount = argc - 1;
  uint8_t printing = 0;
  uint32_t bytes;
  unsigned char data[COUNT];
  //the [argc - 1][MD5_DIGEST_LENGTH] array
  struct sumInfo **checksums = NULL;

  if (!(checksums = malloc(argsAmount * sizeof(unsigned char *)))) {
    printf("Memory allocation error\n");
    goto exit1;
  }
  for (i = 0; i < argsAmount; ++i) {
    if (!(checksums[i] = malloc(sizeof(struct sumInfo)))) {
      printf("Memory allocation error\n");
      goto exit2;
    }
  }

  for (i = 0; i < argsAmount; ++i) {
    //open a file passed
    FILE *file = NULL;

    if (!(file = fopen(argv[i + 1], "rb"))) {
      printf("Failed to open file %s", argv[i + 1]);
      break;
    }
    //calculate md5 sum for the opened file
    MD5_Init(&mdContext);
    while ((bytes = fread(data, 1, COUNT, file)) != 0) {
      MD5_Update(&mdContext, data, bytes);
    }
    MD5_Final(checksums[i]->data, &mdContext);
    checksums[i]->match = 0;
    #ifdef DEBUG
    for (j = 0; j < MD5_DIGEST_LENGTH; ++j) {
      printf("%02x", checksums[i]->data[j]);
    }
    printf(" %s\n", argv[i + 1]);
    #endif
    fclose(file);
  }

  for (i = 0; i < argsAmount; ++i) {
    if (checksums[i]->match) {
      continue;
    }
    for (j = i + 1; j < argsAmount; ++j) {
      if (!strcmp(checksums[i]->data, checksums[j]->data)) {
        checksums[j]->match = 1;
        printing = 1;
        printf("%s ", argv[j + 1]);
      }
    }
    if (printing) {
      printf ("%s\n", argv[i + 1]);
      printing = 0;
    }
  }

  ret = 0;

  for (i = 0; i < argsAmount; ++i) {
    free(checksums[i]);
  }
exit2:
  free(checksums);
exit1:
  return ret;
}

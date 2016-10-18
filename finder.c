#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdarg.h>
#include <openssl/md5.h>
#include <string.h>

#include "finder.h"

#define STRUCTSIZE sizeof(struct sumInfo)

//can't think of a way to handle the return type since it was mentioned that
////a failure when getting a file descriptor is a possible situation and
////should not be treated as a programm failure
////but for the sake of a future handling function has a return code, yup
int md5File(void *rawData, const char *fileName) {
  int ret = -1;
  uint32_t bytes;
  MD5_CTX mdContext;
  unsigned char data[COUNT];
  FILE *file = NULL;
  struct sumInfo *item = (struct sumInfo*)rawData;

  if (!(file = fopen(fileName, "rb"))) {
#ifdef DEBUG
    printf("Failed to open file %s\n", fileName);
#endif
    goto exit;
  }
  MD5_Init(&mdContext);
  while ((bytes = fread(data, 1, COUNT, file)) != 0) {
    MD5_Update(&mdContext, data, bytes);
  }
  MD5_Final(item->data, &mdContext);
  item->match = 0;
  fclose(file);

#ifdef DEBUG
  for (i = 0; i < MD5_DIGEST_LENGTH; ++i) {
    printf("%02x", item->data[i]);
  }
  printf(" %s\n", fileName);
#endif

  ret = 0;

exit:
  return ret;
}


int main(int argc, const char *argv[]) {
  int ret = -1;
  uint32_t i, j;
  uint64_t argsAmount = argc - 1;
  uint8_t printing = 0;
  void *data = NULL;

  if (!(data = calloc(argsAmount, STRUCTSIZE))) {
    printf("Memory allocation error\n");
    goto exit;
  }

  for (i = 0; i < argsAmount; ++i) {
    md5File(data + i*STRUCTSIZE, argv[i + 1]);
  }

  for (i = 0; i < argsAmount; ++i) {
    if (((struct sumInfo *)(data + i*STRUCTSIZE))->match) {
      continue;
    }
    for (j = i + 1; j < argsAmount; ++j) {
      if (!memcmp(data + i*STRUCTSIZE, data + j*STRUCTSIZE, MD5_DIGEST_LENGTH)) {
        ((struct sumInfo *)(data + j*STRUCTSIZE))->match = 1;
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
  free(data);

exit:
  return ret;
}

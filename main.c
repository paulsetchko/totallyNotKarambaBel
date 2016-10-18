#include <stdarg.h>
#include <string.h>
#include "finder.h"

#define STRUCTSIZE sizeof(struct sumInfo)

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
        printf("%s\n", argv[j + 1]);
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

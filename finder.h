#ifndef __FINDER_H__

#define __FINDER_H__

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <openssl/md5.h>

#define COUNT 1024
//#define DEBUG

int md5File(void *, const char *);

struct sumInfo {
  unsigned char data[MD5_DIGEST_LENGTH];
  unsigned char match;
};

#endif

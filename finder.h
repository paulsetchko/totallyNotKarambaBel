#ifndef __FINDER_H__

#define __FINDER_H__

#define COUNT 1024
//#define DEBUG

int md5File(void *, const char *);

struct sumInfo {
  unsigned char data[MD5_DIGEST_LENGTH];
  unsigned char match;
};

#endif

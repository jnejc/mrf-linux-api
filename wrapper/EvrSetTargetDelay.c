#include <stdint.h>
#include <endian.h>
#include <byteswap.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <signal.h>
#include "../api/erapi.h"

int main(int argc, char *argv[])
{
  struct MrfErRegs *pEr;
  int              fdEr;
  int              i;
  int              delay;

  if (argc < 3)
    {
      printf("Usage: %s /dev/era3 <delay>\n", argv[0]);
      return -1;
    }

  fdEr = EvrOpen(&pEr, argv[1]);
  if (fdEr == -1)
    return errno;

  if (argc > 2)
    {
      delay = atoi(argv[2]);
      i = EvrSetTargetDelay(pEr, delay);
    }
  else
    {
      i = EvrGetTargetDelay(pEr);
      printf("%d\n", i);
    }

  EvrClose(fdEr);

  return i;
}

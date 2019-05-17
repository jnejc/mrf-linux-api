#include <stdint.h>
#include <endian.h>
#include <byteswap.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <signal.h>
#include "../api/egapi.h"

int main(int argc, char *argv[])
{
  struct MrfEgRegs *pEg;
  int              fdEg;
  int              i;
  int              tb;
  int              trig;
  int              dbus;
  int              irq;
  int              seqtrig;

  if (argc < 6)
    {
      printf("Usage: %s /dev/ega3 <tb> <trig> <dbus> <irq> <seqtrig>\n", argv[0]);
      return -1;
    }

  fdEg = EvgOpen(&pEg, argv[1]);
  if (fdEg == -1)
    return errno;

  if (argc > 6)
    {
      tb = atoi(argv[2]);
      trig = atoi(argv[3]);
      dbus = atoi(argv[4]);
      irq = atoi(argv[5]);
      seqtrig = atoi(argv[6]);
      i = EvgSetTBinMap(pEg, tb, trig, dbus, irq, seqtrig);
    }

  EvgClose(fdEg);

  return i;
}

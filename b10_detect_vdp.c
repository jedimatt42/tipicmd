#include "banks.h"

#define MYBANK BANK(10)

#include "b10_detect_vdp.h"
#include "b8_setupScreen.h"
#include <vdp.h>

int vdp_type;

int detect_vdp() {
  if (bk_isF18A()) {
      return VDP_F18A;
  }

  unsigned char reg4 = 0;
  VDPWA = 4;
  VDPWA = 0x80 | 15;

  // status register 4 will have the 7 high bits set if a Yamaha VDP
  reg4 = VDPST & 0xFE;

  VDPWA = 0;
  VDPWA = 0x80 | 15;

  #ifdef _CLASSIC_99

  return VDP_9938;

  #else

  if (reg4 != 0xFE) {
    return VDP_9918;
  } else {
    unsigned char reg1 = 0;
    VDPWA = 1;
    VDPWA = 0x80 | 15;

    reg1 = VDPST;

    VDPWA = 0;
    VDPWA = 0x80 | 15;

    if (reg1 & 0x04) {
        return VDP_9958;
    }

    return VDP_9938;

  }

  #endif
}
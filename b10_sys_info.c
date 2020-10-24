#include "banks.h"
#define MYBANK BANK(10)

#include "b10_sys_info.h"
#include "b0_globals.h"
#include "b10_detect_vdp.h"

void sys_info(struct SystemInformation* info) {
  info->dsrList = dsrList;
  info->currentDsr = currentDsr;
  info->currentPath = currentPath;
}

void display_info(struct DisplayInformation* info) {
  info->displayWidth = displayWidth;
  info->displayHeight = displayHeight;
  info->isPal = pal;
  info->vdp_type = vdp_type;
}

#include "banks.h"
#define MYBANK BANK_2

#include "commands.h"
#include "b0_globals.h"
#include "b0_parsing.h"
#include "b1cp_strutil.h"
#include "b2_dsrutil.h"
#include "b2_lvl2.h"
#include "b1cp_terminal.h"
#include <string.h>

void handleCopy() {
  char* filename = strtok(0, " ");
  if (filename == 0) {
    tputs_rom("error, must specify a file name\n");
    return;
  }
  char path[256];
  // check that file exists
  strcpy(path, currentPath);
  strcat(path, filename);

  struct DeviceServiceRoutine* dsr = 0;
  bk_parsePathParam(&dsr, path, PR_REQUIRED);
  if (dsr == 0) {
    tputs_rom("no path: drive or folder specified\n");
    return;
  }
  if (path[strlen(path)-1] != '.') {
    strcat(path, ".");
  }
  unsigned int stat = existsDir(dsr, path);
  if (stat != 0) {
    tputs_rom("error, device/folder not found: ");
    tputs_ram(path);
    tputc('\n');
    return;
  }

  struct AddInfo* addInfoPtr = (struct AddInfo*) 0x8320;
  addInfoPtr->first_sector = 0;
  addInfoPtr->eof_offset = 0;
  addInfoPtr->flags = 0;
  addInfoPtr->rec_length = 0;
  addInfoPtr->records = 0;
  addInfoPtr->recs_per_sec = 0;

  unsigned int source_crubase = currentDsr->crubase;
  unsigned int source_unit = path2unitmask(currentPath);
  unsigned int dest_crubase = dsr->crubase;
  unsigned int dest_unit = path2unitmask(path);

  lvl2_setdir(source_crubase, source_unit, currentPath);
  unsigned int err = lvl2_input(source_crubase, source_unit, filename, 0, addInfoPtr);
  if (err) {
    tputs_rom("error reading file: ");
    tputs_ram(uint2hex(err));
    tputc('\n');
    return;
  }

  int totalBlocks = addInfoPtr->first_sector;
  if (totalBlocks == 0) {
    tputs_rom("error, source file is empty.\n");
    return;
  }

  tputc('\n'); // prepare status line

  // write file meta data
  lvl2_setdir(dest_crubase, dest_unit, path);
  err = lvl2_output(dest_crubase, dest_unit, filename, 0, addInfoPtr);
  if (err) {
    tputs_rom("error writing file: ");
    tputs_ram(uint2hex(err));
    tputc('\n');
    return;
  }

  int blockId = 0;
  while(blockId < totalBlocks) {
    addInfoPtr->first_sector = blockId;
    lvl2_setdir(source_crubase, source_unit, currentPath);
    err = lvl2_input(source_crubase, source_unit, filename, 1, addInfoPtr);
    if (err) {
      tputs_rom("\nerror reading file: ");
      tputs_ram(uint2hex(err));
      tputc('\n');
      return;
    }

    lvl2_setdir(dest_crubase, dest_unit, path);
    err = lvl2_output(dest_crubase, dest_unit, filename, 1, addInfoPtr);
    if (err) {
      tputs_rom("\nerror reading file: ");
      tputs_ram(uint2hex(err));
      tputc('\n');
      return;
    }

    blockId++;
    tputs_rom("\rcopied block ");
    tputs_ram(uint2str(blockId));
    tputs_rom(" of ");
    tputs_ram(uint2str(totalBlocks));
  }
  tputc('\n'); // end status line.
}

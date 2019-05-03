#ifndef _LVL2_H
#define _LVL2_H 1

#include "b2_dsrutil.h"

#define LVL2_OP_PROTECT 0x12
#define LVL2_OP_RENAME 0x13
#define LVL2_OP_INPUT 0x14
#define LVL2_OP_OUTPUT 0x15
#define LVL2_OP_SETDIR 0x17
#define LVL2_OP_MKDIR 0x18
#define LVL2_OP_DELDIR 0x19
#define LVL2_OP_RENDIR 0x1A

struct __attribute__((__packed__)) AddInfo {
  unsigned int buffer;
  unsigned int first_sector;
  unsigned char flags;
  unsigned char recs_per_sec;
  unsigned char eof_offset;
  unsigned char rec_length;
  unsigned int records;
}; 

unsigned char path2unitmask(char* currentPath);

unsigned int lvl2_mkdir(int crubase, char unit, char* dirname);
unsigned int lvl2_protect(int crubase, char unit, char* filename, char protect);
unsigned int lvl2_rename(int crubase, char unit, char* oldname, char* newname);
unsigned int lvl2_rendir(int crubase, char unit, char* oldname, char* newname);
unsigned int lvl2_rmdir(int crubase, char unit, char* dirname);
unsigned int lvl2_setdir(int crubase, char unit, char* path);
unsigned int lvl2_input(int crubase, char unit, char* filename, unsigned char blockcount, struct AddInfo* addInfoPtr);
unsigned int lvl2_output(int crubase, char unit, char* filename, unsigned char blockcount, struct AddInfo* addInfoPtr);

unsigned char __attribute__((noinline)) base_lvl2(int crubase, char unit, char operation, char* name1, char* name2, char param0);
unsigned char __attribute__((noinline)) direct_io(int crubase, char unit, char operation, char* filename, unsigned char blockcount, struct AddInfo* addInfoPtr);
unsigned int __attribute__((noinline)) subroutine(int crubase, unsigned char operation);
void __attribute__((noinline)) call_lvl2(int crubase, unsigned char operation);

#include "banking.h"

DECLARE_BANKED_CHAR(path2unitmask, BANK_2, unsigned char, bk_path2unitmask, (char* currentPath), (currentPath))

DECLARE_BANKED(lvl2_setdir, BANK_2, unsigned int, bk_lvl2_setdir, (int crubase, char unit, char* path), (crubase, unit, path))
DECLARE_BANKED(lvl2_protect, BANK_2, unsigned int, bk_lvl2_protect, (int crubase, char unit, char* filename, char protect), (crubase, unit, filename, protect))
DECLARE_BANKED(lvl2_rename, BANK_2, unsigned int, bk_lvl2_rename, (int crubase, char unit, char* oldname, char* newname), (crubase, unit, oldname, newname))
DECLARE_BANKED(lvl2_rendir, BANK_2, unsigned int, bk_lvl2_rendir, (int crubase, char unit, char* oldname, char* newname), (crubase, unit, oldname, newname))
DECLARE_BANKED(lvl2_rmdir, BANK_2, unsigned int, bk_lvl2_rmdir, (int crubase, char unit, char* dirname), (crubase, unit, dirname))
DECLARE_BANKED(lvl2_input, BANK_2, unsigned int, bk_lvl2_input, (int crubase, char unit, char* filename, unsigned char blockcount, struct AddInfo* addInfoPtr), (crubase, unit, filename, blockcount, addInfoPtr))
DECLARE_BANKED(lvl2_output, BANK_2, unsigned int, bk_lvl2_output, (int crubase, char unit, char* filename, unsigned char blockcount, struct AddInfo* addInfoPtr), (crubase, unit, filename, blockcount, addInfoPtr))

#endif
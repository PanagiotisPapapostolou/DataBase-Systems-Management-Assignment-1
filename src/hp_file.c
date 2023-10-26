#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "bf.h"
#include "hp_file.h"
#include "record.h"

#define CALL_BF(call)       \
{                           \
  BF_ErrorCode code = call; \
  if (code != BF_OK) {         \
    BF_PrintError(code);    \
    exit(code);        \
  }                         \
}

int HP_CreateFile(char *fileName){
  int fileDescriptor;
  void* data;
  int block_num;
  BF_Block* block;
  BF_Block_Init(&block);

  CALL_BF(BF_CreateFile(fileName));
  CALL_BF(BF_OpenFile(fileName, &fileDescriptor));

  CALL_BF(BF_AllocateBlock(fileDescriptor, block));
  CALL_BF(BF_GetBlockCounter(fileDescriptor, &block_num));
  data = BF_Block_GetData(block);

  HP_info* hpinfo=data;
  hpinfo->capacity=0;
  hpinfo->id=block_num-1;
  hpinfo->FileDesc=fileDescriptor;

  return 0;
}

HP_info* HP_OpenFile(char *fileName){
  int fileDescriptor;
  CALL_BF(BF_OpenFile(fileName, &fileDescriptor));
  BF_Block* block;
  BF_Block_Init(&block);
  CALL_BF(BF_GetBlock(fileDescriptor-1, 0, block));
  void * data=BF_Block_GetData(block);
  HP_info* hpinfo=data;
  return hpinfo;
  
}


int HP_CloseFile( HP_info* hp_info ){

  return 0;
}

int HP_InsertEntry(HP_info* hp_info, Record record){
  BF_Block* block;
  BF_Block_Init(&block);
  BF_AllocateBlock(hp_info->FileDesc, block);
  void* data = BF_Block_GetData(block);

  return 0;
}

int HP_GetAllEntries(HP_info* hp_info, int value){
  return 0;
}


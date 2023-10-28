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
  hpinfo->bytes_size=BF_BLOCK_SIZE-sizeof(HP_block_info);
  hpinfo->capacity=(hpinfo->bytes_size/sizeof(Record));
  
  printf("%d\n",hpinfo->capacity);
  printf("%d\n",hpinfo->bytes_size);

  hpinfo->last_block_id=block_num-1;
  hpinfo->FileDesc=fileDescriptor;

  CALL_BF(BF_UnpinBlock(block));
  CALL_BF(BF_CloseFile(fileDescriptor));
  return 0;
}

HP_info* HP_OpenFile(char *fileName){
  int fileDescriptor;
  CALL_BF(BF_OpenFile(fileName, &fileDescriptor));
  BF_Block* block;
  BF_Block_Init(&block);
  CALL_BF(BF_GetBlock(fileDescriptor, 0, block));
  void * data=BF_Block_GetData(block);
  HP_info* hpinfo=data;
  return hpinfo;
  
}


int HP_CloseFile( HP_info* hp_info ){

  return 0;
}

int HP_InsertEntry(HP_info* hp_info, Record record){
  if (hp_info->last_block_id == 0) {
    BF_Block* block;
    BF_Block_Init(&block);

    void* records_data;
    void* block_info_data;

    CALL_BF(BF_AllocateBlock(hp_info->FileDesc, block));
    records_data = BF_Block_GetData(block);
    block_info_data = records_data + hp_info->capacity;

    HP_block_info* block_info = block_info_data;
    block_info->block_id = 1;
    block_info->next = NULL;
    block_info->num_of_records = 0;
    HP_info

    Record* new_record = records_data;
    memcpy(new_record->name, record.name, strlen(record.name) + 1);
    memcpy(new_record->surname, record.surname, strlen(record.surname) + 1);
    memcpy(new_record->city, record.city, strlen(record.city) + 1);
    new_record->id = record.id;

    printf("%s\n", new_record->name);

    CALL_BF(BF_UnpinBlock(block)); 
  }

  // for (int id = 1; id < hp_info->last_block_id; id++) {
  //   BF_GetBlock(hp_info->FileDesc, id, block);
  // }
  // if(hp_info->last_block_id == 0){
  //   BF_Block* last_block;
  //   CALL_BF(BF_GetBlock(hp_info->FileDesc,hp_info->last_block_id,last_block));
  //   void * data=BF_Block_GetData(last_block);
  //   HP_block_info* block_info;
  //   BF_Block* block;
  //   BF_Block_Init(&block);
  //   BF_AllocateBlock(hp_info->FileDesc, block);
  // }
  return 0;
}

int HP_GetAllEntries(HP_info* hp_info, int value){
  return 0;
}


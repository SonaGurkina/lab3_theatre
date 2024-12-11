#ifndef PERFOMANCE_H
#define PERFOMANCE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct perfomace {
  int id;
  char name[50];
  int cost;
  char location[50];
  struct perfomace* next;
} perfomace;

typedef struct DB {
  perfomace* first;
} DB;

void addItemInDB(DB* db,int scene);
void deleteItemFromDB(DB* db, char* name);
void show_all(DB* db);
void searchItemByParam(DB* db);
void redactItemInDB(DB* db, char* name);
void saveDB(DB* db);
void loadDB(DB* db);
#endif

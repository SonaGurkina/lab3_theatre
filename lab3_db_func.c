#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <locale.h>
#include "perfomance.h"

int checkingUniqueness(DB* db, perfomace* item) {
  if (db == NULL && db->first == NULL) return 1;
  perfomace* curr = db->first;
  while (curr != NULL) {
    if (strcmp(item->name, curr->name) == 0) {
      if (item->cost == curr->cost && strcmp(item->location, curr->location) == 0) {
        return 0;
      }
    }
    curr = curr->next;
  }
  return 1;
}

void saveDB(DB* bd);

void addItemInDB(DB* db, int scene) {
  perfomace* item = malloc(sizeof(perfomace));
  if (item == NULL) {
    return;
  }
  if (scene) {
    printf("Название спектакля: ");
    if (scanf(" %49[^\n]", item->name) != 1) {
      free(item);
      return;
    }

    printf("Введите цену: ");
    if (scanf("%i", &item->cost) != 1) {
      free(item);
      while (getchar() != '\n' && getchar() != EOF);
      return;
    }
    while (getchar() != '\n' && getchar() != EOF);

    printf("Введите место проведения: ");
    if (scanf(" %49[^\n]", item->location) != 1) {
      free(item);
      return;
    }

    if (!checkingUniqueness(db, item)) {
      printf("Такой спектакль уже существует\n");
      free(item);
      return;
    }
  }

  if (db->first == NULL) {
    item->next = NULL;
    db->first = item;
  }
  else {
    item->next = db->first;
    db->first = item;
  }
}

void deleteItemFromDB(DB* db, char* name) {
  if (db == NULL || db->first == NULL) {
    printf("База данных пуста или не существует.\n");
    return;
  }

  perfomace* currItem = db->first;
  perfomace* prevItem = NULL;

  if (strcmp(currItem->name,name)==0 && currItem->next==NULL) {
    db->first = NULL;
    printf("Удален спектакль: %s\n", currItem->name);
    free(currItem);
    return;
  }
  while (currItem != NULL) {
    if (strcmp(currItem->name,name)==0) {
      prevItem->next = currItem->next;
      printf("Удален спектакль: %s\n", currItem->name);
      free(currItem);
      return;
    }
    prevItem = currItem;
    currItem = currItem->next;
  }

  printf("Объект не найден.\n");
}

void show_all(DB* a) {
  perfomace* item = a->first;
  if (item == NULL) {
    printf("Список пуст\n");
    return;
  }
  printf("Список спектаклей: \n\n");
  while (item != NULL) {
    printf("Название: %s, Цена: %i, Место: %s\n",item->name, item->cost, item->location);
    item = item->next;
  }
}

void searchItemByParam(DB* db) {
  perfomace* item = db->first;

  int localAction;

  printf("\nВыберите критерий по которому хотите выполнить поиск:\n");
  printf("\nПо названию спектакля - 1\n");
  printf("По цене - 2\n");
  printf("По месту проведения - 3\n");
  printf("Введите число:");
  scanf("%i", &localAction);
  printf("\n\n");

  char name[100];
  int cost;
int counter = 0;
  switch (localAction) {
  case 1:
    printf("Введите имя спектакля: ");
    scanf("%s", name);
    while (item != NULL) {
      if (strcmp(item->name, name) == 0) {
        if (!counter) printf("Вот что удалось найти: \n");
        printf("Название: %s, Цена: %i, Место: %s\n", item->name, item->cost, item->location);
        counter++;
      }
      item = item->next;
    }
    break;
  case 2:
    printf("Введите цену спектакля: ");
    scanf("%i", &cost);
    while (item != NULL) {
      if (item->cost == cost) {
        if (!counter) printf("Вот что удалось найти: \n");
        printf("Название: %s, Цена: %i, Место: %s\n",item->name, item->cost, item->location);
        counter++;
      }
      item = item->next;
    }
    break;
  case 3:
    printf("Введите место проведения спектакля: ");
    scanf("%s", name);
    while (item != NULL) {
      if (strcmp(item->location, name) == 0) {
        if (!counter) printf("Вот что удалось найти: \n");
        printf("Название: %s, Цена: %i, Место: %s\n",item->name, item->cost, item->location);
        counter++;
      }
      item = item->next;
    }
    break;
  default:
    printf("Введён неправильный запрос\n");
    break;
  }

  if (!counter) {
    printf("Данных по вашему запросу не нашлось\n");
  }
  else printf("По запросу найдено %i спектаклей\n",counter);
}

void redactItemInDB(DB* db, char* name) {
  perfomace* item = db->first;
  int found = 0;
  while (item != NULL) {
    if (strcmp(item->name,name)==0) {
      int localAction;
      printf("\nВыберите что хотите изменить в элементе: \n");
      printf("\nНазвание - 1\n");
      printf("Цена - 2\n");
      printf("Место проведения - 3\n");
      printf("Введите число:");
      scanf("%i", &localAction);
      printf("\n\n");

      char string[50];
      int cost;

      switch (localAction){
      case (1):
        printf("Введите новое название - ");
        scanf("%s", string);
        if (strcmp(string, " ") == 0) printf("Значение не должно быть пустым");
        strcpy(item->name, string);
        break;
      case (2):
        printf("Введите новую цену - ");
        scanf("%i", &cost);
        item->cost = cost;
        break;
      case (3):
        printf("Введите новое название - ");
        scanf("%s", string);
        if (strcmp(string, " ") == 0) printf("Значение не должно быть пустым");
        strcpy(item->location, string);
        break;
      default:
        printf("Вы ввели неверную цифру");
        break;
      }
      return;
    }
    item = item->next;
  }
  if (!found) {
    printf("Такой элемент не найден");
  }
}

const char filename[30] = "perfomances.txt";

void saveDB(DB* db) {
  FILE* file = fopen(filename, "w");
  if (file == NULL) {
    return;
  }
  perfomace* item = db->first;
  while (item != NULL) {
    fprintf(file, "%s %i %s\n", item->name, item->cost, item->location);
    item = item->next;
  }
  fclose(file);
}

void loadDB(DB* db) {
  FILE* file = fopen(filename, "r+");
  if (file == NULL) {
    fprintf(stderr, "Файла не существует: %s\n", filename);
    return;
  }
  char name[50], location[50];
  int cost;


  while (fscanf(file, "%s %i %s", name, &cost, location) == 3) {
    addItemInDB(db,0);
    strcpy(db->first->name, name);
    db->first->cost = cost;
    strcpy(db->first->location, location);
  }
  if (ferror(file)) {
    printf("Ошибка чтения файла");
  }
  fclose(file);
}


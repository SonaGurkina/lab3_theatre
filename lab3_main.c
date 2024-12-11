#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <locale.h>
#include <stdlib.h>
#include "perfomance.h"



int main() {
    setlocale(LC_ALL, "Rus");

    DB db = { NULL};
    loadDB(&db);

    int action;
  char itemName[100];

    do {
        printf("\n-.___._Выберите действие_.___.-\n\n");
    printf("Вывести все спектакли - 1\n");
        printf("Добавить новый элемент - 2\n");
        printf("Удалить элемент - 3\n");
        printf("Найти спектакль по параметру - 4\n");
        printf("Изменить информацию об элементе - 5\n");
        printf("Завершить работу программы - 0\n");
        printf("\nВведите номер действия - ");
        scanf("%d", &action);
    printf("\n");

    switch (action){
    case 1:
      show_all(&db);
      break;
        case 2:
      addItemInDB(&db,1);
	saveDB(&db);
      break;
    case 3:
      printf("Название спектакля, который хотите удалить: ");
      scanf("%s", itemName);
      deleteItemFromDB(&db, itemName);
	saveDB(&db);
      break;
    case 4:
      searchItemByParam(&db);
      break;
    case 5:
      printf("Название спектакля, который хотите изменить: ");
      scanf("%s", itemName);
      redactItemInDB(&db, itemName);
	saveDB(&db);
      break;
    case 0:
      break;
    default:
      printf("Число введено неверно\n");
      break;
  }
}while (action != 0);

perfomace* item = db.first;
while (item != NULL) {
  perfomace* next = item->next;
  free(item);
  item = next;
}

return 0;
}

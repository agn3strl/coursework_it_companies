#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>
#include <string.h>  
#include <stdlib.h>  
#include <time.h>
#include "func.h"

int main()
{
    system("chcp 1251");
    IT* companies;
    int size;

    printf("========================================================================================\n");
    printf("|             КУРСОВОЙ ПРОЕКТ ПО ТЕМЕ «РАЗРАБОТКА ПРОГРАММЫ РАБОТЫ С ФАЙЛОВОЙ          |\n");
    printf("|                    БАЗОЙ ДАННЫХ «IT-КОМПАНИИ»»                                       |\n");
    printf("|                                                                                      |\n");
    printf("|                     Разработала студентка группы бТИИ-251                            |\n");
    printf("|                       Вильальба Гофман Агния Хавьеровна                              |\n");
    printf("========================================================================================\n\n");

    printf("\t_____IT-КОМПАНИИ_____\n");

    printf("\nВведите количество записей: ");
    scanf("%d", &size);

    if (size <= 0) {
        printf("Неверный размер массива!\n");
        return -1;
    }

    companies = (IT*)malloc(size * sizeof(IT));
    if (companies == NULL) {
        puts("error");
        return -1;
    }

    int count = 0;
    int n = 0;
    int choice;
    char filename[100];
    int findchoice;

    do {
        printf("\n_____Меню_____\n");
        printf("1 - Добавить новую запись (ввод с клавиатуры)\n");
        printf("2 - Просмотреть все записи\n");
        printf("3 - Поиск записей\n");
        printf("4 - Отсортировать данные\n");
        printf("5 - Сохранить данные в файл\n");
        printf("6 - Загрузить данные из файла\n");
        printf("7 - Добавить n-ое количество тестовых записей\n");
        printf("8 - Выход\n");
        printf("\n");
        printf("Выберите действие: ");
        scanf("%d", &choice);
        printf("\n");

        switch (choice) {
        case 1:
            if (count < size) {
                
                input_company(&companies[count]);
                count += 1;
                printf("\nКомпания успешно добавлена.\n");
            }
            else {
                printf("\nДостигнут максимум компаний (%d).\n", size);
            }
            break;

        case 2:
            print_all_companies(companies, count);
            break;

        case 3:
            printf("Выберите критейрий поиска (1 - по названию, 2 - по рейтингу и капитализации): ");
            scanf("%d", &findchoice);
            if (findchoice == 1) {
                char searchname[100];
                printf("\nВведите название компании для поиска: ");
                scanf("%s", searchname);
                search_by_name(companies, count, searchname);
            }
            else {
                double min_capitalization;
                int rate_choice;
                printf("\nВведите минимальную рыночную капитализацию (млн $): ");
                scanf("%lf", &min_capitalization);
                printf("Выберите рейтинг работодателя (0 - Низкий, 1 - Средний, 2 - Высокий): ");
                scanf("%d", &rate_choice);
                search_by_capandrate(companies, count, min_capitalization, rate_choice);
            }
            break;

        case 4:
            qsort(companies, count, sizeof(IT), comparator);
            printf("Компании отсортированы по рыночной капитализации, по рейтингу работодателя, по количеству сотрудников (по убыванию).\n");
            break;

        case 5:
            printf("Введите имя файла для сохранения: ");
            scanf("%s", filename);
            if (save_companies(companies, count, filename) == 0) printf("\nДанные успешно сохранены в текстовый файл %s.\n", filename);
            break;

        case 6:
            printf("Введите имя файла для загрузки: ");
            scanf("%s", filename);
            if (load_companies(&companies, &count, &size, filename) == 0) printf("\nДанные успешно загружены из файла %s.\n", filename);
            break;
        
        case 7:
            printf("Введите количество тестовых записей: ");
            scanf("%d", &n);
            if (test(&companies, &count, &size, n) == 0) printf("\nДобавлено %d тестовых записей.\n", n);
            count += n;
            break; 

        case 8:
            printf("Выход из программы.\n");
            break;
        }

    } while (choice != 8);

    free(companies);
    companies = NULL;

    return 0;
}


#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>
#include <string.h>  
#include <stdlib.h>  
#include <time.h>
#include "func.h"

int main()
{
    system("chcp 1251");

    printf("========================================================================================\n");
    printf("|             КУРСОВОЙ ПРОЕКТ ПО ТЕМЕ «РАЗРАБОТКА ПРОГРАММЫ РАБОТЫ С ФАЙЛОВОЙ          |\n");
    printf("|                    БАЗОЙ ДАННЫХ «IT-КОМПАНИИ»»                                       |\n");
    printf("|                                                                                      |\n");
    printf("|                     Разработала студентка группы бТИИ-251                            |\n");
    printf("|                       Вильальба Гофман Агния Хавьеровна                              |\n");
    printf("========================================================================================\n\n");

    printf("\t_____IT-КОМПАНИИ_____\n");

    ITArray companies;
    init_itarray(&companies);

    printf("\nВведите начальный размер массива: ");
    int initial_capacity;
    if (scanf("%d", &initial_capacity) != 1 || initial_capacity <= 0) {
        printf("Неверный размер массива! Установлено значение по умолчанию: 10\n");
        initial_capacity = 10;
    }

    if (expand_array(&companies, initial_capacity) != 0) {
        printf("Ошибка выделения памяти!\n");
        return -1;
    }

    printf("Выделена память под %d записей.\n", companies.capacity);

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
        if (scanf("%d", &choice) != 1) {
            printf("Ошибка ввода! Попробуйте снова.\n");
            while (getchar() != '\n'); 
            continue;
        }
        printf("\n");

        switch (choice) {
        case 1:
            if (companies.count >= companies.capacity) {
                if (expand_array(&companies, companies.capacity + 1) != 0) {
                    printf("\nОшибка: невозможно добавить компанию (проблема с памятью)\n");
                    break;
                }
            }
            input_company(&companies.data[companies.count]);
            companies.count += 1;
            printf("\nКомпания успешно добавлена. Всего записей: %d\n", companies.count);
            break;

        case 2:
            print_all_companies(companies.data, companies.count);
            break;

        case 3:
            printf("Выберите критерий поиска (1 - по названию, 2 - по рейтингу и капитализации): ");
            if (scanf("%d", &findchoice) != 1) {
                printf("Ошибка ввода!\n");
                while (getchar() != '\n');
                break;
            }

            if (findchoice == 1) {
                char searchname[100];
                printf("\nВведите название компании для поиска: ");
                scanf("%99s", searchname);
                search_by_name(companies.data, companies.count, searchname);
            }
            else if (findchoice == 2) {
                double min_capitalization;
                int rate_choice;
                printf("\nВведите минимальную рыночную капитализацию (млн $): ");
                if (scanf("%lf", &min_capitalization) != 1) {
                    printf("Ошибка ввода!\n");
                    while (getchar() != '\n');
                    break;
                }
                printf("Выберите рейтинг работодателя (0 - Низкий, 1 - Средний, 2 - Высокий): ");
                if (scanf("%d", &rate_choice) != 1) {
                    printf("Ошибка ввода!\n");
                    while (getchar() != '\n');
                    break;
                }
                search_by_capandrate(companies.data, companies.count, min_capitalization, rate_choice);
            }
            else {
                printf("Неверный выбор критерия поиска.\n");
            }
            break;

        case 4:
            if (companies.count > 0) {
                qsort(companies.data, companies.count, sizeof(IT), comparator);
                printf("Компании отсортированы по рыночной капитализации, по рейтингу работодателя, по количеству сотрудников (по убыванию).\n");
            }
            else {
                printf("Нет данных для сортировки.\n");
            }
            break;

        case 5:
            printf("Введите имя файла для сохранения: ");
            scanf("%99s", filename);
            if (save_companies(companies.data, companies.count, filename) == 0) {
                printf("\nДанные успешно сохранены в текстовый файл %s.\n", filename);
            }
            else {
                printf("\nОшибка при сохранении данных.\n");
            }
            break;

        case 6:
            printf("Введите имя файла для загрузки: ");
            scanf("%99s", filename);
            int loaded = load_companies(&companies, filename);
            if (loaded >= 0) {
                printf("\nДанные успешно загружены из файла %s. Загружено %d записей.\n", filename, loaded);
            }
            else if (loaded == -1) {
                printf("\nОшибка при загрузке данных.\n");
            }
            break;

        case 7:
            printf("Введите количество тестовых записей: ");
            if (scanf("%d", &n) != 1 || n <= 0) {
                printf("Неверное количество записей!\n");
                while (getchar() != '\n');
                break;
            }
            if (test(&companies, n) == 0) {
                printf("\nДобавлено %d тестовых записей. Всего записей: %d\n", n, companies.count);
            }
            else {
                printf("\nОшибка при добавлении тестовых записей.\n");
            }
            break;

        case 8:
            printf("Выход из программы.\n");
            break;

        default:
            printf("Неверный выбор. Попробуйте снова.\n");
            break;
        }

    } while (choice != 8);

    free_itarray(&companies);

    return 0;
}


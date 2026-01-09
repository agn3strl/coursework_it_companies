#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>
#include <string.h>  
#include <stdlib.h>  
#include <time.h>
#include "func.h"

const char* sphere_string(Sphere sphere)
{
    switch (sphere) {
    case SOFTWARE: return "Разработка ПО";
    case HARDWARE: return "Аппаратное обеспечение";
    case CLOUD: return "Облачные технологии";
    case CYBERSECURITY: return "Кибербезопасность";
    }
}

const char* rate_string(Rate rate)
{
    switch (rate) {
    case LOW: return "Низкий";
    case MIDDLE: return "Средний";
    case HIGH: return "Высокий";
    }
}

void init_itarray(ITArray* array) {
    array->data = NULL;
    array->count = 0;
    array->capacity = 0;
}

void input_company(IT* company) {
    printf("_____Ввод данных о компании_____\n");
    printf("Название компании: ");
    scanf("%s", company->name);
    printf("Сфера деятельности (0 - Разработка ПО, 1 - Аппаратное обеспечение, 2 - Облачные технологии, 3 - Кибербезопасность): ");
    int sphere;
    scanf("%d", &sphere);
    company->sphere = (Sphere)sphere;
    printf("Год основания: ");
    scanf("%d", &company->year_of_foundation);
    printf("Количество сотрудников: ");
    scanf("%d", &company->number_of_employees);
    printf("Рыночная капитализация (млн $): ");
    scanf("%lf", &company->market_cap);
    printf("Рейтинг работодателя (0 - Низкий, 1 - Средний, 2 - Высокий): ");
    int rate;
    scanf("%d", &rate);
    company->rate = (Rate)rate;
}

void print_company(const IT* company)
{
    printf("-----Информация о компании-----\n");
    printf("Название: %s\n", company->name);
    printf("Сфера деятельности: %s\n", sphere_string(company->sphere));
    printf("Год основания: %d\n", company->year_of_foundation);
    printf("Количество сотрудников: %d\n", company->number_of_employees);
    printf("Рыночная капитализация: %.2lf млн $\n", company->market_cap);
    printf("Рейтинг работодателя: %s\n", rate_string(company->rate));
    printf("----------------------------------------\n");
}

void print_all_companies(const IT companies[], int count)
{
    if (count == 0) {
        printf("\nНет данных о компаниях.\n");
        return;
    }

    printf("\n_____Все компании_____\n");
    for (int i = 0; i < count; i++) {
        printf("\nКомпания №%d:\n", i + 1);
        print_company(&companies[i]);
    }
}

int save_companies(const IT companies[], int count, const char* filename)
{
    FILE* file;
    file = fopen(filename, "w");

    if (file == NULL) {
        printf("Ошибка открытия файла '%s' для записи.\n", filename);
        return -1;
    }

    for (int i = 0; i < count; i++) {
        fprintf(file, "\nКомпания №%d:\n", i + 1);
        fprintf(file, "Название: %s\n", companies[i].name);
        fprintf(file, "Сфера деятельности: %d\n", companies[i].sphere);
        fprintf(file, "Год основания: %d\n", companies[i].year_of_foundation);
        fprintf(file, "Количество сотрудников: %d\n", companies[i].number_of_employees);
        fprintf(file, "Рыночная капитализация: %.2lf\n", companies[i].market_cap);
        fprintf(file, "Рейтинг работодателя: %d\n", companies[i].rate);
        if (ferror(file)) {
            printf("Ошибка записи в файл '%s'.\n", filename);
            fclose(file);
            return -1;
        }
    }

    if (fclose(file) != 0) {
        printf("Ошибка закрытия файла '%s'.\n", filename);
        return -1;
    }

    return 0;
}

int expand_array(ITArray* companies, int min_capacity)
{
    int new_capacity = companies->capacity;
    if (new_capacity == 0) {
        new_capacity = 10;
    }

    while (new_capacity < min_capacity) {
        new_capacity += 10; 
    }

    IT* new_data = realloc(companies->data, new_capacity * sizeof(IT));
    if (new_data == NULL) {
        printf("Ошибка выделения памяти.\n");
        return -1;
    }

    companies->data = new_data;
    int old_capacity = companies->capacity;
    companies->capacity = new_capacity;

    if (old_capacity != new_capacity) {
        printf("Размер массива увеличен с %d до %d записей.\n",
            old_capacity, new_capacity);
    }

    return 0;
}

int test(ITArray* companies, int n)
{
    if (n <= 0) {
        printf("Некорректное количество тестовых данных: %d\n", n);
        return -1;
    }

    srand(time(NULL));

    if (companies->count + n > companies->capacity) {
        if (expand_array(companies, companies->count + n) != 0) {
            return -1;
        }
    }

    int curr = companies->count;

    for (int i = 0; i < n; i++) {
        sprintf(companies->data[curr + i].name, "Company%d", rand() % 100 + 1);
        companies->data[curr + i].sphere = (Sphere)(rand() % 4);
        companies->data[curr + i].year_of_foundation = 1990 + rand() % 30;
        companies->data[curr + i].number_of_employees = 50 + rand() % 9950;
        companies->data[curr + i].market_cap = 10.0 + (rand() % 990);
        companies->data[curr + i].rate = (Rate)(rand() % 3);
    }

    companies->count += n;

    return 0;
}

int load_companies(ITArray* companies, const char* filename)
{
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Ошибка открытия файла '%s' для чтения.\n", filename);
        return -1;
    }

    int file_record_count = 0;
    char buffer[256];

    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        if (strstr(buffer, "Название:") != NULL) {
            file_record_count++;
        }
    }

    if (ferror(file)) {
        printf("Ошибка чтения файла '%s'.\n", filename);
        fclose(file);
        return -1;
    }

    if (file_record_count == 0) {
        printf("Файл '%s' не содержит данных в правильном формате.\n", filename);
        fclose(file);
        return 0;
    }

    if (companies->count + file_record_count > companies->capacity) {
        if (expand_array(companies, companies->count + file_record_count) != 0) {
            fclose(file);
            return -1;
        }
    }

    rewind(file);
    int loaded = 0;
    IT temp;

    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        if (strstr(buffer, "Компания №") != NULL ||
            strstr(buffer, "----------------------------------------") != NULL) {
            continue;
        }

        if (strstr(buffer, "Название:") != NULL) {
            sscanf(buffer, "Название: %99[^\n]", temp.name);

            fgets(buffer, sizeof(buffer), file);
            sscanf(buffer, "Сфера деятельности: %d", (int*)&temp.sphere);

            fgets(buffer, sizeof(buffer), file);
            sscanf(buffer, "Год основания: %d", &temp.year_of_foundation);

            fgets(buffer, sizeof(buffer), file);
            sscanf(buffer, "Количество сотрудников: %d", &temp.number_of_employees);

            fgets(buffer, sizeof(buffer), file);
            sscanf(buffer, "Рыночная капитализация: %lf", &temp.market_cap);

            fgets(buffer, sizeof(buffer), file);
            sscanf(buffer, "Рейтинг работодателя: %d", (int*)&temp.rate);

            if (companies->count < companies->capacity) {
                companies->data[companies->count] = temp;
                companies->count++;
                loaded++;
            }
            else {
                printf("Ошибка: переполнение массива при загрузке\n");
                break;
            }
        }
    }

    if (ferror(file)) {
        printf("Ошибка чтения файла '%s'.\n", filename);
        fclose(file);
        return -1;
    }

    if (fclose(file) != 0) {
        printf("Ошибка закрытия файла '%s'.\n", filename);
        return -1;
    }

    return loaded;
}

int comparator(const void* a, const void* b) {
    const IT* companyA = (const IT*)a;
    const IT* companyB = (const IT*)b;

    if (companyA->market_cap > companyB->market_cap) return -1;
    if (companyA->market_cap < companyB->market_cap) return 1;

    if (companyA->rate > companyB->rate) return -1;
    if (companyA->rate < companyB->rate) return 1;

    if (companyA->number_of_employees > companyB->number_of_employees) return -1;
    if (companyA->number_of_employees < companyB->number_of_employees) return 1;

    return 0;
}

int search_by_name(const IT companies[], int count, const char* searchname) {
    int found = 0;

    printf("\nРезультаты поиска для \"%s\":\n", searchname);

    for (int i = 0; i < count; i++) {
        if (strcmp(companies[i].name, searchname) == 0) {
            printf("\nНайдена компания (точное совпадение):\n");
            print_company(&companies[i]);
            found = 1;
        }
    }

    if (!found) {
        printf("Компания с названием \"%s\" не найдена.\n", searchname);
    }
    return found;
}

int search_by_capandrate(const IT companies[], int count, double min_capitalization, int rate_choice) {
    Rate search_rate;

    search_rate = (Rate)rate_choice;

    int found = 0;

    printf("\nРезультаты поиска:\n");
    printf("Рыночная капитализация > %.2lf млн $\n", min_capitalization);
    printf("Рейтинг работодателя: %s\n", rate_string(search_rate));
    printf("\n");

    for (int i = 0; i < count; i++) {
        if (companies[i].market_cap > min_capitalization &&
            companies[i].rate == search_rate) {
            printf("\nНайдена компания #%d:\n", found + 1);
            print_company(&companies[i]);
            found++;
        }
    }

    if (!found) {
        printf("Не найдено компаний, соответствующих критериям поиска.\n");
    }
    else {
        printf("Всего найдено %d компаний.\n", found);
    }

    return found;
}

void free_itarray(ITArray* array) {
    if (array->data != NULL) {
        free(array->data);
        array->data = NULL;
    }
    array->count = 0;
    array->capacity = 0;
}
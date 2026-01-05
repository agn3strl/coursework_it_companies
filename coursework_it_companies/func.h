#ifndef FUNC_H
#define FUNC_H

/**
 * Перечисление сфер деятельности IT-компаний
 */
enum sphere {
    SOFTWARE,       /**< Разработка программного обеспечения */
    HARDWARE,       /**< Аппаратное обеспечение */
    CLOUD,          /**< Облачные технологии */
    CYBERSECURITY   /**< Кибербезопасность */
};
typedef enum sphere Sphere;

/**
 * Перечисление рейтингов работодателя
 */
enum rate {
    LOW,            /**< Низкий рейтинг */
    MIDDLE,         /**< Средний рейтинг */
    HIGH            /**< Высокий рейтинг */
};
typedef enum rate Rate;

/**
 * Структура для хранения информации об IT-компании
 */
struct itcompany {
    char name[100];             /**< Название компании */
    Sphere sphere;              /**< Сфера деятельности */
    int year_of_foundation;     /**< Год основания */
    int number_of_employees;    /**< Количество сотрудников */
    double market_cap;          /**< Рыночная капитализация (млн $) */
    Rate rate;                  /**< Рейтинг работодателя */
};
typedef struct itcompany IT;

/**
 * Преобразование сферы деятельности в строковое представление
 * @param sphere значение перечисления Sphere
 * @return указатель на строку с названием сферы деятельности
 */
const char* sphere_string(Sphere sphere);

/**
 * Преобразование рейтинга работодателя в строковое представление
 * @param rate значение перечисления Rate
 * @return указатель на строку с названием рейтинга
 */
const char* rate_string(Rate rate);

/**
 * Ввод данных о компании с клавиатуры
 * @param company указатель на структуру IT для заполнения
 */
void input_company(IT* company);

/**
 * Вывод информации об одной компании на экран
 * @param company указатель на структуру IT для вывода
 */
void print_company(const IT* company);

/**
 * Вывод информации о всех компаниях в базе данных
 * @param companies массив структур IT
 * @param count количество записей в массиве
 */
void print_all_companies(const IT companies[], int count);

/**
 * Сохранение базы данных в текстовый файл
 * @param companies массив структур IT
 * @param count количество записей для сохранения
 * @param filename имя файла для сохранения
 * @return 0 при успешном сохранении, -1 при ошибке
 */
int save_companies(const IT companies[], int count, const char* filename);

/**
 * Загрузка базы данных из текстового файла
 * @param companies указатель на указатель на массив структур IT
 * @param count указатель на переменную с количеством записей
 * @param size указатель на переменную с размером массива
 * @param filename имя файла для загрузки
 * @return 0 при успешной загрузке, -1 при ошибке
 */
int load_companies(IT** companies, int* count, int* size, const char* filename);

/**
 * Генерация тестовых записей для заполнения базы данных
 * @param companies указатель на указатель на массив структур IT
 * @param count указатель на переменную с количеством записей
 * @param size указатель на переменную с размером массива
 * @param n количество тестовых записей для добавления
 * @return 0 при успешном добавлении, -1 при ошибке
 */
int test(IT** companies, int* count, int* size, int n);

/**
 * Функция сравнения для сортировки компаний
 * Сортирует по убыванию: рыночная капитализация → рейтинг → количество сотрудников
 * @param a указатель на первую структуру для сравнения
 * @param b указатель на вторую структуру для сравнения
 * @return отрицательное число если a > b, положительное если a < b, 0 если равны
 */
int comparator(const void* a, const void* b);

/**
 * Поиск компании по точному названию
 * @param companies массив структур IT
 * @param count количество записей в массиве
 * @param searchname название компании для поиска
 * @return 1 если компания найдена, 0 если не найдена
 */
int search_by_name(const IT companies[], int count, const char* searchname);

/**
 * Поиск компаний по минимальной капитализации и рейтингу работодателя
 * @param companies массив структур IT
 * @param count количество записей в массиве
 * @param min_capitalization минимальная рыночная капитализация (млн $)
 * @param rate_choice выбранный рейтинг работодателя (0-2)
 * @return количество найденных компаний
 */
int search_by_capandrate(const IT companies[], int count, double min_capitalization, int rate_choice);

#endif FUNC_H
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
 * Структура для хранения динамического массива IT-компаний
 * Заменяет тройку (IT**, int*, int*) на единый объект
 */
struct itarray {
    IT* data;       /**< Указатель на динамический массив компаний */
    int count;      /**< Текущее количество элементов в массиве */
    int capacity;   /**< Вместимость массива (выделенная память) */
};
typedef struct itarray ITArray;

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
 * Сохраняет все компании в текстовый файл
 * @param companies Указатель на структуру с массивом компаний
 * @param filename Имя файла для сохранения
 * @return 0 при успехе, -1 при ошибке
 */

int save_companies(const IT companies[], int count, const char* filename);

/**
 * Загружает компании из текстового файла
 * @param companies Указатель на структуру с массивом компаний
 * @param filename Имя файла для загрузки
 * @return Количество загруженных записей или -1 при ошибке
 */
int load_companies(ITArray* companies, const char* filename);

/**
 * Добавляет тестовые данные в массив
 * @param companies Указатель на структуру с массивом компаний
 * @param n Количество тестовых записей для добавления
 * @return 0 при успехе, -1 при ошибке
 */
int test(ITArray* companies, int n);

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

/**
 * Инициализирует структуру ITArray нулевыми значениями
 * @param array Указатель на инициализируемую структуру
 */
void init_itarray(ITArray* array);

/**
 * Расширяет динамический массив компаний при необходимости
 * Выделяет память блоками по 10 элементов для эффективности
 * @param companies указатель на структуру ITArray для расширения
 * @param min_capacity минимальная требуемая вместимость массива
 * @return 0 при успешном расширении, -1 при ошибке выделения памяти
 */
int expand_array(ITArray* companies, int min_capacity);

/**
 * Освобождает память, занятую массивом в ITArray
 * @param array Указатель на инициализируемую структуру
 */
void free_itarray(ITArray* array);

#endif FUNC_H
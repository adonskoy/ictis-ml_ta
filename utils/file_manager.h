//
// Created by Антон Донской on 25.04.2018.
//

//
// Created by Антон Донской on 17.04.2018.
//

/*
 * Класс для работы с файлом.
 *
 * Основные функции:
 *      1) Инициализация файлового потока                                   [+]
 *      2) Считывание структуры из бинарного файла                          [+] {checked}
 *      3) Запись структуры в бинарный файл                                 [+] {checked}
 *      4) Считывание любого элемента в текстовом/бинарном виде             [+] {checked}
 *      5) Запись любого элемента в текстовом/бинарном виде                 [+] {checked}
 *      6) Получения указателя на поток                                     [+]
 * (?!) 7) Запись структуры в текстовый файл                                [-] {imposible}
 * (?!) 8) Чтение структуры из текстового файла                             [-] {imposible}
 *      9) Конвертация текстового файла в бинарный для одного типа данных   [+]
 *      10) Конвертация бинарного файла в текстовый для одного типа данных  [+]
 *
 * Режимы чтения:
 *      1) Чтение                                                           [+] {OK}
 *      2) Запись                                                           [+] {OK}
 *
 * Дополненительные функции:
 *      1) Изменение имени файла                                            [+]
 *      2) Удаление файла                                                   [+]
 *
 */

#include <iostream>
#include <fstream>
#include <string>
#include <cstdio>
using namespace std;



class FM {
private:
    fstream stream;
    char mode{};
    char type{};
    char *file_name{};
    string bin_extention = ".bin";
    string txt_extention = ".txt";
public:
    explicit FM(char *file_name_t, char mode_t = 'r', char type_t = 't');

    void open_file(char *file_name_t, char mode_t = 'r', char type_t = 't');

    ~FM();

    template<class T>
    void read_struct_binary(T CurrentStructure);

    template<class T>
    void write_struct_binary(T CurrentStructure);

    template<typename T>
    void get_c(T &tmp);

    template<typename T>
    void write_c(T tmp);

    fstream *get_pointer();

    void close_file(bool for_renaming = false);

    void rename_file(char *new_name);

    void delete_file() ;

    template<typename T>
    void text2bin(string new_file_name = "", bool delete_file = false);

    template<typename T>
    void bin2txt(string new_file_name = "", bool delete_file = false);
};


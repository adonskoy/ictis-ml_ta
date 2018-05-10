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
#include "file_manager.h"
using namespace std;




    explicit FM::FM(char *file_name_t, char mode_t = 'r', char type_t = 't') {
        open_file(file_name_t, mode_t, type_t);
    }

    void FM::open_file(char *file_name_t, char mode_t = 'r', char type_t = 't') {
        if (mode_t == 'w') {
            if (type_t == 't') {
                stream.open(file_name_t, fstream::out);
            } else if (type_t == 'b') {
                stream.open(file_name_t, fstream::out | fstream::binary);
            } else {
                throw ("Wrong type_m. Use 't' or 'b' ");
            }
        } else if (mode_t == 'r') {
            if (type_t == 't') {
                stream.open(file_name_t, fstream::in);
            } else if (type_t == 'b') {
                stream.open(file_name_t, fstream::in | fstream::binary);
            } else {
                throw ("Wrong type_m. Use 't' or 'b' ");
            }
        } else {
            throw ("Wrong mode. Use 'r' or 'w' ");
        }
        mode = mode_t;
        type_m = type_t;
        file_name = file_name_t;
    }

    FM::~FM() {
        stream.close();
    }

    template<class T>
    void FM::read_struct_binary(T CurrentStructure) {
        if (type_m == 'b' && mode == 'r') {
            stream.read((char *) &CurrentStructure, sizeof(CurrentStructure));
        } else {
            throw ("Wrong type_m or mode. Use mode 'r' and type_m 'b' ");
        }
    }

    template<class T>
    void FM::write_struct_binary(T CurrentStructure) {
        if (type_m == 'b' && mode == 'w') {
            stream.write((char *) &CurrentStructure, sizeof(CurrentStructure));
        } else {
            throw ("Wrong type_m or mode. Use mode 'w' and type_m 'b' ");
        }
    }

    template<typename T>
    void FM::get_c(T &tmp) {
        if (mode == 'r') {
            if (type_m == 't') {
                stream >> tmp;
            } else {
                stream.read((char *) &tmp, sizeof(T));
            }
        } else {
            throw ("Wrong mode. Use mode 'r'");
        }

    }

    template<typename T>
    void FM::write_c(T tmp) {
        if (mode == 'w') {
            if (type_m == 't') {

                stream << tmp;
            } else {
                stream.write((char *) &tmp, sizeof(T));
            }
        } else {
            throw ("Wrong mode. Use mode 'w'");
        }
    }

//    fstream FM::*get_pointer() {
//        return stream;
//    }

    void FM::close_file(bool for_renaming = false) {
        stream.close();
        if (!for_renaming) {
            mode = NULL;
            type_m = NULL;
        }
    }

    void FM::rename_file(char *new_name) {
        int result;
        this->close_file();
        result = rename(file_name, new_name);

        if (result != 0) {
            throw ("Error renaming file");
        }
        file_name = new_name;
        this->open_file(file_name, mode, type_m);
    }

    void FM::delete_file() {
        this->close_file();
        if (remove(file_name) != 0)
            throw ("Error deleting file");
    }

    template<typename T>
    void FM::text2bin(string new_file_name = "", bool delete_file = false) {
        cout<<"[WARNING] Last element may be duplicated"<<endl;
        if (new_file_name == "") {
            new_file_name = (string) file_name + bin_extention;
        }
        fstream bf(new_file_name, fstream::out | fstream::binary);
        while (stream) {
            T tmp;
            stream >> tmp;
//            stream.get(tmp);
            bf.write((char *) &tmp, sizeof(T));
        }
        bf.close();
        if (delete_file) {
            stream.close();
            this->delete_file();
        }
    }

    template<typename T>
    void FM::bin2txt(string new_file_name = "", bool delete_file = false) {
        cout<<"[WARNING] Last element may be duplicated"<<endl;
        if (new_file_name == "") {
            new_file_name = (string) file_name + txt_extention;
        }
        fstream bf(new_file_name, fstream::out | fstream::binary);
        while (stream) {
            T tmp;
            stream.read((char *) &tmp, sizeof(T));
            bf << tmp << " ";
        }
        bf.close();
        if (delete_file) {
            stream.close();
            this->delete_file();
        }
    }

struct EEEEEEE {
    int a = 232323;
    int c = 232321243;
    int b = 121212;
};

int main() {
    FM a("/Users/anton/Desktop/maaaain.txt", 'r', 't');


    a.text2bin<int>();

    FM b("/Users/anton/Desktop/maaaain.txt.bin", 'r', 'b');
    b.bin2txt<int>();
}
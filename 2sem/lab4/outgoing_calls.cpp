//
// Created by Антон Донской on 25.04.2018.
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
#include <cmath>

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
    explicit FM(char *file_name_t, char mode_t = 'r', char type_t = 't') {
        open_file(file_name_t, mode_t, type_t);
    }

    void open_file(char *file_name_t, char mode_t = 'r', char type_t = 't') {
        if (mode_t == 'w') {
            if (type_t == 't') {
                stream.open(file_name_t, fstream::out);
            } else if (type_t == 'b') {
                stream.open(file_name_t, fstream::out | fstream::binary);
            } else {
                throw ("Wrong type. Use 't' or 'b' ");
            }
        } else if (mode_t == 'r') {
            if (type_t == 't') {
                stream.open(file_name_t, fstream::in);
            } else if (type_t == 'b') {
                stream.open(file_name_t, fstream::in | fstream::binary);
            } else {
                throw ("Wrong type. Use 't' or 'b' ");
            }
        } else {
            throw ("Wrong mode. Use 'r' or 'w' ");
        }
        mode = mode_t;
        type = type_t;
        file_name = file_name_t;
    }

    ~FM() {
        stream.close();
    }

    template<class T>
    void read_struct_binary(T CurrentStructure) {
        if (type == 'b' && mode == 'r') {
            stream.read((char *) &CurrentStructure, sizeof(CurrentStructure));
        } else {
            throw ("Wrong type or mode. Use mode 'r' and type 'b' ");
        }
    }

    template<class T>
    void write_struct_binary(T CurrentStructure) {
        if (type == 'b' && mode == 'w') {
            stream.write((char *) &CurrentStructure, sizeof(CurrentStructure));
        } else {
            throw ("Wrong type or mode. Use mode 'w' and type 'b' ");
        }
    }

    template<typename T>
    void get_c(T &tmp) {
        if (mode == 'r') {
            if (type == 't') {
                stream >> tmp;
            } else {
                stream.read((char *) &tmp, sizeof(T));
            }
        } else {
            throw ("Wrong mode. Use mode 'r'");
        }

    }

    template<typename T>
    void write_c(T tmp) {
        if (mode == 'w') {
            if (type == 't') {

                stream << tmp;
            } else {
                stream.write((char *) &tmp, sizeof(T));
            }
        } else {
            throw ("Wrong mode. Use mode 'w'");
        }
    }

    fstream *get_pointer() {
        return &stream;
    }

    void close_file(bool for_renaming = false) {
        stream.close();
        if (!for_renaming) {
            mode = NULL;
            type = NULL;
        }
    }

    void rename_file(char *new_name) {
        int result;
        this->close_file();
        result = rename(file_name, new_name);

        if (result != 0) {
            throw ("Error renaming file");
        }
        file_name = new_name;
        this->open_file(file_name, mode, type);
    }

    void delete_file() {
        this->close_file();
        if (remove(file_name) != 0)
            throw ("Error deleting file");
    }

    template<typename T>
    void text2bin(string new_file_name = "", bool delete_file = false) {
        if (new_file_name == "") {
            new_file_name = (string) file_name + bin_extention;
        }
        fstream bf(new_file_name, fstream::out | fstream::binary);
        while (stream) {
            T tmp;
            stream >> tmp;
            bf.write((char *) &tmp, sizeof(T));
        }
        bf.close();
        if (delete_file) {
            stream.close();
            this->delete_file();
        }
    }

    template<typename T>
    void bin2txt(string new_file_name = "", bool delete_file = false) {
        if (new_file_name == "") {
            new_file_name = (string) file_name + txt_extention;
        }
        fstream bf(new_file_name, fstream::in | fstream::binary);
        while (stream) {
            T tmp;
            stream.read((char *) &tmp, sizeof(T));
            bf << tmp;
        }
        bf.close();
        if (delete_file) {
            stream.close();
            this->delete_file();
        }
    }
};



struct date {
    short int d;
    short int m;
    short int y;
};

struct time {
    short int h;
    short int m;
    short int s;
};

struct datetime {
    date Date;
    time Time;
};

struct My {
    char FIO[51];
    char phone_number[16];
    datetime start_time;
    int period_in_seconds;
    float price_per_minute;
};

bool operator <=(datetime T1, datetime T2) {
    if (T1.Date.y < T2.Date.y) {
        return true;
    } else if (T1.Date.y == T2.Date.y) {
        if (T1.Date.m < T2.Date.m) {
            return true;
        } else if (T1.Date.m == T2.Date.m) {
            if (T1.Date.d < T2.Date.d) {
                return true;
            } else if (T1.Date.d == T2.Date.d) {

                if (T1.Time.h < T2.Time.h) {
                    return true;
                } else if (T1.Time.h == T2.Time.h) {
                    if (T1.Time.m < T2.Time.m) {
                        return true;
                    } else if (T1.Time.m == T2.Time.m) {
                        return T1.Time.s <= T2.Time.s;
                    } else {
                        return false;
                    }
                } else {
                    return false;
                }

            } else {
                return false;
            }
        } else {
            return false;
        }
    } else {
        return false;
    }
}

struct for_dataset {
    char phone[16];
    float sum_price = 0;
    int sum_period = 0;
    int count = 0;
};

struct dataset {
public:
    auto array = new for_dataset[10000];
    int size = 0;

    void add(My current) {
        int ex = exsist(current.phone_number);
        if (ex != -1) {
            if (array[ex].count == 3) {
                array[ex] = NULL;
            } else {
                array[ex].count += 1;
                array[ex].sum_period += current.period_in_seconds;
                array[ex].sum_price += (current.price_per_minute / 60 * current.period_in_seconds);
            }
        } else {
            array[size].count = 1;
            array[size].sum_period = current.period_in_seconds;
            array[size].sum_price = (current.price_per_minute / 60 * current.period_in_seconds);
        }
    }

    int exsist(char phone[16]) {
        for (int i(0); i < size; ++i) {
            if (array[i].phone == phone) {
                return i;
            }
        }
        return -1;
    };
};

struct for_convert {
    int cnt;
    datetime T1;
    datetime T2;
    auto array = new My[cnt];
};

int main() {
    FM to_binarnik("input.txt", 'r', 't');
    to_binarnik.text2bin("input.bin");
    to_binarnik.close_file();
    FM file("input.bin", 'r', 'b');

    int n;
    dataset out{};
    datetime T1{}, T2{};
    auto array = new My[n];

    file.get_c(n);
    file.get_c(T1);
    file.get_c(T2);
    file.close_file();

    for (int i(0); i < n; ++i) {
        file.read_struct_binary(array[i]);
    }


    for (int i(0); i < n; ++i) {
        if ((T1 <= array[i].start_time) && (array[i].start_time <= T2)) {
            out.add(array[i]);
        }
    }

    FM out_file("output.txt", 'w', 't');
    out_file.write_c(out.size);
    out_file.write_c("\n");
    for (int i(0); i < out.size; ++i) {
        out_file.write_c(out.array[i].phone);
        out_file.write_c(" ");
        out.array[i].sum_price = round(out.array[i].sum_price * 100) / 100;
        out_file.write_c(out.array[i].sum_price);
        out_file.write_c(" ");
        out_file.write_c(out.array[i].sum_period);
        out_file.write_c("\n");
    }

    return 0;
}
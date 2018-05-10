//
// Created by Антон Донской on 11.04.2018.
//

#include <iostream>
#include <fstream>

#pragma pack(push, r1, 1)
struct TestStruct {
    char id[15];
    int length;
    int count;
};
#pragma pack(pop, r1)

int main() {
    TestStruct h = {"testtest", 5, 10};

    std::fstream fh;
    fh.open("test.txt", std::fstream::out | std::fstream::binary);
    fh.write((char*)&h, sizeof(TestStruct));
    fh.close();

    fh.open("test.txt", std::fstream::in | std::fstream::binary);
    TestStruct h2;
    fh.read((char*)&h2.id, sizeof(h2.id));
    fh.read((char*)&h2.length, sizeof(h2.length));
    fh.read((char*)&h2.count, sizeof(h2.count));

    fh.close();

    std::cout << h2.id << " " << h2.length << " " << h2.count << std::endl;
}


struct My_date {
    short d;
    short m;
    short y;
};

struct My_time {
    short h;
    short m;
    short s;
};

struct New {
    char fio[51];
    char number[16];
    My_date Date;
    My_time Time;
};
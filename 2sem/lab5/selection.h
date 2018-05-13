//
// Created by Антон Донской on 13.05.2018.
//
#include "functions.h"

class Selection {
public:
    Selection() = default;

    ~Selection();

    void input(const char *file_name);

    void select();

    void output(const char *file_name);


private:

    int *_arrayInt{};
    float *_arrayFloat{};

    int _size = 0;
    char _typeVariable{};
    char _taskId{};

    void initArrayInt();

    void initArrayFloat();

    typedef int *(*intptr)(const int *array, int n, int *m);

    typedef float *(*floatptr)(const float *array, int n, int *m);

    intptr getIntFunc();

    floatptr getFloatFunc();

};
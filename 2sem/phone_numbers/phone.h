//
// Created by Антон Донской on 03.04.2018.
//

#include <iostream>
#include <string>
using namespace std;
namespace Phones {
    class Phone {
    private:

        char *Text;
        int TextSize;
        int TextCapacity;
        string *Numbers;
        int NumbersSize;
        int NumbersCapacity;

        void initText();

        void initNumbers();

        void resizeText(int new_capacity);

        void resizeNumbers(int new_capacity);

        bool inNumbers(string number);


    public:

        Phone();

        ~Phone();

        void input(const char *file_name);

        void find();

        void output(const char *file_name);
    };
}
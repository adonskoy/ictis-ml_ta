//
// Created by Антон Донской on 31.03.2018.
//

#include <iostream>
#include <fstream>
using namespace std;



class LocalExtremes{
private:
    int n{}, m{}, ***data{}, **result{}, sizeResult=0;
    int * getEnvirons(int x, int y, int *cntEnv);
public:
    ~LocalExtremes();
    void read(const char * file_name);

    void FindExtremes();

    void write(const char * file_name);
};


void LocalExtremes::read(const char *file_name) {
    ifstream instr(file_name, ios::in);
    if(instr.is_open()) {
        instr >> n;
        instr >> m;
        data = new int **[n];

        for (int i(0); i < n; ++i) {
            data[i] = new int *[m];
            for (int j(0); j < m; ++j) {
                data[i][j] = new int[3];
            }
        }

        for (int i(0); i < n; ++i) {
            int tmp;
            instr >> tmp;

            for (int k(0); k < m; k++) {
                data[i][k][0] = tmp;

            }
        }

        for (int i(0); i < m; ++i) {
            int tmp;
            instr >> tmp;
            for (int j(0); j < n; j++) {
                data[j][i][1] = tmp;
            }
        }

        for (int j(0); j < n; j++) {
            for (int k(0); k < m; k++) {
                instr >> data[j][k][2];
//            cout<<data[j][k][0]<<", "<<data[j][k][1]<<", "<<data[j][k][2]<<endl;
            }
        }
    } else {
        cout << "Cant open " << file_name << endl;
    }
    instr.close();
}


int * LocalExtremes::getEnvirons(int x, int y, int *cntEnv) {
    auto *Envirous = new int[9];
    for (int i(0); i < 3; ++i) {
        for (int j(0); j < 3; ++j) {
            int p_x = x - 1 + i;
            int p_y = y - 1 + j;

            if ((p_x >= 0 && p_x < n) && (p_y >= 0 && p_y < m) && (p_x != x || p_y != y)) {
                Envirous[*cntEnv] = data[p_x][p_y][2];
                *cntEnv = (*cntEnv) + 1;
            }
        }
    }
    return Envirous;
}


void LocalExtremes::FindExtremes() {
    result = new int *[n * m];
    for (int i(0); i < n * m; ++i) {
        result[i] = new int[3];
    }

    for (int i(0); i < n; ++i) {
        for (int j(0); j < m; ++j) {
            int cnt = 0;
            int *res = getEnvirons(i, j, &cnt);
            int tmp = 0;
            for (int k(0); k < cnt; ++k) {
                if (data[i][j][2] >= res[k]) {
                    tmp += 1;
                } else {
                    tmp -= 1;
                }
            }

            if (abs(tmp) == cnt) {
                result[sizeResult] = data[i][j];
                sizeResult++;
            }
        }
    }
};

void LocalExtremes::write(const char* file_name) {

    ofstream outstr(file_name, ios::out);
    if(outstr.is_open()) {
        outstr << sizeResult << endl;
        for (int i = 0; i < sizeResult; i++) {
            outstr << result[i][0] << " " << result[i][1] << " " << result[i][2] << endl;
        }
    } else {
        cout << "Cant open " << file_name << endl;
    }
    outstr.close();
}

LocalExtremes::~LocalExtremes(){
    delete[] data;
    delete[] result;
}

int main(){
    LocalExtremes Problem;
    Problem.read("input.txt");
    Problem.FindExtremes();
    Problem.write("output.txt");
    return 0;
}
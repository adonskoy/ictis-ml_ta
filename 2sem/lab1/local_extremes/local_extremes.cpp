//
// Created by Антон Донской on 31.03.2018.
//

#include <iostream>
#include <fstream>
using namespace std;

int *** read(const char* file_name, int *n, int *m) {
    ifstream instr(file_name, ios::in);
    instr >> *n;
    instr >> *m;
    auto *x = new int[*m];
    auto *y = new int[*n];
    for (int i(0); i < *m; ++i) {
        instr >> x[i];
    }
    for (int i(0); i < *n; ++i) {
        instr >> y[i];
    }
    auto ***z = new int **[*m];
    for (int i(0); i < *m; ++i) {
        z[i] = new int *[*n];
        for (int j(0); j < *n; ++j) {
            z[i][j] = new int[3];
        }
    }
    for (int i(0); i < *m; ++i) {
        for (int j(0); j < *n; ++j) {
            z[i][j][0] = x[i];
            z[i][j][1] = y[j];
            instr >> z[i][j][2];
        }
    }
    instr.close();
    return z;
}

void write(const char* file_name,int** mass,int count) {
    ofstream outstr(file_name, ios::out);
    outstr << count << endl;
    for (int i = 0; i < count; i++) {
        outstr << mass[i][0] << " " << mass[i][1] << " " << mass[i][2] << endl;
    }
    outstr.close();
}

int * getEnvirons(int n,  int m, int *cnt,  int x, int y, int ***z) {
    auto *result = new int[9];
    for (int i(0); i < 3; ++i) {
        for (int j(0); j < 3; ++j) {
            int p_x = x - 1 + i;
            int p_y = y - 1 + j;

            if ((p_x >= 0 && p_x < m) && (p_y >= 0 && p_y < n) && (p_x != x || p_y != y)) {
                result[*cnt] = z[p_x][p_y][2];
                *cnt = (*cnt) + 1;
            }
        }
    }
    return result;
}

int main() {
    int n, m, *x = nullptr, *y = nullptr, ***z = nullptr;


    z = read("input.txt", &n, &m);

    auto **result = new int *[n * m];
    for (int i(0); i < n * m; ++i) {
        result[i] = new int[3];
    }

    int result_cnt = 0;
    for (int i(0); i < m; ++i) {
        for (int j(0); j < n; ++j) {
            int cnt = 0;
            int *res;
            res = getEnvirons(n, m, &cnt, i, j, z);
            int tmp = 0;
            for (int k(0); k < cnt; ++k) {
                if (z[i][j][2] >= res[k]) {
                    tmp += 1;
                } else {
                    tmp -= 1;
                }
            }

            if (abs(tmp) == cnt) {
                result[result_cnt][0] = z[i][j][0];
                result[result_cnt][1] = z[i][j][1];
                result[result_cnt][2] = z[i][j][2];
                result_cnt++;

            }
        }
    }
    write("output.txt", result, result_cnt);
}
//
// Created by Антон Донской on 11.05.2018.
//

#include <cmath>
#include <algorithm>
#include "functions.h"

namespace Functions {
    int *sort(int *array, int n) {
        std::sort(array, array + n);
        return array;
    }

    float *sort(float *array, int n) {
        std::sort(array, array + n);
        return array;
    }

    int *positive_numbers(const int *array, int n, int *m) {
        int s = 0;
        auto *result = new int[n];
        for (int i(0); i < n; ++i) {
            if (array[i] > 0) {
                result[s] = array[i];
                s++;
            }
        }
        *m = s;
        return Functions::sort(result, s);
    }

    float *positive_numbers(const float *array, int n, int *m) {
        int s = 0;
        auto *result = new float[n];
        for (int i(0); i < n; ++i) {
            if (array[i] > 0) {
                result[s] = array[i];
                s++;
            }
        }
        *m = s;
        return Functions::sort(result, s);
    }

    int *negative_numbers(const int *array, int n, int *m) {
        int s = 0;
        auto *result = new int[n];
        for (int i(0); i < n; ++i) {
            if (array[i] < 0) {
                result[s] = array[i];
                s++;
            }
        }
        *m = s;
        return Functions::sort(result, s);

    }

    float *negative_numbers(const float *array, int n, int *m) {
        int s = 0;
        auto *result = new float[n];
        for (int i(0); i < n; ++i) {
            if (array[i] < 0) {
                result[s] = array[i];
                s++;
            }
        }
        *m = s;
        return Functions::sort(result, s);
    }

    int *arifm(const int *array, int n, int *m) {
        int s = 0;
        int M = 0;
        for (int i(0); i < n; ++i) {
            M += array[i];
        }
        M /= n;
        int sigma = 0;
        for (int i(0); i < n; ++i) {
            sigma += pow(M - array[i], 2);
        }
        sigma /= n;
        sigma = static_cast<int>(sqrt(sigma));
        auto *result = new int[n];
        for (int i(0); i < n; ++i) {
            if ((array[i] >= M - sigma) && (array[i] <= M + sigma)) {
                result[s] = array[i];
                s++;
            }
        }
        *m = s;
        return Functions::sort(result, s);
    }

    float *arifm(const float *array, int n, int *m) {

        int s = 0;
        float M = 0;
        for (int i(0); i < n; ++i) {
            M += array[i];
        }
        M /= n;

        float sigma = 0;
        for (int i(0); i < n; ++i) {
            sigma += pow(M - array[i], 2);
        }
        sigma /= n;
        sigma = sqrt(sigma);

        auto *result = new float[n];
        for (int i(0); i < n; ++i) {
            if ((array[i] >= M - sigma) && (array[i] <= M + sigma)) {
                result[s] = array[i];
                s++;
            }
        }
        *m = s;
        return Functions::sort(result, s);
    }
}
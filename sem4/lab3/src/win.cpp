#include <stdio.h>
#include <windows.h>
#include <malloc.h>
#include <chrono>
#include <cstdint>
#include <cstdio>
#include <memory>
#include <mutex>
#include <vector>
#include <winnt.h>
#define fn auto
#define var auto
#define let const auto
#define matrix std::vector<std::vector<int32_t>>

typedef struct MyArgs
{
    matrix &a;
    matrix &b;
    matrix &c;
    int32_t i;
    int32_t k;
} ARGS, *PARGS;

class Mutex {
  public:
    HANDLE mutex;
    Mutex(){
        this->mutex = CreateMutex(NULL,
                             FALSE,
                             NULL); // object name
    }
    void lock() { WaitForSingleObject(mutex, INFINITE); }
    void unlock() { ReleaseMutex(mutex); }
};


Mutex mtx;
std::vector<int32_t> factors(int32_t n) {
    std::vector<int32_t> out;
    for (int32_t i = 1; i <= n; ++i) {
        if (n % i == 0) {
            out.push_back(i);
        }
    }
    return out;
}

fn mult(matrix &a, matrix &b, matrix &c, int32_t number, int32_t blocks) {
    int32_t n = a.size();
    int32_t length = n / blocks;
    let beginRow = ((number) / blocks) * length;
    let endRow = beginRow + length - 1;
    let beginCol = number % blocks;
    let endCol = beginCol + length - 1;

    for (int32_t i = beginRow; i <= endRow; ++i) {
        for (int32_t j = beginCol; j <= endCol; ++j) {
            for (int32_t k = beginCol; k <= endRow; ++k) {
                mtx.lock();
                c[i][j] += a[i][k] * b[k][j];
                mtx.unlock();
            }
        }
    }
}

DWORD WINAPI *mult_pair(LPVOID input) {
    matrix a = ((PARGS)input)->a;
    matrix b = ((PARGS)input)->b;
    matrix c = ((PARGS)input)->c;
    int32_t i = ((PARGS)input)->i;
    int32_t k = ((PARGS)input)->k;
    if (i == k * k - 1) {
        mult(a, b, c, i, k);
    } else {
        mult(a, b, c, i, k);
        mult(a, b, c, i + 1, k);
    }
    return NULL;
}

fn main(int32_t argc, char **argv)->int32_t {
    int n;
    let filename = "input";
    let input = fopen(filename, "r");

    fscanf(input, "%d", &n);
    printf("%d\n", n);

    matrix a(n), b(n), c(n);

    for (int32_t i = 0; i < n; ++i) {
        a[i].resize(n);
        b[i].resize(n);
        c[i].resize(n);
    }

    for (var i = 0; i < n; ++i) {
        for (var j = 0; j < n; ++j) {
            fscanf(input, "%d", &a[i][j]);
        }
    }

    for (var i = 0; i < n; ++i) {
        for (var j = 0; j < n; ++j) {
            c[i][j] = 0;
        }
    }

    for (var i = 0; i < n; ++i) {
        for (var j = 0; j < n; ++j) {
            fscanf(input, "%d", &b[i][j]);
        }
    }


    PARGS pDataArray [n];
    HANDLE hThreadArray[n];
    DWORD dwThreadIdArray[n];

    for (let k : factors(n)) {
        printf("k: %d\n", k);
        let start = std::chrono::steady_clock::now();
        for (int32_t i = 0; i < k * k; i += 2) {
            pDataArray[i] = (PARGS) HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY,
                sizeof(ARGS));
            HANDLE thread;
            pDataArray[i]->a = a;
            pDataArray[i]->b = a;
            pDataArray[i]->c = c;
            pDataArray[i]->i = i;
            pDataArray[i]->k = k;
            hThreadArray[i/2] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE) mult_pair, pDataArray[i], 0, &dwThreadIdArray[i]);
            if (hThreadArray[i] == NULL) {
                printf("Cannot create thread\n");
                ExitProcess(3);
            }
        }
        int count = k == 1 ? 1 : k*k/2;
        WaitForMultipleObjects(count, hThreadArray, TRUE, INFINITE);
        let end = std::chrono::steady_clock::now();
        let time =
            std::chrono::duration_cast<std::chrono::nanoseconds>(end - start)
                .count();

        for (int i = 0; i < n; i++) {
            CloseHandle(hThreadArray[i]);
            if (pDataArray[i] != NULL) {
                HeapFree(GetProcessHeap(), 0, pDataArray[i]);
                pDataArray[i] = NULL;
            }
        }
        printf("%ld\n", time);
        for (var i = 0; i < n; ++i) {
            for (var j = 0; j < n; ++j) {
                printf("%d ", c[i][j]);
                c[i][j] = -1;
            }
            printf("\n");
        }
    }

    return 0;
}

#define posix
#include <chrono>
#include <cstdint>
#include <cstdio>
#include <memory>
#include <mutex>
#include <vector>
#define fn auto
#define var auto
#define let const auto
#define matrix std::vector<std::vector<int32_t>>

#include <pthread.h>
struct args
{
    matrix &a;
    matrix &b;
    matrix &c;
    int32_t i;
    int32_t k;
    args(matrix &a, matrix &b, matrix &c, int32_t i, int32_t k) : a(a), b(b), c(c), i(i), k(k){}
};

class Mutex {
  public:
    pthread_mutex_t mutex;
    void lock() {
        pthread_mutex_lock(&mutex);
    }
    void unlock() {
        pthread_mutex_unlock(&mutex);
    }
};
Mutex mutex;

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
                mutex.lock();
                c[i][j] += a[i][k] * b[k][j];
                mutex.unlock();
            }
        }
    }
}

void *mult_pair(void *input) {
    matrix a = ((struct args*)input)->a;
    matrix b = ((struct args*)input)->b;
    matrix c = ((struct args*)input)->c;
    int32_t i = ((struct args*)input)->i;
    int32_t k = ((struct args*)input)->k;
    if (i == k * k - 1) {
        mult(a, b, c, i, k);
    } else {
        mult(a, b, c, i, k);
        mult(a, b, c, i + 1, k);
    }
    return NULL;
}


fn main(int32_t argc, char **argv)->int32_t {
    int32_t n;
    pthread_mutex_init(&mutex.mutex, NULL);

    let filename = "input";
    let input = fopen(filename, "r");

    fscanf(input, "%d", &n);

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

    for (let k : factors(n)) {
        std::vector<pthread_t> threads;
        let start = std::chrono::steady_clock::now();
        for (int32_t i = 0; i < k * k; i += 2) {

            pthread_t thread;
            args arguments = args(a, b, c, i, k);

            pthread_create(&thread, nullptr, mult_pair, (void *)&arguments);
            threads.push_back(thread);
        }
        for (var &thread : threads) {
            pthread_join(thread, NULL);
        }

        let end = std::chrono::steady_clock::now();
        let time =
            std::chrono::duration_cast<std::chrono::nanoseconds>(end - start)
                .count();

        printf("%ld\n", time);
        for (var i = 0; i < n; ++i) {
            for (var j = 0; j < n; ++j) {
                printf("%d ", c[i][j]);
                c[i][j] = 0;
            }
            printf("\n");
        }
    }

    pthread_mutex_destroy(&mutex.mutex);

    return 0;
}

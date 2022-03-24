#include <chrono>
#include <cstdint>
#include <cstdio>
#include <memory>
#include <mutex>
#include <thread>
#include <vector>

#define fn auto
#define var auto
#define let const auto
#define matrix std::vector<std::vector<int32_t>>
std::mutex mutex;

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

fn main(int32_t argc, char **argv)->int32_t {
    int32_t n;

    if (argc == 1) {
        fprintf(stderr, "No input filename provided\n");
        return 1;
    }

    let filename = argv[1];
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

        std::vector<std::thread> threads;

        let start = std::chrono::steady_clock::now();

        for (int32_t i = 0; i < k * k; i += 2) {
            if (i == k * k - 1) {
                threads.push_back(std::thread(
                    [](matrix &a, matrix &b, matrix &c, int32_t number,
                       int32_t blocks) {
                        mult(a, b, c, number, blocks);
                    },
                    std::ref(a), std::ref(b), std::ref(c), i, k));
            } else {
                threads.push_back(std::thread(
                    [](matrix &a, matrix &b, matrix &c, int32_t number,
                       int32_t blocks) {
                        mult(a, b, c, number, blocks);
                        mult(a, b, c, number + 1, blocks);
                    },
                    std::ref(a), std::ref(b), std::ref(c), i, k));
            }
        }
        for (var &thread : threads) {
            thread.join();
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

    return 0;
}

#include <atomic>
#include <cstdint>
#include <cstdio>
#include <memory>
#include <mutex>
#include <vector>

#define fn auto
#define var auto
#define let const auto
#define matrix std::vector<std::vector<int32_t>>
#define atomicMatrix                                                           \
    std::vector<std::vector<std::unique_ptr<std::atomic<int32_t>>>>

fn mult(matrix &a, matrix &b, atomicMatrix &c, int32_t number, int32_t blocks) {
    int32_t n = a.size();
    int32_t length = n / blocks;
    let beginRow = ((number + 1) / blocks) * length;
    let endRow = beginRow + length - 1;
    let beginCol = number % blocks;
    let endCol = beginCol + length - 1;

    for (int32_t i = beginRow; i <= endRow; ++i) {
        for (int32_t j = beginCol; j <= endCol; ++j) {
            for (int32_t k = beginCol; k <= endRow; ++k) {
                (*c[i][j]).fetch_add(a[i][k] * b[k][j]);
            }
        }
    }
}

fn main(int32_t argc, char **argv)->int32_t {
    int32_t n, blocks;

    if (argc == 1) {
        fprintf(stderr, "No input filename provided\n");
        return 1;
    }

    let filename = argv[1];
    let input = fopen(filename, "r");

    fscanf(input, "%d", &n);
    fscanf(input, "%d", &blocks);

    matrix a(n), b(n);
    atomicMatrix c(n);

    for (var &row : a) {
        row.resize(n);
    }
    for (var &row : b) {
        row.resize(n);
    }

    for (var &row : c) {
        row.resize(n);
    }

    for (var i = 0; i < n; ++i) {
        for (var j = 0; j < n; ++j) {
            fscanf(input, "%d", &a[i][j]);
        }
    }

    for (var i = 0; i < n; ++i) {
        for (var j = 0; j < n; ++j) {
            fscanf(input, "%d", &b[i][j]);
        }
    }

    for (var i = 0; i < n; ++i) {
        for (var j = 0; j < n; ++j) {
            c[i][j] = std::make_unique<std::atomic<int>>(0);
        }
    }
    for (int32_t i = 0; i < blocks * blocks - 1; ++i) {
        mult(a, b, c, i, blocks);
    }

    for (var i = 0; i < n; ++i) {
        for (var j = 0; j < n; ++j) {
            printf("%d ", (*c[i][j]).load());
        }
        printf("\n");
    }

    return 0;
}

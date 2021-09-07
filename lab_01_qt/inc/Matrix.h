//
// Created by denis on 06.09.2021.
//

#ifndef LAB_01_MATRIX_H
#define LAB_01_MATRIX_H

#include "vector"

class Matrix {
public:
    Matrix(std::size_t n, std::size_t m);
    // explicit Matrix(const Matrix&);

    Matrix(Matrix&&);
    Matrix& operator = (Matrix&&);
    ~Matrix();

    std::size_t* operator [](std::size_t i) { return data[i]; }
    const std::size_t* operator [](std::size_t i) const { return data[i]; }

    [[nodiscard]] std::size_t N() const { return n; }
    [[nodiscard]] std::size_t M() const { return m; }

    std::size_t** GetData() { return data; }
    void print();
private:
    std::size_t* buffer = nullptr;
    std::size_t** data = nullptr;

    std::size_t n{};
    std::size_t m{};
};


#endif //LAB_01_MATRIX_H

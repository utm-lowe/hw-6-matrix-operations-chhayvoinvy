#include "matrix.h"
#include <iomanip>

// Constructor: Allocate a 2D array (m x n)
Matrix::Matrix(unsigned int rows, unsigned int cols) : m(rows), n(cols) {
    ar = new double*[m];
    for (int i = 0; i < m; ++i) {
        ar[i] = new double[n]{0.0}; // Initialize with zeros
    }
}

// Copy Constructor: Deep copy from rhs
Matrix::Matrix(const Matrix& rhs) : m(rhs.m), n(rhs.n) {
    ar = new double*[m];
    for (int i = 0; i < m; ++i) {
        ar[i] = new double[n];
        for (int j = 0; j < n; ++j) {
            ar[i][j] = rhs.ar[i][j];
        }
    }
}

// Destructor: Clean up dynamic memory
Matrix::~Matrix() {
    for (int i = 0; i < m; ++i) {
        delete[] ar[i];
    }
    delete[] ar;
}

// Getters
int Matrix::getRows() const { return m; }
int Matrix::getCols() const { return n; }

// Element Access
double& Matrix::at(unsigned int row, unsigned int col) { return ar[row][col]; }
const double& Matrix::at(unsigned int row, unsigned int col) const { return ar[row][col]; }

// Assignment Operator
Matrix& Matrix::operator=(const Matrix& rhs) {
    if (this != &rhs) {
        // Delete existing memory
        for (int i = 0; i < m; ++i) delete[] ar[i];
        delete[] ar;

        // Copy dimensions and reallocate
        m = rhs.m;
        n = rhs.n;
        ar = new double*[m];
        for (int i = 0; i < m; ++i) {
            ar[i] = new double[n];
            for (int j = 0; j < n; ++j) {
                ar[i][j] = rhs.ar[i][j];
            }
        }
    }
    return *this;
}

// Non-member Addition
Matrix operator+(const Matrix& m1, const Matrix& m2) {
    Matrix res(m1.getRows(), m1.getCols());
    for (int i = 0; i < m1.getRows(); ++i)
        for (int j = 0; j < m1.getCols(); ++j)
            res.at(i, j) = m1.at(i, j) + m2.at(i, j);
    return res;
}

// Non-member Subtraction
Matrix operator-(const Matrix& m1, const Matrix& m2) {
    Matrix res(m1.getRows(), m1.getCols());
    for (int i = 0; i < m1.getRows(); ++i)
        for (int j = 0; j < m1.getCols(); ++j)
            res.at(i, j) = m1.at(i, j) - m2.at(i, j);
    return res;
}

// Matrix Multiplication
Matrix operator*(const Matrix& m1, const Matrix& m2) {
    Matrix res(m1.getRows(), m2.getCols());
    for (int i = 0; i < m1.getRows(); ++i) {
        for (int j = 0; j < m2.getCols(); ++j) {
            double sum = 0;
            for (int k = 0; k < m1.getCols(); ++k) {
                sum += m1.at(i, k) * m2.at(k, j);
            }
            res.at(i, j) = sum;
        }
    }
    return res;
}

// Scalar Multiplication
Matrix operator*(double scalar, const Matrix& m) {
    Matrix res(m.getRows(), m.getCols());
    for (int i = 0; i < m.getRows(); ++i)
        for (int j = 0; j < m.getCols(); ++j)
            res.at(i, j) = m.at(i, j) * scalar;
    return res;
}

Matrix operator*(const Matrix& m, double scalar) {
    return scalar * m;
}

// Output Stream: Match the 10-column width requirement
std::ostream& operator<<(std::ostream& os, const Matrix& m) {
    for (int i = 0; i < m.getRows(); ++i) {
        for (int j = 0; j < m.getCols(); ++j) {
            os << std::setw(10) << m.at(i, j) << " ";
        }
        os << "\n";
    }
    return os;
}

// Input Stream
std::istream& operator>>(std::istream& is, Matrix& m) {
    for (int i = 0; i < m.getRows(); ++i)
        for (int j = 0; j < m.getCols(); ++j)
            is >> m.at(i, j);
    return is;
}
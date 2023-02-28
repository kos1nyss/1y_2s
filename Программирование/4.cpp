#include <iostream>

template<class T1, class T2, class T3>
class Matrix {
private:
    T1 **matrix;
    T2 N;
    T3 M;

    void update_matrix(T1 **matrix, T2 n, T3 m) {
        N = n;
        M = m;

        for (int i = 0; i < N; i++) {
            delete[] matrix[i];
        }
        delete[] matrix;

        this->matrix = new T1 *[N];
        for (int i = 0; i < N; i++) {
            this->matrix[i] = new T1[M];
            for (int j = 0; j < M; j++) {
                this->matrix[i][j] = matrix[i][j];
            }
        }
    }

public:
    Matrix() {}

    Matrix(T2 n, T3 m) {
        N = n;
        M = m;
        matrix = new T1 *[N];
        for (int i = 0; i < N; i++) {
            matrix[i] = new T1[M];
        }
    }

    Matrix(const Matrix<T1, T2, T3> &other) {
        update_matrix(other.matrix, other.N, other.M);
    }

    Matrix &operator=(const Matrix<T1, T2, T3> &other) {
        update_matrix(other.matrix, other.N, other.M);

        return *this;
    }

    ~Matrix() {
        for (int i = 0; i < N; i++) {
            delete[] matrix[i];
        }
        delete[] matrix;
    }

    Matrix operator+(const Matrix<T1, T2, T3> &other) {
        Matrix<T1, T2, T3> new_matrix(N, M);

        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                new_matrix[i][j] = matrix[i][j] + other.matrix[i][j];
            }
        }

        return new_matrix;
    }

    Matrix &operator+=(const Matrix<T1, T2, T3> &other) {
        *this = *this + other;
        return *this;
    }

    Matrix operator*(const Matrix<T1, T2, T3> &other) {
        Matrix<T1, T2, T3> new_matrix(N, other.M);

        for (int i = 0; i < N; i++) {
            for (int j = 0; j < other.M; j++) {
                new_matrix[i][j] = 0;
                for (int k = 0; k < other.N; k++) {
                    new_matrix[i][j] += matrix[i][k] * other.matrix[k][j];
                }
            }
        }

        return new_matrix;
    }

    Matrix &operator*=(const Matrix<T1, T2, T3> &other) {
        *this = *this * other;
        return *this;
    }

    Matrix& operator++(int _) {
        Matrix<T1, T2, T3> old_matrix = *this;
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                matrix[i][j]++;
            }
        }
        return old_matrix;
    }

    T1 *operator[](const T2 &index) {
        return matrix[index];
    }

    T1 determinant() {
        if (N != M) {
            return 0;
        }

        double **temp_matrix = new double *[N];
        for (int i = 0; i < N; i++) {
            temp_matrix[i] = new double[N];
            for (int j = 0; j < N; j++) {
                temp_matrix[i][j] = matrix[i][j];
            }
        }

        T1 det;
        T2 shift = 0;
        double k;
        while (shift < N) {
            if (shift == 0) {
                det = temp_matrix[shift][shift];
            } else {
                det *= temp_matrix[shift][shift];
            }
            std::cout << det << std::endl;
            for (int i = shift + 1; i < N; i++) {
                if (temp_matrix[shift][shift] == 0) {
                    return 0;
                }
                k = (double) temp_matrix[i][shift] / temp_matrix[shift][shift];
                for (int j = shift; j < N; j++) {
                    temp_matrix[i][j] -= temp_matrix[shift][j] * k;
                }
            }
            shift++;
        }

        for (int i = 0; i < N; i++) {
            delete[] temp_matrix[i];
        }
        delete[] temp_matrix;

        return det;
    }

    friend std::ostream &operator<<(std::ostream &os, const Matrix &c);

    friend std::istream &operator>>(std::istream &in, Matrix &c);
};

template<class T1, class T2, class T3>
std::ostream &operator<<(std::ostream &os, const Matrix<T1, T2, T3> &m) {
    for (int i = 0; i < m.N; i++) {
        for (int j = 0; j < m.N; j++) {
            os << m[i][j] << ' ';
        }
        std::cout << std::endl;
    }
    return os;
}
template<class T1, class T2, class T3>
std::istream &operator>>(std::istream &in, Matrix<T1, T2, T3> &m) {
    for (int i = 0; i < m.N; i++) {
        for (int j = 0; j < m.N; j++) {
            in >> m[i][j];
        }
    }
    return in;
}
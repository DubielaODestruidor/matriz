#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <thread>
#include <iostream>
#include <algorithm>

namespace mat
{
    template <typename T = double>
    class Matrix {
        std::vector<std::vector<T> > data;

    public:

        // Constroi uma matriz vazia
        Matrix() {
        }

        // Constroi matriz m*n
        Matrix(int m, int n) {
            set_size(m, n);
        }

        // Acessa elemento da matriz
        T &at(int i, int j) {
            return data.at(i).at(j);
        }

        // Pega número de linhas
        int get_num_rows() const {
            return data.size();
        }

        // Pega número de colunas
        int get_num_cols() {
            return data.size() ? data.at(0).size() : 0;
        }

        // Define tamanho da matriz
        void set_size(int m, int n) {
            data.resize(m);
            for (auto &row: data) {
                row.resize(n);
            }
        }

        // Serializa matriz para impressão
        std::string serialize(std::string const &separator = " ") {
            std::ostringstream output;
            for (auto &row: data) {
                for (auto &item: row) {
                    output << item << separator;
                }
                output << "\n";
            }
            return output.str();
        }

        // Zera os elementos da matriz
        void zero() {
            for (auto &row: data) {
                for (auto &item: row) {
                    item = T();
                }
            }
        }

        // Soma matrizes
        Matrix<T> operator+(Matrix<T> &other) {
            auto const m = get_num_rows();
            auto const n = get_num_cols();
            if (m != other.get_num_rows() || n != other.get_num_cols()) {
                throw std::runtime_error("cannot sum matrices with different sizes");
            }
            auto sum = Matrix<T>(m, n);
            for (int i = 0; i < m; i++) {
                for (int j = 0; j < n; j++) {
                    sum.at(i, j) = data.at(i).at(j) + other.at(i, j);
                }
            }
            return sum;
        }

        // Subtrai matrizes
        Matrix<T> operator-(Matrix<T> &other) {
            auto const m = get_num_rows();
            auto const n = get_num_cols();
            if (m != other.get_num_rows() || n != other.get_num_cols()) {
                throw std::runtime_error("cannot subtract matrices with different sizes");
            }
            auto difference = Matrix<T>(m, n);
            for (int i = 0; i < m; i++) {
                for (int j = 0; j < n; j++) {
                    difference.at(i, j) = data.at(i).at(j) - other.at(i, j);
                }
            }
            return difference;
        }

        // Retorna matriz negada
        Matrix<T> operator-() {
            auto const m = get_num_rows();
            auto const n = get_num_cols();
            auto negated = Matrix<T>(m, n);
            for (int i = 0; i < m; i++) {
                for (int j = 0; j < n; j++) {
                    negated.at(i).at(j) = -data.at(i).at(j);
                }
            }
            return negated;
        }

        // Retorna cópia da matriz
        Matrix<T> operator+() {
            return *this;
        }

        // Multiplica por escalar
        Matrix<T> operator*(T value) {
            auto const m = get_num_rows();
            auto const n = get_num_cols();
            auto product = Matrix<T>(m, n);
            for (int i = 0; i < m; i++) {
                for (int j = 0; j < n; j++) {
                    product.at(i, j) = data.at(i).at(j) * value;
                }
            }
            return product;
        }

        // Multiplicar matrizes
        Matrix<T> operator*(Matrix<T> &other) {
            auto const m = get_num_rows();
            auto const n = get_num_cols();
            auto const p = other.get_num_cols();
            if (n != other.get_num_rows()) {
                throw std::runtime_error("Erro no número de colunas/linhas");
            }
            auto product = Matrix<T>(m, p);
            for (int i = 0; i < m; i++) {
                for (int j = 0; j < p; j++) {
                    for (int k = 0; k < n; k++) {
                        product.at(i, j) += data.at(i).at(k) * other.at(k, j);
                    }
                }
            }
            return product;
        }

        //Tirar ruído sal e pimenta com média
        Matrix<T> noise_removal()
        {
            auto const m = get_num_rows();
            auto const n = get_num_cols();
            auto convolved = Matrix<T>(m, n);
            convolved.zero();
            for (int i = 1; i < m - 1; i++) {
                for (int j = 1; j < n - 1; j++) {
                    int values[8];
                    values[0] = data.at(i - 1).at(j - 1);
                    values[1] = data.at(i - 1).at(j + 0);
                    values[2] = data.at(i - 1).at(j + 1);

                    values[3] = data.at(i).at(j - 1);
                    values[4] = data.at(i).at(j + 1);

                    values[5] = data.at(i + 1).at(j - 1);
                    values[6] = data.at(i + 1).at(j + 0);
                    values[7] = data.at(i + 1).at(j + 1);

                    int average = 0;
                    for (int k = 0; k < 8; k++)
                    {
                        average += values[k];
                    }
                    average = (int)((float)average / 8.0f);

                    convolved.at(i, j) = average;
                }
            }
            return convolved;
        }
        
        //Tirarndo ruído sal e pimenta com mediana
        Matrix<T> noise_removal_median()
        {
            auto const m = get_num_rows();
            auto const n = get_num_cols();
            auto convolved = Matrix<T>(m, n);
            convolved.zero();
            for (int i = 1; i < m - 1; i++) {
                for (int j = 1; j < n - 1; j++) {
                    int values[8];
                    int valuesLen = sizeof(values) / sizeof(values[0]);
                    values[0] = data.at(i - 1).at(j - 1);
                    values[1] = data.at(i - 1).at(j + 0);
                    values[2] = data.at(i - 1).at(j + 1);

                    values[3] = data.at(i).at(j - 1);
                    values[4] = data.at(i).at(j + 1);

                    values[5] = data.at(i + 1).at(j - 1);
                    values[6] = data.at(i + 1).at(j + 0);
                    values[7] = data.at(i + 1).at(j + 1);

                    std::sort(values, values + valuesLen);
                    auto median = 0.0;
                    median  = values[3] + values[4] / 2.0;
                    

                    convolved.at(i, j) = median;
                }
            }
            return convolved;
        }
    };
}

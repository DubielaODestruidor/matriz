#include "matrix.h"
#include <iostream>

using namespace mat;
using namespace std;

int main()
{
    auto x = Matrix<int>(5, 5);
    auto y = Matrix<int>(5, 5);

    for(int i = 0; i < x.get_num_rows(); i++)
    {
        for(int j = 0; j < x.get_num_cols(); j++)
        {
            x.at(i, j) = i + j;
            y.at(i, j) = i - j;
        }
    }

    auto z = x * y;

    std::cout << x.serialize() << "\n";
    std::cout << y.serialize() << "\n";
    std::cout << z.serialize() << "\n";

    return 0;
}

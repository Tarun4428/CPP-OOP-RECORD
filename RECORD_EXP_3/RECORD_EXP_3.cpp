#include <iostream>
#include <cassert>
using namespace std;

class Matrix
{
private:
    int data[2][2];

public:
    Matrix(int a = 0, int b = 0, int c = 0, int d = 0)
    {
        data[0][0] = a;
        data[0][1] = b;
        data[1][0] = c;
        data[1][1] = d;
    }

    Matrix operator+(const Matrix &m)
    {
        Matrix result;

        for (int i = 0; i < 2; i++)
            for (int j = 0; j < 2; j++)
                result.data[i][j] = data[i][j] + m.data[i][j];

        return result;
    }

    Matrix operator*(const Matrix &m)
    {
        Matrix result;

        for (int i = 0; i < 2; i++)
        {
            for (int j = 0; j < 2; j++)
            {
                result.data[i][j] = 0;

                for (int k = 0; k < 2; k++)
                    result.data[i][j] += data[i][k] * m.data[k][j];
            }
        }

        return result;
    }

    int* operator[](int index)
    {
        return data[index];
    }

    friend ostream& operator<<(ostream &out, const Matrix &m)
    {
        for (int i = 0; i < 2; i++)
        {
            for (int j = 0; j < 2; j++)
                out << m.data[i][j] << " ";

            out << endl;
        }

        return out;
    }
};

int main()
{
    Matrix A(2, 3, 1, 4);
    Matrix B(2, 0, 1, 5);

    Matrix sum = A + B;
    Matrix product = A * B;

    assert(sum[0][0] == 4);
    assert(sum[1][1] == 9);
    assert(product[0][0] == 7);
    assert(product[0][1] == 15);
    assert(product[1][0] == 6);
    assert(product[1][1] == 20);

    cout << "Matrix A:" << endl;
    cout << A;

    cout << "Matrix B:" << endl;
    cout << B;

    cout << "Sum:" << endl;
    cout << sum;

    cout << "Product:" << endl;
    cout << product;

    cout << "Tests passed!" << endl;

    return 0;
}

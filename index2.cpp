#include <iostream>
using namespace std;

class Matrix
{
private:
    int **p;
    int row, col;

public:
    // Constructor.

    Matrix(int r, int c)
    {
        row = r;
        col = c;

        p = new int *[row];
        for (int i = 0; i < row; ++i)
        {
            p[i] = new int[col];
        }
    }

    Matrix(int arr[2][2])
    {
        row = 2;
        col = 2;
        p = new int *[row];
        for (int i = 0; i < row; ++i)
        {
            p[i] = new int[col];
            for (int j = 0; j < col; ++j)
            {
                p[i][j] = arr[i][j];
            }
        }
    }

    // Copy Constructor.

    Matrix(const Matrix &m)
    {
        row = m.row;
        col = m.col;
        p = new int *[row];
        for (int i = 0; i < row; ++i)
        {
            p[i] = new int[col]; // Corrected line
            for (int j = 0; j < col; ++j)
            {
                p[i][j] = m.p[i][j];
            }
        }
    }

    // Overloaded Assingnment Operator.

    Matrix &operator=(const Matrix &m)
    {
        if (this != &m)
        {
            for (int i = 0; i < row; ++i)
            {
                delete[] p[i];
            }
            delete[] p;
        }
        row = m.row;
        col = m.col;
        p = new int *[row];
        for (int i = 0; i < row; ++i)
        {
            p[i] = new int[col];
            for (int j = 0; j < col; ++j)
            {
                p[i][j] = m.p[i][j];
            }
        }

        return *this;
    }

    // Get function

    int get(int i, int j)
    {
        if (i >= 0 && i < row && j >= 0 && j < col)
        {
            return p[i][j];
        }
        else
        {
            cout << "Index out of bounds!" << endl;
            return 0;
        }
    }

    // Set function
    void set(int i, int j, int val)
    {
        if (i >= 0 && i < row && j >= 0 && j < col)
        {
            p[i][j] = val;
        }
        else
            cout << "Index out of bounds!" << endl;
    }

    // Print Function.

    void print()
    {
        for (int i = 0; i < row; ++i)
        {
            for (int j = 0; j < col; ++j)
            {
                cout << p[i][j] << " ";
            }
        }
        cout << endl;
    }

    // Transpose Function.

    void transpose()
    {
        int **t = new int *[col];
        for (int i = 0; i < col; ++i)
        {
            t[i] = new int[row];
            for (int j = 0; j < row; ++j)
            {
                t[i][j] = p[i][j];
            }
        }
        for (int i = 0; i < row; ++i)
        {
            delete[] p[i];
        }
        delete[] p;
        p = t;
        int temp = row;
        row = col;
        col = temp;
    }

    // Print Sub Matrix Function.

    void printSubMatrix(int r1, int r2, int c1, int c2)
    {
        if (r1 > 0 && r2 < row && c1 > 0 && c2 < col)
        {
            for (int i = r1; i <= r2; ++i)
            {
                for (int j = c1; j <= c2; ++j)
                {
                    cout << p[i][j] << " ";
                }
                cout << endl;
            }
        }
        else
        {
            cout << "Index out of bondes!" << endl;
        }
    }

    // makeEmprty Function.

    void makeEmpty(int n)
    {
        if (n <= row && n <= col)
        {
            for (int i = 0; i < n; ++i)
            {
                for (int j = 0; j < n; ++j)
                {
                    p[i][j] = 0;
                }
            }
        }
        else
            cout << "Index out of bounds!" << endl;
    }

    // Subtract Function.

    void sub(Matrix first, Matrix second)
    {
        if (first.row == second.row && first.col == second.col)
        {
            for (int i = 0; i < row; ++i)
            {
                delete[] p[i];
            }
            delete[] p;
            row = first.row;
            col = first.col;
            p = new int *[row];
            for (int i = 0; i < row; ++i)
            {
                p[i] = new int[col];
                for (int j = 0; j < col; ++j)
                {
                    p[i][j] = first.p[i][j] - second.p[i][j];
                }
            }
        }
        else
        {
            cout << "Dimensions do not match!" << endl;
        }
    }

    // Addition Function.

    void add(Matrix first, Matrix second)
    {
        if (first.row == second.row && first.col == second.col)
        {
            for (int i = 0; i < row; ++i)
            {
                delete[] p[i];
            }
            delete[] p;
            row = first.row;
            col = first.col;
            p = new int *[row];
            for (int i = 0; i < row; ++i)
            {
                p[i] = new int[col];
                for (int j = 0; j < col; ++j)
                {
                    p[i][j] = first.p[i][j] + second.p[i][j];
                }
            }
        }
        else
        {
            cout << "Dimensions do not match!" << endl;
        }
    }

    // Product Function.

    void prod(Matrix first, Matrix second)
    {
        if (first.col == second.col)
        {
            for (int i = 0; i < row; ++i)
            {
                delete[] p[i];
            }
            delete[] p;
            row = first.row;
            col = first.col;
            p = new int *[row];
            for (int i = 0; i < row; ++i)
            {
                p[i] = new int[col];
                for (int j = 0; j < col; ++j)
                {
                    p[i][j] = 0;
                    for (int k = 0; k < first.col; ++k)
                    {
                        p[i][j] += first.p[i][k] * second.p[k][j];
                    }
                }
            }
        }
        else
        {
            cout << "Numbers of colums in the first matrix is not equal to the number of rows in the secomd matrix" << endl;
        }
    }

    // Adjoint Function.

    Matrix adjoint()
    {
        if (row != col || row != 2)
        {
            cout << " Error: Adjoint can only be calculated for a 2x2 square matrix." << endl;
            return *this;
        }
        Matrix adj(2, 2);
        adj.p[0][0] = p[1][1];
        adj.p[0][1] = -p[0][1];
        adj.p[1][0] = -p[1][0];
        adj.p[1][1] = p[0][0];
        return adj;
    }

    // Determenent Function.

    int det()
    {
        if (row != col)
        {
            cout << "Error: Determinant can only be calculated for a square matrix." << endl;
            return 0;
        }
        if (row == 2)
        {
            return p[0][0] * p[1][1] - p[0][1] * p[1][0];
        }
        else
        {
            cout << "Error: This function currently only supports 2x2 matrices." << endl;
            return 0;
        }
    }

    // Inverse Matrix.

    Matrix inverse()
    {
        if (row != col)
        {
            cout << "Error: Inverse can only be calculated for a square matrix." << endl;
            return *this;
        }
        int det = this->det();
        if (det == 0)
        {
            cout << "Error: This matrix is singular, so the inverse cannot be calculated." << endl;
            return *this;
        }
        int inv[2][2];
        inv[0][0] = p[1][1] / det;
        inv[0][1] = -p[0][1] / det;
        inv[1][0] = -p[1][0] / det;
        inv[1][1] = p[0][0] / det;
        return Matrix(inv);
    }

    // destructor.

    ~Matrix()
    {
        for (int i = 0; i < row; ++i)
        {
            delete[] p[i];
        }
        delete[] p;
    }
};

int main()
{
    // Create a 2D Matrix object
    Matrix A(2, 2), B(2, 2);
    A.set(0, 0, 1);
    A.set(0, 1, 2);
    A.set(1, 0, 3);
    A.set(1, 1, 4);

    B.set(0, 0, 2);
    B.set(0, 1, 0);
    B.set(1, 0, 1);
    B.set(1, 1, 2);

    Matrix C(2, 2);
    C.add(A, B);
    cout << "Matrix A + B:" << endl;
    C.print();

    C.sub(A, B);
    cout << "Matrix A - B:" << endl;
    C.print();

    C.prod(A, B);
    cout << "Matrix A * B:" << endl;
    C.print();

    Matrix D = A.inverse();
    cout << "Inverse of A:" << endl;
    D.print();

    int detA = A.det();
    cout << "Determinant of A: " << detA << endl;

    Matrix adjA = A.adjoint();
    cout << "Adjoint of A:" << endl;
    adjA.print();

    return 0;
}

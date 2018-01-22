#ifndef MATRIX_H_INCLUDED
#define MATRIX_H_INCLUDED
#include <stdio.h>
#include <cmath>
class N2_matrix
{
    int degree = 0;
    int mas_size = 1;
    double *massive = NULL;
    N2_matrix()
    {}
public:
    //Constructors
    N2_matrix (const N2_matrix& other_matr)
    {
        degree = other_matr.degree;
        mas_size = other_matr.mas_size;
        massive = new double[mas_size*mas_size];
        for (int i = 0; i < mas_size * mas_size; i ++)
        {
            massive[i] = other_matr.massive[i];
        }
    }


    N2_matrix (int deg)
    {
        degree = deg;
        mas_size = pow(2, degree);
        massive = new double [mas_size * mas_size];
    }
    //interface
    int size() const
    {
        return mas_size;
    }

    double& operator() (int i, int j)
    {
        return massive[i*mas_size + j];
    }

    const double& operator() (int i, int j) const
    {
        return massive[i*mas_size + j];
    }

    void sub_matr (int i, int j, N2_matrix& result) const;

    N2_matrix& operator = (const N2_matrix& other_mas)
    {
        for (int i = 0; i < mas_size * mas_size; i ++)
        {
            massive[i] = other_mas.massive[i];
        }
        return *this;
    }

    int deg() const
    {
        return degree;
    }

    N2_matrix& operator += (const N2_matrix& other_mas)
    {
        for (int i = 0; i < mas_size * mas_size; i ++)
        {
            massive[i] += other_mas.massive[i];
        }
        return *this;
    }

    N2_matrix& operator -= (const N2_matrix& other_mas)
    {
        for (int i = 0; i < mas_size * mas_size; i ++)
        {
            massive[i] -= other_mas.massive[i];
        }
        return *this;
    }
    //destructors
    virtual ~N2_matrix ()
    {
        delete [] massive;
    }
};

void multimatrix (const N2_matrix& matr1, const N2_matrix& matr2, N2_matrix& result);



#endif // MATRIX_H_INCLUDED

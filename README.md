#include <iostream>
#include <cmath>
#include <fstream>
#include <string.h>
using namespace std;

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
void N2_matrix::sub_matr (int i, int j, N2_matrix& result) const
    {
        for (int k = 0; k < mas_size / 2; k ++)
        {
            for (int l = 0; l < mas_size / 2; l ++)
            {
                result(k, l) = operator()((i * mas_size / 2 + k), j * mas_size / 2 + l);
            }
        }
    }
void multimatrix (const N2_matrix& matr1, const N2_matrix& matr2, N2_matrix& result)
{
    if (matr1.deg() == 1)
    {
        result(0, 0) = matr1(0, 0) * matr2(0, 0) + matr1(0, 1) * matr2(1, 0);
        result(0, 1) = matr1(0, 0) * matr2(0, 1) + matr1(0, 1) * matr2(1, 1);
        result(1, 0) = matr1(1, 0) * matr2(0, 0) + matr1(1, 1) * matr2(1, 0);
        result(1, 1) = matr1(1, 0) * matr2(0, 1) + matr1(1, 1) * matr2(1, 1);
        return;
    }
    else
    {
        const int now_deg = matr1.deg() - 1;
        N2_matrix p1(now_deg);
        N2_matrix p2(now_deg);
        N2_matrix p3(now_deg);
        N2_matrix p4(now_deg);
        N2_matrix p5(now_deg);
        N2_matrix p6(now_deg);
        N2_matrix p7(now_deg);
        N2_matrix helper1(now_deg);
        N2_matrix helper2(now_deg);
        N2_matrix tmp(now_deg);
        matr1.sub_matr(0, 0, helper1);
        matr1.sub_matr(1, 1, tmp);
        helper1 += tmp;
        matr2.sub_matr(0, 0, helper2);
        matr2.sub_matr(1, 1, tmp);
        helper2 += tmp;
        multimatrix(helper1, helper2, p1);
        matr1.sub_matr(1, 0, helper1);
        matr1.sub_matr(1, 1, tmp);
        helper1 += tmp;
        matr2.sub_matr(0, 0, tmp);
        multimatrix(helper1, tmp, p2);
        matr2.sub_matr(0, 1, helper2);
        matr2.sub_matr(1, 1, tmp);
        helper2 -= tmp;
        matr1.sub_matr(0, 0, tmp);
        multimatrix(tmp, helper2, p3);
        matr2.sub_matr(1, 0, helper2);
        matr2.sub_matr(0, 0, tmp);
        helper2 -= tmp;
        matr1.sub_matr(1, 1, tmp);
        multimatrix(tmp, helper2, p4);
        matr1.sub_matr(0, 0, helper1);
        matr1.sub_matr(0, 1, tmp);
        helper1 += tmp;
        matr2.sub_matr(1, 1, tmp);
        multimatrix(helper1, tmp, p5);
        matr1.sub_matr(1, 0, helper1);
        matr1.sub_matr(0, 0, tmp);
        helper1 -= tmp;
        matr2.sub_matr(0, 0, helper2);
        matr2.sub_matr(0, 1, tmp);
        helper2 += tmp;
        multimatrix(helper1, helper2, p6);
        matr1.sub_matr(0, 1, helper1);
        matr1.sub_matr(1, 1, tmp);
        helper1 -= tmp;
        matr2.sub_matr(1, 0, helper2);
        matr2.sub_matr(1, 1, tmp);
        helper2 += tmp;
        multimatrix(helper1, helper2, p7);
        helper1 = p1;
        helper1 += p4;
        helper1 -= p5;
        helper1 += p7;
        for (int m = 0; m < matr1.size() / 2; m ++)
        {
            for (int n = 0; n < matr1.size() / 2; n ++)
            {
                result(m, n) = helper1(m, n);
            }
        }
        helper1 = p3;
        helper1 += p5;
        for (int m = 0; m < matr1.size() / 2; m ++)
        {
            for (int n = 0; n < matr1.size() / 2; n ++)
            {
                result(m, matr1.size() / 2 + n) = helper1(m, n);
            }
        }
        helper1 = p2;
        helper1 += p4;
        for (int m = 0; m < matr1.size() / 2; m ++)
        {
            for (int n = 0; n < matr1.size() / 2; n ++)
            {
                result(m + matr1.size() / 2, n) = helper1(m, n);
            }
        }
        helper1 = p1;
        helper1 -= p2;
        helper1 += p3;
        helper1 += p6;
        for (int m = 0; m < matr1.size() / 2; m ++)
        {
            for (int n = 0; n < matr1.size() / 2; n ++)
            {
                result(m + matr1.size() / 2, n + matr1.size() / 2) = helper1(m, n);
            }
        }
    }
}

void help()
{
    cout << " Write '--help' to get help information. " << endl;
    cout << " Write the name of the data-file to open it. " << endl;
    cout << " Write the name of data-file and result-file to build this project. " << endl;
    cout << " Attention! Files should exist at the right directory. " << endl;
    cout << " In case files can't be opened, you'll get a error-message. Program will be closed. " << endl;
    cout << " Wrong data also causes the closing of the program and appearing of the error-message. " << endl;
    cout << " Be kind and check everything before you start to use this program. " << endl;
}
int console_input (int argc, char* argv[])
{
    ifstream in;
    ofstream out;
    if(argc < 2)
    {
        cout << "use: " << endl << argv[0] << " --help" << endl << "to get help information"<< endl;
        return 0;
    }
    else if(argc == 2)
    {
        if (strcmp("--help", argv[1]) == 0)
        {
            help();
            return 0;
        }
        in.open(argv[1]);
        if( !in.is_open())
        {
            cout << "Can't open input file " <<argv[1] << endl;
            return 0;
        }
        char ch;
        while( in.get(ch))
            {
                cout << ch;
            }
        return 0;
    }
    else if (argc > 2)
    {
        in.open(argv[1]);
        if(!in.is_open())
        {
            cout << "Can't open input file " <<argv[1] << endl;
            return 0;
        }
        out.open(argv[2]);
        if(!out.is_open())
        {
            cout<< " Can't open output file " << argv[2] << endl;
            return 0;
        }
        cout << "input: " << endl;
        char ch;
        while( in.get(ch))
        {
            cout << ch;
        }
        return 1;
    }
}
int create_max(int& max, int& degree, int& size1i, int& size1j, int& size2j)
{
    if (size1j > size2j)
    {
        max = size1j;
    }
    else
    {
        max = size2j;
    }
    if (size1i > max)
    {
        max = size1i;
    }
    while (pow(2, degree) < max)
    {
        degree ++;
    }
    max = pow(2, degree);
    return max;
}
void fill_matrix (N2_matrix& One, int& size, int& size_i, int& size_j, ifstream& in)
{
    for (int i = 0; i < size; i ++)
    {
        for (int j = 0; j < size; j ++)
        {
            if ((i < size_i) && (j < size_j))
            {
                in >> One(i, j);
            }
            else
            {
                One(i, j) = 0;
            }
        }
    }
}
int main(int argc, char* argv[])
{
    ifstream in;
    ofstream out;
    if (console_input (argc, argv) == 0)
    {
        return 0;
    }
    in.open(argv[1]);
    out.open(argv[2]);
    int size1i = 0, size1j = 0, size2i = 0, size2j = 0;
    in >> size1i >> size1j >> size2i >> size2j;
    if (size1j != size2i)
    {
        cout << " Error! Wrong data! " << endl;
        return 0;
    }
    int degree = 0;
    int max = 0;
    max = create_max(max, degree, size1i, size1j, size2j);
    if (max == 0)
    {
        double a, b;
        in >> a >> b;
        out << a * b << endl;
        return 0;
    }
    N2_matrix One (degree);
    fill_matrix (One, max, size1i, size1j, in);
    N2_matrix Two (degree);
    fill_matrix (Two, max, size2i, size2j, in);
    N2_matrix Result(degree);
    multimatrix(One, Two, Result);
    cout << endl << "output: " << endl;
    for (int i = 0; i < size1i; i ++)
    {
        for (int j = 0; j < size2j; j ++)
        {
            out << Result(i, j) << " ";
            cout << Result(i, j) << " ";
            if (j == size2j - 1)
            {
                out << endl;
                cout << endl;
            }
        }
    }
    in.close();
    out.close();
    return 0;
}

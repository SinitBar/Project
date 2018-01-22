#include <iostream>
#include <cmath>
#include <fstream>
#include <string.h>
#include "matrix.h"
using namespace std;


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
    }
    return 1;
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

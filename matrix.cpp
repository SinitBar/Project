#include "matrix.h"
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


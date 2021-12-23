//
// Created by Kevin Schmidt on 12/15/21.
//

#ifndef CLASSES_MATRIX_HPP
#define CLASSES_MATRIX_HPP
#include <iostream>
#include <cmath>


template <int ROWS, int COLUMNS, typename TYPE=float>
class Matrix
{
public:
    typedef TYPE value_type;
    static constexpr int rows_ = ROWS;
    static constexpr int columns_ = COLUMNS;

    TYPE data_ [ROWS][COLUMNS];

    Matrix()
    {
        for (int i = 0; i < ROWS; ++i)
        {
            for (int j = 0; j < COLUMNS; ++j)
            {
                data_[i][j] = ((i==j) ? 1 : 0);
            }
        }
    }

    Matrix(std::initializer_list<std::initializer_list<TYPE>> const& list)
    {
        assert(list.size() == ROWS);

        int row = 0;
        int column = 0;

        auto irow = list.begin();
        for (int row = 0; row < ROWS; ++row)
        {
            assert(irow->size() == COLUMNS);
            auto icol = irow->begin();
            for (int col = 0; col < COLUMNS; ++col)
            {
                data_[row][col] = *icol++;
            }
            irow++;
        }
    }

//    Matrix(TYPE in[ROWS][COLUMNS])
//    {        for (int i = 0; i < ROWS; ++i)
//        {
//            for (int j = 0; j < COLUMNS; ++j)
//            {
//                data_[i][j] = in[i][j];
//            }
//        }
//    }

    bool operator==(Matrix const &other) const
    {
        for (int i = 0; i < ROWS; ++i)
        {
            for (int j = 0; j < COLUMNS; ++j)
            {
                if (data_[i][j] != other.data_[i][j])
                {
                    return false;
                }
            }
        }
        return true;
    }

    bool operator!=(Matrix const &other) const
    {
        return !(*this == other);
    }

    friend std::ostream& operator<<(std::ostream& os, Matrix const &other)
    {
        os << '{';
        for (int i = 0; i < ROWS; ++i)
        {
            os << '{';
            for (int j = 0; j < COLUMNS; ++j)
            {
                if (j != 0) os << ", ";
                os << other.data_[i][j];
            }
            os << '}';
            if (i != ROWS - 1) os << ",\n ";
        }
        os << "}\n";
        return os;
    }

    template<typename OTHER>
     Matrix<ROWS, OTHER::columns_, TYPE> operator*(OTHER const &other) const
    {

        using result_type = typeof(data_[0][0] * other.data_[0][0]);
        Matrix<ROWS, OTHER::columns_, result_type> out;
        static_assert(COLUMNS == OTHER::rows_);

        for (int row = 0; row < ROWS; ++row)
        {
            for (int column = 0; column < OTHER::columns_; ++column)
            {
                TYPE value = 0;
                for (int i = 0; i < COLUMNS; ++i)
                {
                    value = value + data_[row][i] * other.data_[i][column];
                }
                out.data_[row][column] = value;
            }
        }

        return out;
    }

    Matrix<ROWS, COLUMNS, TYPE> operator+( Matrix<ROWS,COLUMNS,TYPE> const &other) const
    {
        using result_type = typeof(data_[0][0] + other.data_[0][0]);
        Matrix<ROWS, COLUMNS, result_type> out;

        for (int row = 0; row < ROWS; ++row)
        {
            for (int column = 0; column < COLUMNS; ++column)
            {
                out.data_[row][column] = data_[row][column] + other.data_[row][column];
            }
        }

        return out;
    }

    Matrix<ROWS, COLUMNS, TYPE> operator-( Matrix<ROWS,COLUMNS,TYPE> const &other) const
    {
        return *this + other*(-1);
    }

    Matrix<ROWS, COLUMNS, TYPE> operator*(float scalar) const
    {
        Matrix<ROWS, COLUMNS, TYPE> out;

        for (int i = 0; i < ROWS; ++i)
        {
            for (int j = 0; j < COLUMNS; ++j)
            {
                out.data_[i][j] = data_[i][j]*scalar;
            }
        }
        return out;
    }




    Matrix& normalize()
    {
        assert(COLUMNS == 1);
        //assert(data_[ROWS-1][0] > 1e-8);
        for (int i = 0; i < ROWS; ++i)
        {
            data_[i][0]/=data_[ROWS-1][0];
        }
        return *this;
    }

};

template<int ROWS2, int COLUMNS2, typename TYPE1, typename TYPE2>
auto error(Matrix<ROWS2,COLUMNS2,TYPE1> const &a, Matrix<ROWS2,COLUMNS2,TYPE2> const &b)
{
    using result_type = typeof( a.data_[0][0] + b.data_[0][0] );

    result_type error = 0;
    for (int i=0; i<ROWS2; ++i)
    {
        for (int j=0; j<COLUMNS2; ++j)
        {
            result_type e = abs(a.data_[i][j] - b.data_[i][j]);
            if (e > error)
            {
                error = e;
            }
        }
    }
    return error;

}

Matrix<3,3,float> rotate(float degrees);

Matrix<3,3> translate(float tx, float ty);

Matrix<3,3> scale(float sx, float sy);

Matrix<3,3> scale(float s);


Matrix<4,4,float> rotate(float degrees, float l,float m,float n);

Matrix<4,4> translate(float tx, float ty, float tz);
Matrix<4,4> translate(Matrix<4,1> const & d);

Matrix<4,4> scale(float sx, float sy, float sz);

Matrix<4,4> scale3d(float s);

Matrix<4,4> perspective(float altitude);


Matrix<4,4> motion_linear(float t, Matrix<4,1> v, float t1, float t2);
Matrix<4,4> motion_rotate(float t, float angular_velocity, float l, float m, float n, float t1, float t2);
Matrix<4,4> motion_circular(float t, float radius, float angular_velocity, float starting_angle);

#endif //CLASSES_MATRIX_HPP

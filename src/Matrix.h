#pragma once
#include "stdafx.h"
#include<memory.h>
#include<assert.h>
template<class T>
class Matrix
{
public:
	Matrix(size_t rows, size_t cols)
	{
		assert(rows != 0);
		assert(cols != 0);
		n_rows = rows;
		n_cols = cols;
		matrix.resize(rows);
		for (size_t i = 0; i != rows; ++i)
		{
			matrix[i].resize(cols);
		}
	}
	size_t Get_NumRows() const
	{
		return n_rows;
	}
	size_t Get_NumCols() const
	{
		return n_cols;
	}
	const T & Get_Element(size_t i, size_t j) const {
		return matrix[i][j];
	}
	void Set_Element(size_t i, size_t j, const T& v)
	{
		assert(i < n_rows && j < n_cols);
		matrix[i][j] = v;
	}
	Matrix operator + (const Matrix & m) const
	{
		assert(m.Get_NumCols() == n_cols && m.Get_NumRows() == n_rows);
		Matrix ret(m.Get_NumRows(), m.Get_NumCols());
		for (size_t i = 0; i != n_rows; ++i)
			for (size_t j = 0; j != n_cols; ++j)
			{
				ret.Set_Element(i, j, matrix[i][j] + m.Get_Element(i, j));
			}
		return ret;
	}
	Matrix operator * (const Matrix & m) const
	{
		assert(n_cols == m.Get_NumRows());
		Matrix ret(n_rows, m.Get_NumCols());
		for (size_t i = 0; i != n_rows; ++i)
			for (size_t j = 0; j != m.Get_NumCols(); ++j)
			{
				T value(matrix[i][0] * m.Get_Element(0, j));
				for (size_t k = 1; k != n_cols; ++k)
				{
					value = value + matrix[i][k] * m.Get_Element(k, j);
				}
				ret.Set_Element(i, j, value);
			}
		return ret;
	}
private:
	std::vector< std::vector<T> > matrix;
	size_t n_cols, n_rows;
};

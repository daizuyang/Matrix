// Matrix.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<vector>
#include<map>
#include<memory.h>
#include<assert.h>
class Poly
{
public:
	Poly()
	{
	}
	Poly(const std::vector<char> &var)
	{
		bool map[26];
		memset(map, 0, sizeof(map));
		variables.clear();
		for (size_t i = 0; i != var.size(); ++i)
		{
			assert(var[i] >= 'a' && var[i] <= 'z');
			size_t pos = var[i] - 'a';
			assert(map[pos] == false);
			map[pos] = true;
			variables.push_back(var[i]);
		}

	}
	void SetCoeff(const std::map<char, int> &v, const double &value)
	{
		poly.push_back(std::pair< std::map<char, int>, double>(v, value) );
	}
	void SetCoeff(std::pair<const std::map<char, int>,double> item)
	{
		poly.push_back(item);
	}
	Poly operator * (const Poly & p) const
	{
		Poly ret(merge_variables(p.getVaribles()));
		size_t num = Get_Num_Item();
		size_t num_p = p.Get_Num_Item();
		for(size_t i = 0;i!= num; ++i)
			for (size_t j = 0; j != num_p; ++j)
			{
				const std::pair<std::map<char, int>, double> & item = Get_Item(i);
				const std::pair<std::map<char, int>, double> & item_p = p.Get_Item(j);
				std::map<char, int> v = item.first;
				for (auto k = item_p.first.begin(); k != item_p.first.end(); ++k)
				{
					v[k->first] = v[k->first] + k->second;
				}
				ret.SetCoeff(v, item.second * item_p.second);
			}
		return ret;
	}
	Poly operator + (const Poly & p) const
	{
		Poly ret(merge_variables(p.getVaribles()));
		size_t num = Get_Num_Item();
		size_t num_p = p.Get_Num_Item();
		for (size_t i = 0; i != num; ++i)
		{
			const std::pair<std::map<char, int>, double> & item = Get_Item(i);
			ret.SetCoeff(item);
		}
		for (size_t j = 0; j != num_p; ++j)
		{
			const std::pair<std::map<char, int>, double> & item_p = p.Get_Item(j);
			ret.SetCoeff(item_p);
		}
		return ret;
	}
	size_t Get_Num_Item() const
	{
		return poly.size();
	}
	const std::pair< std::map<char, int>, double> & Get_Item(size_t i) const
	{
		assert(i<poly.size());
		return poly[i];

	}
private:
	const std::vector<char> getVaribles() const
	{
		return variables;
	}
	std::vector<char> merge_variables(const std::vector<char> &p_variables) const {
		int map[26];
		memset(map, 0, sizeof(map));
		for (size_t i = 0; i != variables.size(); ++i)
		{
			map[variables[i] - 'a'] = true;
		}
		for (size_t i = 0; i != p_variables.size(); ++i)
		{
			map[p_variables[i] - 'a'] = true;
		}
		std::vector<char> newVariables;
		for (size_t i = 0; i != 26; ++i)
		{
			if (map[i])
				newVariables.push_back('a' + i);
		}
		return newVariables;
	}
	std::vector<char> variables;
	std::vector< std::pair< std::map<char, int>, double> > poly;

};
template<class T>
class Matrix
{
public:
	Matrix(size_t rows, size_t cols)
	{
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
		for(size_t i = 0;i!=n_rows; ++i)
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
int main()
{
	Poly p1({'c', 'b', 'z'});
	p1.SetCoeff({ {'c',1},{'b',2} }, 1.5);
	p1.SetCoeff({ {'z',-2},{'c',-2} }, 0.5);

	Poly p2({ 'x', 'y', 'z' });
	p2.SetCoeff({ { 'x',1 },{ 'y',2 } }, -2);
	p2.SetCoeff({ { 'z',2 } }, 2);

	Poly p3 = p1 * p2;

	Matrix<double> mat(2,3), mat2(3,3);
	mat.Set_Element(0, 1, 1.2);
	mat2.Set_Element(1, 2, 1);
	mat2.Set_Element(0, 1, -2.2);
	auto ma3 = mat * mat2;

	Matrix<Poly> mp1(1, 2), mp2(2,1);
	mp1.Set_Element(0, 0, p1);
	mp2.Set_Element(0, 0, p2);
	auto mp3 = mp1*mp2;

    return 0;
}



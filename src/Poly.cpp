#include "stdafx.h"
#include"Poly.h"
#include<assert.h>
#include<memory.h>
Poly::Poly() {}
Poly::Poly(const std::vector<char> &var)
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
void Poly::SetCoeff(const std::map<char, int> &v, const double &value)
{
	poly.push_back(std::pair< std::map<char, int>, double>(v, value));
}
void Poly::SetCoeff(std::pair<const std::map<char, int>, double> item)
{
	poly.push_back(item);
}
Poly Poly::operator * (const Poly & p) const
{
	Poly ret(merge_variables(p.getVaribles()));
	size_t num = Get_Num_Item();
	size_t num_p = p.Get_Num_Item();
	for (size_t i = 0; i != num; ++i)
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
Poly Poly::operator + (const Poly & p) const
{
	return add_or_minus(1, p);
}
Poly Poly::operator - (const Poly & p) const
{
	return add_or_minus(-1, p);
}
Poly Poly::operator - () const
{
	Poly ret(getVaribles());
	size_t num = Get_Num_Item();
	for (size_t j = 0; j != num; ++j)
	{
		const std::pair<std::map<char, int>, double> & item = Get_Item(j);
		ret.SetCoeff(std::pair<std::map<char, int>, double>(item.first, -item.second));
	}
	return ret;
}

size_t Poly::Get_Num_Item() const
{
	return poly.size();
}
const std::pair< std::map<char, int>, double> & Poly::Get_Item(size_t i) const
{
	assert(i<poly.size());
	return poly[i];
}
const std::vector<char> Poly::getVaribles() const
{
	return variables;
}
std::vector<char> Poly::merge_variables(const std::vector<char> &p_variables) const {
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

Poly Poly::add_or_minus(int sign, const Poly & p2) const
{
	assert((sign == 1) || (sign == -1));
	Poly ret(merge_variables(p2.getVaribles()));
	size_t num = Get_Num_Item();
	size_t num_p2 = p2.Get_Num_Item();
	for (size_t i = 0; i != num; ++i)
	{
		const std::pair<std::map<char, int>, double> & item = Get_Item(i);
		ret.SetCoeff(item);
	}
	for (size_t j = 0; j != num_p2; ++j)
	{
		const std::pair<std::map<char, int>, double> & item = p2.Get_Item(j);
		ret.SetCoeff(std::pair<std::map<char, int>, double>(item.first, sign*item.second));
	}
	return ret;
}


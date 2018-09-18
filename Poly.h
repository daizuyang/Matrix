#pragma once
#include "stdafx.h"
#include<vector>
#include<map>
class Poly
{
public:
	Poly();
	Poly(const std::vector<char> &var);
	void SetCoeff(const std::map<char, int> &v, const double &value);
	void SetCoeff(std::pair<const std::map<char, int>, double> item);
	Poly operator * (const Poly & p) const;
	Poly operator + (const Poly & p) const;
	size_t Get_Num_Item() const;
	const std::pair< std::map<char, int>, double> & Get_Item(size_t i) const;
private:
	const std::vector<char> getVaribles() const;
	std::vector<char> merge_variables(const std::vector<char> &p_variables) const;
	std::vector<char> variables;
	std::vector< std::pair< std::map<char, int>, double> > poly;
};

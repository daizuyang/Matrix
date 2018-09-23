#pragma once
#include<utility>
#include<map>
namespace Utils
{
	enum Sign
	{
		positive = 1,
		minus = -1
	};
	const size_t MaxV('z'-'a'+1);
	typedef std::pair<std::map<char, int>, double> ItemType;
}

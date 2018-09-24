#include "stdafx.h"
#include "NGram.h"

NGram::NGram(string source)
{
	phrase = source;
}

void NGram::add(string to)
{
	ng[to]++;
}

void NGram::add(string to, int value)
{
	ng[to] += value;
}

string NGram::getMax()
{
	int best = -1; //the highest value of value
	string ans = ""; //the key with the highest value
	for (auto& pair: ng) { //loops through all the key and value pairs
		if (pair.second > best) {
			ans = pair.first;
			best = pair.second;
		}
	}

	return ans;
}

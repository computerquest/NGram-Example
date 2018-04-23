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
	int best = -1;
	string ans = "";
	for (auto& pair: ng) {
		if (pair.second > best) {
			ans = pair.first;
			best = pair.second;
		}
	}

	return ans;
}

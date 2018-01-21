#pragma once
#include <string>
#include <map>
using namespace std;

class NGram {
public:
	string phrase;
	map<string, int> ng;

	NGram(string souce);

	void add(string to);
	void add(string to, int value);
};
#include "stdafx.h"
#include <algorithm>
#include <string>
#include <sstream>
#include <vector>
#include <iterator>
#include <fstream>
#include "NGram.h"
using namespace std;

void sanitize(string &in) {
	char c[] = { ',','.','/','!','?','-','*','_','(',')','&','%','$','#',':',';', '\\'};

	for (int a = 0; a < sizeof(c) / sizeof(c[0]); a++) {
		in.erase(remove(in.begin(), in.end(), c[a]), in.end());
	}

	transform(in.begin(), in.end(), in.begin(), ::tolower);
}

void split(const std::string &s, char delim, vector<string> &result) {
	stringstream ss(s);
	string item;
	while (getline(ss, item, delim)) {
		result.push_back(item);
	}
}

void splitMain(const string &s, char delim, vector<string> &elems) {
	split(s, delim, elems);
}

NGram* find(vector<NGram> &stuff, string z) {
	for (int i = 0; i < stuff.size(); i++) {
		if (stuff[i].phrase == z) {
			return &stuff[i];
		}
	}

	stuff.push_back(NGram(z));
	return &stuff.back();
}
int main() {
	vector<string> all;
	vector<NGram> two;
	vector<NGram> three;
	vector<NGram> one;

	ifstream file;
	file.open("big.txt");

	string x;
	while (file >> x) {
		splitMain(x, ' ', all);
	}
	file.close();

	for (int i = 0; i < all.size(); i++) {
		sanitize(all[i]);
	}

	NGram *n = new NGram("");
	for (int i = 0; i < all.size(); i++) {
		for (int size = 1; size <= 3; size++) {
			if (i + size + 1 >= all.size()) {
				break;
			}

			string search = "";
			for (int a = 0; a < size && a + i < all.size(); a++) {
				search += all[i + a] + " "; //this could be problematic with a hanging space but we type in that manner
			}

			switch (size) {
			case 2:
				n = find(two, search);
				break;
			case 3:
				n = find(three, search);
				break;
			case 1:
				n = find(one, search);
				break;
			}
			n->add(all[i + size + 1]);
		}
	}

	delete n;

	return 0;
}


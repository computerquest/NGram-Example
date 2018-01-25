#include "stdafx.h"
#include <algorithm>
#include <string>
#include <sstream>
#include <vector>
#include <iterator>
#include <fstream>
#include <iostream>
#include "NGram.h"
using namespace std;

void sanitize(string &in) {
	char c[] = { ',','.','/','!','?','-','*','_','(',')','&','%','$','#',':',';', '\\', '"','\'', '@' };

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

void writeNG(vector<NGram> &ng, string out) {
	ofstream file;
	file.open(out);

	for (int i = 0; i < ng.size(); i++) {
		if (ng[i].phrase == "") {
			continue;
		}
		string info = ng[i].phrase + "|";
		map<string, int>::iterator it;
		for (it = ng[i].ng.begin(); it != ng[i].ng.end(); it++)
		{
			if (it->first == "") {
				continue;
			}
			info += it->first + "*" + to_string(it->second) + "|";
		}

		file << info << endl;
	}

	file.close();
}

void readNG(vector<NGram> &ng, string out) {
	ifstream file;
	file.open(out);

	string x;
	while (getline(file, x)) {
		vector<string> all;
		splitMain(x, '|', all);
		NGram n(all[0]);
		for (int i = 1; i < all.size(); i++) {
			vector<string> next;
			splitMain(all[i], '*', next);
			n.add(next[0], stoi(next[1]));
		}
		ng.push_back(n);
	}


	file.close();
}

template<typename KeyType, typename ValueType>
std::pair<KeyType, ValueType> get_max(const std::map<KeyType, ValueType>& x) {
	using pairtype = std::pair<KeyType, ValueType>;
	return *std::max_element(x.begin(), x.end(), [](const pairtype & p1, const pairtype & p2) {
		return p1.second < p2.second;
	});
}

int main() {
	vector<string> all;
	vector<NGram> two;
	vector<NGram> three;
	vector<NGram> one;
	string root = "";
	ifstream file;
	do {
		cout << "sherlock holmes, fairy tales, trump, or green eggs and ham" << endl;
		getline(cin, root);
		file = ifstream(root+".txt");
	} while (!file.good());

	ifstream f(root+"one.txt");
	//this creates
	if (!f.good()) {
		string x;
		while (file >> x) {
			splitMain(x, ' ', all);
		}
		file.close();

		for (int i = 0; i < all.size(); i++) {
			sanitize(all[i]);
		}

		int maxIteration = 20000;
		NGram *n = new NGram("");
		for (int i = 0; i < all.size() && i < maxIteration; i++) {
			for (int size = 0; size < 3; size++) {
				if (i + size + 1 >= all.size()) {
					break;
				}

				string search = "";
				for (int a = 0; a < size+1 && a + i < all.size(); a++) {
					search += all[i + a] + " ";
				}

				switch (size) {
				case 1:
					n = find(two, search);
					break;
				case 2:
					n = find(three, search);
					break;
				case 0:
					n = find(one, search);
					break;
				}
				n->add(all[i + size+1]);
			}
		}

		writeNG(one, root+"one.txt");
		writeNG(two, root+"two.txt");
		writeNG(three, root+"three.txt");
	}
	else {
		readNG(one, root+"one.txt");
		readNG(two, root+"two.txt");
		readNG(three, root+"three.txt");
	}

	while (true) {
		string x = "";
		cout << "starting word " << endl;
		cin >> x;
		x += " ";
		vector<string> words;
		for (int i = 0; i < 50; i++) {
			words.push_back(x);
			cout << x;
			map<string, int> a = find(one, x)->ng;
			map<string, int> b;
			map<string, int> c;
			if (i > 1) {
				b = find(two, words[i - 1] + words[i])->ng;
				if (i > 2) {
					c = find(three, words[i - 2] + words[i - 1] + words[i])->ng;
				}
			}

			pair<string, int> oneFind;
			pair<string, int> twoFind;
			pair<string, int> threeFind;

			if (a.size() > 0) {
				oneFind = get_max(a);
			}
			if (b.size() > 0) {
				twoFind = get_max(b);
			}
			if (c.size() > 0) {
				threeFind = get_max(c);
			}

			if (oneFind.first == twoFind.first || oneFind.first == threeFind.first) {
				x = oneFind.first;
			}
			else if (twoFind.first == threeFind.first && twoFind.first != "" && twoFind.first != " ") {
				x = twoFind.first;
			}
			else {
				x = oneFind.first;
				if (words.size() > 3) {
					if (threeFind.first != " " && threeFind.first != "") {
						x = threeFind.first;
					}
				}
				else if (words.size() > 2) {
					if (twoFind.first != " " && twoFind.first != "") {
						x = twoFind.first;
					}
				}
			}
			x += " ";
		}
		cout << endl;
		cout << endl;
	}
	return 0;
}


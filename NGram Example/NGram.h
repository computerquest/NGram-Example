#pragma once
#include <string>
#include <map>
using namespace std;

//ngram class
class NGram {
public:
	string phrase; //the stimulating word or phrase
	map<string, int> ng; //a map of the words and their occerences that follow phrase

	NGram(string souce); //constructor for the ngram that sets the source phrase


	void add(string to); //increments the value of the key to in map ng
	void add(string to, int value); //overload of the add function that allows an addition of more than one to key to in map ng

	string getMax(); //gets the maximum value in the map ng and returns its key
};
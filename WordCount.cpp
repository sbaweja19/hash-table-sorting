// WordCount.cpp

#include "WordCount.h"

using namespace std;

// Default constructor
WordCount::WordCount() {}

// Simple hash function. Do not modify.
size_t WordCount::hash(std::string word) const {
	size_t accumulator = 0;
	for (size_t i = 0; i < word.size(); i++) {
		accumulator += word.at(i);
	}
	return accumulator % CAPACITY;
}

int WordCount::getTotalWords() const {
	int total = 0;
	for(size_t i = 0; i < 100; i++){
		for(vector<pair<string, int> >::const_iterator j = table[i].begin(); j!=table[i].end(); j++){
			total += j->second;
		}
		
	}
	return total;
}

int WordCount::getNumUniqueWords() const {
	int words = 0;
	for (int i =0; i<100; i++){
		words += table[i].size();
	}
	return words;
}

int WordCount::getWordCount(std::string word) const {
	word = makeValidWord(word);
	int words = 0;
	for (int i = 0; i<100; i++){
		for(vector<pair<string, int> >::const_iterator j = table[i].begin(); j != table[i].end(); j++){
			if(j->first == word)
				words = j->second;
		}
	}
	return words;
}
	
int WordCount::incrWordCount(std::string word) {
	word = makeValidWord(word);
	if(word == "")
		return 0;

	size_t index = hash(word);
	int o = 0;
	bool find = false;
	for(vector<pair<string, int> >::iterator i = table[index].begin(); i != table[index].end(); i++){
		if(i->first == word){
			i->second++;
			find = true;
			o = i->second;
		}
	}
	if(!find){
		table[index].push_back(make_pair(word,1));
		o = 1;
	}
	return o;
}

int WordCount::decrWordCount(std::string word) {
	word = makeValidWord(word);
	if (word == "")
		return -1;

	size_t index = hash(word);
	int o = 0;
	bool find = false;
	for(vector<pair<string, int> >::iterator i = table[index].begin(); i != table[index].end(); i++){
		if(i->first == word){
			if(i->second > 1){
				i->second--;
				o = i->second;
				find = true;

			}
			else if(i->second ==1){
				table[index].erase(i);
				o = 0;
				find = true;
				
				break;
			}
		}
	}
	if(!find){
		o=-1;
	}
	return o;
}


bool WordCount::isWordChar(char c) {
	if(!isalpha(c) && c != '-' && c != '\'')
		return false;

	else return true;
}

std::string WordCount::makeValidWord(std::string word) {
	std::string valid = word;
	for (unsigned long i = 0; i < valid.size(); i++){
		if(!isWordChar(valid[i])){
			valid.erase(i, 1);
			i--;
		}
	}
	

	while(valid.back() == '-' || valid.back() == '\''){
		valid.erase(valid.size()-1, 1);
	}

	while(valid.front() == '-' || valid.front() == '\''){
		valid.erase(0, 1);
	}

	for (unsigned long i = 0; i < valid.size(); i++){
		valid[i] = tolower(valid[i]);
	}
	return valid;
}

void WordCount::dumpWordsSortedByWord(std::ostream &out) const {
	vector<pair<string, int> > list;

	for (int i = 0; i<100; i++){
		for(vector<pair<string, int> >::const_iterator j = table[i].begin(); j != table[i].end(); j++){
			list.push_back(make_pair(j->first, j->second));
		}
	}

	pair<string, int> temp;
	bool swapped;

	for (int i = list.size() - 1; i > 0; i--) {
		swapped = false;
		for (int j = 0; j < i; j++) {
			if (list[j].first < list[j+1].first) {
				// swap
				temp = list[j];
				list[j] = list[j+1];
				list[j+1] = temp;
				swapped = true;
			}
		}
		if (!swapped) {
			// in order
			break;
		}
	}

	for(unsigned long i = 0; i < list.size(); i++){
		out << list[i].first << ',' << list[i].second << endl;
		//if(i < list.size() - 1)
		//	out << endl;
	}
	
}

void WordCount::dumpWordsSortedByOccurence(std::ostream &out) const {
	vector<pair<string, int> > list;
	for (int i = 0; i<100; i++){
		for(vector<pair<string, int> >::const_iterator j = table[i].begin(); j != table[i].end(); j++){
			list.push_back(make_pair(j->first, j->second));
		}
	}

	pair<string, int> temp;
	bool swapped;

	for (int i = list.size() - 1; i > 0; i--) {
		swapped = false;
		for (int j = 0; j < i; j++) {
			if (list[j].second > list[j+1].second) {
				// swap
				temp = list[j];
				list[j] = list[j+1];
				list[j+1] = temp;
				swapped = true;
			}
			else if (list[j].second == list[j+1].second && list[j].first > list[j+1].first){
				// swap
				temp = list[j];
				list[j] = list[j+1];
				list[j+1] = temp;
				swapped = true;
			}
		}
		if (!swapped) {
			// in order
			break;
		}
	}

	for(unsigned long i = 0; i < list.size(); i++){
		out << list[i].first << ',' << list[i].second << endl;
		//if(i < list.size() - 1)
		//	out << endl;
	}
	return;
}

void WordCount::addAllWords(std::string text) {

	size_t start = 0;
	size_t end = 0;
	while(end < text.size()){
		if(isWordChar(text[end])){
			start = end;
			while(start < text.size() && (text[start] != ' ' && text[start] != '\n' && text[start]!= '\t')){
				start++;
			}
			string a = text.substr(end, start-end);
			this->incrWordCount(a);
			end = start;
		}
		else
			end++;
	}
	
}


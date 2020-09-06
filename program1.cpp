#include <iostream>
#include <string> 
#include<tr1/unordered_map>
#include <bits/stdc++.h> 
#include <fstream>
#include <sstream>
#include <vector>


using namespace std;

// Structure for Trie 
struct Trie { 
    bool isEndOfWord; 
    tr1::unordered_map<char, Trie*> map; 
    string frequency; 
}; 

// Function to create a new Trie node 
Trie* getNewTrieNode() 
{ 
    Trie* node = new Trie; 
    node->isEndOfWord = false; 
    return node; 
} 

// Function to insert a word with its frequency 
// in the dictionary built using a Trie 
void insert(Trie*& root, const string& str, 
             const string& frequency) 
{ 
  
    // If root is null 
    if (root == NULL) 
        root = getNewTrieNode(); 
  
    Trie* temp = root; 
    for (int i = 0; i < str.length(); i++) { 
        char x = str[i]; 
  
        // Make a new node if there is no path 
        if (temp->map.find(x) == temp->map.end()) 
            temp->map[x] = getNewTrieNode(); 
  
        temp = temp->map[x]; 
    } 
  
    // Mark end of word and store the meaning 
    temp->isEndOfWord = true; 
    temp->frequency = frequency; 
} 
 
// Function to search a word in the Trie 
// and return its meaning if the word exists 
string getFrequency(Trie* root, const string& word) 
{ 
  
    // If root is null i.e. the dictionary is empty 
    if (root == NULL) 
        return ""; 
  
    Trie* temp = root; 
  
    // Search a word in the Trie 
    for (int i = 0; i < word.length(); i++) { 
        temp = temp->map[word[i]]; 
        if (temp == NULL) 
            return ""; 
    } 
  
    // If it is the end of a valid word stored 
    // before then return its meaning 
    if (temp->isEndOfWord) 
        return "Yes, " + temp->frequency; 
    return "No"; 
} 

int main() {
	string path;
    cout << "Enter the Dictionary's path" << endl;
    getline(cin, path);
    
    Trie* root = NULL; 
    
//    path = "C:/Users/goelp/Desktop/Bobble/EnglishDictionary.csv";
    ifstream  data(path.c_str());
    string line;
    vector<vector<string> > parsedCsv;
    while(getline(data,line))
    {
        stringstream lineStream(line);
        string cell;
        vector<string> parsedRow;
        while(getline(lineStream,cell,','))
        {
            parsedRow.push_back(cell);
        }

        parsedCsv.push_back(parsedRow);
    }
    
//    cout << parsedCsv.size();

	for (int i = 0; i < parsedCsv.size(); i++)
	{
		insert(root, parsedCsv[i][0], parsedCsv[i][1]);
	}	
	
	string word;
	cout << "Enter the word to search"<< endl;
	cin >> word;
	
	cout << getFrequency(root, word);
    
    return 0;
}

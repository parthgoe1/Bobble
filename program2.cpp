#include <iostream>
#include <string> 
#include<tr1/unordered_map>
#include <bits/stdc++.h> 
#include <fstream>
#include <sstream>
#include <vector>
#define alpha_size 5000

using namespace std;

// Trie node 
struct TrieNode  
{ 
    struct TrieNode* children[alpha_size]; 
  	string frequency;
    bool isLeaf; 
}; 

// Returns new trie node (initialized to NULLs) 
struct TrieNode* createNode() 
{ 
    struct TrieNode* pNode = new TrieNode; 
  
    for (int i = 0; i < alpha_size; i++) 
        pNode->children[i] = NULL; 
  
    pNode->isLeaf = false; 
  
    return pNode; 
}; 

// function to insert a node in Trie 
void insert_node(struct TrieNode* root, const string& key, const string& frequency) 
{ 
    int level; 
    int length = key.size(); 
    struct TrieNode* pCrawl = root; 
  
    for (level = 0; level < length; level++)  
    { 
        int index = key[level] - 'a'; 
  
        if (pCrawl->children[index] == NULL) 
            pCrawl->children[index] = createNode(); 
  
        pCrawl = pCrawl->children[index]; 
    } 
  
    pCrawl->isLeaf = true;
	pCrawl->frequency = frequency;
} 

// function to check if current node is leaf node or not 
bool isLeafNode(struct TrieNode* root) 
{ 
    return root->isLeaf != false; 
} 

// function to display the content of Trie 
void display(struct TrieNode* root, char str[], int level, const string& frequency) 
{ 
    // If node is leaf node, it indicates end 
    // of string, so a null character is added 
    // and string is displayed 
    if (isLeafNode(root))  
    { 
    	if (frequency == root->frequency){
    		str[level] = '\0'; 
        	cout << str << endl; 
		}
    } 
  
    int i; 
    for (i = 0; i < alpha_size; i++)  
    { 
        // if NON NULL child is found 
        // add parent key to str and 
        // call the display function recursively 
        // for child node 
        if (root->children[i])  
        { 
            str[level] = i + 'a'; 
            display(root->children[i], str, level + 1, frequency); 
        } 
    } 
} 

int main() {
	string path;
    cout << "Enter the Dictionary's path" << endl;
    getline(cin, path);
    
    struct TrieNode* root = createNode(); 
    
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
    

	for (int i = 0; i < parsedCsv.size(); i++)
	{
		
		stringstream ss;
		ss << i;
		string s;
		ss >> s;

		insert_node(root, parsedCsv[i][0], s);

	}	
	
	string num;
	cout << "Enter the number to search"<< endl;
	cin >> num;
	int level = 0; 
	char str[20]; 
	
	display(root, str, level, num);
    
    return 0;
}

#include <iostream>
#include <string>
#include <vector>
#include <utility>
using namespace std;


template <class T>
class Trie {    
private:
    // Define TrieNode for the first phase (Trie)
    /* DO NOT CHANGE */
    struct TrieNode {
        static const int ALPHABET_SIZE = 128;
        TrieNode* children[ALPHABET_SIZE];
        char keyChar;
        bool isEndOfKey;
        T* data;

        TrieNode(char c) : keyChar(c), isEndOfKey(false), data(NULL) {

                for (int i = 0; i< ALPHABET_SIZE; i++) {
                children[i] = NULL;
                
            }
            
            }
    };

    TrieNode* root;

public: // Do not change.

    Trie(); 
    ~Trie();
    
    Trie& insert(const string& username); 
    void remove(std::string username);
    T* search(std::string username); 
    void findStartingWith(std::string prefix, std::vector<T*> &results); 
    void wildcardSearch(const std::string &wildcardKey, std::vector<T*> &results); 
    void print(); 

private: // you may add your own utility member functions here.
    void print(const std::string& primaryKey); // Do not change this line.
    void printTrie(TrieNode* node, const std::string& currentKey); // Do not change this line.
    void deleteTrieNode(TrieNode* node);
    void wildcardHelper(TrieNode* node, const std::string &wildcardKey, int ind, std::vector<T*> &results);
};
/* DO NOT CHANGE */
template <class T>
Trie<T>::Trie() : root(new TrieNode('\0')) {}

template <class T>
Trie<T>::~Trie() {
    /* IMPLEMENT THIS */
    deleteTrieNode(root);
}

template <class T>
Trie<T>& Trie<T>::insert(const string& key) {
    /* IMPLEMENT THIS */
    TrieNode* temp = root;
    for (int i = 0; i < key.length(); i++) {
        int index = key[i];
        if (!temp->children[index]) {
            temp->children[index] = new TrieNode(index);
        }
        temp = temp->children[index];
    }
    temp->isEndOfKey = true;
    temp->data = new T(key);
    return *this;
}

template <class T>
T* Trie<T>::search(std::string username) {
    /* IMPLEMENT THIS */
    TrieNode* temp = root;
    int i, finder;
    for(i = 0; i<username.length(); i++){
        finder = username[i];
        if(!temp->children[finder]){
            return NULL;
        }
        temp = temp->children[finder];
    }
    if(temp->isEndOfKey) return temp->data;
    else return NULL;
}

template <class T>
void Trie<T>::remove(std::string username) {
    /* IMPLEMENT THIS */
    TrieNode* temp = root;
    if(temp){
        int i, finder;
        for(i = 0; i<username.length(); i++){
            finder = username[i];
            if(!temp->children[finder]){
                return;
            }
            temp = temp->children[finder];
        }
        if(temp->isEndOfKey) temp->isEndOfKey = false;
        return;
    }
    else return;

}

template <class T>
void Trie<T>::findStartingWith(string prefix,vector<T*> &results) {
/* IMPLEMENT THIS */
    TrieNode* temp = root;
    string newPre;
    if(temp && prefix.length()!= 0){
        int i, finder, j;
        for(i = 0; i<prefix.length(); i++){
            finder = prefix[i];
            if((!temp->children[finder])) return;
            temp = temp->children[finder];
        }
        if(temp->isEndOfKey == true) results.push_back(temp->data);
        for (j = 0; j < root->ALPHABET_SIZE; j++) {
            if (temp->children[j] != NULL) {
                newPre = prefix + temp->children[j]->keyChar;
                findStartingWith(newPre, results);
            }
        }
        
    }
    
}

template <class T>
void Trie<T>::wildcardSearch(const std::string &wildcardKey, std::vector<T*> &results) {
/* IMPLEMENT THIS */
        
    int i;
    for(i = 0; i < root->ALPHABET_SIZE; i++) {
        if(root->children[i]) {
            wildcardHelper(root->children[i], wildcardKey, 0, results);
        }
    }
}

template <class T>
void Trie<T>::wildcardHelper(TrieNode* node, const std::string &wildcardKey, int ind, std::vector<T*> &results) {
    if(wildcardKey.length() <= ind || node == NULL) {
        if (node && node->isEndOfKey) {
            results.push_back((node->data));
        }
        return;
    }
    if(wildcardKey[ind] == '*') {
        if(ind == wildcardKey.length() - 1) {
            if(node->isEndOfKey) results.push_back(node->data);
        
            int i;
            for(i = 0; i < node->ALPHABET_SIZE; i++) {
                if(node->children[i]) {
                    wildcardHelper(node->children[i], wildcardKey, ind, results);
                }
            }
            
        }
        else {
            int i;
            for(i = 0; i < node->ALPHABET_SIZE; i++) {
                if(node->children[i]) {
                    wildcardHelper(node->children[i], wildcardKey, ind, results);
                    wildcardHelper(node->children[i], wildcardKey, ind + 1, results);
                    
                }
            }
        }
    }
    else if(wildcardKey[ind] == '?') {
        if(ind == wildcardKey.length() - 1) {
            if(node->isEndOfKey) results.push_back(node->data);
        }
        else {
            int i;
            for(i = 0; i < node->ALPHABET_SIZE; i++) {
                if(node->children[i]) {
                    wildcardHelper(node->children[i], wildcardKey, ind + 1, results);
                }
            }
        }
    }
    else {
        if(ind == wildcardKey.length() -1 ) {
            if(node->isEndOfKey && node->keyChar == wildcardKey[ind]) results.push_back(node->data);
        }
        else {
            if(node->keyChar == wildcardKey[ind]) {
                int i;
                for(i = 0; i < node->ALPHABET_SIZE; i++) {
                    if(node->children[i]) {
                        wildcardHelper(node->children[i], wildcardKey, ind + 1, results);
                    }
                }
            }
            
        }
    }
}


/* DO NOT CHANGE */
template<class T>
void Trie<T>::print() {
    print("");
}
/* DO NOT CHANGE */
template <class T>
void Trie<T>::print(const std::string& primaryKey) {
    if (primaryKey.empty()) {
        // Print the entire tree.
        printTrie(root, "");
    } else {
        // Print specific keys.
        TrieNode* primaryNode = root;
        for (int i = 0; i < primaryKey.length(); i++) {
            
            int index = primaryKey[i];
            if (!primaryNode->children[index]) {
                std::cout << "{}" << std::endl; // Primary key not found, nothing to print.
                return ;
            }
            primaryNode = primaryNode->children[index];
        }

        }
    }
/* DO NOT CHANGE */
template <class T>
void Trie<T>::printTrie(TrieNode* node, const std::string& currentKey) {
    if (!node) {
        return;
    }
    if (node->isEndOfKey) {
        std::cout << currentKey <<std::endl;
        std::cout << "Watched Movies:" << std::endl;
        if(node->data) {
            node->data->printMovies();
        }
    }
    for (int i = 0; i < root->ALPHABET_SIZE; ++i) {
        if (node->children[i]) {
            printTrie(node->children[i], currentKey + static_cast<char>(i));
        }
    }
}

template <class T>
void Trie<T>::deleteTrieNode(TrieNode* node) {
    if(node) {
        for (int i = 0; i < root->ALPHABET_SIZE; i++) {
            if (node->children[i]) {
                deleteTrieNode(node->children[i]);
            }
        }
        delete node->data;
        delete node;
    }
    else return;
}




#include <string>
#include <vector>
#include <iostream>
#include <utility>
#include <algorithm>
using namespace std;

// do not add any other library.
// modify parts as directed by assignment text and comments here.

template <class T>
class BST {
private:
    // Define TreeNode for the second phase (Binary Search Tree)
    /* DO NOT CHANGE */
    struct TreeNode {
        std::string key;
        T data;
        TreeNode* left;
        TreeNode* right;
        TreeNode(const std::string &k, const T& value) : key(k), data(value), left(NULL), right(NULL) {}
        
    };

    TreeNode* root;


public: // Do not change.

    BST();
    ~BST();
    TreeNode* getRoot() { return root; }
    bool isEmpty() { return root == NULL; }

    BST& insert(const std::string key, const T& value);
    bool search(std::string value) const;
    void remove(std::string value);
    BST<T>* merge(BST<T>* bst);
    BST<T>* intersection(BST<T>* bst);
    std::vector<TreeNode> tree2vector(TreeNode* root);
    void print();
    
private:// you may add your own utility member functions here.

    void print(TreeNode* node, std::string indent, bool last, bool isLeftChild); // Do not change.
    void deleteNode(TreeNode* node);
    void removeNode(TreeNode** node, std::string key);
    T getMin(TreeNode* node);
    std::string getMinKey(TreeNode* node);
    void tree2vectorHelp(TreeNode* node, std::vector<TreeNode>& result );
};

    // Constructor
    template <class T>
    BST<T>::BST() : root(NULL) {}

    // Destructor
    template <class T>
    BST<T>::~BST() {
    /* IMPLEMENT THIS */
        if(root){
            deleteNode(root);
        }
    }

    // Insert function for BST.    
    template <class T>
    BST<T>& BST<T>::insert(const string key, const T& value) {
             /* IMPLEMENT THIS */
        TreeNode* node = new TreeNode(key,value);
        TreeNode* temp = root;
        TreeNode* temp2;

        if(root == NULL){
            root = node;
            getRoot();
        }
        else{
            while (temp != NULL) {
                temp2 = temp;
                if (key < temp->key) temp = temp->left;
                else if (key > temp->key) temp = temp->right;
                else delete node;
            }
        
            if (key < temp2->key)  temp2->left = node;
            else temp2->right = node;
            getRoot();
        }
    }
    
    // Search function for BST.
    template <class T>
    bool BST<T>::search(std::string value) const {
     /* IMPLEMENT THIS */
     TreeNode* temp = root;
        if(root){
            while(temp){
                if(temp->key == value) return true;
                else if(temp->key<value) temp = temp->right;
                else temp = temp->left;
            }
        }
        else return false;
        return false;
    }
    
    
    // Remove a node from BST for given key. If key not found, do not change anything.
    template <class T>
    void BST<T>::remove(std::string key) {
        /* IMPLEMENT THIS */
        removeNode(&root, key);
    }
    
    // A helper function for converting a BST into vector.
    template <class T>
    vector<typename BST<T>::TreeNode> BST<T>::tree2vector(TreeNode* root) {
        vector<TreeNode> result;
        TreeNode* current = root;
        if(current) tree2vectorHelp(current, result);
        return result;
    }
    
    // Merge two BST's and return merged BST.
    template <class T>
    BST<T>* BST<T>::merge(BST<T>* bst) {
    /* IMPLEMENT THIS */
        BST<T>* merged = new BST<T>();
        
        std::vector<TreeNode> first = tree2vector(getRoot());
        std::vector<TreeNode> second = tree2vector(bst->getRoot());
        if (first.size()==0 && second.size()==0) return NULL;
        else if(first.size() == 0) return bst;
        else if(second.size() == 0) return this;
        
        int i = 0, j = 0;
        
        
        
        while(i < first.size() && j < second.size()) {
            if(first[i].key < second[j].key) {
                merged->insert(first[i].key, first[i].data);
                i++;
            }
            else {
                merged->insert(second[j].key, second[j].data);
                j++;
            }
        }

        while(i < first.size()) {
            merged->insert(first[i].key, first[i].data);
            i++;
        }
        
        while(j < second.size()) {
            merged->insert(second[j].key, second[j].data);
            j++;
        }
        
        return merged;
    }
        
    // Intersect two BST's and return new BST.
    template <class T>
    BST<T>* BST<T>::intersection(BST<T>* bst) {
    /* IMPLEMENT THIS */
        BST<T>* sect = new BST<T>();
        
        std::vector<TreeNode> first = tree2vector(getRoot());
        std::vector<TreeNode> second = tree2vector(bst->getRoot());
        if (first.size()==0 || second.size()==0) return NULL;
        
        int i, j;
        
        for(i = 0; i < first.size(); i++) {
            for(j = 0; j < second.size(); j++) {
                if(first[i].key == second[j].key) {
                    sect->insert(first[i].key, first[i].data);
                }
            }
        }

        return sect;
    }
    
    /* DO NOT CHANGE */
    template <class T>
    void BST<T>::print() {
        print(root, "", true, false);
    
    }
    
    /* DO NOT CHANGE */
    template <class T>
    void BST<T>::print(TreeNode* node, string indent, bool last, bool isLeftChild) {
        if (node != NULL) {
            cout << node->key << endl;
            print(node->left, indent, false, true);
            print(node->right, indent, true, false);
        }
    
    }

template <class T>
void BST<T>::deleteNode(TreeNode* node){
    if(node){
        deleteNode(node->right);
        deleteNode(node->left);
        delete node;
    }
}

template <class T>
void BST<T>:: removeNode(TreeNode** node, std::string key){
    if(*node){
        if(key < (*node)->key) removeNode(&((*node)->left), key);
        else if(key > (*node)->key) removeNode(&((*node)->right), key);
        else{
            if((*node)->left == NULL){
                TreeNode* temp = *node;
                (*node) = (*node)->right;
                delete temp;
            }
            else if((*node)->right == NULL) {
                TreeNode* temp = *node;
                (*node) = (*node)->left;
                delete temp;
            }
            else{
                (*node)->data = getMin((*node)->right);
                (*node)->key = getMinKey((*node)->right);
                string newKey = getMinKey((*node)->right);
                removeNode(&((*node)->right), newKey);
            }
        }
    }
    else return;
}

template <class T>
T BST<T>:: getMin(TreeNode* node){
    if(node->left == NULL) return node->data;
    else getMin(node->left);
}

template <class T>
std::string BST<T>::getMinKey(TreeNode* node){
    if(node->left == NULL) return node->key;
    else getMinKey(node->right);
}

template <class T>
void BST<T>::tree2vectorHelp(TreeNode* node, std::vector<TreeNode>& result) {
    if (node == NULL) return;
    else{
        tree2vectorHelp(node->left, result); 
        result.push_back(*node); 
        tree2vectorHelp(node->right, result);
    }
}
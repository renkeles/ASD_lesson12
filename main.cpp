#include <iostream>

typedef struct Node{
    size_t key;
    struct Node* left;
    struct Node* right;
} TreeNode;

TreeNode* treeInsert(TreeNode *treeNode, size_t data){
    TreeNode* newNode;
    newNode = new TreeNode;
    newNode->key = data;
    newNode->left = nullptr;
    newNode->right = nullptr;
    TreeNode *current = treeNode;
    TreeNode *parent = treeNode;
    if(treeNode == nullptr){
        treeNode = newNode;
    }else{
        while (1){
            parent = current;
            if(current->key > data){
                current = current->left;
                if(current == nullptr){
                    parent->left = newNode;
                    return treeNode;
                }
            }else{
                current = current->right;
                if(current == nullptr){
                    parent->right = newNode;
                    return treeNode;
                }
            }
        }
    }
    return treeNode;
}

void printTree(TreeNode *root){
    if (root){
        std::cout << root->key;
        if(root->left || root->right){
            std::cout << "(";
            if(root->left){
                printTree(root->left);
            }else{
                std::cout << "*";
            }
            std::cout << ",";
            if(root->right){
                printTree(root->right);
            }else{
                std::cout << "*";
            }
            std::cout << ")";
        }
    }
}

TreeNode* getSuccessor(TreeNode* node){
    TreeNode *current = node->right;
    TreeNode *parent = node;
    TreeNode *successor = node;

    while(current != nullptr){
        parent = successor;
        successor = current;
        current = current->left;
    }
    if(successor != node->right){
        parent->left = successor->right;
        successor->right = node->right;
    }
    return successor;
}

bool remove(TreeNode* root, size_t key){
    TreeNode *current = root;
    TreeNode *parent = root;
    bool isLeftChild = true;

    while(current->key != key){
        parent = current;
        if(key < current->key){
            current = current->left;
            isLeftChild = true;
        }else{
            current = current->right;
            isLeftChild = false;
        }
        if(current == nullptr){
            return false;
        }
    }
    if(current->left == nullptr && current->right == nullptr){
        if(current == root){
            root = nullptr;
        }else if(isLeftChild){
            parent->left = nullptr;
        }else{
            parent->right = nullptr;
        }
    }else if(current->right == nullptr){
        if(isLeftChild){
            parent->left = current->left;
        }else{
            parent->right = current->left;
        }
    }else if(current->left == nullptr){
        if(isLeftChild){
            parent->left = current->right;
        }else{
            parent->right = current->right;
        }
    }else{
        TreeNode* successor = getSuccessor(current);
        if(current == root){
            root = successor;
        }else if(isLeftChild){
            parent->left = successor;
        }else{
            parent->right = successor;
        }
        successor->left = current->left;
    }
    return true;
}

void setTreeNodeList(TreeNode** treeNodeList, const size_t count, const size_t size){
    for(size_t i = 0; i < count; i++){
        treeNodeList[i] = new TreeNode;
        treeNodeList[i] = nullptr;
        //treeNodeList[i] = treeInsert(treeNodeList[i], (rand() % 100));
        treeNodeList[i] = treeInsert(treeNodeList[i], 49);
        for(size_t j = 1; j < size; j++){
            treeInsert(treeNodeList[i], (rand() % 100));
        }
    }
}

void preOrderTravers(TreeNode* root){
    if(root){
        std::cout.width(5);
        std::cout << root->key;
        preOrderTravers(root->left);
        preOrderTravers(root->right);
    }
}

void inOrderTravers(TreeNode* root){
    if(root){
        inOrderTravers(root->left);
        std::cout.width(5);
        std::cout << root->key;
        inOrderTravers(root->right);
    }
}

void postOrderTravers(TreeNode* root){
    if(root){
        postOrderTravers(root->left);
        postOrderTravers(root->right);
        std::cout.width(5);
        std::cout << root->key;
    }
}


void testTree(){
    TreeNode *tree = nullptr;
    tree = treeInsert(tree, 10);
    treeInsert(tree, 8);
    treeInsert(tree, 19);
    treeInsert(tree, 5);
    treeInsert(tree, 9);
    treeInsert(tree, 16);
    treeInsert(tree, 21);
    printTree(tree);
    std::cout << std::endl;
    remove(tree, 5);
    printTree(tree);
    std::cout << std::endl;
    remove(tree, 19);
    printTree(tree);
    std::cout << std::endl;
    remove(tree, 8);
    printTree(tree);
    treeInsert(tree, 10);
    std::cout << std::endl;
    printTree(tree);
    treeInsert(tree, 8);
    treeInsert(tree, 19);
    treeInsert(tree, 5);
    treeInsert(tree, 9);
    treeInsert(tree, 16);
    treeInsert(tree, 21);
    std::cout << std::endl;
    printTree(tree);
    std::cout << std::endl;
    preOrderTravers(tree);
    std::cout << std::endl;
    inOrderTravers(tree);
    std::cout << std::endl;
    postOrderTravers(tree);
    delete tree;
}



void treeNodeList(){
    const size_t count = 10;
    const size_t size = 10;
    TreeNode** treeNodeList = new TreeNode*[count];
    setTreeNodeList(treeNodeList, count, size);

    /*
    for(size_t i = 0; i < count; i++){
        printTree(treeNodeList[i]);
        std::cout << std::endl;
    }
    */
    /*
    for(size_t i = 0; i < count; i++){
        //preOrderTravers(treeNodeList[i]);
        //inOrderTravers(treeNodeList[i]);
        postOrderTravers(treeNodeList[i]);
        std::cout << std::endl;
    }
    */

    delete[] treeNodeList;
}

int main() {
    testTree();
    //treeNodeList();


    return 0;
}

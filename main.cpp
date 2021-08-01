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
        while (current->key != data){
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
                std::cout << "null";
            }
            std::cout << ",";
            if(root->right){
                printTree(root->right);
            }else{
                std::cout << "null";
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

int main() {
    TreeNode *tree = treeInsert(tree, 10);
    treeInsert(tree, 8);
    treeInsert(tree, 15);
    treeInsert(tree, 6);
    treeInsert(tree, 1);
    treeInsert(tree, 19);
    treeInsert(tree, 2);
    treeInsert(tree, 5);
    printTree(tree);
    std::cout << std::endl;
    remove(tree, 6);
    printTree(tree);
    std::cout << std::endl;
    remove(tree, 1);
    printTree(tree);


    return 0;
}

#include <string>
#include <iostream>
#include <cstring>

struct Tnode {
    std::string word;
    int count;
    Tnode* left;
    Tnode* right;
};

struct Tnode_cstyle {
    const char* word;
    int count;
    Tnode_cstyle* left;
    Tnode_cstyle* right;
};

Tnode* enter_new_word(Tnode* node, std::string str)
{
    if (node == nullptr) {
        node = new Tnode{str, 1, nullptr, nullptr};
    } else if (str.compare(node->word) == 0) {
        ++node->count;
    } else if (str.compare(node->word) < 0) {
        node->left = enter_new_word(node->left, str);
    } else {
        node->right = enter_new_word(node->right, str);
    }

    return node;
}

void delete_all(Tnode * node)
{
    if (node == nullptr) {
        return;
    }
    if (node->left) {
        delete_all(node->left);
    }
    if (node->right) {
        delete_all(node->right);
    }
    delete node;
    node = nullptr;
}

void print_tree(Tnode* node)
{
    if (node == nullptr) {
        return;
    }
    if (node->left) {
        print_tree(node->left);
    }
    std::cout << node->word << " " << node->count << "\n";
    if (node->right) {
        print_tree(node->right);
    }
}

Tnode_cstyle* enter_new_long_word(Tnode_cstyle* node, const char* str, int n)
{
    if (node == nullptr) {
        char* word = new char[n + 1];
        strcpy(word, str);
        node = new Tnode_cstyle{word, 1, nullptr, nullptr};
    } else if (strcmp(str, node->word) == 0) {
        ++node->count;
    } else if (strcmp(str, node->word) < 0) {
        node->left = enter_new_long_word(node->left, str, n);
    } else {
        node->right = enter_new_long_word(node->right, str, n);
    }

    return node;
}

void delete_all_cstyle(Tnode_cstyle* node)
{
    if (node == nullptr) {
        return;
    }
    if (node->left) {
        delete_all_cstyle(node->left);
    }
    if (node->right) {
        delete_all_cstyle(node->left);
    }
    delete[] node->word;
    delete node;
    node = nullptr;
}

void print_tree_cstyle(Tnode_cstyle* node)
{
    if (node == nullptr) {
        return;
    }
    if (node->left) {
        print_tree_cstyle(node->left);
    }
    std::cout << node->word << " " << node->count << "\n";
    if (node->right) {
        print_tree_cstyle(node->right);
    }
}

int main()
{
    Tnode* root = nullptr;
    root = enter_new_word(root, "whatsup");
    enter_new_word(root, "kuku");
    enter_new_word(root, "yup");
    print_tree(root);
    delete_all(root);

    std::cout << "--------------\n";
    Tnode_cstyle* new_root = nullptr;
    new_root = enter_new_long_word(new_root, "blabla", strlen("blabla"));
    new_root = enter_new_long_word(new_root, "aaaaa", strlen("aaaaa"));
    new_root = enter_new_long_word(new_root, "kuda", strlen("kuda"));
    new_root = enter_new_long_word(new_root, "kuda", strlen("kuda"));
    print_tree_cstyle(new_root);
    delete_all_cstyle(new_root);
}
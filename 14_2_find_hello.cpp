#include <iostream>
#include <string>

using namespace std;

struct node
{
    string key_value;
    node *left;
    node *right;
};

struct Not_found
{
};

class Btree
{
  private:
    void destroy_tree(node *leaf);
    void insert(string key, node *leaf);
    node *find(string key, node *leaf);

    node *root;

  public:
    Btree() { root = nullptr; }
    ~Btree() { destroy_tree(); }

    void insert(string key);
    node *find(string key) { return find(key, root); }
    void destroy_tree() { destroy_tree(root); }
};

void Btree::destroy_tree(node *leaf)
{
    if (leaf != nullptr)
    {
        destroy_tree(leaf->left);
        destroy_tree(leaf->right);
        delete leaf;
    }
}

void Btree::insert(string key, node *leaf)
{
    if (key < leaf->key_value)
    {
        if (leaf->left != nullptr)
            insert(key, leaf->left);
        else
        {
            leaf->left = new node;
            leaf->left->key_value = key;
            leaf->left->left = nullptr;
            leaf->left->right = nullptr;
        }
    }
    else if (key >= leaf->key_value)
    {
        if (leaf->right != nullptr)
            insert(key, leaf->right);
        else
        {
            leaf->right = new node;
            leaf->right->key_value = key;
            leaf->right->left = nullptr;
            leaf->right->right = nullptr;
        }
    }
}

node *Btree::find(string key, node *leaf)
{
    if (leaf != nullptr)
    {
        if (key == leaf->key_value)
            return leaf;
        if (key < leaf->key_value)
            return find(key, leaf->left);
        else
            return find(key, leaf->right);
    }
    else
        throw Not_found{};
}

void Btree::insert(string key)
{
    if (root != nullptr)
        insert(key, root);
    else
    {
        root = new node;
        root->key_value = key;
        root->left = nullptr;
        root->right = nullptr;
    }
}

int main()
{
    try
    {
        Btree mytree;
        mytree.insert("mama");
        mytree.insert("mia");
        mytree.insert("hello");
        cout << mytree.find("hello")->key_value << '\n';
        cout << mytree.find("hellllo")->key_value << '\n';
    }
    catch (Not_found e)
    {
        cerr << "Not found" << '\n';
    }
}
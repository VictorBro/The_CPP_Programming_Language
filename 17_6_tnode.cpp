#include "17_6_tnode.h"

Tree::Tnode *Tree::enter_new_word(Tnode *node, std::string str)
{
    if (node == nullptr)
    {
        node = new Tnode{str, 1};
    }
    else if (str.compare(node->word_) == 0)
    {
        ++node->count_;
    }
    else if (str.compare(node->word_) < 0)
    {
        node->left_ = enter_new_word(node->left_, str);
    }
    else
    {
        node->right_ = enter_new_word(node->right_, str);
    }
    return node;
}

void Tree::delete_all(Tnode *node)
{
    if (node == nullptr)
    {
        return;
    }
    if (node->left_)
    {
        delete_all(node->left_);
    }
    if (node->right_)
    {
        delete_all(node->right_);
    }
    delete node;
    node = nullptr;
}

void Tree::print_tree(Tnode *node, std::ostream &output)
{
    if (node == nullptr)
    {
        return;
    }
    if (node->left_)
    {
        print_tree(node->left_, output);
    }
    output << node->word_ << " " << node->count_ << "\n";
    if (node->right_)
    {
        print_tree(node->right_, output);
    }
}

Tree::Tnode *Tree::insert(std::string str)
{
    root_ = enter_new_word(root_, str);
    return root_;
}

void Tree::print_to(std::ostream &output)
{
    print_tree(root_, output);
}
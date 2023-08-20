#include "17_6_tnode.h"

using namespace std;

int main()
{
    Tree my_tree{};
    my_tree.insert("whatsup");
    my_tree.insert("kuku");
    my_tree.insert("yup");
    my_tree.print_to(cout);
}
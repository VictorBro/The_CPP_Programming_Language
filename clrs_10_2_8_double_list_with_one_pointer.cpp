#include <iostream>

using namespace std;

struct Node
{
    int data;
    Node *np;
};

class DoubleLinkedList
{
    Node *head;
    Node *tail;

  public:
    DoubleLinkedList() : head{nullptr}, tail{nullptr} {}
    ~DoubleLinkedList();
    void insert(int val);
    void remove(int val);
    Node *search(int val) const;
    void reverse_list();
    Node *get_head() const { return head; }
    Node *get_tail() const { return tail; }
};

Node *xor_prev_next(Node *prev, Node *next)
{
    uintptr_t x = reinterpret_cast<uintptr_t>(prev);
    uintptr_t y = reinterpret_cast<uintptr_t>(next);
    return reinterpret_cast<Node *>(x ^ y);
}

ostream &operator<<(ostream &os, const DoubleLinkedList &list)
{
    Node *head = list.get_head();
    Node *tail = list.get_tail();
    if (head == nullptr)
    {
        os << "head : nullptr, tail : ";
        if (tail == nullptr)
        {
            os << "nullptr";
        }
        else
        {
            os << tail;
        }
    }
    else
    {
        Node *prev = nullptr;
        Node *curr = head;
        Node *next;
        while (curr != nullptr)
        {
            if (curr != head)
            {
                os << ", ";
            }
            os << curr->data;
            next = xor_prev_next(prev, curr->np);
            prev = curr;
            curr = next;
        }
    }
    return os;
}

DoubleLinkedList::~DoubleLinkedList()
{
    Node *prev = nullptr;
    Node *curr = head;
    Node *next;

    cout << "\ndestruction:\n";
    while (curr != nullptr)
    {
        next = xor_prev_next(prev, curr->np);
        prev = curr;
        curr = next;
        cout << "deleting " << prev->data << '\n';
        delete prev;
    }
    head = nullptr;
}

void DoubleLinkedList::insert(int val)
{
    Node *temp = new Node;
    temp->data = val;
    temp->np = xor_prev_next(nullptr, head);

    if (head != nullptr)
    {
        head->np = xor_prev_next(temp, head->np);
    }
    else // initialize tail after first insert
    {
        tail = temp;
    }
    head = temp;
}

void DoubleLinkedList::remove(int val)
{
    Node *prev = nullptr;
    Node *curr = head;
    Node *next;

    while (curr != nullptr)
    {
        next = xor_prev_next(prev, curr->np);
        if (curr->data == val)
        {
            if (prev != nullptr)
            {
                Node *prev_of_prev = xor_prev_next(prev->np, curr);
                prev->np = xor_prev_next(prev_of_prev, next);
            }
            else
            {
                head = next;
            }
            if (next != nullptr)
            {
                Node *next_of_next = xor_prev_next(curr, next->np);
                next->np = xor_prev_next(prev, next_of_next);
            }
            else
            {
                tail = prev;
            }
            delete curr;
            break;
        }
        prev = curr;
        curr = next;
    }
}

void DoubleLinkedList::reverse_list()
{
    Node *temp = tail;
    tail = head;
    head = temp;
}

Node *DoubleLinkedList::search(int val) const
{
    Node *prev = nullptr;
    Node *curr = head;
    Node *next;

    while (curr != nullptr)
    {
        if (curr->data == val)
        {
            break;
        }
        next = xor_prev_next(prev, curr->np);
        prev = curr;
        curr = next;
    }

    return curr;
}

int main(int argc, char const *argv[])
{
    DoubleLinkedList list;
    list.insert(1);
    list.remove(1);
    cout << list << '\n';
    list.insert(1);
    list.insert(2);
    list.insert(3);
    list.insert(4);
    cout << list << '\n';
    list.reverse_list();
    cout << list << '\n';
    list.remove(2);
    cout << list << '\n';
    Node *a = list.search(2);
    if (a == nullptr)
    {
        cout << "nullptr\n";
    }
    else
    {
        cout << a << a->data << '\n';
    }
    a = list.search(3);
    if (a == nullptr)
    {
        cout << "nullptr\n";
    }
    else
    {
        cout << a << " : " << a->data << '\n';
    }
    return 0;
}

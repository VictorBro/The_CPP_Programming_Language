#include <iostream>
#include <list>
#include <string>
#include <memory>

using list_itr = std::list<std::shared_ptr<std::string>>::iterator;

class Doc_editor
{
  std::list<std::shared_ptr<std::string>> doc;
  std::shared_ptr<std::string> last_string;
  bool is_deleted = false;
  int n = -1;

public:
  Doc_editor() = default;
  Doc_editor(std::initializer_list<std::shared_ptr<std::string>> ilist) : doc{ilist} {}

  void insert_at(size_t, std::string);
  void print();
  void delete_at(size_t);
  void undo();
};

void Doc_editor::insert_at(size_t position, std::string str)
{
  if (position >= doc.size())
  {
    int i = doc.size();
    for (; i < position; ++i)
    {
      doc.push_back(std::shared_ptr<std::string>(new std::string{"*"}));
    }
    last_string = std::shared_ptr<std::string>(new std::string{str});
    doc.push_back(last_string);
  }
  else
  {
    list_itr temp_itr = doc.begin();
    for (int i = 0; i < position; ++i)
    {
      ++temp_itr;
    }
    last_string = std::shared_ptr<std::string>(new std::string{str});
    doc.insert(temp_itr, last_string);
  }
  is_deleted = false;
  n = position;
}

void Doc_editor::delete_at(size_t position)
{
  if (position < doc.size())
  {
    list_itr temp_itr = doc.begin();
    for (int i = 0; i < position; ++i)
    {
      ++temp_itr;
    }
    last_string = *temp_itr;
    doc.erase(temp_itr);
    is_deleted = true;
    n = position;
  }
}

void Doc_editor::undo()
{
  if (n != -1)
  {
    if (is_deleted)
    {
      insert_at(n, *last_string);
    }
    else
    {
      delete_at(n);
    }
    n = -1;
  }
}

void Doc_editor::print()
{
  for (auto x : doc)
    std::cout << *x << std::endl;
}

int main()
{
  Doc_editor my_doc;
  my_doc.insert_at(0, "puki");
  my_doc.insert_at(0, "kuki");
  my_doc.insert_at(0, "hi");
  my_doc.undo();
  my_doc.insert_at(0, "pokemon");
  my_doc.insert_at(3, "hara");
  my_doc.insert_at(7, "wow");
  my_doc.delete_at(0);
  my_doc.delete_at(3);
  my_doc.undo();
  my_doc.delete_at(105);
  my_doc.print();
}
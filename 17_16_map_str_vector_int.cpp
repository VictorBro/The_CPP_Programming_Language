#include <map>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#include <iterator>

using std::istream;
using std::string;
using std::vector;

typedef std::map<string, vector<int>> LineIndex;
typedef vector<string>::const_iterator EntryIt;

LineIndex *make_line_index(istream &input, const vector<string> &entries)
{
  string line, word;
  int line_number = 0;
  LineIndex *index = new LineIndex;
  for (EntryIt p = entries.begin(); p != entries.end(); ++p)
  {
    (*index)[*p];
  }

  while (std::getline(input, line))
  {
    if (line == "end")
      break;
    ++line_number;
    std::istringstream words{line};

    while (words >> word)
    {
      LineIndex::iterator p = index->find(word);
      if (p != index->end())
      {
        p->second.push_back(line_number);
      }
    }
  }

  return index;
}

int main(int argc, char *argv[])
{
  vector<string> entries;
  for (int i = 1; i != argc; ++i)
  {
    entries.push_back(string{argv[i]});
  }
  LineIndex *index = make_line_index(std::cin, entries);
  vector<string>::iterator p = entries.begin();
  for (; p != entries.end(); ++p)
  {
    std::cout << "Word " << *p << " appears in lines ";
    LineIndex::iterator lines = index->find(*p);
    std::copy(lines->second.begin(), lines->second.end(), std::ostream_iterator<int>{std::cout, ", "});
    std::cout << ".\n";
  }
}
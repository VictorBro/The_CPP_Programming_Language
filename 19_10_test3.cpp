#include <iostream>
#include <vector>
#include <algorithm>

int solution(const std::vector<int> &A)
{
  int n = A.size();
  int result = 0;
  for (int i = 0; i < n - 1; i++)
  {
    if (A[i] == A[i + 1])
      result = result + 1;
  }
  //int r = 0;
  int r = -1;
  for (int i = 0; i < n; i++)
  {
    int count = 0;
    if (i > 0)
    {
      if (A[i - 1] != A[i])
        count = count + 1;
      else
        count = count - 1;
    }
    if (i < n - 1)
    {
      if (A[i + 1] != A[i])
        count = count + 1;
      else
        count = count - 1;
    }
    r = std::max(r, count);
  }
  return result + r;
}

int main()
{
  std::cout << solution({1,1,0,1,0,0}) << std::endl;
  std::cout << solution({1,1,1}) << std::endl;
  std::cout << solution({1}) << std::endl;
  std::cout << solution({1,0,1}) << std::endl;
}
#include <iostream>
#include <vector>

bool solution(const std::vector<int> &A, int k)
{
  int n = A.size();

  for (int i = 0; i < n - 1; i++)
  {
    if (A[i] + 1 < A[i + 1])
      return false;
  }

  //if (A[0] != 1 && A[n - 1] != k)
  if (A[0] != 1 || A[n - 1] != k)
    return false;
  else
    return true;
}

int main()
{
  std::cout << solution({1,1,2,3,3}, 3) << std::endl;
  std::cout << solution({1,1,2,3,4}, 3) << std::endl;
  std::cout << solution({1,1,1,3,3}, 3) << std::endl;
  std::cout << solution({1}, 1) << std::endl;
}
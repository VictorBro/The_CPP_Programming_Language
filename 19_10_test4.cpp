#include <iostream>
#include <vector>
#include <algorithm>

int solution(const std::vector<int> &A)
{
  int n = A.size();
  int minCost = 2000000000;
  int P = 1;
  
  for (int Q = 3; Q < n - 1; ++Q)
  {
    minCost = std::min(minCost, A[P] + A[Q]);
    if (A[P] > A[Q - 1])
      P = Q - 1;
  }

  return minCost;
}

int main()
{
  std::cout << solution({5,2,4,6,3,7}) << std::endl;
  std::cout << solution({1,2,4,6,3,1}) << std::endl;
  std::cout << solution({1,1,1,1,1,1}) << std::endl;
  std::cout << solution({1,2,3,4,5,6}) << std::endl;
  std::cout << solution({6,5,4,3,2,1}) << std::endl;
  std::cout << solution({1000000000,1000000000,1000000000,1000000000,1000000000,6}) << std::endl;
  std::cout << solution({6,100,200,100,200,1}) << std::endl;
  std::cout << solution({5,2,4,6,3}) << std::endl;
  std::cout << solution({5,4,2,6,3,7}) << std::endl;
}
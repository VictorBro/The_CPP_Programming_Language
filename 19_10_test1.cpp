#include <iostream>

int solution(int A, int B)
{
  long long prod = static_cast<long long>(A) * static_cast<long long>(B);
  int count = 0; 
  for (; prod > 0; ++count, prod &= prod - 1)
    ;
  return count;
}

int main()
{
  std::cout << solution(100000000, 100000000) << std::endl;
  std::cout << solution(3, 7) << std::endl;
  std::cout << solution(700, 0) << std::endl;
  std::cout << solution(15, 1) << std::endl;
}
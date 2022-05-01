#include <iostream>
#include <algorithm>
#include <iterator>
#include "containerFactorial.hpp"

void taskTwo(std::ostream& out)
{
  ContainerFactorial cont(10);

  std::copy(cont.begin(), cont.end(), std::ostream_iterator<unsigned long long>(out, " "));
  out << '\n';

  std::copy(cont.rbegin(), cont.rend(), std::ostream_iterator<unsigned long long>(out, " "));
  out << "\n";
}

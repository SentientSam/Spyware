#include <iostream>
#include <vector.h>
#include <gheap.h>

typedef unsigned long ElementType;

int main()
{
  fsu::Vector < ElementType > v;  // a vector
  ElementType e;
  while (std::cin >> e)
  {
    v.PushBack(e);
  }
  fsu::g_heap_sort(v.Begin(),v.End());
  for (typename fsu::Vector < ElementType > ::Iterator i = v.Begin(); i != v.End(); ++i)
  {
    std::cout << *i << '\n';
  }
  return 0;
}

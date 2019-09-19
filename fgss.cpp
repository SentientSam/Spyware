#include <cstdlib>
#include <iostream>
#include <fstream>

#include <vector.h>
#include <deque.h>
#include <list.h>
#include <compare.h>
#include <gheap.h> // g_heap_sort
#include <gsort.h> // g_insertion_sort
#include <gbsearch.h> // iterative implementations
#include <rbsearch.h> // recursive implementations
#include <gssearch.h> // sequential search versions (forward iterators)
#include <genalg.h>

int main(int argc, char* argv[])
{
  bool BATCH = 0;
  if (argc > 1) BATCH = 1;
  std::istream* isptr = &std::cin;
  std::ifstream ifs;
  if (BATCH)
  {
    ifs.open(argv[1]);
    if (ifs.fail())
    {
      std::cout << " ** Error: cannot open file " << argv[1] << '\n';
      return 0;
    }
    isptr = &ifs;
  }

  typedef char ElementType; const char* e_t = "char";

  typedef fsu::LessThan <ElementType>    PredicateType1;
  // typedef fsu::GreaterThan <ElementType> PredicateType2;

  fsu::Vector < ElementType > V;  // a vector
  fsu::Deque  < ElementType > D;  // a deque
  fsu::List   < ElementType > L;  // a list
  ElementType *               A;  // an array
  PredicateType1              LT; // predicate object
  // PredicateType2              GT; // predicate object

  fsu::Vector < ElementType > ::Iterator Vitr,   Vloc,   altVloc;
  fsu::Deque  < ElementType > ::Iterator Ditr,   Dloc,   altDloc;
  fsu::List   < ElementType > ::Iterator Litr,   Lloc,   altLloc;
  ElementType                          * Aitr, * Aloc, * altAloc;
  // fsu::Pair<fsu::Vector<ElementType>::Iterator,fsu::Vector<ElementType>::Iterator> pv;
  // fsu::Pair<fsu::Deque<ElementType>::Iterator,fsu::Deque<ElementType>::Iterator> pd;
  // fsu::Pair<fsu::List<ElementType>::Iterator,fsu::List<ElementType>::Iterator> pl;
  // fsu::Pair<ElementType*,ElementType*> pp;

  ElementType e, s; // entry, sentinel
  unsigned int i, size = 0;

  std::cout << "Begin test of generic sort and search < " << e_t << " >\n\n";
    if (!BATCH)
      std::cout << "  You will enter characters for storage into a vector V. These will be\n"
		<< "  copied to a deque D and an array A in several ways, then sorted with\n"
		<< "  various order relations. Then the program enters an interactive phase\n"
		<< "  where you will be prompted to enter search values. The sentinel value\n"
		<< "  will be used to terminate your original input and to end the program.\n\n";
    std::cout << "Enter sentinel: ";
  *isptr >> s;
  if (BATCH) std::cout << s << '\n';
  std::cout << "Enter elements ('"
       << s
       << "' to end): ";
  *isptr >> e;
  while (e != s)
  {
    if (BATCH) std::cout << e;
    V.PushBack(e); L.PushBack(e); D.PushBack(e); ++size;
    *isptr >> e;
  }
  if (BATCH) std::cout << e << '\n';

  std::cout << "V as entered:                " << V << '\n';
  std::cout << "D as entered:                " << D << '\n';
  std::cout << "L as entered:                " << L << '\n';

  // copy to array
  A = new ElementType [size];
  fsu::g_copy(V.Begin(), V.End(), A);
  std::cout << "A as copied:                 ";
  for (i = 0; i < size; ++i)
    std::cout << A[i];
  std::cout << '\n';

  // apply generic sort to each container and display
  // Vector:
  fsu::g_heap_sort(V.Begin(), V.End(),LT);
  std::cout << "g_heap_sort(V):              " << V << '\n';
  // Deque:
  fsu::g_heap_sort(D.Begin(), D.End(),LT);
  std::cout << "g_heap_sort(D):              " << D << '\n';
  // Array:
  fsu::g_heap_sort(A, A + size, LT);
  std::cout << "g_heap_sort(A,<):            ";
  for (i = 0; i < size; ++i)
    std::cout << A[i];
  std::cout << '\n';
  // List:
  L.Sort(LT);
  std::cout << "L.Sort(<):                   " << L << '\n';
  // end generic sort */

  // now do binary search
  while(1)
  {
    std::cout << "Enter search value ('"
	 << s
	 << "' to quit): ";
    *isptr >> e;
    if (BATCH) std::cout << e << '\n';
    if (e == s) break;

    // calculate pair versions
    // pv = fsu::g_range (V.Begin(), V.End(),e,LT);
    // pd = fsu::g_range (D.Begin(), D.End(),e,LT);
    // pp = fsu::g_range (A,A+size,e,LT);
    // pv = fsu::g_range (V.Begin(), V.End(),e);
    // pd = fsu::g_range (D.Begin(), D.End(),e);
    // pp = fsu::g_range (A,A+size,e);

    // test of g_lower_bound, g_upper_bound on Vector
    Vloc = fsu::g_lower_bound(V.Begin(), V.End(), e, LT);
    // check recursive version
    altVloc = alt::g_lower_bound(V.Begin(), V.End(), e, LT);
    if (Vloc != altVloc)
      std::cout << " ** Error: fsu:: and alt:: g_lower_bound do not agree on Vector\n";
    // */
    std::cout << "V = " << V << '\n';
    std::cout << "    ";
    for (Vitr = V.Begin(); Vitr != Vloc; ++Vitr) std::cout << ' ';
    std::cout << "^lb\n";

    Vloc = fsu::g_upper_bound(V.Begin(), V.End(), e, LT);
    // check recursive version
    altVloc = alt::g_upper_bound(V.Begin(), V.End(), e, LT);
    if (Vloc != altVloc)
      std::cout << " ** Error: fsu:: and alt:: g_upper_bound do not agree on Vector\n";
    // */
    std::cout << "V = " << V << '\n';
    std::cout << "    ";
    for (Vitr = V.Begin(); Vitr != Vloc; ++Vitr) std::cout << ' ';
    std::cout << "^ub\n";

    // test of g_lower_bound, g_upper_bound on Deque
    Dloc = fsu::g_lower_bound(D.Begin(), D.End(), e, LT);
    // check recursive version
    altDloc = alt::g_lower_bound(D.Begin(), D.End(), e, LT);
    if (Dloc != altDloc)
      std::cout << " ** Error: fsu:: and alt:: g_lower_bound do not agree on Deque\n";
    // */
    std::cout << "D = " << D << '\n';
    std::cout << "    ";
    for (Ditr = D.Begin(); Ditr != Dloc; ++Ditr) std::cout << ' ';
    std::cout << "^lb\n";
    Dloc = fsu::g_upper_bound(D.Begin(), D.End(), e, LT);
    // check recursive version
    altDloc = alt::g_upper_bound(D.Begin(), D.End(), e, LT);
    if (Dloc != altDloc)
      std::cout << " ** Error: fsu:: and alt:: g_upper_bound do not agree on Deque\n";
    // */
    std::cout << "D = " << D << '\n';
    std::cout << "    ";
    for (Ditr = D.Begin(); Ditr != Dloc; ++Ditr) std::cout << ' ';
    std::cout << "^ub\n";

    // test of g_lower_bound, g_upper_bound on array
    Aloc = fsu::g_lower_bound(A, A + size, e, LT);
    // check recursive version
    altAloc = alt::g_lower_bound(A, A + size, e, LT);
    if (Aloc != altAloc)
      std::cout << " ** Error: fsu:: and alt:: g_lower_bound do not agree on array\n";
    // */
    std::cout << "A = ";
    for (Aitr = A; Aitr != A + size; ++Aitr) std::cout << *Aitr; std::cout << '\n';
    std::cout << "    ";
    for (Aitr = A; Aitr != Aloc; ++Aitr) std::cout << ' ';
    std::cout << "^lb\n";
    Aloc = fsu::g_upper_bound(A, A + size, e, LT);
    // check recursive version
    altAloc = alt::g_upper_bound(A, A + size, e, LT);
    if (Aloc != altAloc) 
      std::cout << " ** Error: fsu:: and alt:: g_upper_bound do not agree on array\n";
    // */
    std::cout << "A = ";
    for (Aitr = A; Aitr != A + size; ++Aitr) std::cout << *Aitr; std::cout << '\n';
    std::cout << "    ";
    for (Aitr = A; Aitr != Aloc; ++Aitr) std::cout << ' ';
    std::cout << "^ub\n";

    // test of g_lower_bound, g_upper_bound on List
    Lloc = seq::g_lower_bound(L.Begin(), L.End(), e, LT);
    std::cout << "L = " << L << '\n';
    std::cout << "    ";
    for (Litr = L.Begin(); Litr != Lloc; ++Litr) std::cout << ' ';
    std::cout << "^lb\n";
    Lloc = seq::g_upper_bound(L.Begin(), L.End(), e, LT);
    std::cout << "L = " << L << '\n';
    std::cout << "    ";
    for (Litr = L.Begin(); Litr != Lloc; ++Litr) std::cout << ' ';
    std::cout << "^ub\n";

    /* // test bool-valued generic search
    std::cout << e << " is ";
    if (!fsu::g_binary_search(V.Begin(), V.End(), e, LT))
      std::cout << "not ";
    std::cout << "in V\n";
    std::cout << e << " is ";
    if (!fsu::g_binary_search(D.Begin(), D.End(), e, LT))
      std::cout << "not ";
    std::cout << "in D\n";
    std::cout << e << " is ";
    if (!fsu::g_binary_search(A, A + size, e, LT))
      std::cout << "not ";
    std::cout << "in A\n";
    std::cout << e << " is ";
    if (!seq::g_sequential_search(L.Begin(), L.End(), e, LT))
      std::cout << "not ";
    std::cout << "in L\n";
    // */
  }
  std::cout << "End test of g_heap_sort/g_binary_search < " << e_t << " >\n";
  return 0;
}

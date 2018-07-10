#include <stdio.h>
#include <assert.h>
#include "ds_set.h"

int main () {

  // DS_SET TESTS
  ds_set<int> a;
  // insertion test
  for ( int i = 1; i < 8; i++ ) {
    //std::cout << "Head" << std::endl;
    int to_add = i*3;
    std::cout << "inserting " << to_add << std::endl;
    //std::cout << "After variable declaration" << std::endl;
    a.insert (to_add);
    //std::cout << "Finished adding " << to_add << std::endl;
  }
  printf("size: %d\n", a.size());
  assert (a.size() == 7);

  std::cout << "A List: "  << a << std::endl;

  // iterator test
  std::cout << "Iterator test" << std::endl;
  typename ds_set<int>::iterator itr;
  for ( itr = a.begin(); itr != a.end(); ++itr ) {
      std::cout << *itr << " ";
      //print_iter (itr, "Testing");
  }
  std::cout << std::endl;

  // balanced tree insertion test
  ds_set<int> b;
  b.insert(8);
  b.insert(4);
  b.insert(12);
  b.insert(2);
  b.insert(6);
  b.insert(10);
  b.insert(14);
  b.insert(1);
  b.insert(3);
  b.insert(5);
  b.insert(7);
  b.insert(9);
  b.insert(11);
  b.insert(13);
  b.insert(15);

  // Print the values of the iterator
  typename ds_set<int>::iterator b_itr;
  for ( b_itr = b.begin(); b_itr != b.end(); ++b_itr ) {
    print_iter(b_itr, "MAIN - PRINT TEST");
  }

  std::cout << b << std::endl;
  assert( b.size() == 15 );

  // reverse iterrator test
  typename ds_set<int>::iterator b_itr_r = b.begin ();
  b_itr = b.begin ();
  ++b_itr;

  while ( b_itr != b.end() ){ ++b_itr; ++b_itr_r; }

  // print backwards
  for ( b_itr_r; b_itr_r != b.end(); --b_itr_r ) {
    print_iter(b_itr_r, "REVERSE ITERATION");
  }

  // erase test
  ds_set<std::string> c;
  c.insert("delta");
  c.insert("bravo");
  c.insert("foxtrot");
  c.insert("alpha");
  c.insert("charlie");
  c.insert("epsilon");
  c.insert("galio");

  assert( c.size() == 7 );
  std::cout << "C SET #1 => " << c << std::endl;
  std::cout << "Erasing 'charlie'" << std::endl;
  c.erase("charlie");
  std::cout << "After erase: " << c << std::endl;

  // erasing inside a node (non-leaf, non-root)
  c.insert("charlie");
  std::cout << "C SET #2 => " << c << std::endl;
  std::cout << "Erasing 'bravo'" << std::endl;
  c.erase("bravo");
  std::cout << "After erase: " << c << std::endl;

  return 0;
}

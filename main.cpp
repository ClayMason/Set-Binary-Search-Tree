#include <stdio.h>
#include <assert.h>
#include "ds_set.h"

int main () {

  // DS_SET TESTS
  ds_set<int> a;
  // insertion test
  for ( int i = 1; i < 20; i++ ) {
    //std::cout << "Head" << std::endl;
    int to_add = i*3;
    //std::cout << "After variable declaration" << std::endl;
    a.insert (to_add);
    //std::cout << "Finished adding " << to_add << std::endl;
  }
  printf("size: %d\n", a.size());
  assert (a.size() == 19);

  std::cout << "A List: "  << a << std::endl;

  // iterator test
  std::cout << "Iterator test" << std::endl;
  typename ds_set<int>::iterator itr;
  for ( itr = a.begin(); itr != a.end(); ++itr ) {
      std::cout << *itr << " ";
  }
  std::cout << std::endl;

  return 0;
}

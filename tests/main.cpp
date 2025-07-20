#include <assert.h>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>

#include "./hash-map.test.cpp"
#include "./hash-set.test.cpp"


int main()
{
  std::cout << "Rodando testes..." << std::endl;

  test_hash_map_main();
  test_hash_set_main();
  
  std::cout << "Finalizado" << std::endl;

  return EXIT_SUCCESS;
}
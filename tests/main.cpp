#include <iostream>
#include <stdlib.h>
#include <stdio.h>

#include "../src/hash-map.cpp"

void test_put()
{
    Hash_Map<size_t> map(100);

    assert(map.put("teste", 100));
    assert(map.put("teste", 100));
    
    assert(map.put("teste2", 100));
    assert(map.put("teste2", 100));
}

int main(int argc, const char* argv[])
{
  std::cout << "Rodando testes..." << std::endl;

  test_put();

  std::cout << "Finalizado" << std::endl;

  return EXIT_SUCCESS;
}
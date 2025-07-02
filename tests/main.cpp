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

  assert(map.occupancy == 2);
}

void test_lookup()
{
  Hash_Map<size_t> map(100);

  assert(map.put("teste", 100));
  
  auto r = map.lookup("teste");
  assert(r.success);
  assert(r.value == 100);
  
  auto r2 = map.lookup("teste2");
  assert(!r2.success);
  
  assert(map.put("teste2", 200));
  
  auto r3 = map.lookup("teste2");
  assert(r3.success);
  assert(r3.value == 200);

  assert(map.put("teste", 240));
  
  auto r4 = map.lookup("teste");
  assert(r4.success);
  assert(r4.value == 240);

  assert(map.occupancy == 2);
}

int main()
{
  std::cout << "Rodando testes..." << std::endl;

  test_put();
  test_lookup();

  std::cout << "Finalizado" << std::endl;

  return EXIT_SUCCESS;
}
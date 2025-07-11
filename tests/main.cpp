#include <assert.h>
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
  assert(map.occupancy == 1);

  auto r = map.lookup("teste");
  assert(r.success);
  assert(r.value == 100);
  
  auto r2 = map.lookup("teste2");
  assert(!r2.success);
  
  assert(map.put("teste2", 200));
  assert(map.occupancy == 2);
  
  auto r3 = map.lookup("teste2");
  assert(r3.success);
  assert(r3.value == 200);

  assert(map.put("teste", 240));
  
  auto r4 = map.lookup("teste");
  assert(r4.success);
  assert(r4.value == 240);

  assert(map.occupancy == 2);
}

void test_remove()
{
  Hash_Map<size_t> map(1024);

  assert(map.put("teste", 100));
  assert(map.occupancy == 1);

  auto r1 = map.remove("teste");
  assert(r1.success);
  assert(r1.value = 100);

  assert(map.occupancy == 0);

  auto r2 = map.remove("teste");
  assert(!r2.success);

  auto r3 = map.remove("teste2");
  assert(!r3.success);
  assert(map.occupancy == 0);

  assert(map.put("teste1", 100));
  assert(map.put("teste2", 100));
  assert(map.put("teste3", 100));

  auto r4 = map.remove("teste2");
  assert(r4.success);
  assert(map.occupancy == 2);
}

void test_hashing_to_same_bucket()
{
  Hash_Map<size_t> map(1); // apenas um bucket

  assert(map.put("teste1", 101));
  assert(map.put("teste2", 102));
  assert(map.put("teste3", 103));

  assert(map.occupancy == 3);

  auto r1 = map.lookup("teste1");
  assert(r1.success);
  assert(r1.value == 101);

  auto r2 = map.lookup("teste2");
  assert(r2.success);
  assert(r2.value == 102);

  auto r3 = map.remove("teste2");
  assert(r3.success);
  assert(r3.value == 102);
  assert(map.occupancy == 2);
}

void test_dict()
{
  Hash_Map<size_t> map(1000);

  std::string tokens[] = {"texto", "palavra", "nome", "idade", "texto"};

  for (const auto &token : tokens)
  {
    auto key = token.c_str();
    auto result = map.lookup(key);

    if (result.success)
    {
      map.put(key, result.value + 1);
    }
    else
    {
      map.put(key, 1);
    }
  }

  assert(map.lookup("texto").success);
  assert(map.lookup("texto").value == 2);

  assert(map.lookup("palavra").success);
  assert(map.lookup("palavra").value == 1);

  assert(map.lookup("palavra não existente").success == false);

  /*
  for (size_t i = 0; i < map.capacity; i++)
  {
    if (map.bucket[i])
    {
      auto item = map.bucket[i];
      do
      {
        std::cout << "index: " << i << ", key:  " << item->key << ", value: " << item->value << std::endl;
      } while ((item = item->next_item));
    }
  }
  */
}

int main()
{
  std::cout << "Rodando testes..." << std::endl;

  test_put();
  test_lookup();
  test_dict();
  test_remove();
  test_hashing_to_same_bucket();

  std::cout << "Finalizado" << std::endl;

  return EXIT_SUCCESS;
}
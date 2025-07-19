#include <assert.h>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>

#include "../src/hash-map.cpp"
#include "../src/hash-set.cpp"

void test_hash_map_put()
{
  Hash_Map<size_t> map(100);

  assert(map.put("teste", 100));
  assert(map.put("teste", 100));
    
  assert(map.put("teste2", 100));
  assert(map.put("teste2", 100));

  assert(map.occupancy == 2);
}

void test_hash_map_lookup()
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

void test_hash_map_remove()
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

void test_hash_map_hashing_to_same_bucket()
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

void test_hash_set_add()
{
  Hash_Set<size_t> map(1024);

  assert(map.add(1));
  assert(!map.add(1));

  assert(map.occupancy == 1);

  assert(map.add(3));
  assert(!map.add(1));
  assert(!map.add(3));

  assert(map.occupancy == 2);

  assert(map.add(7));
  assert(!map.add(7));

  assert(map.occupancy == 3);
}

void test_hash_set_has()
{
  Hash_Set<size_t> map(1024);

  assert(!map.has(1));

  assert(map.add(1));

  assert(map.has(1));

  assert(map.add(3));
  
  assert(map.has(1));
  
  assert(!map.add(3));
  assert(map.has(3));
}

void test_hash_set_clear()
{
  Hash_Set<size_t> map(1024);

  assert(map.occupancy == 0);
  map.clear();
  assert(map.occupancy == 0);

  assert(map.add(3));
  assert(map.occupancy == 1);
  map.clear();
  assert(map.occupancy == 0);
}

// @todo João, custom structs não funciona...
struct Test_Struct_Type {
  size_t id;
  const char* text;
};

void test_hash_set_changing_hash_func_and_compare()
{
  Hash_Set<std::string> map(1024);

  std::string v01 = "texto";
  std::string v02 = "palavra";
  std::string v03 = "texto";
  
  assert(map.add(v01));
  assert(map.add(v02));
  assert(!map.add(v01));
  assert(!map.add(v03));
}

void test_hash_set_remove()
{
  Hash_Set<size_t> map(1024);

  assert(map.occupancy == 0);
  assert(!map.remove(3));
  assert(map.occupancy == 0);
  assert(map.add(3));
  assert(map.occupancy == 1);
  assert(map.has(3));
  assert(map.remove(3));
  assert(map.occupancy == 0);
  assert(!map.has(3));

  assert(!map.remove(1027));
  assert(map.add(1027));
  assert(map.has(1027));
  assert(map.remove(1027));
  assert(!map.has(1027));
}

void test_hash_map_dict()
{
  Hash_Map<size_t> map(1000);

  std::string tokens[] = {
    "texto", "palavra", "nome", "idade", "texto",
    "cidade", "palavra", "nome", "idade", "Marcos",
    "texto", "palavra", "nome", "idade", "carro",
    "carro", "carro", "carros", "viajar", "texto",
    "texto", "palavra", "nome", "casa", "Avião",
  };

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
  assert(map.lookup("texto").value == 5);

  assert(map.lookup("palavra").success);
  assert(map.lookup("palavra").value == 4);

  assert(map.lookup("Avião").success);
  assert(map.lookup("Avião").value == 1);

  assert(map.lookup("nome").success);
  assert(map.lookup("nome").value == 4);

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

void test_hash_map_clear()
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

  map.clear();

  assert(map.occupancy == 0);

  assert(map.put("teste", 240));
  
  auto r4 = map.lookup("teste");
  assert(r4.success);
  assert(r4.value == 240);

  assert(map.occupancy == 1);

  map.clear();

  auto r5 = map.lookup("teste");
  assert(!r5.success);

  assert(map.occupancy == 0);
}

void test_hash_map_with_stdstrings()
{
  Hash_Map<size_t> map(100);

  const char* v01 = "texto";
  const char* v02 = "texto";
  
  assert(map.put(v01, 13));

  assert(map.lookup(v02).success);
 
  assert(map.put(v02, 14));
 
  assert(map.lookup(v01).success);
  assert(map.lookup(v01).value == 14);
}

int main()
{
  std::cout << "Rodando testes..." << std::endl;

  test_hash_map_put();
  test_hash_map_lookup();
  test_hash_map_dict();
  test_hash_map_remove();
  test_hash_map_clear();
  test_hash_map_hashing_to_same_bucket();
  test_hash_map_with_stdstrings();

  test_hash_set_add();
  test_hash_set_has();
  test_hash_set_remove();
  test_hash_set_clear();
  test_hash_set_changing_hash_func_and_compare();

  std::cout << "Finalizado" << std::endl;

  return EXIT_SUCCESS;
}
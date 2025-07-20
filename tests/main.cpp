#include <assert.h>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>

#include "./hash-map.test.cpp"
#include "../src/hash-set.cpp"
#include "../src/hash.cpp"

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

void test_hash_set_std_string()
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

struct Test_Struct_Type {
  size_t id;
  const char* text;
};

inline size_t hash_for_test_struct_type(Test_Struct_Type value)
{
  static std::hash<size_t> hasher;

  return hasher(value.id);
}

inline bool compare_for_test_struct_type(Test_Struct_Type* v1, Test_Struct_Type* v2)
{
  return v1->id == v2->id;
}

void test_hash_set_changing_hash_func_and_compare()
{
  Test_Struct_Type t01 = { 1, "texto" };
  Test_Struct_Type t02 = { 2, "nome" };
  Test_Struct_Type t03 = { 3, "verbo" };
  Test_Struct_Type t04 = { 1, "verbo" };
  
  Hash_Set<Test_Struct_Type, compare_for_test_struct_type, hash_for_test_struct_type> set(1024);

  assert(set.add(t01));
  assert(set.add(t02));
  assert(set.add(t03));
  assert(!set.add(t04));
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

int main()
{
  std::cout << "Rodando testes..." << std::endl;

  test_hash_map_main();
  

  test_hash_set_add();
  test_hash_set_has();
  test_hash_set_remove();
  test_hash_set_clear();
  test_hash_set_std_string();
  test_hash_set_changing_hash_func_and_compare();

  std::cout << "Finalizado" << std::endl;

  return EXIT_SUCCESS;
}
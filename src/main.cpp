#include <iostream>
#include <stdlib.h>
#include <stdio.h>

#include "hash-map.cpp"

int main()
{
  std::cout << "olá mundo dos hash maps!!" << std::endl;

  Hash_Map<size_t> map(100);

  map.put("teste", 200);
  map.put("teste2", 1000);
  map.put("teste3", 262);
  map.put("joao", 400);

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

  std::cout << "occupacy: " << map.occupancy << std::endl;
  
  return EXIT_SUCCESS;
}
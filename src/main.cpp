#include <iostream>
#include <stdlib.h>
#include <stdio.h>

#include "hash-map.cpp"

int main(int argc, const char* argv[])
{
  std::cout << "olá mundo dos hash maps!!";

  Hash_Map<size_t> map(200);

  if (map.put("teste", 100))
  {
    std::cout << "inseriu";
  }
  else
  {
    std::cout << "não inseriu";
  }

  if (map.put("teste", 200))
  {
    std::cout << "inseriu segunda";
  }
  else
  {
    std::cout << "não inseriu segunda";
  }

  return EXIT_SUCCESS;
}
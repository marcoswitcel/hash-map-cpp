#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <fstream>
#include <sstream>
#include <functional>

#include "./hash-map.test.cpp"
#include "./hash-set.test.cpp"

// #define DEBUG_WORD_LOADING true

bool load_test_data(std::function<void(std::string)> processor_func)

{
  std::ifstream file_handle("test-words.txt", std::ios::in);

  if (!file_handle.good())
  {
    #ifdef DEBUG_WORD_LOADING
      std::cout << "Arquivo de testes não encontrado" << std::endl;
    #endif
    return true;
  }

  std::string line;
  while (std::getline(file_handle, line))
  {
    #ifdef DEBUG_WORD_LOADING
      std::cout << "linha encontrada" << std::endl;
    #endif
    std::istringstream iss(line);
    std::string word;

    iss >> word;

    bool success = !iss.fail();

    if (success) {
      #ifdef DEBUG_WORD_LOADING
        std::cout << "linha parseada" << std::endl;
      #endif
      #ifdef DEBUG_WORD_LOADING
        std::cout << word.c_str() << std::endl;
      #endif
      if (processor_func)
      {
        processor_func(word);
      }

    } else {
      #ifdef DEBUG_WORD_LOADING
        std::cout << "linha ignorada" << std::endl;
      #endif
    }
  }

  file_handle.close();

  #ifdef DEBUG_WORD_LOADING
    std::cout << "Arquivo de testes processado com sucesso!" << std::endl;
  #endif
  return true;
}

void test_processor_func(std::string word)
{
  // @todo João, implementar
}

int main()
{
  std::cout << "Rodando testes..." << std::endl;

  test_hash_map_main();
  test_hash_set_main();

  // @todo João, @wip terminar de adicionar aos sets e hashs
  load_test_data(test_processor_func);
  
  std::cout << "Finalizado" << std::endl;

  return EXIT_SUCCESS;
}
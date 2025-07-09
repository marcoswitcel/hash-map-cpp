#pragma once

#include <assert.h>
#include <stdint.h>
#include <string.h>

/**
 * @brief representa o sucesso ou falha da operação em questão, por exemplo: sucesso na busca
 * significa que existia um valor associado a chave e ele foi recuperado, enquanto que sucesso
 * na remoção significa que o valor associado a chave existia e foi removido.
 * 
 * @tparam Type 
 */
template <typename Type>
struct Result {
  /**
   * @brief sinaliza o sucesso ou falha da oporação, sinaliza também se o campo `value`
   * contém ou não o valor desejado.
   */
  bool success;
  /**
   * @brief valor buscado em caso de sucesso
   */
  Type value;

  Result()
  {
    this->success = false;
  }
};

inline char* copy_key(const char* key)
{
  return strcpy(new char[strlen(key) + 1], key);
}

size_t hash(const char* value)
{
  // @todo João, implementar uma função razoável
  size_t hashed_value = 0;
  size_t length = strlen(value);

  for (size_t i = 0; i < length;  i++)
  {
    hashed_value += value[i];
  }
  
  return hashed_value;
}

/**
 * @brief representa uma entrada no Hash Map
 * 
 * @tparam Value_Type 
 */
template <typename Value_Type>
struct Hash_Table_Item {
  const char* key;
  Value_Type value;
  Hash_Table_Item* next_item;
};

template <typename Value_Type>
struct Hash_Map {

  /**
   * @brief Define a capacidade máxima de elementos armazenados separadamente, quanto maior
   * o número, melhor a performance, porém, mais memória será usada desde a alocação inicial.
   * Esse campo em conjunto com o campo `occupancy` podem ser usados para 'especular' a 'eficiência' atual
   * do Hash Map, considerando que quanto mais cheio o Map esteja, mais entradas duplicadas terá e por
   * consequência, mais tempo os 'lookups', 'put' e 'removes' tomarão.
   * 
   */
  size_t capacity;
  /**
   * @brief mantém o controle da quantidade de elementos armazenados
   * 
   */
  size_t occupancy;

  Hash_Table_Item<Value_Type>** bucket;

  Hash_Map(size_t capacity)
  {
    this->capacity = capacity;
    this->occupancy = 0;
    // aloncado um 'array' de ponteiros inicializados para default: 0/NULL
    this->bucket = new Hash_Table_Item<Value_Type>*[capacity]();
  }

  ~Hash_Map()
  {
    // iterando e desalocando 'Itens' por 'bucket'
    for (size_t i = 0; i < this->capacity; i++)
    {
      Hash_Table_Item<Value_Type>* item = this->bucket[i];
      Hash_Table_Item<Value_Type>* next = NULL;
      
      while (item)
      {
        next = item->next_item;
        delete[] item->key;
        delete item;
        item = next;
      }
    }

    delete[] this->bucket;
  }

  /**
   * @brief faz a busca da chave especificada no Hash Map pelo valor associado a chave
   * 
   * @param key chave que deve ser procurada
   * @return Result<Value_Type> o retorno pode ser tanto de um sucesso na operação realizada (busca), com o valor
   * associado retornado junto, ou um retorno de falha, que no caso da busca sinaliza que chave não está registrada no momento
   * (ou nunca foi registrada ou foi removida).
   */
  Result<Value_Type> lookup(const char* key)
  {
    Result<Value_Type> result;

    size_t index = hash(key) % this->capacity;
    Hash_Table_Item<Value_Type>* item = this->bucket[index];

    while (item)
    {
      if (strcmp(item->key, key) == 0)
      {
        result.success = true;
        result.value = item->value;
        
        return result;
      }

      item = item->next_item;
    } 

    return result;
  }

  Result<Value_Type> remove(const char* key)
  {
    Result<Value_Type> result;

    size_t index = hash(key) % this->capacity;

    Hash_Table_Item<Value_Type>* previous_item = NULL;
    Hash_Table_Item<Value_Type>* item = this->bucket[index];

    for (; item; previous_item = item, item = item->next_item)
    {
      if (strcmp(item->key, key) == 0)
      {
        if (previous_item == NULL)
        {
          this->bucket[index] = item->next_item;
        }
        else
        {
          previous_item->next_item = item->next_item;
        }
        
        result.success = true;
        result.value = item->value;
        
        this->occupancy--;
        delete[] item->key;
        delete item;
  
        return result;
      }
    }

    return result;
  }

  bool put(const char* key, Value_Type value)
  {
    size_t index = hash(key) % this->capacity;

    Hash_Table_Item<Value_Type>* item = this->bucket[index];

    if (item == NULL)
    {
      Hash_Table_Item<Value_Type>* new_item = new Hash_Table_Item<Value_Type>();

      new_item->key = copy_key(key);
      new_item->value = value;

      this->bucket[index] = new_item;
      this->occupancy++;
      
      return true;
    }

    do
    {
      if (strcmp(item->key, key) == 0)
      {
        item->value = value;
        
        return true;
      }
      else if (item->next_item == NULL)
      {
        Hash_Table_Item<Value_Type>* new_item = new Hash_Table_Item<Value_Type>();
        new_item->key = copy_key(key);
        new_item->value = value;

        item->next_item = new_item;
        this->occupancy++;
        
        return true;
      }
    } while ((item = item->next_item));
    
    return false;
  }
};

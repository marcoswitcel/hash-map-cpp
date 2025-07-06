#pragma once

#include <assert.h>
#include <stdint.h>
#include <string.h>

template <typename Type>
struct Result {
  bool success;
  Type value;

  Result()
  {
    this->success = false;
  }
};

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
    this->bucket = new Hash_Table_Item<Value_Type>*[capacity];
  }

  ~Hash_Map()
  {
    // @todo João, implementar o destructor
    // delete[] this->bucket;
  }

  Result<Value_Type> lookup(const char* key)
  {
    Result<Value_Type> result;

    size_t index = hash(key) % this->capacity;
    Hash_Table_Item<Value_Type>* item = this->bucket[index];

    if (!item) return result;

    do
    {
      if (strcmp(item->key, key) == 0)
      {
        result.success = true;
        result.value = item->value;
        
        return result;
      }
    } while ((item = item->next_item));

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

    do
    {
      if (item == NULL)
      {
        item = new Hash_Table_Item<Value_Type>();

        // @todo João, ajustar copyString
        item->key = key; // @copyString
        item->value = value;

        this->bucket[index] = item;
        this->occupancy++;
        
        return true;
      }
      else if (strcmp(item->key, key) == 0)
      {
        item->key = key; // @copyString
        item->value = value;
        
        return true;
      }
      else if (item->next_item == NULL)
      {
        Hash_Table_Item<Value_Type>* new_item = new Hash_Table_Item<Value_Type>;
        new_item->key = key; // @copyString
        new_item->value = value;

        item->next_item = new_item;
        this->occupancy++;
        
        return true;
      }
    } while ((item = item->next_item));
    
    return false;
  }
};

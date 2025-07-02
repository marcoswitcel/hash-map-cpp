#pragma once

#include <assert.h>
#include <stdint.h>
#include <string.h>

size_t hash(const char* value)
{
  // @todo João, implementar uma função razoável
  return strlen(value);
}

template <typename Value_Type>
struct Hash_Table_item {
  const char* key;
  Value_Type value;
  Hash_Table_item* next_item;
};

template <typename Value_Type>
struct Hash_Map {

  size_t capacity;
  size_t occupancy;

  Hash_Table_item<Value_Type>** bucket;

  Hash_Map(size_t capacity)
  {
    this->capacity = capacity;
    this->bucket = new Hash_Table_item<Value_Type>*[capacity];
  }

  bool put(const char* key, Value_Type value)
  {
    size_t index = hash(key) % this->capacity;

    Hash_Table_item<Value_Type>* item = this->bucket[index];

    do
    {
      if (item == NULL)
      {
        item = new Hash_Table_item<Value_Type>();

        item->key = key;
        item->value = value;

        this->bucket[index] = item;
        this->occupancy++;
        
        return true;
      }
      else if (strcmp(item->key, key) == 0)
      {
        item->key = key;
        item->value = value;
        
        return true;
      }
      else if (item->next_item == NULL)
      {
        Hash_Table_item<Value_Type>* new_item = new Hash_Table_item<Value_Type>;
        new_item->key = key;
        new_item->value = value;

        item->next_item = new_item;
        this->occupancy++;
        
        return true;
      }
    } while (item = item->next_item);
    
    return false;
  }
};

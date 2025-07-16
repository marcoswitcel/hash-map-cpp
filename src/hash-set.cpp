#pragma once

#include <stdint.h>
#include <cstring>

template <typename Value_Type>
inline size_t hash_value(Value_Type value)
{
  static std::hash<Value_Type> hasher;

  return hasher(value);
}

template <typename Value_Type>
struct Hash_Set_Item {
  Value_Type value;
  Hash_Set_Item* next_item;

  Hash_Set_Item(Value_Type value)
  {
    this->value = value;
    this->next_item = NULL;
  }
};


template <typename Value_Type>
struct Hash_Set {
  size_t capacity;
  size_t occupancy;
  Hash_Set_Item<Value_Type>** bucket;

  Hash_Set(size_t capacity)
  {
    this->capacity = capacity;
    this->occupancy = 0;
    // aloncado um 'array' de ponteiros inicializados para default: 0/NULL
    this->bucket = new Hash_Set_Item<Value_Type>*[capacity]();
  }

  ~Hash_Set()
  {
    // @todo implementar
  }

  bool add(Value_Type value)
  {
    size_t index = hash_value(value) % this->capacity;
    Hash_Set_Item<Value_Type>* item = this->bucket[index];

    if (item == NULL)
    {
      this->bucket[index] = new Hash_Set_Item<Value_Type>(value);
      this->occupancy++;
      
      return true;
    }

    do
    {
      if (std::memcmp(&item->value, &value, sizeof(Value_Type)) == 0)
      {
        return false;
      }
      else if (item->next_item == NULL)
      {
        item->next_item = new Hash_Set_Item<Value_Type>(value);
        this->occupancy++;
        
        return true;
      }
    } while ((item = item->next_item));
    
    return false;
  }

  bool has(Value_Type value)
  {
    size_t index = hash_value(value) % this->capacity;
    Hash_Set_Item<Value_Type>* item = this->bucket[index];

    while (item)
    {
      if (std::memcmp(&item->value, &value, sizeof(Value_Type)) == 0)
      {
        return true;
      }

      item = item->next_item;
    }
    
    return false;
  }

  bool remove(Value_Type value)
  {
    size_t index = hash_value(value) % this->capacity;

    Hash_Set_Item<Value_Type>* item = this->bucket[index];
    Hash_Set_Item<Value_Type>* previous_item = NULL;

    while (item)
    {
      if (std::memcmp(&item->value, &value, sizeof(Value_Type)) == 0)
      {
        if (previous_item == NULL)
        {
          this->bucket[index] = item->next_item;
        }
        else
        {
          previous_item->next_item = item->next_item;
        }

        this->occupancy--;
        delete item;

        return true;
      }

      previous_item = item;
      item = item->next_item;
    }

    return false;
  }

  void clear()
  {
    // @todo implementar
  }
};

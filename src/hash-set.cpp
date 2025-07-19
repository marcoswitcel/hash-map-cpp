#pragma once

#include <stdint.h>
#include <cstring>

template <typename Value_Type>
inline size_t default_hash_value(Value_Type value)
{
  static std::hash<Value_Type> hasher;

  return hasher(value);
}

template <typename Value_Type>
inline bool value_compare_by_byte(Value_Type* v1, Value_Type* v2)
{
  return std::memcmp(v1, v2, sizeof(Value_Type)) == 0;
}

// especialização para std::string
inline bool value_compare_by_byte(std::string* v1, std::string* v2)
{
  return v1->compare(v2->c_str()) == 0;
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

template <typename Value_Type,
  bool (*equality)(Value_Type*, Value_Type*) = value_compare_by_byte,
  size_t (*hash_value)(Value_Type) = default_hash_value>
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
      if (equality(&item->value, &value))
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
      if (equality(&item->value, &value))
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
    // iterando e desalocando 'Itens' por 'bucket'
    for (size_t i = 0; i < this->capacity; i++)
    {
      Hash_Set_Item<Value_Type>* item = this->bucket[i];
      Hash_Set_Item<Value_Type>* next = NULL;
      this->bucket[i] = NULL;
      
      while (item)
      {
        next = item->next_item;
        delete item;
        item = next;
      }
    }

    this->occupancy = 0;
  }
};

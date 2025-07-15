#pragma once

#include <stdint.h>

template <typename Value_Type>
struct Hash_Set_Item {
  Value_Type value;
  Hash_Set_Item* next_item;
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
    // @todo implementar
    return false;
  }

  bool has(Value_Type value)
  {
    // @todo implementar
    return false;
  }

  bool remove(Value_Type value)
  {
    // @todo implementar
    return false;
  }

  void clear()
  {
    // @todo implementar
  }
};

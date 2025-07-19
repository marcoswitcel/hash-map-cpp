#pragma once

#include <stdint.h>

/**
 * @brief função hash simples, autor mencionado abaixo
 * 
 * @author hash function design by Daniel J. Bernstein (djb):
 * @reference https://www.reddit.com/r/learnprogramming/comments/1h5gmb/creating_a_simple_hash_function/ 
 * 
 * @param data 
 * @param size 
 * @return uint32_t 
 */
uint32_t hash(const char* data, uint32_t size)
{
  uint32_t hash = 5831;
  uint8_t byte;

  for (uint32_t i = 0; i < size; i++)
  {
    byte = data[i];
    hash = ((hash << 5) + hash) + byte;
  }

  return hash;
}


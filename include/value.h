#pragma once

/* Types supported by algol
 * NUMBERS (all numbers are represented as double)
 * STRING
 * BOOLEAN
*/

template <typename T>
class RuntimeVal {
public:
   RuntimeVal(T value) {
      this->value = value;
   }
   T value;
};

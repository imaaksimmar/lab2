#pragma once 
#include <iostream>
#include <stdexcept>


class Bit {
private:
    bool value; 

public:
    Bit() : value(false) {}
    Bit(bool v) : value(v) {}

    Bit(int v) : value(v!=0) {
        if(v!=0 && v!=1) {
            throw std::invalid_argument("Bit: only 0 or 1 is allowed");
        }
    }

    bool GetValue() const { 
        return value;
     }
   
  
    Bit operator&(const Bit& otherBit) const { 
        return Bit(value & otherBit.value); 
    }

    Bit operator|(const Bit& otherBit) const { 
        return Bit(value | otherBit.value); 
    }
    Bit operator^(const Bit& otherBit) const { 
        return Bit(value != otherBit.value); 
    }
    Bit operator~() const { 
        return Bit(!value); 
    }

};





#pragma once 
#include <iostream>
#include "exceptions.hpp"


class Bit {
private:
    bool value; 

public:
    Bit() : value(false) {}
    
    Bit(bool v) : value(v) {}

    Bit(int v) : value(v!=0) {
        if(v!=0 && v!=1) {
            throw InvalidArgument();
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



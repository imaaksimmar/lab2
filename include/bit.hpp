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
        if (v!=0 && v!=1) {
            throw std::invalid_argument("Bit: only 0 or 1 is allowed");
        }
    }

    bool GetValue() const { 
        return value;
     }
   
     // где используется 
    explicit operator bool() const { 
        return value;
     }
    explicit operator int() const { 
        if(value) return 1;
        else return 0; 
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

    // сравнение 
    bool operator==(const Bit& other) const { 
        return value == other.value; 
    }
    bool operator!=(const Bit& other) const { 
        return value != other.value;
     }
    // вывод в поток 
    friend std::ostream& operator<<(std::ostream& os, const Bit& b);
};


// Реализация оператора вывода 
inline std::ostream& operator<<(std::ostream& os, const Bit& b) {
    return os << (b.value ? '1' : '0');
}




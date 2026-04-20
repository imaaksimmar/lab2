#pragma once
#include <exception>
#include <string>

class Exceptions : public std::exception {
protected:
    std::string message;
public:
    Exceptions(const std::string& msg) : message(msg) {}
    const char* what() const noexcept override { return message.c_str(); }
};


class IndexOutOfRange : public Exceptions {
public:
    IndexOutOfRange() : Exceptions("Index out of range") {}
};

class InvalidArgument : public Exceptions {
public:    
    InvalidArgument() : Exceptions("Invalid arguments") {}
};

class NullPointer : public Exceptions {
public:
    NullPointer() : Exceptions("Null pointer") {}
};

class SizeMismatch : public Exceptions {
public:   
    SizeMismatch() : Exceptions("Size mismatch") {}
};

class EmptyCollection : public Exceptions {
public:    
    EmptyCollection() : Exceptions("Sequence is empty") {}
};


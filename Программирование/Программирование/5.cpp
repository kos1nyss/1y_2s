#include <iostream>
#include <vector>

struct reference {
    char* byte;
    unsigned int n;

public:
    reference(char* byte, unsigned int n) {
        this->byte = byte;
        this->n = n;
    }

    reference& operator = (bool value) {
        char p = (char)pow(2, n);
        if (value) {
            *byte |= p;
        } else {
            *byte = *byte & ~p;
        }
        return *this;
    }

    operator bool() {
        char p = (char)pow(2, n);
        char new_byte = *byte | p;
        return *byte == new_byte;
    }
};

template<>
class std::vector<bool> {

    std::vector<char> bytes;
    int _size = 0;

public:
    reference operator[] (int index) {
        return reference(&bytes[index / 8], index % 8);
    }

    void push_back(bool value) {
        _size++;
        if (_size % 8 == 1) {
            bytes.push_back(0);
        }
        (*this)[_size - 1] = value;
    }

    size_t size() {
        return _size;
    }

    void insert(int n, bool value) {
        this->push_back((*this)[_size - 1]);
        for (int i = _size - 1; i >= n; i--) {
            (*this)[i] = (bool)(*this)[i - 1];
        }
        (*this)[n] = value;
     }

     void erase(int n) {
        for (int i = n; i < _size - 1; i++) {
            (*this)[i] = (bool)(*this)[i + 1];
        }
        _size--;
        if (_size % 8 == 0){
            bytes.erase(bytes.end());
        }
    }
};

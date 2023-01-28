#include <iostream>

class String {
private:
    char* characters;
    int size;

    void update_data(const char* characters, int size) {
        this->characters = new char[size];
        for (int i = 0; i < size; i++) {
            this->characters[i] = characters[i];
        }
    }

public:

    String(const char* characters) {
        size = 0;
        while (characters[size]) {
            size++;
        }
        size++;

        update_data(characters, size);
    }

    String(const String& other) {
        this->size = other.size;
        update_data(other.characters, size);
    }

    String& operator = (const String& other) {
        delete[] characters;
        this->size = other.size;
        update_data(other.characters, other.size);
        return *this;
    }
    
    ~String() {
        delete[] characters;
    }

    String operator + (const String& other) {
        char* updated_characters = new char[this->size + other.size - 2];

        for (int i = 0; i < (this->size - 1); i++) {
            updated_characters[i] = this->characters[i];
        }
        for (int i = 0; i < other.size; i++) {
            updated_characters[i + this->size - 1] = other.characters[i];
        }

        String new_string = String(updated_characters);
        delete[] updated_characters;
        return new_string;
    }

    void operator += (const String& other) {
        size = size + other.size - 1;
        char* updated_characters = new char[this->size + other.size - 1];

        for (int i = 0; i < (this->size - 1); i++) {
            updated_characters[i] = this->characters[i];
        }
        for (int i = 0; i < other.size; i++) {
            updated_characters[i + this->size - 1] = other.characters[i];
        }
        delete[] characters;
        characters = updated_characters;
    }

    char& operator [] (int index) {
        return characters[index];
    }

    bool operator < (const String& other) {
        return size < other.size;
    }

    bool operator > (const String& other) {
        return size > other.size;
    }

    bool operator == (const String& other) {
        return size == other.size;
    }

    int find(char c) {
        for (int i = 0; i < size; i++) {
            if (characters[i] == c) {
                return i;
            }
        }
        return -1;
    }

    int length() {
        return size;
    }

    char* str() {
        return characters;
    }

    char at(int n) {
        if (0 <= n && n < size) {
            return characters[n];
        }
        return -1;
    }

    void set_size(int size) {
        this->size = size;
    }

    friend std::ostream& operator << (std::ostream& os, const String& s);
    friend std::istream& operator >> (std::istream& in, String& s);
};

std::ostream& operator << (std::ostream& os, const String& s) {
    os << s.characters;
    return os;
}

std::istream& operator >> (std::istream& in, String& s) {
    in >> s.characters;
    int size = 0;
    while (s.characters[s.size]) {
        size++;
    }
    s.set_size(size + 1);
    return in;
}
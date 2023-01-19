#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <stdexcept>
#include <random>

class FibonacciCode {
private:
    std::vector<int> fibonacci_seq;
    std::vector<int> key;

    bool is_fibonacci_seq(std::vector<int> new_key) {
        int size = new_key.size();
        std::sort(new_key.begin(), new_key.end());
        for (int i = 0; i < size; i++) {
            if (!(fibonacci_seq[i] == new_key[i]))
                return false;
        }
        return true;
    }

    std::vector<std::string> split_into_words(std::string text) {
        std::vector<std::string> words;
        std::stringstream ss(text);
        std::string word;
        while (ss >> word) {
            words.push_back(word);
        }
        return words;
    }

public:
    FibonacciCode() {
        int next_number;
        for (int i = 0; i < 30; i++) {
            if (i == 0) {
                next_number = 1;
            }
            else if (i == 1) {
                next_number = 2;
            }
            else {
                next_number = fibonacci_seq[i - 1] + fibonacci_seq[i - 2];
            }
            fibonacci_seq.push_back(next_number);
        }
    }

    void set_key(std::vector<int> new_key) {
        if (new_key.size() <= 30 && is_fibonacci_seq(new_key)) {
            key = new_key;
        }
        else {
            throw std::exception("Ключ должен быть последовательностью Фибоначчи и состоять меньше чем из 30 элементов");
        }
    }

    std::vector<int> get_key() { return key; }

    std::string encode(std::string src) {
        std::vector<std::string> words = split_into_words(src);

        int words_len = words.size();
        if (words_len != key.size()) {
            throw std::exception("Длина ключа должна быть равна количеству слов в тексте");
        }
        std::stringstream ss_encode;
        for (int i = 0; i < words_len; i++) {
            for (int j = 0; j < words_len; j++) {
                if (key[i] == fibonacci_seq[j]) {
                     if (i != 0) {
                         ss_encode << ' ';
                     }
                     ss_encode << words[j];
                     break;
                }
            }
        }
        return ss_encode.str();
    } 

    std::string decode(std::string src) {
        std::vector<std::string> words = split_into_words(src);

        int words_len = words.size();
        if (words_len != key.size()) {
            throw std::exception("Длина ключа должна быть равна количеству слов в тексте");
        }
        std::stringstream ss_decode;
        for (int i = 0; i < words_len; i++) {
            for (int j = 0; j < words_len; j++) {
                if (key[j] == fibonacci_seq[i]) {
                    if (i != 0) {
                        ss_decode << ' ';
                    }
                    ss_decode << words[j];
                    break;
                }
            }
        }

        ss_decode << std::endl;
        return ss_decode.str();
    }
};

int main()
{
    FibonacciCode coder;
    std::string text = "Hello, my name is Kostya.";
    try {
        coder.set_key({ 2, 8, 5, 1, 3 });
        std::string encoded = coder.encode(text);
        std::cout << encoded << std::endl;
        std::cout << coder.decode(encoded);
    }
    catch(std::exception ex) {
        std::cout << ex.what() << std::endl;
    }
}
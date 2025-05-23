#ifndef FASTREADERFORGRAPHFILES
#define FASTREADERFORGRAPHFILES

typedef unsigned int uint32;
typedef long long int64;
typedef unsigned long long uint64;

#include <fstream>
#include <vector>
#include <string>

class FastGraphReader {
    std::ifstream file_;
    char* buffer_;
    uint64 bufferSize_;
    uint64 position_;
    uint64 dataSize_;

    void fillBuffer_() {
        file_.read(buffer_, bufferSize_);
        dataSize_ = file_.gcount();
        position_ = 0;
    }

public:
    FastGraphReader(const std::string& filename, uint64 buf_size = 1 << 20)
        : bufferSize_(buf_size), position_(0), dataSize_(0) {
       
        std::ios_base::sync_with_stdio(false);
        std::cin.tie(nullptr);
        file_.open(filename, std::ios::binary);
        if (!file_.is_open()) {
            throw std::runtime_error("File wasn't opened.");
        }
        buffer_ = new char[bufferSize_];
        fillBuffer_();
    }

    int parseInt() {
        uint64 result = 0;
        bool found = false;
        char c;

        while (true) {
            if (position_ >= dataSize_) {
                if (file_.eof()) {
                    break;
                }
                fillBuffer_();
                if (dataSize_ == 0) {
                    break;
                }
            }

            c = buffer_[position_++];
            if (c >= '0' && c <= '9') {
                found = true;
                result = result * 10 + (c - '0');
            }
            else if (found) {
                break;
            }
        }

        if (!found) {
            throw std::runtime_error("Invalid number format");
        }

        return result;
    }

    ~FastGraphReader() {
        delete[] buffer_;
        file_.close();
    }

};


#endif 



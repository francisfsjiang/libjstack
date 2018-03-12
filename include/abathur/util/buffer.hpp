#ifndef _ABATHUR_BUFFER_H_
#define _ABATHUR_BUFFER_H_

#include <iostream>

namespace abathur::util {
    class Buffer {
    private:
        const static size_t DEFAULT_BUFFER_SIZE = 1024;
        char* data_;
        size_t len_; //buffer's full length
        size_t pos_;
        size_t size_;
    public:
        Buffer();
        Buffer(int lne);

        size_t capacity() const;
        size_t size() const;

        char* data();

        size_t pos() const;

        int write(const char*, size_t);
        int write(const char*, size_t, size_t);

        int read(size_t src_len, size_t src_pos, char* dst_data) const;
    };
}

#endif //_ABATHUR_BUFFER_H_

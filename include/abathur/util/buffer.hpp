#ifndef _ABATHUR_BUFFER_H_
#define _ABATHUR_BUFFER_H_

#include <iostream>
#include <vector>

namespace abathur::util {
    class Buffer {
        friend std::ostream & operator<<(std::ostream &, Buffer&);
//        friend std::istream & operator>>(std::istream &, Buffer&);

    private:
        const static size_t DEFAULT_BUFFER_SIZE = 1024;
        char* data_;
        size_t capacity_;
        size_t writer_pos_;
        size_t reader_pos_;
    public:
        Buffer();
        Buffer(int);
        Buffer(const Buffer&);

        ~Buffer();

        size_t resize();
        size_t resize(size_t);

        size_t capacity() const;
        size_t writeable_len() const;
        size_t size() const;

        char* data();
        char* data_to_write();
        char* data_to_read() const;

        size_t get_reader_pos() const;
        size_t get_writer_pos() const;

        size_t set_reader_pos(size_t);
        size_t set_writer_pos(size_t);

        size_t write(const char*, size_t);
        size_t read(char*, size_t) const;

        int read(size_t, size_t, char*) const;
        int shrink();

    };
}

#endif //_ABATHUR_BUFFER_H_

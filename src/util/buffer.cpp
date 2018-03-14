#include "abathur/util/buffer.hpp"

#include <algorithm>
#include <cstring>

namespace abathur::util {
    Buffer::Buffer() {
        data_ = new char[DEFAULT_BUFFER_SIZE];
        len_ = DEFAULT_BUFFER_SIZE;
        pos_ = 0;
        size_ = 0;
    }

    Buffer::Buffer(int len) {
        data_ = new char[len];
    }

    size_t Buffer::capacity() const {
        return len_;
    }

    size_t Buffer::size() const {
        return size_;
    }

    size_t Buffer::pos() const {
        return pos_;
    }

    char* Buffer::data() {
        return data_;
    }

    int Buffer::write(const char* src_data, size_t src_len) {
        return write(src_data, src_len, pos_);
    }
    int Buffer::write(const char* src_data, size_t src_len, size_t dst_pos) {
        size_t cp_len = src_len + dst_pos > len_ ? len_ - dst_pos: src_len + dst_pos;
        memcpy(data_ + dst_pos, src_data, cp_len);
        size_ += cp_len;
        pos_ += cp_len;
        return static_cast<int>(cp_len);
    }

    int Buffer::read(size_t src_len, size_t src_pos, char* dst_data) const {

        memcpy(dst_data, data_ + src_pos, src_len);
        return static_cast<int>(src_len);
    }
}

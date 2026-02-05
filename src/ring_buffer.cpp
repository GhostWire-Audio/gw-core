#include "gw/core/ring_buffer.h"
#include <cstdlib>
#include <cstring>
#include <algorithm>

namespace gw::core {
    RingBuffer::RingBuffer(const size_t capacity)
        : capacity_(capacity + 1), // +1 to distinguish full from empty
          buffer_(nullptr),
          write_pos_(0),
          read_pos_(0) {
        if (capacity_ > 0) {
            buffer_ = new float[capacity_];
            std::memset(buffer_, 0, capacity_ * sizeof(float));
        }
    }

    RingBuffer::~RingBuffer() {
        free_memory();
    }

    RingBuffer::RingBuffer(RingBuffer &&other) noexcept
        : capacity_(other.capacity_),
          buffer_(other.buffer_),
          write_pos_(other.write_pos_.load()),
          read_pos_(other.read_pos_.load()) {
        other.capacity_ = 0;
        other.buffer_ = nullptr;
        other.write_pos_ = 0;
        other.read_pos_ = 0;
    }

    RingBuffer &RingBuffer::operator=(RingBuffer &&other) noexcept {
        if (this != &other) {
            free_memory();

            capacity_ = other.capacity_;
            buffer_ = other.buffer_;
            write_pos_.store(other.write_pos_.load());
            read_pos_.store(other.read_pos_.load());

            other.capacity_ = 0;
            other.buffer_ = nullptr;
            other.write_pos_ = 0;
            other.read_pos_ = 0;
        }
        return *this;
    }

    size_t RingBuffer::write(const float *data, size_t count) {
        if (!buffer_ || !data) return 0;

        const size_t available = get_available_write();
        const size_t to_write = std::min(count, available);

        size_t write_idx = write_pos_.load(std::memory_order_relaxed);

        for (size_t i = 0; i < to_write; ++i) {
            buffer_[write_idx] = data[i];
            write_idx = (write_idx + 1) % capacity_;
        }

        // Release fence: ensure all writes complete before updating write_pos
        write_pos_.store(write_idx, std::memory_order_release);

        return to_write;
    }

    size_t RingBuffer::read(float *data, size_t count) {
        if (!buffer_ || !data) return 0;

        const size_t available = get_available_read();
        const size_t to_read = std::min(count, available);

        size_t read_idx = read_pos_.load(std::memory_order_relaxed);
        for (size_t i = 0; i < to_read; ++i) {
            data[i] = buffer_[read_idx];
            read_idx = (read_idx + 1) % capacity_;
        }

        // Release fence: ensure all reads complete before updating read_pos
        read_pos_.store(read_idx, std::memory_order_release);

        return to_read;
    }

    size_t RingBuffer::get_available_read() const {
        const size_t write_idx = write_pos_.load(std::memory_order_acquire);
        const size_t read_idx = read_pos_.load(std::memory_order_acquire);

        if (write_idx >= read_idx) {
            return write_idx - read_idx;
        } else {
            return capacity_ - read_idx + write_idx;
        }
    }

    size_t RingBuffer::get_available_write() const {
        const size_t available_read = get_available_read();

        // capacity - 1 because we reserve one slot to distinguish full from empty
        return (capacity_ - 1) - available_read;
    }

    void RingBuffer::clear() {
        write_pos_.store(0, std::memory_order_relaxed);
        read_pos_.store(0, std::memory_order_relaxed);
    }

    void RingBuffer::free_memory() {
        if (buffer_) {
            delete[] buffer_;
            buffer_ = nullptr;
        }
    }
}

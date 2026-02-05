#ifndef GW_CORE_RING_BUFFER_H
#define GW_CORE_RING_BUFFER_H

#include <cstddef>
#include <atomic>

namespace gw::core {
    /**
        *  A lock-free, single-producer single-consumer (SPSC) ring buffer.
        *
        *  This is designed for communication between non-real-time thread
        *  (producer) and a real-time audio thread (consumer).
        *
        *  CRITICAL USAGE RULES:
        *  - Only ONE thread can write (producer)
        *  - Only ONE thread can read (consumer)
        *  - Do NOT use with multiple producers or consumers
        *
        *  This implementation uses atomic operations for thread safety
        *  without locks, making it suitable for real-time audio
        *
        *  The buffer stores float samples. For multichannel audio,
        *  you typically create one RingBuffer per channel or interleave
        *  the channels yourself.
        */
    class RingBuffer {
    public:
        /**
         *  Create a ring buffer.
         *
         *  @param capacity Number of samples the buffer can hold
         *
         *  Note: Actual capacity is capacity-1 to distinguish full from empty
         */
        explicit RingBuffer(size_t capacity);

        ~RingBuffer();

        // Ring buffers should not be copied (they manage memory)
        RingBuffer(const RingBuffer &) = delete;

        RingBuffer &operator=(const RingBuffer &) = delete;

        // Move is allowed
        RingBuffer(RingBuffer &&other) noexcept;

        RingBuffer &operator=(RingBuffer &&other) noexcept;

        /**
         *  Write samples to the buffer (producer side)
         *
         *  @param data Samples to write
         *  @param count Number of samples
         *  @return Number of samples actually written (may be less if the buffer is full)
         *
         *  NOT real-time safe (allocates if buffer is full).
         *  Typically called from main/UI thread
         */
        size_t write(const float *data, size_t count);

        /**
         *  Read samples from the buffer (consumer side).
         *
         *  @param data Destination for samples
         *  @param count Number of samples to read
         *  @return Number of samples actually read (may be less if buffer is empty)
         *
         *  IS real-time safe.
         *  Typically called from the audio thread.
         */
        size_t read(float *data, size_t count);

        /**
         *  Get number of samples available to ead.
         *
         *  Real-time safe.
         */
        [[nodiscard]] size_t get_available_read() const;

        /**
         *  Get number of samples that can be written.
         *
         *  Real-time safe.
         */
        [[nodiscard]] size_t get_available_write() const;

        /**
         *  Clear all data (reset read/write positions).
         *
         *  NOT real-time safe (requires synchronization).
         *  Should only be called when audio is stopped.
         */
        void clear();

        /**
         *  Get total capacity
         */
        [[nodiscard]] size_t get_capacity() const { return capacity_; }

    private:
        size_t capacity_;
        float *buffer_;

        // Atomic indices for lock-free operation
        std::atomic<size_t> write_pos_;
        std::atomic<size_t> read_pos_;

        void free_memory();
    };
}

#endif //GW_CORE_RING_BUFFER_H

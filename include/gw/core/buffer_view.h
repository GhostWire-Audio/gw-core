#ifndef GW_CORE_BUFFER_VIEW_H
#define GW_CORE_BUFFER_VIEW_H

#include <cstddef>

namespace gw::core {
    // Forward declaration
    class AudioBuffer;
    /**
        *  A non-owning view into an audio buffer or channel.
        *
        *  This is like std::span<float> but with channel awareness.
        *
        *  BufferView is cheap to copy (just like pointers and sizes).
        *  It does NOT own the memory - the underlying buffer must
        *  outlive all views that point to it.
        *
        *  This is real-time safe (no allocations).
        */
    class BufferView {
    public:
        /**
         *  Construct an empty view.
         */
        BufferView();

        /**
         *  Construct a view of a single channel.
         *
         *  @param data Pointer to sample data
         *  @param num_samples Number of samples
         */
        BufferView(float *data, size_t num_samples);

        /**
         *  Construct a view from an AudioBuffer channel.
         *
         *  @param buffer Buffer to view
         *  @param channel Channel index
         */
        BufferView(AudioBuffer &buffer, size_t channel);

        // Default copy/move - all cheap
        BufferView(const BufferView &) = default;

        BufferView &operator=(const BufferView &) = default;

        BufferView(BufferView &&) = default;

        BufferView &operator=(BufferView &&) = default;

        // Accessors
        float *data() { return data_; }
        [[nodiscard]] const float *data() const { return data_; }
        [[nodiscard]] size_t size() const { return num_samples_; }
        [[nodiscard]] bool empty() const { return num_samples_ == 0 || data_ == nullptr; }

        // Array-like access
        float &operator[](size_t index) { return data_[index]; }
        const float &operator[](size_t index) const { return data_[index]; }

        /**
         *  Get a sub-view (slice) of this view.
         *
         *  @param offset Starting sample index
         *  @param count Number of samples (or 0 for "rest of buffer")
         *  @return View of the subrange
         */
        [[nodiscard]] BufferView subview(size_t offset, size_t count = 0) const;

        /**
         *  Fill with a constant value.
         *  Real-time safe.
         */
        void fill(float value);

        /**
         *  Clear to zero (silence).
         *  Real-time safe.
         */
        void clear();

    private:
        float *data_;
        size_t num_samples_;
    };
}

#endif //GW_CORE_BUFFER_VIEW_H

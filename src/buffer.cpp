#include "gw/core/buffer.h"
#include <new>  // for std::nothrow

namespace gw::core {
    AudioBuffer::AudioBuffer(size_t num_channels, size_t num_samples)
        : num_channels_(num_channels),
          num_samples_(num_samples),
          data_(nullptr) {
        // Allocate channel pointers
        data_ = new(std::nothrow) float *[num_channels_];
        if (!data_) return;

        // Allocate sample data for each channel
        for (size_t ch = 0; ch < num_channels_; ++ch) {
            data_[ch] = new(std::nothrow) float[num_samples_]();
        }
    }

    AudioBuffer::~AudioBuffer() {
        if (data_) {
            for (size_t ch = 0; ch < num_channels_; ++ch) {
                delete[] data_[ch];
            }
            delete[] data_;
        }
    }
} // namespace gw::core

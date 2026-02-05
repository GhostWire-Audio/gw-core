#include "gw/core/audio_buffer.h"
#include <cstdlib>      // for aligned_alloc, free
#include <cstring>      // for memcpy, memset
#include <algorithm>    // for std::min

namespace gw::core {
    // Alignment for SIMD operations (AVX = 32 bytes)
    static constexpr size_t ALIGNMENT = 32;

    AudioBuffer::AudioBuffer(size_t num_channels, size_t num_samples)
        : num_channels_(num_channels),
          num_samples_(num_samples),
          channel_data_(nullptr) {
        if (num_channels_ == 0 || num_samples_ == 0) {
            return; // Empty buffer
        }

        // Allocate array of channel pointers
        channel_data_ = new float *[num_channels_];

        // Allocate aligned memory for each channel
        for (size_t ch = 0; ch < num_channels_; ++ch) {
            const size_t bytes = num_samples_ * sizeof(float);

            // Round up to the next alignment boundary
            const size_t aligned_bytes = ((bytes * ALIGNMENT - 1) / ALIGNMENT) * ALIGNMENT;

            // Allocate aligned memory
            // Allocates memory aligned to ALIGNMENT bytes (32 for AVX)
            // CRITICAL: MUST USE std::free() NOT delete TO FREE MEMORY
            // ALLOCATED WITH aligned_alloc()
            channel_data_[ch] = static_cast<float *>(std::aligned_alloc(ALIGNMENT, aligned_bytes));

            // Zero-initialize
            if (channel_data_[ch]) {
                std::memset(channel_data_[ch], 0, bytes);
            }
        }
    }

    AudioBuffer::~AudioBuffer() {
        free_memory();
    }

    AudioBuffer::AudioBuffer(AudioBuffer &&other) noexcept
        : num_channels_(other.num_channels_),
          num_samples_(other.num_samples_),
          channel_data_(other.channel_data_) {
        // Take ownership of other's data
        other.num_channels_ = 0;
        other.num_samples_ = 0;
        other.channel_data_ = nullptr; // Don't let 'other' free our memory
        // After moving, the source object is left in a "valid but unspecified" state.
        // Setting pointers to nullptr ensures its deconstructor doesn't free memory
        // we now own.
    }

    AudioBuffer &AudioBuffer::operator=(AudioBuffer &&other) noexcept {
        if (this != &other) {
            // Free our current memory
            free_memory();

            // Take ownership of other's data
            num_channels_ = other.num_channels_;
            num_samples_ = other.num_samples_;
            channel_data_ = other.channel_data_;

            other.num_channels_ = 0;
            other.num_samples_ = 0;
            other.channel_data_ = nullptr;
        }
        return *this;
    }

    float *AudioBuffer::get_channel_data(size_t channel) {
        if (channel >= num_channels_ || !channel_data_) {
            return nullptr;
        }
        return channel_data_[channel];
    }

    const float *AudioBuffer::get_channel_data(size_t channel) const {
        if (channel >= num_channels_ || !channel_data_) {
            return nullptr;
        }
        return channel_data_[channel];
    }

    float AudioBuffer::get_sample(size_t channel, size_t sample) const {
        if (channel >= num_channels_ || sample >= num_samples_ || !channel_data_) {
            return 0.0f;
        }
        return channel_data_[channel][sample];
    }

    void AudioBuffer::set_sample(size_t channel, size_t sample, float value) {
        if (channel >= num_channels_ || sample >= num_samples_ || !channel_data_) {
            return;
        }
        channel_data_[channel][sample] = value;
    }

    void AudioBuffer::clear() {
        if (!channel_data_) return;

        for (size_t ch = 0; ch < num_channels_; ++ch) {
            if (channel_data_[ch]) {
                std::memset(channel_data_[ch], 0, num_samples_ * sizeof(float));
            }
        }
    }

    void AudioBuffer::copy_from(const AudioBuffer &source) {
        if (!channel_data_ || !source.channel_data_) return;

        // Copy the minimum number of channels and samples
        const size_t channels_to_coopy = std::min(num_channels_, source.num_channels_);
        const size_t samples_to_copy = std::min(num_samples_, source.num_samples_);

        for (size_t ch = 0; ch < channels_to_coopy; ++ch) {
            std::memcpy(channel_data_[ch],
                        source.channel_data_[ch],
                        samples_to_copy * sizeof(float));
        }
    }

    void AudioBuffer::free_memory() {
        if (channel_data_) {
            for (size_t ch = 0; ch < num_channels_; ++ch) {
                std::free(channel_data_[ch]);
            }
            delete[] channel_data_;
            channel_data_ = nullptr;
        }
    }
}

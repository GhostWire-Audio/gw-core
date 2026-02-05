#ifndef GW_CORE_AUDIO_BUFFER_H
#define GW_CORE_AUDIO_BUFFER_H

#include <cstddef>

namespace gw::core {
    /**
     *  A multichannel audio buffer with aligned memory.
     *
     *  Memory layout: planar (non-interleaved)
     *      Channel 0: [sample0, sample1, sample 2, ...]
     *      Channel 1: [sample0, sample1, sample 2, ...]
     *      Channel 2: [sample0, sample1, sample 2, ...]
     *
     *  This is the format preferred by most DSP algorithms and SIMD operations
     *
     *  IMPORTANT: This class allocates memory in the constructor.
     *  DO NOT create AudioBuffer objects in the real-time audio thread!
     *  Create them in advance and reuse them.
     */
    class AudioBuffer {
    public:
        /**
         *  Create an audio buffer
         *
         *  @param num_channels Number of audio channels
         *  @param num_samples Number of samples per channel
         *
         *  Memory is allocated and zero-initialized.
         *  Allocation uses 32-byte alignment for AVX compatibility.
         */
        AudioBuffer(size_t num_channels, size_t num_samples);

        /**
         *  Destructor frees aligned memory.
         */
        ~AudioBuffer();

        // Audio buffers are expensive to copy - disable copy operations
        AudioBuffer(const AudioBuffer &) = delete;

        AudioBuffer &operator=(const AudioBuffer &) = delete;

        // Move operations are allowed (transfer ownership)
        AudioBuffer(AudioBuffer &&other) noexcept;

        AudioBuffer &operator=(AudioBuffer &&other) noexcept;

        // Accessors
        [[nodiscard]] size_t get_num_channels() const { return num_channels_; }
        [[nodiscard]] size_t get_num_samples() const { return num_samples_; };

        /**
         *  Get pointer to a specific channel's data.
         *
         *  @param channel Channel index (0 to num_channels-1)
         *  @return Pointer to channel data, or null ptr if channel is out of range
         */
        float *get_channel_data(size_t channel);

        [[nodiscard]] const float *get_channel_data(size_t channel) const;

        /**
         *  Get a specific sample from a specific channel
         *
         *  @param channel Channel index
         *  @param sample Sample index
         *  @return Sample value, or 0.0f if the indices are out of range.
         */
        [[nodiscard]] float get_sample(size_t channel, size_t sample) const;

        /**
         *  Set a specific sample in a specific channel
         *
         *  @param channel Channel index
         *  @param sample Sample index
         *  @param value Sample value
         */
        void set_sample(size_t channel, size_t sample, float value);

        /**
         *  Clear all samples to zero (silence).
         *  This is real-time safe (just writes zeros).
         */
        void clear();

        /**
         *  Copy data from another buffer.
         *
         *  @param source Buffer to copy from
         *
         *  Copies min(this->samples, source->samples) samples
         *  from min(this->channels, source->channels) channels.
         *
         *  This is NOT real-time safe due to potential cache misses
         *  with large buffers, but it's fine for offline processing.
         */
        void copy_from(const AudioBuffer &source);

    private:
        size_t num_channels_;
        size_t num_samples_;
        float **channel_data_; // Array of pointers to channel data

        // Helper to free memory
        void free_memory();
    };
}

#endif

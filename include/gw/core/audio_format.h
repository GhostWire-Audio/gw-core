#ifndef GW_CORE_AUDIO_FORMAT_H
#define GW_CORE_AUDIO_FORMAT_H

#include <cstddef>
#include <cstdint>

namespace gw::core {
    /**
     *  Describes the format of an audio stream.
     *
     *  Immutable once created, real-time audio threads need stable format information
     */
    class AudioFormat {
    public:
        /**
         * Constructs an audio format
         *
         * @param sample_rate Samples per second (e.g., 44100, 48000)
         * @param num_channels Number of audio channels (e.g., 1 = mono, 2 = stereo)
         * @param bit_depth Bits per sample (typically 16, 24, or 32)
         */
        AudioFormat(uint32_t sample_rate,
                    uint32_t num_channels,
                    uint32_t bit_depth);

        // Getters
        [[nodiscard]] uint32_t get_sample_rate() const { return sample_rate_; }
        [[nodiscard]] uint32_t get_num_channels() const { return num_channels_; }
        [[nodiscard]] uint32_t get_bit_depth() const { return bit_depth_; }

        /**
         *  Calculates bytes per sample based on bit depth.
         *  Assumes packed samples (no padding).
         */
        [[nodiscard]] size_t get_bytes_per_sample() const;

        /**
         *  Calculate bytes per frame (one sample for all channels).
         */
        [[nodiscard]] size_t get_bytes_per_frame() const;

        // Equality comparison
        bool operator==(const AudioFormat &other) const;

        bool operator!=(const AudioFormat &other) const;

    private:
        uint32_t sample_rate_; // Hz
        uint32_t num_channels_; // 1=mono, 2=stereo, etc.
        uint32_t bit_depth_; // bits per sample
    };
}


#endif //GW_CORE_AUDIO_FORMAT_H


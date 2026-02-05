#include "gw/core/audio_format.h"

namespace gw::core {
    AudioFormat::AudioFormat(uint32_t sample_rate,
                             uint32_t num_channels,
                             uint32_t bit_depth)
        : sample_rate_(sample_rate),
          num_channels_(num_channels),
          bit_depth_(bit_depth) {
        // Could add validation here:
        // - Is sample_rate reasonable? (e.g. 8000 to 192000)
        // - Is num_channels > 0?
        // - Is bit_depth valid? (8, 16, 24, 32)
        // For now, we're gonna trust the caller, but I may implement these later on
    }

    size_t AudioFormat::get_bytes_per_sample() const {
        // Integer division rounds down, so we round up
        return (bit_depth_ + 7) / 8;
    }

    size_t AudioFormat::get_bytes_per_frame() const {
        return get_bytes_per_sample() * num_channels_;
    }

    bool AudioFormat::operator==(const AudioFormat &other) const {
        return sample_rate_ == other.sample_rate_ &&
               num_channels_ == other.num_channels_ &&
               bit_depth_ == other.bit_depth_;
    }

    bool AudioFormat::operator!=(const AudioFormat &other) const {
        return !(*this == other);
    }
}

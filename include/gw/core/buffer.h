#ifndef GW_CORE_BUFFER_H
#define GW_CORE_BUFFER_H

#include <cstddef>

namespace gw {
namespace core {

/**
 *  A simple audio buffer for demonstration
 *
 *  This is a placeholder to show the project structure.
 *  Real implementation will come in later milestones.
 */
class AudioBuffer {
public:
    AudioBuffer(size_t num_channels, size_t num_samples);
    ~AudioBuffer();

    // Delete copy operations (we'll add proper ones later)
    AudioBuffer(const AudioBuffer&) = delete;
    AudioBuffer& operator=(const AudioBuffer&) = delete;

    size_t get_num_channels() const { return num_channels_; };
    size_t get_num_samples() const { return num_samples_; };

private:
    size_t num_channels_;
    size_t num_samples_;
    float** data_;  // 2D array: channels x samples
};

}   // namespace core
}   // namespace gw

#endif  // GW_CORE_BUFFER_H
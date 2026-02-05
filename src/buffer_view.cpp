#include "gw/core/buffer_view.h"
#include "gw/core/audio_buffer.h"
#include <cstring>
#include <algorithm>

namespace gw::core {
    BufferView::BufferView()
        : data_(nullptr),
          num_samples_(0) {
    }

    BufferView::BufferView(float *data, size_t num_samples)
        : data_(data),
          num_samples_(num_samples) {
    }

    BufferView::BufferView(AudioBuffer &buffer, size_t channel)
        : data_(buffer.get_channel_data(channel)),
          num_samples_(buffer.get_num_samples()) {
    }

    BufferView BufferView::subview(size_t offset, size_t count) const {
        if (offset >= num_samples_ || !data_) {
            return {}; // Empty view
        }

        const size_t remaining = num_samples_ - offset;
        const size_t actual_count = (count == 0) ? remaining : std::min(count, remaining);

        return {data_ + offset, actual_count};
    }

    void BufferView::fill(float value) {
        if (!data_) return;

        for (size_t i = 0; i < num_samples_; ++i) {
            data_[i] = value;
        }
    }

    void BufferView::clear() {
        if (!data_) return;
        std::memset(data_, 0, num_samples_ * sizeof(float));
    }
}

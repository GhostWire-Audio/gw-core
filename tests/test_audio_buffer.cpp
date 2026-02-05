#include <gw/core/audio_buffer.h>
#include <cassert>
#include <iostream>
#include <cmath>

void test_audio_buffer() {
    // Test construction
    gw::core::AudioBuffer buffer(2, 512);

    assert(buffer.get_num_channels() == 2);
    assert(buffer.get_num_samples() == 512);

    // Test that memory is zero-initialized
    for (size_t ch = 0; ch < 2; ++ch) {
        const float *data = buffer.get_channel_data(ch);
        assert(data != nullptr);
        for (size_t i = 0; i < 512; ++i) {
            assert(data[i] == 0.0f);
        }
    }

    std::cout << "  - Construction and initialization: OK" << std::endl;

    // Test sample access
    buffer.set_sample(0, 100, 0.5f);
    assert(buffer.get_sample(0, 100) == 0.5f);
    assert(buffer.get_sample(1, 100) == 0.0f);

    std::cout << "  - Sample access: OK" << std::endl;

    // Test clear
    buffer.clear();
    assert(buffer.get_sample(0, 100) == 0.0f);

    std::cout << "  - Clear: OK" << std::endl;

    // Test copy_from
    gw::core::AudioBuffer source(2, 512);
    for (size_t i = 0; i < 512; ++i) {
        float phase = static_cast<float>(i) / 512.0f;
        source.set_sample(0, i, std::sin(2.0f * 3.14159f * phase));
    }

    buffer.copy_from(source);

    for (size_t i = 0; i < 512; ++i) {
        assert(buffer.get_sample(0, i) == source.get_sample(0, i));
    }

    std::cout << "  - Copy: OK" << std::endl;

    // Test move semantics
    const gw::core::AudioBuffer moved = std::move(buffer);
    assert(moved.get_num_channels() == 2);
    assert(moved.get_num_samples() == 512);
    assert(buffer.get_channel_data(0) == nullptr); // Original is now empty

    std::cout << "  - Move semantics: OK" << std::endl;
}

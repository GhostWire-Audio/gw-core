#include <gw/core/audio_format.h>
#include <cassert>
#include <iostream>

void test_audio_format() {
    // Test construction
    const gw::core::AudioFormat format(48000, 2, 24);

    assert(format.get_sample_rate() == 48000);
    assert(format.get_num_channels() == 2);
    assert(format.get_bit_depth() == 24);
    // Test bytes per sample calculation
    assert(format.get_bytes_per_sample() == 3); // 24 bits = 3 bytes

    // Test bytes per frame
    assert(format.get_bytes_per_frame() == 6); // 2 channels * 3 bytes

    // Test equality
    const gw::core::AudioFormat format2(48000, 2, 24);
    assert(format == format2);

    const gw::core::AudioFormat format3(44100, 2, 24);
    assert(format != format3);

    std::cout << "  - Construction: OK" << std::endl;
    std::cout << "  - Byte calculations: OK" << std::endl;
    std::cout << "  - Equality: OK" << std::endl;
}

#include <gw/core/version.h>
#include <gw/core/audio_format.h>
#include <gw/core/audio_buffer.h>
#include <gw/core/buffer_view.h>
#include <gw/core/ring_buffer.h>
#include <iostream>
#include <cmath>

int main() {
    std::cout << "=== GhostWire Audio Engine ===" << std::endl;
    std::cout << gw::core::get_version_string() << std::endl;
    std::cout << std::endl;

    // 1. Audio Format
    std::cout << "1. Audio Format" << std::endl;
    gw::core::AudioFormat format(48000, 2, 24);
    std::cout << "  Sample Rate: " << format.get_sample_rate() << " Hz" << std::endl;
    std::cout << "  Channels: " << format.get_num_channels() << std::endl;
    std::cout << "  Bit Depth: " << format.get_bit_depth() << " bits" << std::endl;
    std::cout << "  Bytes/Sample: " << format.get_bytes_per_sample() << std::endl;
    std::cout << std::endl;

    // 2. Audio Buffer
    std::cout << "2. Audio Buffer (aligned memory)" << std::endl;
    gw::core::AudioBuffer buffer(2, 512);
    std::cout << "  Created buffer: " << buffer.get_num_channels()
            << " channels × " << buffer.get_num_samples() << " samples" << std::endl;

    // Generate a sine wave in channel 0
    float frequency = 440.0f;
    float sample_rate = 48000.0f;
    for (size_t i = 0; i < buffer.get_num_channels(); i++) {
        float sample = std::sin(2.0f * 3.14159f * frequency * static_cast<float>(i) / sample_rate);
        buffer.set_sample(0, i, sample);
    }
    std::cout << "  Generated 440 Hz sine wave in channel 0" << std::endl;
    std::cout << std::endl;

    // 3. Buffer View
    std::cout << "3. Buffer View (non-owning access)" << std::endl;
    gw::core::BufferView view(buffer, 0);
    std::cout << "  Created view of channel 0: " << view.size() << " samples" << std::endl;

    auto first_quarter = view.subview(0, 128);
    std::cout << "  Created subview: samples 0-127" << std::endl;
    std::cout << "  First sample: " << first_quarter[0] << std::endl;
    std::cout << std::endl;

    // 4. Ring Buffer
    std::cout << "4. Ring Buffer (lock-free)" << std::endl;
    gw::core::RingBuffer ring(1024);
    std::cout << "  Created ring buffer with capacity: " << ring.get_capacity() - 1 << std::endl;

    // Write some sine wave data
    float write_data[256];
    for (size_t i = 0; i < 256; ++i) {
        write_data[i] = std::sin(2.0f * 3.14159f * static_cast<float>(i) / 256.0f);
    }

    size_t written = ring.write(write_data, 256);
    std::cout << "  Wrote " << written << " samples" << std::endl;
    std::cout << "  Available to read: " << ring.get_available_read() << std::endl;
    std::cout << "  Available to write: " << ring.get_available_write() << std::endl;

    // Read them back
    float read_data[256];
    size_t read_count = ring.read(read_data, 256);
    std::cout << "  Read " << read_count << " samples" << std::endl;
    std::cout << "  Ring buffer now empty: " << (ring.get_available_read() == 0 ? "yes" : "no") << std::endl;
    std::cout << std::endl;

    std::cout << "Milestone 1 complete! Real-time audio buffers are ready." << std::endl;

    return 0;
}

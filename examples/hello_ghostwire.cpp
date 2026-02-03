#include <gw/core/version.h>
#include <gw/core/buffer.h>
#include <iostream>

int main() {
    std::cout << "=== GhostWire Audio Engine ===" << std::endl;
    std::cout << gw::core::get_version_string() << std::endl;
    std::cout << std::endl;

    // Create a simple buffer
    const gw::core::AudioBuffer buffer(2, 512); // 2 channels, 512 samples

    std::cout << "Created audio buffers:" << std::endl;
    std::cout << " Channels: " << buffer.get_num_channels() << std::endl;
    std::cout << " Samples: " << buffer.get_num_samples() << std::endl;

    return 0;
}

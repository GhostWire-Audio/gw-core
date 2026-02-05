#include <gw/core/ring_buffer.h>
#include <cassert>
#include <iostream>
#include <vector>

void test_ring_buffer() {
    gw::core::RingBuffer ring(100);

    assert(ring.get_capacity() == 101); // +1 for full/empty distinction
    assert(ring.get_available_read() == 0);
    assert(ring.get_available_write() == 100);

    std::cout << "  - Construction: OK" << std::endl;

    // Write some data
    const std::vector<float> write_data = {1.0f, 2.0f, 3.0f, 4.0f, 5.0f};
    const size_t written = ring.write(write_data.data(), write_data.size());

    assert(written == 5);
    assert(ring.get_available_read() == 5);
    assert(ring.get_available_write() == 95);

    std::cout << "  - Write: OK" << std::endl;

    // Read data back
    std::vector<float> read_data(5);
    const size_t read_count = ring.read(read_data.data(), read_data.size());

    assert(read_count == 5);
    assert(ring.get_available_read() == 0);
    assert(ring.get_available_write() == 100);

    for (size_t i = 0; i < 5; i++) {
        assert(read_data[i] == write_data[i]);
    }
    std::cout << "  - Read: OK" << std::endl;

    // Test wraparound
    const std::vector<float> large_data(60, 7.0f);
    ring.write(large_data.data(), large_data.size());
    ring.write(large_data.data(), large_data.size()); // This wraps around

    assert(ring.get_available_read() == 100); // Full (minus 1)

    std::vector<float> read_back(100);
    ring.read(read_back.data(), 100);

    assert(ring.get_available_read() == 0);

    std::cout << "  - Wraparound: OK" << std::endl;
    // Test clear
    ring.write(write_data.data(), write_data.size());
    ring.clear();

    assert(ring.get_available_read() == 0);
    assert(ring.get_available_write() == 100);

    std::cout << "  - Clear: OK" << std::endl;
}

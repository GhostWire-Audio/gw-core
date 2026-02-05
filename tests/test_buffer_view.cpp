#include <gw/core/buffer_view.h>
#include <gw/core/audio_buffer.h>
#include <cassert>
#include <iostream>

void test_buffer_view() {
    // Create a buffer to view
    gw::core::AudioBuffer buffer(2, 100);

    // Fill with test data
    for (size_t i = 0; i < 100; ++i) {
        buffer.set_sample(0, i, static_cast<float>(i));
    }

    // Create a view
    gw::core::BufferView view(buffer, 0);

    assert(view.size() == 100);
    assert(!view.empty());
    assert(view[0] == 0.0f);
    assert(view[50] == 50.0f);

    std::cout << "  - Basic view: OK" << std::endl;

    // Test subview
    auto subview = view.subview(10, 20);
    assert(subview.size() == 20);
    assert(subview[0] == 10.0f); // First element of a subview
    assert(subview[19] == 29.0f); // Last element of a subview

    std::cout << "  - Subview: OK" << std::endl;

    // Test fill
    subview.fill(99.0f);
    for (size_t i = 0; i < 20; ++i) {
        assert(subview[i] == 99.0f);
    }

    // Verify it affected the original buffer
    assert(buffer.get_sample(0, 10) == 99.0f);
    assert(buffer.get_sample(0, 29) == 99.0f);
    assert(buffer.get_sample(0, 9) == 9.0f);
    assert(buffer.get_sample(0, 30) == 30.0f);

    std::cout << "  - Fill: OK" << std::endl;

    // Test clear
    subview.clear();
    for (size_t i = 0; i < 20; ++i) {
        assert(subview[i] == 0.0f);
    }

    std::cout << "  - Clear: OK" << std::endl;
}

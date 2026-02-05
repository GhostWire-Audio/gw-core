#include <iostream>

// Forward declarations of test functions
void test_audio_format();

void test_audio_buffer();

void test_buffer_view();

void test_ring_buffer();

int main() {
    std::cout << "=== Running GhostWire Core Tests ===" << std::endl;

    try {
        std::cout << "\n[1/4] Testing AudioFormat..." << std::endl;
        test_audio_format();
        std::cout << "  ✓ AudioFormat tests passed" << std::endl;

        std::cout << "\n[2/4] Testing AudioBuffer..." << std::endl;
        test_audio_buffer();
        std::cout << "  ✓ AudioBuffer tests passed" << std::endl;

        std::cout << "\n[3/4] Testing BufferView..." << std::endl;
        test_buffer_view();
        std::cout << "  ✓ BufferView tests passed" << std::endl;

        std::cout << "\n[4/4] Testing RingBuffer..." << std::endl;
        test_ring_buffer();
        std::cout << "  ✓ RingBuffer tests passed" << std::endl;

        std::cout << "\n=== All tests passed! ===" << std::endl;
        return 0;
    } catch (const std::exception &e) {
        std::cerr << "\n✗ Test failed: " << e.what() << std::endl;
        return 1;
    }
}

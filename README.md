# gw-core

Real-time audio DSP engine for GhostWire Audio.

## Status: Milestone 1 Complete ✓

### Current Features

- **AudioBuffer**: Aligned memory buffers for multi-channel audio
- **BufferView**: Non-owning views into buffers (like `std::span`)
- **AudioFormat**: Audio stream metadata (sample rate, channels, bit depth)
- **RingBuffer**: Lock-free SPSC ring buffer for thread communication
- **Unit Tests**: Comprehensive test coverage

### Build Instructions

```bash
mkdir build && cd build
cmake ..
cmake --build .
```

### Run Tests

```bash
./tests/gw-core-tests
```

### Run Example

```bash
./examples/hello_ghostwire
```

## Architecture

This is a library-first design:

- `include/gw/core/` - Public API headers
- `src/` - Private implementation
- `examples/` - Demonstration programs
- `tests/` - Unit tests

## Next: Milestone 2

- DSP node interface
- Parameter system with smoothing
- Basic DSP processors (gain, pan, mix)
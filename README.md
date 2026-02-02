# GW-Core  
*The engine room of GhostWire Audio*

GW-Core is a real-time, cross-platform C++ audio engine and DSP framework focused on building sound software that is fast, safe, and understandable.

This project exists to explore how audio systems actually work at a low level: buffers, threads, parameter smoothing, DSP graphs, and the rules that keep real-time code from falling apart under pressure.

It’s designed as a **library first**, not an app. Other tools and plugins in the GhostWire ecosystem build on top of this.

---

## What This Is

- A headless C++ audio engine
- A modular DSP node and graph system
- A real-time safe parameter and messaging model
- An offline renderer for testing and analysis
- A foundation for plugins and creative tools

---

## Design Goals

- **Real-time safety**  
  No memory allocation, locks, or blocking calls in the audio thread.

- **Clarity over cleverness**  
  The code should be readable by someone learning systems programming, not just impressive to experts.

- **Testability**  
  Offline rendering and deterministic processing paths are first-class features.

- **Cross-platform**  
  Built to run on Windows, Linux, and macOS.

---

## Status

This is an active research project. APIs will change. Systems will be refactored. Stability comes after understanding.

---

## Structure

- `include/` — Public API
- `src/` — Engine internals
- `apps/` — Command-line tools and experiments
- `tests/` — Unit and regression tests

---

## Part of GhostWire Audio

GW-Core is part of the **GhostWire Audio** open-source lab for exploring real-time sound systems and creative DSP.

If you’re curious about how audio software is built under the hood, you’re in the right place.

# Redstar Designer

A lightweight amp control-surface application built in C++ with JUCE,
exploring the architecture patterns behind connected guitar-amp software
such as preset editors and patch managers.

This is a deliberately scoped demonstration of **application** engineering —
not a DSP engine. The focus is clean state management, a maintainable
component architecture, and reliable preset handling: the data-flow concerns
that sit at the heart of connected audio products.

## Architecture

The app is built around a single source of truth and a strict separation
between data, UI, and persistence:
Source/
├── Main.cpp                 Application entry point and window
├── MainComponent            Root component, owns model + UI
├── Identifiers.h            Centralised ValueTree property names
│
├── Domain/
│   ├── AmpState             The amp parameter state (ValueTree) — single
│   │                        source of truth
│   ├── PresetLibrary        Collection of presets; add / apply / randomise
│   └── PresetSerializer     XML save/load, schema-versioned, atomic writes
│
└── UI/
├── ParameterPanel       Five amp controls, two-way bound to AmpState
└── PatchBrowser         Preset list with save / randomise / load

### Key design decisions

- **Single source of truth.** All amp settings live in one `AmpState`
  ValueTree. The UI never holds its own copy — it observes the tree and
  reflects it. Presets read from and write to the same tree.

- **Two-way data binding.** The `ParameterPanel` listens to the ValueTree
  and updates its sliders when the state changes (e.g. on preset load), and
  writes back when the user turns a knob. A guard flag prevents the
  update feedback loop.

- **Reliable persistence.** Presets serialise to XML with a schema version
  for forward compatibility, and use atomic writes (temp file + rename) so a
  crash mid-save cannot corrupt a preset.

## Build

Requires [JUCE](https://github.com/juce-framework/JUCE) cloned locally,
CMake 3.22+, and an MSVC toolchain (Visual Studio).
cmake --preset vs
cmake --build vs-build

Run: `vs-build/RedstarDesigner_artefacts/Debug/Redstar Designer.exe`

## Roadmap

- [x] ValueTree-based amp state model
- [x] Parameter panel with two-way binding
- [x] Preset library: save, load, randomise
- [x] XML serialisation with versioning and atomic writes
- [ ] Mock device layer + connection state machine
- [ ] Real device communication (USB/MIDI)
- [ ] Cloud patch sync

## Status

Early work in progress — built as a focused exploration of JUCE application
architecture.
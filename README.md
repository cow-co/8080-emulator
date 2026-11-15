# 8080 Emulator

## Fun side-project to exercise my C coding


## Commands

### Test

`make test`

### Run CPU Diagnostic

`make diag`

### Build

`make build`


## Design

There are effectively three layers to the software stack here:

- The emulator itself (in `opcodes`, `processor`, and `state`): this represents the 8080 itself, as well as the memory to which it communicates
- The "machine" code, which represents the machine into which the 8080/memory hardware was incorporated (in the example provided, this is a Space Invaders arcade cabinet)
- The "host" code, which handles the input/output from/to the actual real hardware on which our emulator is running. This is the layer that (for example) reads a keyboard press, and converts that to a "shoot gun" input in the machine layer.

If other arcade machines used the same setup as Space Invaders, then you could incorporate them simply by creating some new code at the machine layer. Machines with different numbers/types of input would require changes to both the machine and host layers, since the API from the machine layer will change.


## How to Incorporate a Different "Emulated System"

If you want to build a representation of a different 8080-based system (ie. other than Space Invaders), you will generally need to change the emulator and host layers:

- At the emulator layer:
  - You will need to define a machine state `struct` (see `machine_state.h`) to represent the state of the overall machine, including any bespoke memory/processing hardware that it has beyond the basic 8080. This will include your own implementation of the `reset_machine()` function.
  - Define a `DisplayParams` instance, which helps the host layer define window dimensions and such.
  - Define any input and output types that might be needed, as well as functions to handle them (see `machine_api.h` for inspiration).
  - Implement a run loop `run_machine()` as well as `queued_sfx()` to update the current sounds that should play, and `graphics_state()` to retrieve the framebuffer.
- At the host layer:
  - Make any changes that might be necessary to accommodate the changes you made at the machine layer (eg. changing how SFX are handled).
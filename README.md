# 8080 Emulator

## Fun side-project to exercise my C coding


## Commands

### Test

`make test`

### Build

`make build`


## Design

There are effectively three layers to the software stack here:

- The emulator itself (in `opcodes`, `processor`, and `state`): this represents the 8080 itself, as well as the memory to which it communicates
- The "machine" code, which represents the machine into which the 8080/memory hardware was incorporated (in the example provided, this is a SPace Invaders arcade cabinet)
- The "host" code, which handles the input/output from/to the actual real hardware on which our emulator is running. This is the layer that (for example) reads a keyboard press, and converts that to a "shoot gun" input in the machine layer.

If other arcade machines used the same setup as Space Invaders, then you could incorporate them simply by creating some new code at the machine layer. Machines with different numbers/types of input would require changes to both the machine and host layers, since the API from the machine layer will change.

The APIs exposed by each layer, that are relevant to the layer(s) above, are outlined below.

### Emulator Layer API

Functions exposed:

- `run()`: Executes the code loaded into memory. Alternatively: generates a disassembly of the binary.
- `load_binary()`: Loads a binary file into memory. _Caller_ closes the file pointer!
- `reset_state()`: Resets the state of the 8080 and memory.

### Machine Layer API

This layer exposes any input and output functions required for the machine hardware being emulated. In the bundled example, this is a Space Invaders arcade cabinet. All implementations, however, should expose:
- `load_rom()`: Handles loading the ROM files for the specific executable we are emulating.
- `key_press()`: When a binary input  (eg. a button) is activated.
- `key_release()`: When a binary input  (eg. a button) is deactivated.
- `reset_machine()`
- `run_machine()`
- An enumeration of supported inputs for passing in to the `key_press()` and `key_release()` functions.
- An instance of `DisplayParams`, describing the parameters of the display for the machine (eg. the Space Invaders display was 224 * 220, with one-byte pixels, and a 60Hz refresh rate).
- `graphics_state()`: Returning a pointer to the buffer containing the raw pixel data to be rendered. Note that this _may not_ be a direct pass-through from the emulator memory in cases where the memory layout is not representative of what should be displayed (eg. the display in Space Invaders was rotated by 90 degrees in the cabinet). This returns a pointer to `uint8_t` so that we can be very clear about the size of the bytes (`unsigned char` is not _required_ to be 8 bits).

### Host Layer API


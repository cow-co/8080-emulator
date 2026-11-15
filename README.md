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
- The "machine" code, which represents the machine into which the 8080/memory hardware was incorporated (in the example provided, this is a SPace Invaders arcade cabinet)
- The "host" code, which handles the input/output from/to the actual real hardware on which our emulator is running. This is the layer that (for example) reads a keyboard press, and converts that to a "shoot gun" input in the machine layer.

If other arcade machines used the same setup as Space Invaders, then you could incorporate them simply by creating some new code at the machine layer. Machines with different numbers/types of input would require changes to both the machine and host layers, since the API from the machine layer will change.
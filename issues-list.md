# Current List of Issues

- Stuck in an infinite loop in `ClearScreen` (`0x1A5C` to `0x1A68`). The JNZ seems never to fire.
  - The first iteration of the loop is

```
1A5C LXI       H, $2400
1A5F MVI       M, #0x00
1A61 INX       H
1A62 MOV       A, H
1A63 CPI       #0x40
1A65 JNZ       $1a5f
```

  - then subsequent iterations are

```
1A5F MVI       M, #0x00
1A61 INX       H
1A62 MOV       A, H
1A63 CPI       #0x40
1A65 JNZ       $1a5f
```

  - Interesting that this is happening when the CPU diagnostic is passing. All these instructions are tested in the diagnostic, so I presume the issue is perhaps related to something in the memory space that the procedure is working with (the video buffer)
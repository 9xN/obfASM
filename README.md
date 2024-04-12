# obfASM

`obfASM` is a useful tool designed to obfuscate assembly code by injecting benign, harmless Intel-based ASM instructions throughout the code. This enhances the complexity of the assembly code, thus making it harder for someone to understand the logic and reverse engineer it. This also helps by changing the signature of the code, therefore able to bypass *some* signature based detections mechanisms employed by AV/EDR systems.

---

## Getting Started
To compile this code on a Unix-like system with gcc installed, use the command:

```bash
gcc -o obfasm obfasm.c
```

To run the program:

```bash
./obfasm input.asm output.asm
```

Where `input.asm` is your initial ASM file and `output.asm` will be the resulting file with added random and harmless ASM code.

---

## How it works

`obfASM` inserts randomly chosen ASM instructions before and after each line from the input file. The code snippets inserted serve no functional purpose in the program execution and are intended purely to obfuscate the original code and increase its complexity.

ASM snippets added include commands like:
```asm
NOP
MOV AX, AX
MOV EAX, EAX
XCHG BX, BX
ADD EAX, 0
AND EAX, 0xFFFFFFFF
OR EAX, 0x0
```

---

## Prerequisites

- GCC installed for code compilation

---

## Note

The added ASM instructions were chosen to be universally benign, not to affect the program execution flow. However, depending on the targeted reverse engineering tool, these instructions might not be completely harmless or invisible. Hence, consider the target environment and additional complexities before integrating `obfASM` into your workflow.

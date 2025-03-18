# SenzuVM - Custom Virtual Machine in C

SenzuVM is a minimalist virtual machine written in C that simulates a CPU, memory, and instruction execution at the byte level. It was designed to deepen low-level programming skills and demonstrate core concepts of systems architecture, memory layout, and instruction parsing.

---

## * Features*

- *Custom CPU architecture with general-purpose registers (AX, BX, CX, DX)*
- *Stack simulation and instruction pointer (SP, IP)*
- *Dynamic memory allocation and manual memory management*
- *Custom instruction set (ISA) with support for:*
  - *`MOV`**: move a value into a register*
  - *`NOP`**: no operation*
- *Bytecode encoding and memory representation*
- *Internal assembler-like structure to build instructions dynamically*
- *Hexadecimal output of loaded programs*

---

## * File Structure*

```
SenzuVM/
├── SenzuVM.c       # Main implementation of the VM
├── SenzuVM.h       # All definitions, types, and instruction set
├── .gitignore      # Git tracking exclusions
└── README.md       # This documentation file
```

---

## * Architecture Overview*

### *VM Structure:*

```c
struct s_vm {
    CPU c;         // CPU containing registers
    Stack s;       // Memory block (simulated stack)
    Program *m;    // Loaded program (bytecode)
};
```

### *Registers:*

```c
struct s_registers {
    Reg ax, bx, cx, dx;  // General-purpose
    Reg sp, ip;          // Stack & Instruction pointer
};
```

### *Instruction Format:*

```c
struct s_instruction {
    Opcode o;     // Operation code
    Args a[];     // Optional arguments (0–2 bytes)
};
```

*Example for **`MOV AX, 0x05`**:*

```c
01 00 05   // 01 = mov, 00 = AX, 05 = value
```

### *Stack:*

```c
typedef int8 Stack[((unsigned int)(-1))];  // Large memory block
```

---

## *⚙️ Instruction Set (ISA)*

```c
enum e_opcode {
    mov = 0x01,  // move value to register
    nop = 0x02   // no operation
};
```

### *Instruction Size Mapping*

```c
static IM instrmap[] = {
    { mov, 0x03 },  // mov = 3 bytes (opcode + reg + val)
    { nop, 0x01 }   // nop = 1 byte
};
```

---

## * Example: Generating a Bytecode Program*

*In **`exampleprogram()`**, the following instructions are built:*

1. *`MOV AX, 5`*
2. *`NOP`*

```c
*a1 = 0x00;        // AX
*(a1 + 1) = 0x05;  // Value

// Instruction output in memory:
01 00 05 02
```

*This program is stored in **`vm->m`** and printed in hexadecimal form:*

```c
printhex((int8 *)prog, (map(mov) + map(nop)), ' ');
// Output: 01 00 05 02
```

---

## * Memory Allocation & Utilities*

- *Memory is dynamically allocated using **`malloc`*
- *Structures are zeroed with a macro shortcut: **`zero($1 p, size)`*
- *Data is copied using a macro wrapper for **`memcpy`**: **`copy($1 dst, $1 src, len)`*

---

## * Output Example*

```bash
$ ./SenzuVM
vm  = 0x5629acbfc2a0
prog = 0x5629acbfc2ac
01 00 05 02
```

*This output confirms:*

- *VM is initialized at a memory address*
- *Bytecode program is loaded in memory*
- *Program corresponds to **`MOV AX, 5`** followed by **`NOP`*

---

## * Current Limitations*

- *The virtual machine does not yet execute instructions*
- *No branching (**`JMP`**), arithmetic (**`ADD`**), or memory access operations*
- *No assembler parser (everything is generated in C)*

---

## * Future Improvements*

*If extended, SenzuVM could support:*

- *Instruction execution engine (**`run()`** function)*
- *More instructions: **`ADD`**, **`JMP`**, **`PUSH`**, **`POP`**, **`CMP`**, **`JZ`**, **`JNZ`*
- *Text-based assembler compiler*
- *Instruction debugging / logging / register visualization*

---

## *👨‍ Author*

*Developed by Hodeifa as a personal project to understand CPU and VM internals using pure C. This project demonstrates key system-level programming skills and can be extended in many directions depending on learning goals.*
##  Acknowledgments

Some low-level utilities and architectural inspiration were based on the work of **Dr. JB**, whose contributions to system design deeply influenced parts of this project.


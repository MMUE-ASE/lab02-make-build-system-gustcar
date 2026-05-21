# Debugging with VS Code — Cortex-Debug + OpenOCD

---

## How It Works

When you press **F5** in VS Code, the following happens:

```text
VS Code
  └── Cortex-Debug (extension)
        ├── launches → OpenOCD  (GDB server) ──SWD──► ST-LINK  (hardware on NUCLEO board) ──SWD──► STM32F412ZG
        └── launches → arm-none-eabi-gdb
                      (GDB client, connects to OpenOCD via TCP)
```

1. **OpenOCD** opens an SWD connection with the microcontroller via the integrated ST-LINK on the NUCLEO board. It acts as a GDB server on port 50000.
2. **arm-none-eabi-gdb** connects to that server, loads the `.elf` binary into the microcontroller's flash, and halts execution at the start of `main()`.
3. From that point, you control execution line by line from the editor.

No STM32CubeIDE or STM32CubeProgrammer is needed for debugging.

---

## Quick Start

1. Connect the NUCLEO-F412ZG board via USB.
2. Open this lab's folder (the repo root) in VS Code.
3. Press **F5** — VS Code will run `make all` automatically, flash the firmware, and start the debug session.
4. Execution automatically stops at the beginning of `main()`.

### Keys During the Session

| Key           | Action                                                       |
| ------------- | ------------------------------------------------------------ |
| **F5**        | Continue to next breakpoint                                  |
| **F10**       | Step over — executes current line without entering functions |
| **F11**       | Step into — enters called functions                          |
| **Shift+F11** | Step out of current function                                 |
| **Shift+F5**  | Stop debug session                                           |

### Breakpoints

Click the left margin of any code line (red dot appears) to add a breakpoint. Execution will stop when reaching that line.

---

## What You Can Inspect

### Local and Global Variables

In the **Variables** panel (left), you can see the value of all variables in the current scope while stepping through code.

### Processor Registers

In the **Cortex Registers** panel, you can see R0–R15, PC, SP, and Cortex-M4 status registers in real time.

### Peripheral Registers (SVD)

The **Cortex Peripherals** panel shows the current value of all microcontroller registers: `RCC_AHB1ENR`, `GPIOB_MODER`, `GPIOB_IDR`, `GPIOC_BSRR`… This is especially useful to verify that your GPIO driver functions write the correct values to the hardware registers.

To enable it, you need the SVD file for the STM32F412. The file is already referenced in `.vscode/launch.json` — no further changes needed.

---

## Common Troubleshooting

| Symptom                    | Likely Cause                                        | Solution                                                                                   |
| -------------------------- | --------------------------------------------------- | ------------------------------------------------------------------------------------------ |
| `spawn openocd.exe ENOENT` | VS Code cannot find the executable                  | Check `cortex-debug.openocdPath` in `.vscode/settings.json`                                |
| `Examination failed`       | MCU in sleep or HardFault                           | Already fixed with `debug/openocd-connect.cfg` — if persists, disconnect and reconnect USB |
| `No ST-LINK device found`  | ST-LINK driver not installed or board not connected | Install STM32CubeProgrammer for drivers; reconnect USB                                     |
| GDB does not load `.elf`   | Project not yet built                               | Run `make all` in the terminal, or let VS Code's `preLaunchTask` handle it on the next F5  |

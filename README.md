[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-22041afd0340ce965d47ae6ef1cefeee28c7c493a6346c4f15d667ab976d596c.svg)](https://classroom.github.com/a/TLWvkECk)
# Lab 2.1 — Makefile Build System

[![Hardware](https://img.shields.io/badge/Hardware-STM32_NUCLEO--F412ZG-03234B.svg?logo=stmicroelectronics&logoColor=white)](https://www.st.com/en/evaluation-tools/nucleo-f412zg.html)
[![Toolchain](https://img.shields.io/badge/Toolchain-arm--none--eabi--gcc-A8B9CC.svg?logo=arm&logoColor=white)](https://developer.arm.com/downloads/-/arm-gnu-toolchain-downloads)
[![GitHub Classroom](https://img.shields.io/badge/GitHub-Classroom-181717.svg?logo=github)](https://classroom.github.com/classrooms/274591709-mmue-arquitectura-sistemas-embebidos-2026)

---

## Table of Contents

- [Context](#context)
- [Objectives](#objectives)
- [Getting Started](#getting-started)
- [Phase Overview](#phase-overview)
- [Phase 0 — Warm-up exercises](#phase-0--warm-up-exercises)
- [Phase 1 — Explicit rules](#phase-1--explicit-rules)
- [Phase 2 — Pattern rule](#phase-2--pattern-rule)
- [Phase 3 — Utility targets](#phase-3--utility-targets)
- [Milestones](#milestones)
- [CI and submission](#ci-and-submission)
- [Common errors](#common-errors)
- [Rubric](#rubric)

---

## Context

In Lab 1 the firmware was built by running `bash scripts/build.sh` — a script that
compiled every file unconditionally on every run. This lab replaces that script with a
**Makefile** that tracks file timestamps and recompiles only what changed.

The firmware behaviour is identical to Lab 1. The objective is the build system.

---

## Objectives

- Write a Makefile that builds `output/lab2.elf`, `.bin`, and `.hex`.
- Expose the `all`, `clean`, `flash`, `size`, and `help` targets.
- Understand explicit rules, then generalise them with a pattern rule.
- Verify that Make only recompiles the files that changed.
- Override `EXTRA_CFLAGS` from the command line and from CI.

---

## Getting Started

```bash
# 1 — clone your repository
git clone https://github.com/<org>/<assigned-repo>.git
cd <assigned-repo>

# 2 — copy your completed Lab 1 solution into this workspace
#     (the repo ships with the unresolved Lab 1 skeleton — you need your own solution to build)
bash scripts/copy_lab1.sh <path-to-your-lab1-repo>

# 3 — open the Makefile and read the phase headers before writing any code
```

Read [`docs/make_guide.md`](docs/make_guide.md) whenever you need a concept refresher.

---

## Phase Overview

| Phase                                            | Goal                                   | Estimated time | Done when                                   |
| ------------------------------------------------ | -------------------------------------- | -------------- | ------------------------------------------- |
| [0 — Warm-up](#phase-0--warm-up-exercises)       | Learn Make syntax with small exercises | 20 min         | Ex 3 Part B compiles both `.o` files        |
| [1 — Explicit rules](#phase-1--explicit-rules)   | Working build with one rule per file   | 30 min         | `make all` produces ELF, BIN, HEX           |
| [2 — Pattern rule](#phase-2--pattern-rule)       | Replace two explicit rules with one    | 20 min         | `make all` still works; Makefile is shorter |
| [3 — Utility targets](#phase-3--utility-targets) | Add `clean`, `size`, `flash`, `.PHONY` | 20 min         | CI green; board flashed                     |

---

## Phase 0 — Warm-up exercises

**Before touching the lab Makefile**, run the three exercises in
[`docs/exercises/`](docs/exercises/README.md).
They use the same toolchain (`arm-none-eabi-gcc`) and cover every concept you need:
rule syntax, `$@`/`$<`/`$^`, order-only prerequisites, and pattern rules.

```bash
cd docs/exercises/ex1_hello
make
```

Each exercise takes about 5–7 minutes. The
[exercises README](docs/exercises/README.md) explains what to observe at each step.

---

## Phase 1 — Explicit rules

Open `Makefile` and complete TODOs **P1.1 through P1.8** in order.

In this phase you write one compile rule per source file — verbose, but it lets you
see a working build before introducing any advanced syntax.

| TODO | What to write                                      |
| ---- | -------------------------------------------------- |
| P1.1 | `SRCS` — list the two `.c` files                   |
| P1.2 | `ASM_OBJ` — path to the assembled startup object   |
| P1.3 | `all` — default target depending on ELF, BIN, HEX  |
| P1.4 | Explicit rule to compile the assembly startup file |
| P1.5 | Explicit rule: `output/gpio.o` from `src/gpio.c`   |
| P1.6 | Explicit rule: `output/main.o` from `src/main.c`   |
| P1.7 | Link rule: produce `$(ELF)` from the three objects |
| P1.8 | Two `objcopy` rules for `.bin` and `.hex`          |

**Check:** `make all` → three files in `output/`. ✓

---

## Phase 2 — Pattern rule

Complete TODOs **P2.1 and P2.2**.

P1.5 and P1.6 are almost identical — only the filename differs. A _static pattern
rule_ replaces both with a single rule that matches any `.c` in `src/`.

| TODO | What to write                                                       |
| ---- | ------------------------------------------------------------------- |
| P2.1 | `OBJS` — derive object paths from `SRCS` via substitution reference |
| P2.2 | Static pattern rule `$(OBJS): $(BUILDDIR)/%.o : $(SRCDIR)/%.c`      |

Do these three steps **together, before running make** — having P1.5/P1.6 and the
pattern rule active simultaneously causes "overriding recipe" warnings:

1. Delete the explicit rules P1.5 and P1.6.
2. Write the P2.2 pattern rule.
3. Update P1.7 to list `$(OBJS)` instead of the two hardcoded paths.

**Check:** `make clean && make all` still produces the three artifacts. ✓

---

## Phase 3 — Utility targets

Complete TODOs **P3.1 through P3.4** and the `scripts/build.sh` wrapper.

| TODO | What to write                                 |
| ---- | --------------------------------------------- |
| P3.1 | `clean` — `rm -rf $(BUILDDIR)`                |
| P3.2 | `size` — run `$(SIZE)` on `$(ELF)`            |
| P3.3 | `flash` — invoke `bash scripts/flash.sh`      |
| P3.4 | `.PHONY` declaration for all non-file targets |

Also open `scripts/build.sh` and replace the `exit 1` stub with a Make invocation.

**Check:** `make flash` → board programmed; LED turns on when B1 is pressed. ✓

---

## Milestones

| Milestone                | How to verify                                                       |
| ------------------------ | ------------------------------------------------------------------- |
| M1 — ELF produced        | `make all` exits 0; `output/lab2.elf` exists                        |
| M2 — BIN and HEX         | `output/lab2.bin` and `output/lab2.hex` exist                       |
| M3 — Clean works         | `make clean` removes `output/`; `make all` rebuilds from scratch    |
| M4 — Board works         | `make flash`; press B1 → LD2 on; release → LD2 off                  |
| M5 — Incremental rebuild | `touch src/main.c && make all` → only `main.o` and ELF rebuild      |
| M5b — Header tracking    | `touch inc/gpio.h && make all` → both `main.o` and `gpio.o` rebuild |

---

## CI and submission

Every `push` triggers the **Lab 2.1 — Build Verification** workflow which runs:

```text
make all    →  verifies ELF, BIN, HEX exist
make size   →  prints section sizes in the job log
make clean  →  verifies output/ is removed
```

Results appear in the **Actions** tab. Push as many times as needed — each push
updates the feedback. Submission is the last commit pushed before the deadline.

### Commit conventions

```text
feat(lab2): implement pattern rule for C compilation
fix(lab2): add missing .PHONY declaration
docs(lab2): replace reference solution with own Lab 1 code
```

---

## Common errors

| Symptom                                    | Likely cause                                                                       |
| ------------------------------------------ | ---------------------------------------------------------------------------------- |
| `Makefile:N: *** missing separator`        | Recipe line uses spaces instead of a tab                                           |
| `No rule to make target 'output/lab2.elf'` | `all` does not depend on `$(ELF)`, or `$(ELF)` rule is missing                     |
| `undefined reference to main`              | `SRCS` is empty or `main.c` is not listed                                          |
| `make clean` does nothing                  | `clean` is not declared `.PHONY` and a file named `clean` exists                   |
| Touching a `.h` does not trigger rebuild   | `-include` line or `-MMD` flag is missing (both are provided — do not delete them) |
| `EXTRA_CFLAGS` override has no effect      | Used `=` instead of `?=` for that variable                                         |
| `warning: overriding recipe for target`    | Explicit rule (P1.5/P1.6) and pattern rule (P2.2) both match the same target — delete P1.5 and P1.6 before writing P2.2 |

---

## Rubric

| Criterion                                                  | Weight |
| ---------------------------------------------------------- | -----: |
| `make all` produces ELF, BIN, and HEX (M1, M2)             |    30% |
| Pattern rule and dependency declarations correct (Phase 2) |    20% |
| Incremental rebuild works (M5)                             |    15% |
| `make clean` removes `output/` (M3)                        |    10% |
| `EXTRA_CFLAGS` overridable — CI green                      |    10% |
| `scripts/build.sh` invokes Make correctly                  |     5% |
| Commit quality — Conventional Commits                      |    10% |

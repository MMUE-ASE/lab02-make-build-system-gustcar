# Reference Guide — GNU Make

This guide covers the concepts needed to complete the lab `Makefile`.
It is not an exhaustive tutorial — it is a minimal reference focused on the project TODOs.

---

## 1. What does Make do?

`make` reads the `Makefile` and decides **which files need to be rebuilt** by comparing
the modification timestamps of targets and their dependencies. If the target is newer
than all its dependencies, Make does nothing.

```bash
make          # build the default target (set via .DEFAULT_GOAL := all in this Makefile)
make clean    # run the clean target
make size     # run the size target
```

---

## 2. Anatomy of a rule

```makefile
target: dependencies
    recipe line 1
    recipe line 2
```

- **`target`** — the file to produce (or the name of an action).
- **`dependencies`** — files that must exist and be up-to-date first.
- **`recipe`** — shell commands; **must be preceded by a tab character (`\t`), not spaces**.

### Suppressing command echo (`@`)

By default Make prints each command before running it. Prefix with `@` to silence it:

```makefile
help:
    @echo "Usage: make [target]"   # prints only the message, not the echo command
    echo "Usage: make [target]"    # prints the command AND the message
```

The provided `help:` target uses `@echo` for this reason.

### Each recipe line runs in a new shell

Make spawns a **separate shell process** for every recipe line.
State (current directory, variables) does **not** carry over between lines:

```makefile
# WRONG — the cd has no effect on the next line
broken:
    cd subdir
    $(CC) main.c        # still compiles from the original directory

# CORRECT — chain with && to stay in the same shell
fixed:
    cd subdir && $(CC) main.c
```

In this lab, all recipes are single commands, so this does not affect your work —
but it explains why `&&` is used in CI scripts.

---

## 3. Variables

```makefile
CC = arm-none-eabi-gcc         # simple definition
EXTRA_CFLAGS ?= -DDEBUG        # assign only if not already set (also reads from env)
CFLAGS = $(CPU_FLAGS) $(EXTRA_CFLAGS)  # expansion with $()
```

| Operator | Behavior                                                       |
| -------- | -------------------------------------------------------------- |
| `=`      | Deferred expansion (evaluated each time the variable is used). |
| `:=`     | Immediate expansion (evaluated once at definition time).       |
| `?=`     | Assigns only if the variable has no value yet.                 |
| `+=`     | Appends to the existing value (preserves prior content).       |

`EXTRA_CFLAGS ?=` allows overriding flags from the command line or CI environment
without modifying the `Makefile`:

```bash
make all EXTRA_CFLAGS="-DDEBUG"     # command-line override
EXTRA_CFLAGS="-DDEBUG" make all     # environment variable override
```

### Deferred vs immediate expansion

`=` is evaluated **each time the variable is referenced**, which means it can forward-reference
variables defined later in the file:

```makefile
CFLAGS = $(CPU_FLAGS) -O0   # fine — CPU_FLAGS can be defined anywhere
CPU_FLAGS = -mcpu=cortex-m4
```

`:=` is evaluated **once at definition time** — a forward reference would be empty:

```makefile
CFLAGS := $(CPU_FLAGS) -O0  # CPU_FLAGS is empty here if not defined yet
CPU_FLAGS := -mcpu=cortex-m4
```

---

## 4. Automatic variables

Available **inside a rule's recipe**:

| Variable | Meaning                                                    |
| -------- | ---------------------------------------------------------- |
| `$@`     | The **target** name.                                       |
| `$<`     | The **first dependency**.                                  |
| `$^`     | **All dependencies** (no duplicates).                      |
| `$?`     | All dependencies **newer than the target**.                |

Example:

```makefile
output/lab2.elf: output/main.o output/gpio.o output/startup.o
    $(CC) $(LDFLAGS) -o $@ $^
#                       ^^  ^^
#                       |   all dependencies
#                       target (output/lab2.elf)
```

---

## 5. Pattern rule

A pattern rule uses `%` as a wildcard that matches **one or more characters** (the _stem_).
Make substitutes the same stem into both the target pattern and the dependency pattern:

```makefile
$(OBJS): $(BUILDDIR)/%.o : $(SRCDIR)/%.c | $(BUILDDIR)
    $(CC) $(CFLAGS) -c $< -o $@
```

For example, when building `output/gpio.o`:

- `%` matches the stem `gpio`
- target becomes `output/gpio.o`
- dependency becomes `src/gpio.c`
- `$<` expands to `src/gpio.c`
- `$@` expands to `output/gpio.o`

The `$(OBJS):` prefix at the start makes it a **static pattern rule** — it applies only to
the targets listed in `$(OBJS)`, not every `.o` in the project. This avoids ambiguity and
produces clearer error messages than a global `%.o : %.c` rule.

---

## 6. Order-only prerequisite

The `|` separator means the directory must **exist before** compiling, but its
modification timestamp must **not** trigger a recompile:

```makefile
$(BUILDDIR)/%.o : $(SRCDIR)/%.c | $(BUILDDIR)
```

Without `| $(BUILDDIR)`, Make would fail if `output/` does not yet exist.

If `$(BUILDDIR)` were a normal (non-order-only) prerequisite, every new file added to
`output/` would update the directory's timestamp and cause everything to recompile.

---

## 7. `.PHONY`

Declares targets that **do not produce a file** with that name.
Without `.PHONY`, if a file called `clean` happened to exist, Make would consider it
up-to-date and skip the recipe entirely.

```makefile
.PHONY: all clean flash size help
```

A common symptom: running `make clean` does nothing, even though the recipe is correct —
a file named `clean` exists in the project directory.

---

## 8. Substitution reference

Generate an object list from the source list:

```makefile
SRCS = src/main.c src/gpio.c
OBJS = $(SRCS:src/%.c=output/%.o)
# OBJS → output/main.o output/gpio.o
```

The syntax `$(VAR:pattern=replacement)` replaces every word in `VAR` that matches
`pattern` with `replacement`. The `%` in the pattern matches the stem (same concept as
in pattern rules).

---

## 9. Automatic header dependencies (`-MMD`)

When a `.c` file includes a header, Make does not know about that dependency unless
you tell it. The `-MMD -MP` compiler flags (already in `CFLAGS`) generate a `.d` file
alongside each `.o` that lists the headers that file depends on:

```makefile
CFLAGS = ... -MMD -MP
-include $(wildcard $(BUILDDIR)/*.d)   # load all generated dependency files (already in Makefile)
```

With this in place, touching `inc/gpio.h` triggers recompilation of every `.c` that
includes it — without you having to list those dependencies manually.

You do not need to write any code for this feature; it is provided. Use milestone M5b
to verify it works: touch `inc/gpio.h` and run `make all` — both `main.o` and `gpio.o`
should recompile.

---

## 10. Mapping from `build.sh` (Lab 1) to `Makefile` (Lab 2.1)

Each command in the Lab 1 script has a direct equivalent in the `Makefile`:

| `build.sh` (Lab 1)                                             | Rule / variable in `Makefile` (Lab 2.1) |
| -------------------------------------------------------------- | --------------------------------------- |
| `${CC} ${CPU_FLAGS} -g3 -c startup/startup_stm32f412zg.s -o …` | Assembly rule P1.4                      |
| `${CC} ${CFLAGS} -c src/gpio.c -o output/gpio.o`               | Pattern rule P2.2                       |
| `${CC} ${CFLAGS} -c src/main.c -o output/main.o`               | Pattern rule P2.2                       |
| `${CC} -nostdlib -T linker/... -o output/lab1.elf ...`         | Link rule P1.7                          |
| `${OBJCOPY} -O binary ... .bin`                                | Binary rule P1.8                        |
| `${OBJCOPY} -O ihex   ... .hex`                                | Hex rule P1.8                           |
| `arm-none-eabi-size output/lab1.elf`                           | `size` target P3.2                      |
| `bash scripts/flash.sh`                                        | `flash` target P3.3                     |

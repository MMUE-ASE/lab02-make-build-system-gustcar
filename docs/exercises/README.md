# Warm-up Exercises — GNU Make

These three short exercises build the Make vocabulary you need before writing the lab
Makefile. Each one runs in Git Bash with the toolchain already installed — no extra
software required.

**Estimated time:** 20–25 minutes total.

---

## How to run

Open Git Bash, `cd` into the exercise folder, and type `make`:

```bash
cd docs/exercises/ex1_hello
make
```

---

## Exercise 1 — Hello, Make (`ex1_hello/`)

**You will learn:** rule syntax, the tab requirement, default target, `.PHONY`, `$@`.

**What to do:** open `ex1_hello/Makefile` and complete the three TODOs.

**Expected output after TODO 1:**

```text
Hello from Make!
  This target is named: hello
```

**Run `make` a second time.** Because the targets are `.PHONY`, Make always
re-executes the recipe — there are no files to compare timestamps against.

**After completing TODO 2**, run `make clean` to see the clean target execute.
Running `make` again still invokes `hello` — `clean` only runs when named explicitly.

**Key observation:** remove `.PHONY` and create an empty file named `hello`
(`touch hello`), then run `make` again. Make says "nothing to be done" because
it sees a file named `hello` that is already "up to date". This is the bug
`.PHONY` prevents.

---

## Exercise 2 — Compile one file (`ex2_one_file/`)

**You will learn:** explicit compile rule, `$<` and `$@`, order-only prerequisite
(`|`), how Make tracks timestamps.

**What to do:** open `ex2_one_file/Makefile` and complete the three TODOs.

**Expected output after TODO 2:**

```text
arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=soft -O0 -ffreestanding -c utils.c -o output/utils.o
```

**Run `make` a second time.** Output:

```text
make: Nothing to be done for 'all'.
```

Make compared the timestamp of `output/utils.o` against `utils.c` — the object
is newer, so nothing to rebuild.

**Run `touch utils.c` then `make` again.** The compile command reappears —
`utils.c` is now newer than `output/utils.o`, so Make recompiles it.

**Key observation:** this timestamp comparison is the core mechanic of Make.
In a project with 50 source files, only the changed ones are recompiled.

---

## Exercise 3 — Two files and a pattern rule (`ex3_two_files/`)

**You will learn:** substitution reference (`$(VAR:pattern=replacement)`),
static pattern rule, and the refactoring workflow from explicit → general rules.

**What to do:** open `ex3_two_files/Makefile` and complete Part A first, then Part B.

### Part A — Explicit rules

Complete TODOs A1–A4. Both `.o` files should compile:

```text
arm-none-eabi-gcc ... -c utils.c -o output/utils.o
arm-none-eabi-gcc ... -c math.c  -o output/math.o
```

Notice that the two explicit rules (A3 and A4) are nearly identical — only the
filename differs. This duplication is the motivation for Part B.

### Part B — Pattern rule

Complete TODOs B1 and B2 by doing all three steps **together, before running make** —
having A3/A4 and the pattern rule active at the same time causes "overriding recipe"
warnings from Make:

1. Delete the explicit rules A3 and A4 above.
2. Write the B2 pattern rule.
3. Update `all` to depend on `$(OBJS)` instead of the two hardcoded paths.

Then run `make clean && make`. The output should be identical to Part A, but the
Makefile is now shorter and would handle any number of `.c` files without additional
rules.

**Key observation:** `touch utils.c` and run `make` — only `utils.o` recompiles,
not `math.o`. The pattern rule tracks dependencies per file, not globally.

---

## You are ready for the lab Makefile

After these three exercises you have seen:

| Concept                              | Exercise |
| ------------------------------------ | -------- |
| Rule syntax and tab character        | Ex 1     |
| Default target and `.PHONY`          | Ex 1     |
| `$@`, `$<` automatic variables        | Ex 2, 3  |
| `$^` automatic variable               | Lab Makefile P1.7 |
| Order-only prerequisite `\|`         | Ex 2, 3  |
| Timestamp-based incremental rebuild  | Ex 2, 3  |
| Substitution reference               | Ex 3     |
| Static pattern rule                  | Ex 3     |

Return to the root [README.md](../../README.md) and start Phase 1.

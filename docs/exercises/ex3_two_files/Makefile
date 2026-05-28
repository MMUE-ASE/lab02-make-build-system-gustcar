# Exercise 3 — Two files and a pattern rule
# Concepts: substitution reference, static pattern rule, refactoring explicit rules
#
# This exercise has two parts:
#   Part A — start with two explicit rules (like Exercise 2, repeated twice)
#   Part B — replace them with a single pattern rule
# -----------------------------------------------------------------------

CC       = arm-none-eabi-gcc
CFLAGS   = -mcpu=cortex-m4 -mthumb -mfloat-abi=soft -O0 -ffreestanding
BUILDDIR = output

# --- Part A: explicit rules --------------------------------------------------

# TODO A1: List the two source files in SRCS.
#          They live in the current directory (no subfolder prefix needed here).
#          You will not use SRCS in Part A — it is here so Part B can derive
#          OBJS from it with a substitution reference.
SRCS = math.c utils.c

# TODO A2: Write the default target "all" that depends on output/utils.o
#          and output/math.o (list them explicitly for now).
#
# YOUR RULE HERE
#all: output/utils.o output/math.o
all: $(OBJS)

$(BUILDDIR):
	mkdir -p $@

# TODO A3: Write an explicit rule for output/utils.o from utils.c
#          (same pattern as Exercise 2, TODO 2)
#
# YOUR RULE HERE
#output/utils.o: utils.c | $(BUILDDIR)
#	$(CC) $(CFLAGS) -c $< -o $@


# TODO A4: Write an explicit rule for output/math.o from math.c
#
# YOUR RULE HERE
#output/math.o: math.c | $(BUILDDIR)
#	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: all clean

clean:
	rm -rf $(BUILDDIR)

# --- Part B: refactor to a pattern rule --------------------------------------
# Once Part A is working, do all three steps below together before running make.
# Having A3/A4 and the pattern rule active at the same time causes "overriding
# recipe" warnings from Make.

# TODO B1: Derive OBJS from SRCS using a substitution reference.
#          Replace the .c suffix with a path inside $(BUILDDIR)/.
#          Hint: $(SRCS:%.c=$(BUILDDIR)/%.o)
OBJS = $(SRCS:%.c=$(BUILDDIR)/%.o)

# TODO B2: Do these three things together, then run make:
#          1. Delete the explicit rules A3 and A4 above.
#          2. Write the pattern rule below.
#          3. Update "all" to depend on $(OBJS) instead of the two hardcoded paths.
#
#          Form:   $(OBJS): $(BUILDDIR)/%.o : %.c | $(BUILDDIR)
#                      $(CC) $(CFLAGS) -c $< -o $@
#
# YOUR RULE HERE
$(OBJS): $(BUILDDIR)/%.o : %.c | $(BUILDDIR)
	$(CC) $(CFLAGS) -c $< -o $@

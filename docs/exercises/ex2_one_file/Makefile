# Exercise 2 — Compile one file
# Concepts: explicit rule, $< and $@, order-only prerequisite, timestamp tracking
#
# After each TODO, run 'make' and observe which commands execute.
# Then run 'make' a second time — notice "Nothing to be done".
# Then run 'touch utils.c' and 'make' again — it recompiles.
# -----------------------------------------------------------------------

CC       = arm-none-eabi-gcc
CFLAGS   = -mcpu=cortex-m4 -mthumb -mfloat-abi=soft -O0 -ffreestanding
BUILDDIR = output

# TODO 1: Write the default target "all" that depends on output/utils.o
#
# YOUR RULE HERE


# This rule creates the output directory when needed — provided, do not change.
$(BUILDDIR):
	mkdir -p $@

# TODO 2: Write an explicit rule to compile utils.c into output/utils.o.
#         - Target:      output/utils.o
#         - Dependency:  utils.c
#         - Also add | $(BUILDDIR) as an order-only prerequisite (after the |)
#         - Recipe:      $(CC) $(CFLAGS) -c $< -o $@
#                        ($< = first dependency = utils.c)
#                        ($@ = target         = output/utils.o)
#
# YOUR RULE HERE


# TODO 3: Add .PHONY for "all"
#
# YOUR LINE HERE

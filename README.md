# Simple custom OS

Simple OS I've began to develop as a follow along of "The little book about OS" development (![link here](https://littleosbook.github.io/#accessing-memory)).

The project have just started and right now only sets the segment tables and display test text onto screen.

# Buildd (Linux)

In orther to properly build this project you will need to create a i686 gcc cross compiler as described in this article (https://wiki.osdev.org/GCC_Cross-Compiler) which should be visible in PATH.

Once built use make for building the ISO image (myOS.iso) an then run it in any virtual machine.
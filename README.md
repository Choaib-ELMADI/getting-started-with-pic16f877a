[![Choaib ELMADI - Microcontrollers](https://img.shields.io/badge/Choaib_ELMADI-PIC16F877A-8800dd)](https://elmadichoaib.vercel.app) ![Status - Building](https://img.shields.io/badge/Status-Building-2bd729) ![Platform - PIC16F877A](https://img.shields.io/badge/Platform-PIC16F877A-f7d620) [![Credit - SM training academy](https://img.shields.io/badge/Credit-SM_training_academy-3b8af2)](https://www.youtube.com/@SMtrainingacademy)

# Getting Started with PIC16F877A

Welcome to the `getting-started-with-pic16f877a` repository! This repository is designed to help you learn about the PIC16F877A microcontroller through a variety of resources and projects.

## Repository Structure

The repository is structured as follows:

- **Docs**: This folder contains multiple text files and images to explain various concepts related to the PIC16F877A microcontroller.
- **MPLAB Projects**: Here, you'll find PIC16F877A projects written in assembly language for use with MPLAB IDE.
- **MPLABX Projects**: This folder contains PIC16F877A projects written in C language for use with MPLAB X IDE and Micro C compiler.
- **Proteus 8**: Here, you'll find simulations of the projects created in MPLAB and MPLABX.

![Note](https://img.shields.io/badge/NOTE:-fb151a)

Projects in the **"MPLAB Projects"**, **"MPLABX Projects"**, and **"Proteus 8"** folders have the same name for easy reference and correlation between code and simulation.

## Uploading Code to PIC16F877A

### Case 1: With Development Board and Programmer

If you have a development board and a programmer:

![With Development Board and Programmer](./Docs/0.%20Upload%20Code/0.1%20upload-code__dev-board.png)

### Case 2: Only PIC with Programmer

If you have only the PIC16F877A microcontroller and a programmer:

![Only PIC with Programmer](./Docs/0.%20Upload%20Code/0.2%20upload-code__microcontroller.png)

## Interrupt Service Routine Function Prototype

When using MPLAB X IDE, the syntax for defining an interrupt service routine (ISR) depends on whether you are using C99 or C90 standards.

### Using C99

For C99, the interrupt function is written as follows:

```cpp
void __interrupt() interruptFunctionName(void);
```

### Using C90

For C90, the interrupt function is written as follows:

```cpp
void interrupt interruptFunctionName(void);
```

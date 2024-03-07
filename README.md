# IOT-DLL (WIP)

## A minimalistic C Data Link Layer (DLL) protocol for the Internet of Things

This is a set of embedded C libraries which provides for a modular, flexible set of link layer protocols, focusing on the LLC protocols. This project is a work in progress.

The aim is to provide a simulator tool to determine the performance of data link algorithms, alongside the framework to implement the algorithms on an embedded device.

This project was spawned from a University of Southampton course, 'Embedded Networked Systems', which teaches students the fundementals of the layered network stack model and its applications in Embedded Networked Devices and the Internet of Things (IoT).

## Table of Contents

- Requirements
- Installation
- Configuration

## Requirements

This project has been written with the GCC c-compiler to the c17 standard. It is built with GNU Make, and has been built with MinGW make.

## Installation and Execution

### Simulation
1. Clone the project with `git clone https://github.com/benjaminaheath/iot-dll.git` into your local system.
2. Configure the DLL's parameters using the `lib/comms_config.h` file
3. Build by typing `make` into your shell at the repository top level
4. Run the executable main.exe for your local simulation executable

### Baremental Binary Execution
1. This is a WIP and will come when the DLL is complete and has been tested.

## Configuration

- Configure the DLL for your application using the `lib/comms_config.h` file
- The C prepreoessor will chop and change what is compiled based on the define statements in this header
- Each line has a different for building the DLL, from changing the way numbers are printed in simulation to the maximum payload size of the frame
- Some config parameters are buggy and may not be fully tested, so it's best to simulate them before building for a baremetal platform
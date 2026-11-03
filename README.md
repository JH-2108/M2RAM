# M2RAM 
A custom 128KB SRAM module designed using an M.2 form factor. 

# Overview 
M2RAM is an electronics project focused on designing and building a functional external memory expansion module. 

The project uses an AS6C1008 asynchronous SRAM chip mounted on a custom M.2 PCB. It is designed to communicate with an external host controller through a compatible memory interface. 

The project explores computer memory architecture, digital electronics, PCB designing and some parts of embedded programming. 

# Features 
- 128 KB asynchronous SRAM
- Custom M.2 2280 PCB
- 8-bit data bus
- 17-bit address bus
- External host-controller compatibility
- Custom memory read/write interface
- KiCAD-designed schematic and PCB

# Hardware 
| Components | Description |
|---|---|
| AS6C1008-55SIN | 128KB asynchronous SRAM | 
| 74HC595 | Shift registers for digital signal expansion | 
| M.2 edge connector | Physical module interface | 
| Capacitors | Power supply decoupling | 
| Resistors | Signal conditioning and pull ups | 

# How it works 
The SRAM stores data in an array of memory locations, with each location containing 8 bits. 

The host controller communicates with the memory through its address, data and control signals. 

The controller selects a memory address and performs read or write operations using the SRAM control interface. 

An external M.2 breakout adapter may be used during development and testing. A custom adapter PCB is not a mandatory part of the project. 

# Bill of Materials

Will be added later 

# Pictures of the project 

**PCB design** 

**Top layer**

<img width="1153" height="350" alt="image" src="https://github.com/user-attachments/assets/817e6127-29b9-49c5-9b19-90456494086a" />

**Bottom layer**

<img width="1150" height="335" alt="image" src="https://github.com/user-attachments/assets/75fa28cd-67b1-4655-b08c-d1d14a75430e" />

**Schematics** 

<img width="1197" height="622" alt="image" src="https://github.com/user-attachments/assets/b6d12577-b07a-41b3-a56d-41b0f73b666b" />


**3D rendered PCB design** 

<img width="1197" height="342" alt="image" src="https://github.com/user-attachments/assets/e4ebf039-d8b8-4093-b85f-05c955345c3e" />

**Physical picture**

A photo will be added later


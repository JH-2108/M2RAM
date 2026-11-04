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

An external M.2 breakout adapter can be used to simplify development and testing. 

# M2RAM Breakout Adapter

A separate breakout adapter PCB was designed as a companion to the M2RAM memory module. 

The adapter provides a female M.2 M-key socket that accepts the M2RAM module through its gold edge contacts. 

Instead of requiring a host controller to connect directly to the M.2 connector, the adapter exposes the module's electrical interface through two rows of 2.54mm through-hole header connections. 

# Adapter features
- Female M.2 M-key socket for connecting the M2RAM module.
- 8 pin data interface exposing DQ0-DQ7
- 8 pin control and power interface
- 3.3V power and GND connections
- Decoupling capacitors for supply stability
- Through hole header connections for convenient wiring to external controllers.

# Adapter interface
|Header |pin|Signal|
|---|---|---|
|J2 | 1 | DQ0|
|J2 | 2 | DQ1|
|J2 | 3 | DQ2|
|J2 | 4 | DQ3|
|J2 | 5 | DQ4|
|J2 | 6 | DQ5|
|J2 | 7 | DQ6|
|J2 | 8 | DQ7|
|J3 | 1 | SRCLR|
|J3 | 2 | SRCLK|
|J3 | 3 | RCLK|
|J3 | 4 | U2SER|
|J3 | 5 | OE|
|J3 | 6 | +3V3|
|J3 | 7 | GND|
|J3 | 8 | GND|

The adapter does not contain additional SRAM or shift registers. It simple exposes the existing M2RAM module interface to external hardware. 

Note: The adapter is an optional development accessory. The M2RAM module can be used with a compatible custom host interface without this particular adapter. 

# Bill of Materials

Will be added later 

# Pictures of the M2RAM

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

# Pictures of the M2RAM adapter

**PCB Design** 

**Top layer**

<img width="336" height="700" alt="image" src="https://github.com/user-attachments/assets/b6ec17b8-0479-42c5-838c-33b3fa6055d1" />

**Bottom layer**

<img width="332" height="702" alt="image" src="https://github.com/user-attachments/assets/fea9e641-6e43-464f-96b4-f14ea9f04dd1" />

**Schematics**

<img width="1077" height="682" alt="image" src="https://github.com/user-attachments/assets/1b4bf78d-a64e-4d56-8c55-bbd61ed68501" />

**3D rendered PCB**

<img width="300" height="625" alt="image" src="https://github.com/user-attachments/assets/a03fba8e-eda8-4a02-8b19-6fa12e5525db" />


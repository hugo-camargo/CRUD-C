# CRUD System in C

This is a console-based CRUD (Create, Read, Update, Delete) application written in C, designed to manage records for:
- Cleaners (Faxineiros)
- Clients (Clientes)
- Services (Servicos)

The application allows:
- Registering, consulting, updating, and deleting records for cleaners, clients, and services.
- Generating reports related to services within specific dates or for specific cleaners.

## Features

### Cleaners Management
- Register new cleaners
- Search for specific cleaners by CPF
- Update cleaner details
- Delete cleaner records
- List all registered cleaners

### Clients Management
- Register new clients
- Search for specific clients by CPF
- Update client details
- Delete client records
- List all registered clients

### Services Management
- Register new services
- Search services by cleaner's CPF or client's CPF
- Update service details
- Delete service records
- List all registered services

### Reports
- Clients who hired services within a specific period
- All services on a specific date
- All services of a particular cleaner

## Requirements

To run this project, you need:
- **GCC Compiler** (for compiling the C code)
- **Windows, Linux, or MacOS** (terminal-based execution)

## Installation

1. Clone this repository:

    - git clone https://github.com/hugo-camargo/CRUD-C.git

2. Navigate to the project directory:

    - cd CRUD-C

3. Compile the project using GCC: 
    - Windows - gcc project.c -o crud
    - Linux - gcc -o project project.c

4. Run the executable:

    - ./crud  # For Linux/MacOS
    - crud.exe  # For Windows

## Usage

Upon running the program, you will be presented with the main menu (in portuguese at program):

```
MENU DE OPCOES:

1. Cleaners Menu
2. Clients Menu
3. Services Menu
4. Reports Menu
5. Exit
```

Navigate through the options using the corresponding numbers to access the submenus for each category. The interface is user-friendly and intuitive.

## File Structure

- **project.c**: Main source code for the CRUD system.
- **arq_faxineiro.bin**: Binary file to store cleaner records.
- **arq_cliente.bin**: Binary file to store client records.
- **arq_servico.bin**: Binary file to store service records.
- **arq_relatorio_X.txt**: Text files generated for reports.

## Known Issues

- The reports generation functionality previously had issues related to file handling. This has been resolved by correcting the logic for opening and closing files.
- If running on **Linux**, the function `strlwr()` is not supported. A custom implementation may be required.

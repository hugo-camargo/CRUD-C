# 🧹 Cleaning Services Management System (C Project)

A C-based application for managing data related to cleaning services, including **cleaners (faxineiros)**, **clients**, and **service appointments**. The system handles registration and storage of data using binary files, enabling persistent storage of structured records.

## 📦 Features

- Register and store:
  - Cleaners (name, CPF, RG, phone numbers, sex, birthdate)
  - Clients (name, CPF, address, emails, phone numbers, birthdate)
  - Services (date, cleaner and client CPF, service value)
- File-based storage using binary files
- Dynamic memory allocation for records
- Structs to represent and organize data

## 📁 Project Structure

- `project.c` — Main source code containing all logic and data structure definitions

### Data Structures Used

```c
struct Data {
    int dia, mes, ano;
};

struct Faxineiro {
    char cpf[15], rg[15], nome[40], sexo[3];
    char telefone[15], telefone2[15];
    struct Data data;
};

struct Cliente {
    char cpf[15], nome[40], endereco[100], cep[10], cidade[50];
    char email[45], email2[45], telefone[15], telefone2[15];
    struct Data data;
};

struct Servico {
    char cpf_cliente[15], cpf_faxineiro[15];
    struct Data data;
    float valor;
};
```

## ⚙️ Requirements

- GCC or any C compiler
- Works on Linux, macOS, or Windows with minimal adjustments

## 🛠️ How to Compile

```bash
gcc project.c -o cleaning_system
```

## ▶️ How to Run

```bash
./cleaning_system
```

*(Note: Depending on the code structure, a menu interface or command-line options might be included.)*

## 📝 License

This project is licensed under the [MIT License](LICENSE).

---

Feel free to contribute or modify the system for academic or real-world use cases.

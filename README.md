# ATM Console Application in C++

## 📌 Overview

This is a simple console-based **ATM System** built using **C++**, allowing users to:

- Log in using account number and PIN
- Perform **Quick Withdraw**
- Perform **Normal Withdraw**
- **Deposit** funds
- **Check balance**
- **Log out** of their session

The program simulates real ATM functionality with a user-friendly CLI interface and handles all client data through a text file (`clients.txt`).

---

## 🗂️ Features

### ✅ Authentication
- Secure login using account number and PIN

### 💸 Quick Withdraw
- Choose from preset amounts (20, 50, 100, ..., 1000)

### 💵 Normal Withdraw
- Enter a custom amount (must be a multiple of 5)

### 💰 Deposit
- Deposit any positive amount to the account

### 💳 Balance Inquiry
- View the current account balance

---

## 📄 File: `clients.txt` Format

**Each line represents a client with the following format:**
- AccountNumber#//#PinCode#//#FullName#//#Phone#//#AccountBalance
  
**Example:**
- A250#//#1234#//#John Doe#//#05348469856#//#1000.50


---

## 🛠️ How to Run

1. Open the project in a C++ compiler or IDE (e.g., Code::Blocks, Visual Studio, g++, etc.)
2. Make sure the `clients.txt` file exists in the same directory.
3. Compile and run the program.
4. Use valid credentials from `clients.txt` to log in.

---

## 📦 Dependencies

- Standard C++ Libraries (`<iostream>`, `<fstream>`, `<iomanip>`, `<string>`, `<vector>`, `<limits>`)

---

## 🧑‍💻 Author

This project was developed as a learning exercise for structured programming and file handling in C++.

---

## 📜 License

This project is open source - free to use.


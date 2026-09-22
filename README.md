# Turing Machine

A simple **one-tape Turing Machine simulator** written in C++.

---

## 📌 Features

* Single tape Turing Machine
* Reads input from a `.txt` file
* Step-by-step execution in console
* Press **P** to stop execution at any time
* Detects possible infinite tape expansion

---

## ⚙️ Requirements

* Windows OS (uses `conio.h` and `windows.h`)
* C++ compiler (e.g. MinGW / MSYS2)

---

## ▶️ How to Run

Run the program from **PowerShell** or **Command Prompt**:

```powershell
.\main.exe 1.txt
```

The `.txt` file is passed as a command-line argument to the program.

---

## 📄 Input File Format

The program expects a `.txt` file with this structure:

```txt
<TAPE>

<HEAD_POSITION>

<RULES...>
```

### Example:

```txt
M00110100N00000000P

2

0 0 0 R 0
0 1 1 R 0
0 N N L 1
```

---

## 🧠 Rule Format

Each rule has the format:

```txt
<current_state> <read_symbol> <write_symbol> <direction> <next_state>
```

* `direction`:

  * `L` → move left
  * `R` → move right

---

## ⛔ Halting

The machine stops when:

* No matching rule is found
* Or the user presses **P**

---

## 📊 Output

After execution, the program prints:

* Total steps
* Final state
* Head position
* Final tape
* Current symbol under the head

---

## ⚠️ Notes

* Head position in input is **1-based**
* Output head position is **0-based**
* Blank symbol is `_`
* Infinite movement warning appears after 10,000 repeated moves in the same direction

---

## 📁 Example Files

* `main.cpp` – source code
* `input.txt` – example machine input

---

## 🚀 Future Improvements

* Cross-platform support (remove Windows-specific libraries)
* Better visualization
* Multi-tape support

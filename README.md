# 🔹 C & C++ Practice Tasks  
This repository contains my C/C++ practice tasks from the ITI Open Source Track.  
Each task focuses on a specific concept such as terminal control, cross-platform input handling, animations, loops, and algorithmic logic.

---

## 🚀 **Task 1 — ANSI Text, Colors & Positioning**
This task focuses on controlling the terminal using **ANSI escape codes** to:

- Move the cursor to specific coordinates  
- Change text colors  
- Reset formatting  
- Clear the screen  
- Print text at custom X/Y positions  

It builds the foundations needed for creating UI-like behavior inside the terminal.

**Key skills learned:**

- Working with ANSI escape sequences  
- Using functions to structure terminal output  
- Cross-platform terminal behavior (Linux / Windows support)

---

## 🚀 **Task 2 — Interactive Menu (Up/Down Arrows + Pages)**
This task builds a fully interactive menu interface:

- Navigate using **Up/Down Arrow keys**  
- Highlight the selected item  
- Enter the page using **Enter**  
- Return using **Backspace**  
- Exit using **ESC**  
- Works on both **Linux** and **Windows**

**Features implemented:**

- `getch_cross()` → a cross-platform function for reading keypresses without Enter  
- `showMenu()` → draws the menu and highlights the selected item  
- `page()` → opens an inner screen with navigation  
- A clean and efficient `main()` loop to handle user interaction  

---

## 🚀 **Task 3 — Magic Box Generator (Odd Size: 3 or 5)**
This task generates a **Magic Square** (Siamese method) using simple movement rules.

**Highlights:**

- Grid printing using ASCII box-drawing  
- Filling the magic box step-by-step  
- Animation using delays  
- Wrapping logic (edges loop around)
- Fully structured using functions

**What the program does:**

1. Takes an odd number (3 or 5)  
2. Places “1” in the top-middle cell  
3. Fills numbers using these rules:  
   - If the previous number is divisible by *n*, move **down**  
   - Otherwise: move **up-right**  
4. Wrap around when reaching edges  
5. Prints the magic box after every update  

---

## 📁 **Project Structure**

/repo-root
│
├── Task1/
│ ├── main.cpp
│ ├── headers.h
│ └── Library.cpp
│
├── Task2/
│ ├── main.cpp
│ ├── headers.h
│ └── Library.cpp
│
├── Task3/
│ └── magic_box.cpp
│
└── 


## ▶️ **How to Compile & Run**

### **Linux**
```bash
g++ main.cpp Library.cpp -o run
./run

Windows (MinGW / g++ installed)
g++ main.cpp Library.cpp -o run.exe
run.exe

For Task 3:
g++ magic_box.cpp -o magic
./magic
```
Cross-Platform Notes

getch_cross() handles OS-specific behavior

Windows uses <conio.h>

Linux uses <termios.h> + <unistd.h>

ANSI colors and cursor movement work on both platforms

🛠 Technologies Used

C++ (Core Logic)

ANSI Escape Codes

Terminal I/O

Linux GCC

Windows MinGW

VS Code

📌 Author

Haneen Ahmed (Nino)
ITI OS – Open Source Track

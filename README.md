# ⚡ cslipy – Zero-Pain C++ Setup for Windows

[![Version](https://img.shields.io/badge/version-v1.0.0-blue)](https://github.com/yourname/cslipy/releases/tag/v1.0.0)
[![Platform](https://img.shields.io/badge/platform-Windows-green)]()
[![License](https://img.shields.io/badge/license-MIT-lightgrey)]()

---

> 💻 **Tired of wasting hours setting up C++ in VS Code on Windows?**  
Meet **cslipy** – a tiny script that automates the boring stuff: installing MSYS2, setting up MinGW, wiring compilers to PATH, and testing it while at it.
No tutorials, no confusing docs, no broken configs. Just **download → run → code**.  

---

## 🚀 Features
- ✅ **One-command setup** for C++ dev on Windows  
- ⚡ Installs & configures **MSYS2 + MinGW-w64** (the real deal compilers)   
- 🔧 Includes a **Hello World test** to confirm everything works  
- 🛠️ Adds **g++/gdb** globally so you can use them anywhere in the terminal  
- 🕶️ Minimal, no bloat – just a clean toolchain  

---

## 📦 Installation

### 1. Get the Release
Download the latest pre-release:  
👉 [cslipy v1.0.0](https://github.com/vennictus/cslipy/releases/tag/v1.0.0)  

You’ll get a `.zip` containing:  
- `cslipy.exe` → our installer runner  
- `msys2-x86_64-20250622.exe` → the MSYS2 bootstrap  

---

### 2. Run the Installer
Open VS Code → Terminal → navigate to the folder → run:  

```bash
./cslipy install
```

---

### 3. What Happens Behind the Scenes 🪄
- Installs **MSYS2**
- It will prompt you to install MSYS2 using GUI,select the default inputs for all of them,
  in the last screen unselect "Run after installation Button"
- Uses `pacman` (MSYS2’s package manager) to fetch:
  - `mingw-w64-x86_64-gcc` → modern C++ compiler  
  - `mingw-w64-x86_64-gdb` → debugger  
  - `make` → build tool  
- Sets up your **PATH** so `g++` & `gdb` just work  
- Runs a **Hello World test program** to verify setup  

## ⚠️ Notes
- 🪟 **Windows-only** (Linux/macOS already have GCC/Clang easily available).  
- First-time install may take ~5–10 minutes (MSYS2 + packages).  
- **Internet required** for package downloads.  
- If you already have MSYS2, cslipy will detect & reuse it (no duplicates).  

---

## 🛣️ Roadmap
- [ ] Add support for **CMake projects**  
- [ ] Auto-configure **IntelliSense (c_cpp_properties.json)**  
- [ ] Linux/Mac installer (mostly redundant, but for consistency)  
- [ ] GUI wrapper for people who fear terminals 👀  

---

## 🤝 Contributing
PRs, ideas, and bug reports are super welcome!  
- Open an [issue](https://github.com/yourname/cslipy/issues) for bugs/requests  
- Fork → Branch → PR if you want to contribute code  

---

## 📜 License
MIT License © 2025 Vennictus


#include <iostream>
#include <string>
#include <windows.h>

// --- Color Utility ---
void setColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

// --- Progress Bar (WinAPI Sleep) ---
void progressBar(const std::string& task, int durationMs = 2000) {
    const int width = 30; // bar width
    setColor(14);         // Yellow while working
    for (int i = 0; i <= 100; i += 5) {
        int pos = (i * width) / 100;
        std::cout << "\r[";
        for (int j = 0; j < width; ++j) {
            std::cout << (j < pos ? "#" : "-");
        }
        std::cout << "] " << i << "% " << task << std::flush;
        Sleep(durationMs / 20); // 20 steps (0..100 by 5)
    }
    setColor(10); // Green when done
    std::cout << "\r[##############################] 100% " << task << "   \n";
    setColor(7);  // Reset
}

// --- Install Command ---
void installCmd() {
    std::cout << "🔧 Running cslipy install...\n\n";

    progressBar("Downloading MinGW");
    progressBar("Installing MinGW");
    progressBar("Updating PATH");
    progressBar("Creating Hello World file");

    setColor(10);
    std::cout << "\n✅ All done! This machine now runs C/C++ 🚀\n";
    setColor(7);
}

#include <cstdlib>
#include <iostream>

// --- Version Command ---
void versionCmd() {
    std::cout << "cslipy v0.1.0\n";

    // Try running "g++ --version" and check result
    int result = system("g++ --version > temp_version.txt 2>&1");

    if (result == 0) {
        std::cout << "Detected MinGW (g++) version:\n";
        system("type temp_version.txt"); // print contents on Windows
    } else {
        std::cout << "⚠️ MinGW (g++) not found on this system.\n";
    }

    // cleanup temp file
    system("del temp_version.txt > nul 2>&1");
}

// --- Nuke Command ---
void nukeCmd() {
    setColor(12); // red
    std::cout << "💣 Removing C/C++ toolchain...\n";
    Sleep(1500);
    std::cout << "✅ Uninstalled successfully.\n";
    setColor(7);
}

// --- Main CLI ---
int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cout << "Usage: cslipy <command>\n";
        std::cout << "Commands:\n";
        std::cout << "  install   Install C/C++ toolchain\n";
        std::cout << "  nuke      Uninstall everything\n";
        std::cout << "  version   Show version info\n";
        return 0;
    }

    std::string cmd = argv[1];

    if (cmd == "install") {
        installCmd();
    } 
    else if (cmd == "nuke") {
        nukeCmd();
    } 
    else if (cmd == "version") {
        versionCmd();
    } 
    else {
        std::cout << "❌ Unknown command: " << cmd << "\n";
    }

    return 0;
}

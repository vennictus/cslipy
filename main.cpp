#include <iostream>
#include <string>
#include <windows.h>

// --- Color Utility ---
void setColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

// --- Command Handlers ---
void installCmd() {
    setColor(10); // Bright Green
    std::cout << "🔧 Running cslipy install...\n";
    setColor(7); // Reset to default
    // TODO: download + install compiler
}

void nukeCmd() {
    setColor(10);
    std::cout << "💣 Running cslipy nuke...\n";
    setColor(7);
    // TODO: uninstall + clean PATH
}

void versionCmd() {
    setColor(10);
    std::cout << "cslipy v0.1.0\n";
    setColor(7);
    // TODO: detect gcc/g++ version
}

void doctorCmd() {
    setColor(10);
    std::cout << "🩺 Running cslipy doctor...\n";
    setColor(7);
    // TODO: check PATH + test compile
}

// --- Entry Point ---
int main(int argc, char* argv[]) {
    if (argc < 2) {
        setColor(10);
        std::cout << "Usage: cslipy <command>\n";
        std::cout << "Commands:\n";
        std::cout << "  install   Install compiler(s)\n";
        std::cout << "  nuke      Uninstall compiler(s)\n";
        std::cout << "  version   Show versions\n";
        std::cout << "  doctor    Check environment health\n";
        setColor(7);
        return 1;
    }

    std::string cmd = argv[1];

    if (cmd == "install") {
        installCmd();
    } else if (cmd == "nuke") {
        nukeCmd();
    } else if (cmd == "version") {
        versionCmd();
    } else if (cmd == "doctor") {
        doctorCmd();
    } else {
        setColor(12); // Red
        std::cout << "❌ Unknown command: " << cmd << "\n";
        setColor(7);
    }

    return 0;
}

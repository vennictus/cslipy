#include <iostream>
#include <string>

// --- Command Handlers ---
void installCmd() {
    std::cout << "🔧 Running cslipy install...\n";
    // TODO: download + install compiler
}

void nukeCmd() {
    std::cout << "💣 Running cslipy nuke...\n";
    // TODO: uninstall + clean PATH
}

void versionCmd() {
    std::cout << "cslipy v0.1.0\n";
    // TODO: detect gcc/g++ version
}

void doctorCmd() {
    std::cout << "🩺 Running cslipy doctor...\n";
    // TODO: check PATH + test compile
}

// --- Entry Point ---
int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cout << "Usage: cslipy <command>\n";
        std::cout << "Commands:\n";
        std::cout << "  install   Install compiler(s)\n";
        std::cout << "  nuke      Uninstall compiler(s)\n";
        std::cout << "  version   Show versions\n";
        std::cout << "  doctor    Check environment health\n";
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
        std::cout << "❌ Unknown command: " << cmd << "\n";
    }

    return 0;
}

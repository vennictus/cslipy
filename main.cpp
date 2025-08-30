#include <iostream>
#include <string>
#include <windows.h>
#include <fstream>
#include <cstdlib>

// --- Utility: Set console text color ---
void setColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

// --- Utility: Check if directory exists ---
bool dirExists(const char* path) {
    DWORD ftyp = GetFileAttributesA(path);
    return (ftyp != INVALID_FILE_ATTRIBUTES && (ftyp & FILE_ATTRIBUTE_DIRECTORY));
}

// --- Progress bar ---
void progressBar(const std::string& task, int durationMs = 2000) {
    const int width = 30;
    setColor(14);
    for (int i = 0; i <= 100; i += 5) {
        int pos = (i * width) / 100;
        std::cout << "\r[";
        for (int j = 0; j < width; ++j)
            std::cout << (j < pos ? "#" : "-");
        std::cout << "] " << i << "% " << task << std::flush;
        Sleep(durationMs / 20);
    }
    setColor(10);
    std::cout << "\r[##############################] 100% " << task << "   \n";
    setColor(7);
}

// --- Install ---
void installCmd() {
    std::cout << "📦 Installing cslipy toolchain...\n\n";

    // Step 1: Check MSYS2
    progressBar("Checking for MSYS2");
    int msysCheck = system("if exist C:\\msys64 (exit 0) else (exit 1)");
    if (msysCheck != 0) {
        progressBar("Running MSYS2 installer");
        system("start /wait msys2-x86_64-20250622.exe");
    }

    // Step 2: Update MSYS2 core
    progressBar("Updating MSYS2 core system");
    int updateResult = system(
        "C:\\msys64\\usr\\bin\\bash -lc \"pacman -Sy --noconfirm && pacman -Syu --noconfirm\""
    );
    if (updateResult != 0) {
        setColor(12);
        std::cout << "❌ MSYS2 update failed.\n";
        setColor(7);
        return;
    }

    // Step 3: Check for GCC
    progressBar("Checking for GCC");
    int gccCheck = system("C:\\msys64\\usr\\bin\\bash -lc \"command -v g++\"");
    if (gccCheck != 0) {
        progressBar("Installing MinGW-w64 GCC");
        int gccInstall = system(
            "C:\\msys64\\usr\\bin\\bash -lc \"pacman -S --noconfirm mingw-w64-x86_64-gcc\""
        );
        if (gccInstall != 0) {
            setColor(12);
            std::cout << "❌ GCC installation failed.\n";
            setColor(7);
            return;
        }
    }

    // Step 4: Ensure PATH (Windows side)
    progressBar("Ensuring MinGW-w64 is in PATH");
    system("powershell -Command \"if (-not ($env:Path -match 'C:\\\\msys64\\\\mingw64\\\\bin')) "
           "{ [Environment]::SetEnvironmentVariable('Path', $env:Path + ';C:\\\\msys64\\\\mingw64\\\\bin', 'User') }\"");

    // Step 5: Test Hello World
    // Step 5: Test Hello World
progressBar("Compiling Hello World test");
{
    std::ofstream hello("hello.cpp");
    hello << "#include <iostream>\nint main(){std::cout<<\"Hello from cslipy!\\n\";return 0;}";
}

// Detect current directory (Windows)
char buffer[MAX_PATH];
GetCurrentDirectoryA(MAX_PATH, buffer);
std::string winDir(buffer);

// Convert it to MSYS2 path using cygpath
std::string msysDirCmd = "C:\\msys64\\usr\\bin\\bash -lc \"cygpath -u '" + winDir + "'\"";
FILE* pipe = _popen(msysDirCmd.c_str(), "r");
char msysDir[512];
fgets(msysDir, sizeof(msysDir), pipe);
_pclose(pipe);

// Trim newline
std::string msysDirStr(msysDir);
msysDirStr.erase(msysDirStr.find_last_not_of(" \n\r\t") + 1);

// Compile in correct directory
std::string cmd = 
    "C:\\msys64\\usr\\bin\\bash -lc \""
    "export PATH=/mingw64/bin:$PATH && "
    "cd '" + msysDirStr + "' && "
    "g++ hello.cpp -o hello && ./hello\"";

int runResult = system(cmd.c_str());
if (runResult != 0) {
    setColor(12);
    std::cout << "❌ Hello World compilation failed.\n";
    setColor(7);
    return;
}
    
}


// --- Nuke ---
// --- Nuke ---
// --- Nuke ---
void nukeCmd() {
    std::cout << "💣 Running cslipy nuke...\n\n";

    // Step 1: Kill running MSYS2 processes
    progressBar("Stopping MSYS2 processes");
    system("taskkill /F /IM msys2.exe >nul 2>&1");
    system("taskkill /F /IM bash.exe >nul 2>&1");
    system("taskkill /F /IM mintty.exe >nul 2>&1");

    // Step 2: Remove MSYS2 installation
    progressBar("Removing MSYS2 installation");
    system("rmdir /S /Q C:\\msys64 >nul 2>&1");

    // Step 3: Remove PATH entries (permanent + session)
    progressBar("Cleaning PATH");
    system("powershell -Command \"[Environment]::SetEnvironmentVariable('Path', "
           "($env:Path -replace 'C:\\\\msys64\\\\mingw64\\\\bin;?', ''), 'User')\"");

    std::string currentPath;
    if (const char* p = std::getenv("PATH")) currentPath = p;
    size_t pos;
    while ((pos = currentPath.find("C:\\msys64\\mingw64\\bin;")) != std::string::npos) {
        currentPath.erase(pos, strlen("C:\\msys64\\mingw64\\bin;"));
    }
    SetEnvironmentVariableA("PATH", currentPath.c_str());

    // Step 4: Remove Start Menu shortcuts
    progressBar("Removing Start Menu entries");
    system("rmdir /S /Q \"C:\\ProgramData\\Microsoft\\Windows\\Start Menu\\Programs\\MSYS2 64bit\" >nul 2>&1");

    // Step 5: Remove uninstall registry entries
    progressBar("Cleaning registry uninstall entries");
    system("powershell -Command \"Remove-Item -Path 'HKCU:\\Software\\Microsoft\\Windows\\CurrentVersion\\Uninstall\\MSYS2 64bit' -Recurse -Force -ErrorAction SilentlyContinue\"");
    system("powershell -Command \"Remove-Item -Path 'HKLM:\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Uninstall\\MSYS2 64bit' -Recurse -Force -ErrorAction SilentlyContinue\"");

    // Step 6: Delete temp files
    progressBar("Deleting temp files");
    system("del /Q hello.cpp >nul 2>&1");
    system("del /Q hello.exe >nul 2>&1");

    setColor(10);
    std::cout << "\n✅ System fully cleaned. cslipy nuked successfully.\n";
    setColor(7);
}


// --- Version ---
void versionCmd() {
    std::cout << "cslipy v0.1.0\n";

    int result = system("g++ --version > temp_version.txt 2>&1");

    if (result == 0) {
        setColor(10);
        std::cout << "✅ Detected MinGW (g++) version:\n";
        setColor(7);
        system("type temp_version.txt");
    } else {
        setColor(12);
        std::cout << "⚠️ MinGW (g++) not found on this system.\n";
        setColor(7);
    }

    system("del temp_version.txt > nul 2>&1");
}

// --- Help ---
void helpCmd() {
    setColor(11);
    std::cout << "cslipy - The one-click C/C++ setup tool for Windows\n\n";
    setColor(7);

    std::cout << "Usage:\n";
    setColor(14); std::cout << "  cslipy install"; setColor(7); std::cout << "   Install MinGW and setup environment\n";
    setColor(14); std::cout << "  cslipy nuke";    setColor(7); std::cout << "      Remove C/C++ setup completely\n";
    setColor(14); std::cout << "  cslipy version"; setColor(7); std::cout << "   Show installed compiler version\n";
    setColor(14); std::cout << "  cslipy help";    setColor(7); std::cout << "      Show this help message\n";
}

// --- Main ---
int main(int argc, char* argv[]) {
    if (argc < 2) {
        helpCmd();
        return 0;
    }

    std::string command = argv[1];
    if (command == "install") {
        installCmd();
    } else if (command == "nuke") {
        nukeCmd();
    } else if (command == "version") {
        versionCmd();
    } else if (command == "help") {
        helpCmd();
    } else {
        setColor(12);
        std::cout << "Unknown command: " << command << "\n";
        setColor(7);
        helpCmd();
    }

    return 0;
}

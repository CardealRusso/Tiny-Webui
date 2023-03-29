#include <Windows.h>
#include <stdio.h>
#include <string.h>

int main() {
    const char* ChromiumBrowsers[] = {"chrome", "msedge", "vivaldi", "brave"};
    char path[MAX_PATH];

    for (int i = 0; i < sizeof(ChromiumBrowsers)/sizeof(ChromiumBrowsers[0]); i++) {
        HKEY hKey;
        DWORD pathSize = sizeof(path);
        sprintf(path, "Software\\Microsoft\\Windows\\CurrentVersion\\App Paths\\%s.exe", ChromiumBrowsers[i]);

        if (RegOpenKeyEx(HKEY_CURRENT_USER, path, 0, KEY_READ, &hKey) == ERROR_SUCCESS ||
            RegOpenKeyEx(HKEY_LOCAL_MACHINE, path, 0, KEY_READ, &hKey) == ERROR_SUCCESS) {
            if (RegQueryValueEx(hKey, "Path", NULL, NULL, (LPBYTE)path, &pathSize) == ERROR_SUCCESS) {
                RegCloseKey(hKey);
                char command[MAX_PATH + 1000];
		//I needed to use base64 for the html because windows insists on refusing to correctly pass the quotes to the browser in the --app value
                sprintf(command, "\"%s\\%s.exe\" --no-first-run --disable-gpu --disable-software-rasterizer --no-proxy-server --safe-mode --disable-extensions --disable-background-mode --disable-plugins --disable-plugins-discovery --disable-translate --bwsi --disable-sync --incognito --app=data:text/html;charset=utf-8;base64,PHRpdGxlPkhlbGxvIFdvcmxkITwvdGl0bGU+CjxsaW5rIHJlbD0iaWNvbiIgaHJlZj0iaHR0cHM6Ly9zdGF0aWMtMDAuaWNvbmR1Y2suY29tL2Fzc2V0cy4wMC93ZWJ2aWV3LWljb24tMjU2eDI1Ni1hOWMyd3poOC5wbmciPgo8c3R5bGU+CmJvZHkgewpiYWNrZ3JvdW5kLWNvbG9yOiAjM2EzMDRhOwp9CiNoZWxsbyB7CnBvc2l0aW9uOiBhYnNvbHV0ZTsKdG9wOiA1MCU7CmxlZnQ6IDUwJTsKdHJhbnNmb3JtOiB0cmFuc2xhdGUoLTUwJSwgLTUwJSk7CmZvbnQtc2l6ZTogNTBweDsKY29sb3I6IHdoaXRlOwp9Cjwvc3R5bGU+CjxkaXYgaWQ9ImhlbGxvIj5IZWxsbyBXb3JsZCE8L2Rpdj4KPHNjcmlwdD4KKCgpID0+IHsKY29uc3QgZGl2ID0gZG9jdW1lbnQuZ2V0RWxlbWVudEJ5SWQoImhlbGxvIik7CmxldCB4ID0gaW5uZXJXaWR0aCAvIDI7CmxldCB5ID0gaW5uZXJIZWlnaHQgLyAyOwpsZXQgeERpcmVjdGlvbiA9IDE7CmxldCB5RGlyZWN0aW9uID0gMTsKY29uc3QgbW92ZURpdiA9ICgpID0+IHsKeCArPSB4RGlyZWN0aW9uOwp5ICs9IHlEaXJlY3Rpb247CmlmICh4ICsgZGl2Lm9mZnNldFdpZHRoID49IGlubmVyV2lkdGggfHwgeCA8PSAwKSB7CnhEaXJlY3Rpb24gKj0gLTE7CmRpdi5zdHlsZS5jb2xvciA9IGdldFJhbmRvbUNvbG9yKCk7Cn0KaWYgKHkgKyBkaXYub2Zmc2V0SGVpZ2h0ID49IGlubmVySGVpZ2h0IHx8IHkgPD0gMCkgewp5RGlyZWN0aW9uICo9IC0xOwpkaXYuc3R5bGUuY29sb3IgPSBnZXRSYW5kb21Db2xvcigpOwp9CmRpdi5zdHlsZS5sZWZ0ID0gYCR7eH1weGA7CmRpdi5zdHlsZS50b3AgPSBgJHt5fXB4YDsKfTsKY29uc3QgZ2V0UmFuZG9tQ29sb3IgPSAoKSA9PiBgIyR7TWF0aC5yYW5kb20oKS50b1N0cmluZygxNikuc3Vic3RyKC02KX1gOwpzZXRJbnRlcnZhbChtb3ZlRGl2LCAxMCk7Cn0pKCk7Cjwvc2NyaXB0Pg==", path, ChromiumBrowsers[i]);
                system(command);
                break;
            }
            RegCloseKey(hKey);
        }
    }

    return 0;
}

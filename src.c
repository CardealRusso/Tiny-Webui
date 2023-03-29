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
                sprintf(command, "\"%s\\%s.exe\" --no-first-run --disable-gpu --disable-software-rasterizer --no-proxy-server --safe-mode --disable-extensions --disable-background-mode --disable-plugins --disable-plugins-discovery --disable-translate --bwsi --disable-sync --incognito --app=data:text/html;charset=utf-8;base64,PHN0eWxlPgpib2R5IHsKICBiYWNrZ3JvdW5kLWNvbG9yOiMyMDIxMjQ7CiAgY29sb3I6QkRDMUM2OwogIGZvbnQtZmFtaWx5OiBDYW1icmlhLCBHZW9yZ2lhLCBzZXJpZjsKICBtYXJnaW46IGF1dG87CiAgd2lkdGg6IDU5JTsKICBib3JkZXI6IDFweCBzb2xpZCAjM0M0MDQzOwogIHBhZGRpbmc6IDEwcHg7CglvdmVyZmxvdzogaGlkZGVuOwp9Cjwvc3R5bGU+Cjx0aXRsZT5UaW55LVdlYnVpPC90aXRsZT4KPGxpbmsgcmVsPSJpY29uIiB0eXBlPSJpbWFnZS94LWljb24iIGhyZWY9Imh0dHBzOi8vc3RhdGljLTAwLmljb25kdWNrLmNvbS9hc3NldHMuMDAvd2Vidmlldy1pY29uLTUxMng1MTItOXR0MTg3angucG5nIj4KPGgxPlRpbnktV2ViVUk8L2gxPgpSdW5uaW5nIG9uIAoKPHNjcmlwdD4Kd2luZG93LnJlc2l6ZVRvKDgwMCw2MDApOwpkb2N1bWVudC5hZGRFdmVudExpc3RlbmVyKCdrZXlkb3duJywgKGUpID0+IHsKICAgIGUgPSBlIHx8IHdpbmRvdy5ldmVudDsKICAgIGlmKGUua2V5Q29kZSA9PSAxMTYpewogICAgICAgIGUucHJldmVudERlZmF1bHQoKTsKICAgIH0KfSk7CmRvY3VtZW50LmFkZEV2ZW50TGlzdGVuZXIoJ2NvbnRleHRtZW51JywgZXZlbnQgPT4gZXZlbnQucHJldmVudERlZmF1bHQoKSk7CmNvbnN0IGFnZW50ID0gd2luZG93Lm5hdmlnYXRvci51c2VyQWdlbnQudG9Mb3dlckNhc2UoKTsKICBjb25zdCBicm93c2VyID0KICAgIGFnZW50LmluZGV4T2YoJ2VkZ2UnKSA+IC0xID8gJ2VkZ2UnCiAgICAgIDogYWdlbnQuaW5kZXhPZignZWRnJykgPiAtMSA/ICdjaHJvbWl1bSBiYXNlZCBlZGdlJwogICAgICA6IGFnZW50LmluZGV4T2YoJ29wcicpID4gLTEgJiYgd2luZG93Lm9wciA/ICdvcGVyYScKICAgICAgOiBhZ2VudC5pbmRleE9mKCdjaHJvbWUnKSA+IC0xICYmIHdpbmRvdy5jaHJvbWUgPyAnY2hyb21lJwogICAgICA6IGFnZW50LmluZGV4T2YoJ3RyaWRlbnQnKSA+IC0xID8gJ2llJwogICAgICA6IGFnZW50LmluZGV4T2YoJ2ZpcmVmb3gnKSA+IC0xID8gJ2ZpcmVmb3gnCiAgICAgIDogYWdlbnQuaW5kZXhPZignc2FmYXJpJykgPiAtMSA/ICdzYWZhcmknCiAgICAgIDogJ290aGVyJzsKZG9jdW1lbnQuYm9keS5pbm5lckhUTUwrPWJyb3dzZXIKPC9zY3JpcHQ+Cg==", path, ChromiumBrowsers[i]);
                system(command);
                break;
            }
            RegCloseKey(hKey);
        }
    }

    return 0;
}

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
                sprintf(command, "\"%s\\%s.exe\" --no-first-run --disable-gpu --disable-software-rasterizer --no-proxy-server --safe-mode --disable-extensions --disable-background-mode --disable-plugins --disable-plugins-discovery --disable-translate --bwsi --disable-sync --incognito --app=data:text/html;charset=utf-8;base64,PHN0eWxlPgpib2R5IHsKICBiYWNrZ3JvdW5kLWltYWdlOiBsaW5lYXItZ3JhZGllbnQodG8gcmlnaHQsICM2NDY4NzAgLCAjMzkyNDU0KTsKICBmb250LWZhbWlseTogQ2FtYnJpYSwgR2VvcmdpYSwgc2VyaWY7CiAgbWFyZ2luOiBhdXRvOwogIHdpZHRoOiA1OSU7CiAgYm9yZGVyOiAxcHggc29saWQgcGluazsKICBwYWRkaW5nOiAxMHB4Owp9Cjwvc3R5bGU+Cjx0aXRsZT5UaW55LVdlYnVpPC90aXRsZT4KPGxpbmsgcmVsPSJpY29uIiB0eXBlPSJpbWFnZS94LWljb24iIGhyZWY9Imh0dHBzOi8vc3RhdGljLTAwLmljb25kdWNrLmNvbS9hc3NldHMuMDAvd2Vidmlldy1pY29uLTUxMng1MTItOXR0MTg3angucG5nIj4KPGgxPlRpbnktV2ViVUk8L2gxPgpSdW5uaW5nIG9uIAoKPHNjcmlwdD4KZG9jdW1lbnQuYWRkRXZlbnRMaXN0ZW5lcigna2V5ZG93bicsIChlKSA9PiB7CiAgICBlID0gZSB8fCB3aW5kb3cuZXZlbnQ7CiAgICBpZihlLmtleUNvZGUgPT0gMTE2KXsKICAgICAgICBlLnByZXZlbnREZWZhdWx0KCk7CiAgICB9Cn0pOwpkb2N1bWVudC5hZGRFdmVudExpc3RlbmVyKCdjb250ZXh0bWVudScsIGV2ZW50ID0+IGV2ZW50LnByZXZlbnREZWZhdWx0KCkpOwpjb25zdCBhZ2VudCA9IHdpbmRvdy5uYXZpZ2F0b3IudXNlckFnZW50LnRvTG93ZXJDYXNlKCk7CiAgY29uc3QgYnJvd3NlciA9CiAgICBhZ2VudC5pbmRleE9mKCdlZGdlJykgPiAtMSA/ICdlZGdlJwogICAgICA6IGFnZW50LmluZGV4T2YoJ2VkZycpID4gLTEgPyAnY2hyb21pdW0gYmFzZWQgZWRnZScKICAgICAgOiBhZ2VudC5pbmRleE9mKCdvcHInKSA+IC0xICYmIHdpbmRvdy5vcHIgPyAnb3BlcmEnCiAgICAgIDogYWdlbnQuaW5kZXhPZignY2hyb21lJykgPiAtMSAmJiB3aW5kb3cuY2hyb21lID8gJ2Nocm9tZScKICAgICAgOiBhZ2VudC5pbmRleE9mKCd0cmlkZW50JykgPiAtMSA/ICdpZScKICAgICAgOiBhZ2VudC5pbmRleE9mKCdmaXJlZm94JykgPiAtMSA/ICdmaXJlZm94JwogICAgICA6IGFnZW50LmluZGV4T2YoJ3NhZmFyaScpID4gLTEgPyAnc2FmYXJpJwogICAgICA6ICdvdGhlcic7CmRvY3VtZW50LmJvZHkuaW5uZXJIVE1MKz1icm93c2VyCjwvc2NyaXB0Pgo=", path, ChromiumBrowsers[i]);
                system(command);
                break;
            }
            RegCloseKey(hKey);
        }
    }

    return 0;
}

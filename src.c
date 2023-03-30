#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#ifdef _WIN32
#include <Windows.h>
#include <string.h>
#include <tchar.h>
#endif

void create_html_file(char* filename) {
		const char* html_content = "hello<br>world";
    char* temp_dir = getenv("TEMP");
    srand(time(NULL));
    sprintf(filename, "%s\\tiny-webui_%d.html", temp_dir, rand());
    FILE* fp = fopen(filename, "w");
    if (fp != NULL) {
        fprintf(fp, "%s", html_content);
        fclose(fp);
    } else {
        exit(EXIT_FAILURE);
    }
}

int main() {
    const char* ChromiumBrowsers[] = {"chrome", "msedge", "vivaldi", "brave"};
    char path[MAX_PATH];
    char filename[MAX_PATH];
    char command[MAX_PATH*2];
    char* browser = NULL;

#ifdef _WIN32
    for (int i = 0; i < sizeof(ChromiumBrowsers)/sizeof(ChromiumBrowsers[0]); i++) {
        HKEY hKey;
        DWORD pathSize = sizeof(path);
        sprintf(path, "Software\\Microsoft\\Windows\\CurrentVersion\\App Paths\\%s.exe", ChromiumBrowsers[i]);

        if (RegOpenKeyEx(HKEY_CURRENT_USER, path, 0, KEY_READ, &hKey) == ERROR_SUCCESS ||
            RegOpenKeyEx(HKEY_LOCAL_MACHINE, path, 0, KEY_READ, &hKey) == ERROR_SUCCESS) {
            if (RegQueryValueEx(hKey, "Path", NULL, NULL, (LPBYTE)path, &pathSize) == ERROR_SUCCESS) {
                RegCloseKey(hKey);
								
                browser = (char*)ChromiumBrowsers[i];
								
                break;
            }
            RegCloseKey(hKey);
        }
    }
#else
    // Code for Linux goes here
#endif
    if (browser != NULL) {
			create_html_file(filename);
			sprintf(command, "\"%s\\%s.exe\" --no-first-run --disable-gpu --disable-software-rasterizer --no-proxy-server --safe-mode --disable-extensions --disable-background-mode --disable-plugins --disable-plugins-discovery --disable-translate --bwsi --disable-sync --incognito --app=%s", path, browser, filename);
			system(command);
    }

    return 0;
}

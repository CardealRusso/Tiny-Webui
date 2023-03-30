#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#ifdef _WIN32
#include <Windows.h>
#endif

void create_html_file(char* filename) {
    const char* html_content = "<style> body { background-color: #202124; color: BDC1C6; font-family: Cambria, Georgia, serif; margin: auto; width: 59%; border: 1px solid #3c4043; padding: 10px; overflow: hidden; }</style><title>Tiny-Webui</title><link rel=icon href=https://i.imgur.com/MwgvSt9.png><h1>Tiny-WebUI</h1><script>window.resizeTo(800,600);document.addEventListener('keydown', function(event) { event.preventDefault();});document.addEventListener('contextmenu', function(event) { event.preventDefault();});document.addEventListener('wheel', function(event) { event.preventDefault();});navigator.userAgentData.brands.forEach(brand => brand.brand.includes('Not A(Brand') || (document.body.innerHTML += `${brand.brand} ${brand.version}<br>`));</script>";
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
    const char* ChromiumBrowsers[] = {"chrome","msedge", "vivaldi", "brave", "chromium-browser","chrome-browser","Chrome","Chromium"};
    char path[MAX_PATH];
    char filename[MAX_PATH];
    char command[MAX_PATH*2];
    char* browser = NULL;

    for (int i = 0; i < sizeof(ChromiumBrowsers)/sizeof(ChromiumBrowsers[0]); i++) {
      #ifdef _WIN32
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
      #else
        #ifdef __linux__
        sprintf(path, "/usr/bin/%s", ChromiumBrowsers[i]);
        #elif __APPLE__
        sprintf(path, "/Applications/%s.app/Contents/MacOS/%s", ChromiumBrowsers[i], ChromiumBrowsers[i]);
        #endif
        if (access(path, X_OK) == 0) {
            browser = (char*)ChromiumBrowsers[i];
            break;
        }
      #endif
    }
    if (browser != NULL) {
        create_html_file(filename);
        sprintf(command, "\"%s\\%s\" --no-first-run --disable-gpu --disable-software-rasterizer --no-proxy-server --safe-mode --disable-extensions --disable-background-mode --disable-plugins --disable-plugins-discovery --disable-translate --bwsi --disable-sync --incognito --app=%s", path, browser, filename);
        system(command);
        return 0;
    } else {
        exit(EXIT_FAILURE);
    }
}

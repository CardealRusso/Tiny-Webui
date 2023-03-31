#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>

#ifdef _WIN32
#include <Windows.h>
#endif
#ifdef __linux__
#include <unistd.h>
#endif

void create_html_file(char* filename) {
    const char* html_content = "<style> body { background-color: #202124; color: BDC1C6; font-family: Cambria, Georgia, serif; margin: auto; width: 59%; border: 1px solid #3c4043; padding: 10px; overflow: hidden; }</style><title>Tiny-Webui</title><link rel=icon href=https://i.imgur.com/MwgvSt9.png><h1>Tiny-WebUI</h1><script> window.resizeTo(800, 600); document.addEventListener('keydown', function (event) { event.preventDefault(); }); document.addEventListener('contextmenu', function (event) { event.preventDefault(); }); document.addEventListener('wheel', function (event) { event.preventDefault(); }); navigator.userAgentData.brands.forEach((brand) => brand.brand.includes('Not') || (document.body.innerHTML += `${brand.brand} ${brand.version}<br>`));document.body.innerHTML += 'On '+navigator.userAgentData.platform</script>";
    #ifdef _WIN32
        sprintf(filename, "%s\\tiny-webui_%d.html", getenv("TEMP"), rand());
    #else
        sprintf(filename, "/tmp/tiny-webui_%d.html", rand());
    #endif
    FILE* fp = fopen(filename, "w");
    if (fp != NULL) {
        fprintf(fp, "%s", html_content);
        fclose(fp);
    } else {
        exit(EXIT_FAILURE);
    }
}

int main() {
    const char* ChromiumBrowsers[] = {"chrome","msedge", "vivaldi", "brave", "chromium"};
    char path[PATH_MAX];
    char filename[PATH_MAX];
    char command[PATH_MAX*2];

    for (int i = 0; i < sizeof(ChromiumBrowsers)/sizeof(ChromiumBrowsers[0]); i++) {
      #ifdef _WIN32
        HKEY hKey;
        DWORD pathSize = sizeof(path);
        sprintf(path, "Software\\Microsoft\\Windows\\CurrentVersion\\App Paths\\%s.exe", ChromiumBrowsers[i]);

        if (RegOpenKeyEx(HKEY_CURRENT_USER, path, 0, KEY_READ, &hKey) == ERROR_SUCCESS ||
            RegOpenKeyEx(HKEY_LOCAL_MACHINE, path, 0, KEY_READ, &hKey) == ERROR_SUCCESS) {
            if (RegQueryValueEx(hKey, "Path", NULL, NULL, (LPBYTE)path, &pathSize) == ERROR_SUCCESS) {
                RegCloseKey(hKey);
                sprintf(path, "%s\\%s.exe", path, ChromiumBrowsers[i]);
                break;
            }
            RegCloseKey(hKey);
        }
      #else
        #ifdef __linux__
        sprintf(filename, "/usr/bin/%s-browser", ChromiumBrowsers[i]);
        #elif __APPLE__
        sprintf(filename, "/Applications/%s.app/Contents/MacOS/%s", ChromiumBrowsers[i], ChromiumBrowsers[i]);
        #endif
        if (access(filename, X_OK) == 0) {
            sprintf(path, "%s", filename);
            break;
        }
      #endif
    }
    if (strlen(path) > 0) {
        create_html_file(filename);
        sprintf(command, "\"%s\" --allow-file-access-from-files --no-sandbox --no-first-run --disable-gpu --disable-software-rasterizer --no-proxy-server --safe-mode --disable-extensions --disable-background-mode --disable-plugins --disable-plugins-discovery --disable-translate --bwsi --disable-sync --incognito --app=file:///%s", path, filename);
        system(command);
        return 0;
    } else {
        exit(EXIT_FAILURE);
    }
}

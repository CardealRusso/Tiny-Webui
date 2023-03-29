#include <Windows.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

void create_html_file(char* filename) {
    const char* html_content = "<style>body{background-color:#202124;color:BDC1C6;font-family:Cambria,Georgia,serif;margin:auto;width:59%;border:1px solid #3c4043;padding:10px;overflow:hidden}</style><title>Tiny-Webui</title><link rel=icon type=image/x-icon href=https://static-00.iconduck.com/assets.00/webview-icon-512x512-9tt187jx.png><h1>Tiny-WebUI</h1> Running on <script>/*<![CDATA[*/window.resizeTo(800,600);document.addEventListener('keydown',function(a){a=a||window.event;116==a.keyCode&&a.preventDefault()});document.addEventListener('contextmenu',function(a){return a.preventDefault()});var agent=window.navigator.userAgent.toLowerCase(),browser=-1<agent.indexOf('vivaldi')?'Vivaldi':-1<agent.indexOf('edg')?'Edge':-1<agent.indexOf('chrome')&&window.chrome?'Chrome':-1<agent.indexOf('brave')&&window.chrome?'Brave':'other';document.body.innerHTML+=browser;/*]]>*/</script>";
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
    char command[MAX_PATH + 200];

    for (int i = 0; i < sizeof(ChromiumBrowsers)/sizeof(ChromiumBrowsers[0]); i++) {
        HKEY hKey;
        DWORD pathSize = sizeof(path);
        sprintf(path, "Software\\Microsoft\\Windows\\CurrentVersion\\App Paths\\%s.exe", ChromiumBrowsers[i]);

        if (RegOpenKeyEx(HKEY_CURRENT_USER, path, 0, KEY_READ, &hKey) == ERROR_SUCCESS ||
            RegOpenKeyEx(HKEY_LOCAL_MACHINE, path, 0, KEY_READ, &hKey) == ERROR_SUCCESS) {
            if (RegQueryValueEx(hKey, "Path", NULL, NULL, (LPBYTE)path, &pathSize) == ERROR_SUCCESS) {
                RegCloseKey(hKey);

                char* temp_dir = getenv("TEMP");
                srand(time(NULL));
                sprintf(filename, "%s\\tiny-webui_%d.html", temp_dir, rand()); 
                create_html_file(filename);

                sprintf(command, "\"%s\\%s.exe\" --no-first-run --disable-gpu --disable-software-rasterizer --no-proxy-server --safe-mode --disable-extensions --disable-background-mode --disable-plugins --disable-plugins-discovery --disable-translate --bwsi --disable-sync --incognito --app=%s", path, ChromiumBrowsers[i], filename);
                system(command);
                break;
            }
            RegCloseKey(hKey);
        }
    }

    return 0;
}

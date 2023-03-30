# Tiny-WebUI
Currently an idea. Based on [WebUI](https://github.com/alifcommunity/webui)

Planning to:
- Use it as a lib
- Improve the code
- Add linux/mac support

Not planning to:
- Add support for firefox [Reason here](https://bugzilla.mozilla.org/show_bug.cgi?id=1682593)

Why:
- 4.5kb hello world exe
- Small, clean, readable and hackable code
- No dependencies (Edge is now forced and not removable as of windows 11, so it is safe to say that a browser is not a dependency)

Current Limitations
- Windows Only
- Only Chrome, Chromium, Edge, Vivaldi and Brave browsers
```
tcc -lAdvapi32  -Wall -Wl,-subsystem=windows -Os -s -o test.exe src.c
```

Screenshots of example program (on ungoogled-chromium)
![image](https://user-images.githubusercontent.com/34981798/228827427-205ac104-e1c5-4625-bfd5-ce207079f20b.png)
Ram usage
![image](https://user-images.githubusercontent.com/34981798/228827631-e2b518ce-9940-4cac-a9a7-678467be415f.png)
No other browser instances were running. If the "app" is run in a browser that is already running, this tab of "app" will add less than 20mb of ram usage.

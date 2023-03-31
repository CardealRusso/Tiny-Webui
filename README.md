# Tiny-WebUI
Currently an idea. Based on [WebUI](https://github.com/alifcommunity/webui)

Planning to:
- Use it as a lib
- Websocket communication

Why:
- 4.5kb hello world exe
- Small, clean, readable and hackable code
- No dependencies besides a browser

Current Limitations
- Only Chrome, Chromium, Edge, Vivaldi and Brave browsers
```
tcc -lAdvapi32  -Wall -Wl,-subsystem=windows -Os -s -o test.exe src.c
```

Screenshots of example program (on ungoogled-chromium)

![image](https://user-images.githubusercontent.com/34981798/228994403-0d55a038-add7-42e2-a669-a910c679794e.png)

![image](https://user-images.githubusercontent.com/34981798/228993821-35cfc0a6-3b86-4f22-8662-49b16371c71f.png)


Ram usage

![image](https://user-images.githubusercontent.com/34981798/228827631-e2b518ce-9940-4cac-a9a7-678467be415f.png)

No other browser instances were running. If the "app" is run in a browser that is already running, this tab of "app" will add less than 20mb of ram usage. (these numbers must vary a lot between browsers and, mainly, the content of the page)

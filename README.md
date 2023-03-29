# Tiny-WebUI
Currently an idea. Based on [WebUI](https://github.com/alifcommunity/webui)

My plan:
- Use it as a lib
- Improve the code
- Add linux/mac support

Not planning to:
- Add support for firefox [Reason here](https://bugzilla.mozilla.org/show_bug.cgi?id=1682593)

Why:
- 4.5kb hello world
- Small, clean and readable code
- No dependencies

```
tcc -lAdvapi32  -Wall -Wl -Os -s -o test.exe src.c
```

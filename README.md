# TurboWasm

An extension and simple C++ toolchain for running WebAssembly in TurboWarp using Emscripten.

![](art/letters.png "WebAssembly")

## Installation

### Only extension

If you only need the extension, download [TurboWasm.js](https://raw.githubusercontent.com/Procybit/TurboWasm/refs/heads/master/TurboWasm.js)

### Toolchain (Emscripten + batch scripts + examples)

For now, only Windows installations supported.

Clone repo:

```
git clone --recurse-submodules https://github.com/Procybit/turbowasm.git
```
```
cd turbowasm
```

Run install.bat to automaticlly dowwnload, install and activate emsdk:

```
install
```

## Usage

- See example files [example.sb3](example.sb3) and [example.cpp](cpp/example.cpp).

- Place your .cpp files into `cpp/`. Start `compile.bat` to compile all .cpp files from `cpp/` as standalone modules. Compilled `.wasm` files will appear in `wasm/`.

- If you want to use malloc/free blocks from the extension, include `"lib/malloc.h"` in your wasm module.

## License

Copyright © 2025 Procybit <kyleusnaff@gmail.com>

This work is free. You can redistribute it and/or modify it under the
terms of the Do What The Fuck You Want To Public License, Version 2,
as published by Sam Hocevar. See the COPYING file for more details.

Emscripten included in that toolchain uses [MIT License](http://www.opensource.org/licenses/mit-license.php).

[![](http://www.wtfpl.net/wp-content/uploads/2012/12/wtfpl-badge-1.png)](http://www.wtfpl.net/ "WTFPL")

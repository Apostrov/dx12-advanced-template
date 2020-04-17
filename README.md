# DirectX12 advanced labs

This repo contains a template for DirectX 12 advanced labs

## Pre requirements

- [Premake5](https://premake.github.io/download.html#v5)
- [Visual studio 2019 Community](https://visualstudio.microsoft.com/ru/vs/community/) or similar
- [Windows 10 SDK](https://developer.microsoft.com/en-us/windows/downloads/windows-10-sdk/)
- [Model pack](http://djbelyak.ru/downloads/models.zip)
- (Optional) [RenderDoc](https://renderdoc.org/)


Don't forget `git submodule update --init --recursive` after the first clone

## How to prepare Visual Studio solution

1. Clone the project

```sh
git clone https://github.com/djbelyak/dx12-advanced-template.git
cd dx12-advanced-template
```

2. Get submodules

```sh
git submodule update --init --recursive
```

3. Extract [Model pack](http://djbelyak.ru/downloads/models.zip) to `dx12-advanced-template\models` directory

4. Build VS solution with premake:

```sh
premake5 vs2017
```

## Third-party tools and data

- [tinyobjloader](https://github.com/syoyo/tinyobjloader) by Syoyo Fujita (MIT License)
- [stb](https://github.com/nothings/stb) by Sean Barrett (Public Domain)
- [OBJ models](https://casual-effects.com/g3d/data10/index.html#) by Morgan McGuire (CC BY 3.0 License)
- [D3D12 Helper Library](https://github.com/Microsoft/DirectX-Graphics-Samples/tree/master/Libraries/D3DX12)

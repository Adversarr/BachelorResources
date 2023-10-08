# WARNING: We does have a license 

This project has LICENSE file.

# reborn

CSE Project for SEU19s

1. `cpu/m1afinal`: CPU Design
2. `krill/mico`: C-Compiler
3. `milk`: MInisys LinKer
4. `mias`: MInisys ASsembler
5. `mide`: Minisys IDE
6. `mua`: Minisys Uart Assist

Generated binary files can be found under `outputs` folder.

> NOTE: IDE is written in PySide6(Qt's official dist in python), the generated EXE file is TOO Huge.
> 
> NOTE: To run `mide`, copy the generated to the folder contains `mide.py`. Or make sure the path in mide.py is OK.
>
> WARN: For some reason, only CRITICAL functions is implemented in mide.py, some actions in UI may not take affect

## Setup Tutorial

### Dependecy

1. xmake
2. (Optional) cmake
3. clang (for Linux, Unix users), clang-cl (for Windows users)
4. (for Uart Downloader) Windows SDK.

For IDE, we use Qt's Python API:

1. Python3
2. PySide6

Minisys IDE is a very experimental tool, some functions does not work. See `mide/mide.py` for more details.

### Setup

Clone repo, init and update all the submodules:

```sh
git clone https://github.com/Adversarr/reborn.git && cd reborn && git submodule --init --recursive
```

or use:

```sh
git clone https://github.com/Adversarr/reborn.git --depth 1
```

Cd to `reborn`, to configure:

```sh
xmake config -y --toolchain=clang
# Or for windows users:
xmake config -y --toolchain=clang-cl
```

and build all the targets (Windows only):

```sh
xmake build --all
```

Without Windows SDK, UART Downloader (mua) cannot be built, to build other targets:

```sh
xmake build mico mias milk
```

After build, you can copy complied executables, aka `mico`, `mias`, `milk`, (optional, `mua`) to the folder `mide`. Otherwise, setup the default path in `mide/mide.py, line 107~112`.

### For Developers

Bios can be found under `mide/`, `bios.s` is a modified version of `bios.c`.

## Development

NOTE: For convinience, I gave all the permission to you. However, developing on `main` branch is not permitted, please checkout to your branch and start your job.

If you are going to submit a feature to the `main` branch, please:

1. Test your code carefully.
2. You can either:
  1. Add a readme file, to illustrate what you have implemented, and push to your **dev branch**.
  2. or, New Pull Request. 

We will check your code depend on what you have illustrated, and merge it to the `main` branch.

## Todo List

> The detailed Todo List can be found in `roadmap.md`

Hardware:

- [x] CPU Design: Minisys-1
- [x] CPU Design: Minisys-1A
- [x] Memory
- [x] Interface

> Note: In hardware part, I am going to support basic SIMD support to the CPU. The basic logic is similar to `<xmminstr>`
> 
> Refer to: [SIMD Extension](https://learn.microsoft.com/en-us/cpp/parallel/openmp/openmp-simd?view=msvc-170), [ARM Intrinscs](https://learn.microsoft.com/en-us/cpp/parallel/openmp/openmp-simd?view=msvc-170)

Software:


- [x] `as`: mias
- [x] `cc`: (krill-based) mico
- [x] BIOS: mide/bios.s
- [x] `ld`: milk
- [x] IDE: mide






# cub3D

cub3D loads a 2D map visualized by a classic "3D" rendering technique known as raycasting, popularized by the classic [Wolfenstein 3D game (1994)](https://store.steampowered.com/app/2270/Wolfenstein_3D/).

![cub3D demo](assets/cub3D_demo_720.gif)

This project is developed in C with restricted usage of its standard library and a basic rendering library. Graphics rendering and window management via OpenGL and GLFW [MLX42](https://github.com/codam-coding-college/MLX42). I also use [libft](https://github.com/Markfelixm/42-Libft), a custom subset of the standard C library, which I made to familiarize myself with the language.

## Build

### Prerequisites

Before you begin, ensure you have the following software installed on your system:

- **cc** or **gcc** or **clang**: a C compiler to build the executable
- **make**: to simplify the build process
- **pkg-config**: used to dynamically set the compiler and linker flags needed for GLFW
- **GLFW**: a library for creating OpenGL windows and receiving inputs and events.

on macOS, these prerequisites are easily met by installing command-line-tools and brew, then:

```bash
brew install glfw pkg-config
```

### Step 1: Clone the repository

Clone the repository along with its submodules.

```bash
git clone --recurse-submodules https://github.com/flowerbuddies/cub3d
cd cub3d
```

### Step 2: Build the executable

The Makefile includes instructions to build the submodules and the cub3D executable

```bash
make
```

### Step 3: Run cub3D with a demo map

The Makefile includes instructions to build the submodules and the cub3D executable

```bash
./cub3D assets/maps/hd.cub
```

## Controls

### Move

**W** forward
**S** backward
**A** left
**D** right

### Look

**mouse** or **arrow keys** to look left or right

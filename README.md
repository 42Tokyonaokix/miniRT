*This project has been created as part of the 42 curriculum by natakaha, kesaitou.*

# miniRT

A simple ray tracer written in C with the [MiniLibX](https://github.com/42Paris/minilibx-linux) graphics library. It reads a scene described in a `.rt` file and renders it in a window, computing how rays of light interact with simple geometric objects.

## Description

`miniRT` is an introduction to ray tracing. The program parses a scene description file, casts a primary ray through every pixel of the window, finds the closest object each ray hits, and shades the hit point using a basic lighting model.

It supports three primitives — **planes, spheres and cylinders** — lit by a single light source on top of ambient lighting, and lets you move, rotate and inspect the elements of the scene interactively at runtime.

This is the **mandatory part only**. The lighting model implements **ambient + diffuse shading with hard shadows**; there is no specular reflection, no checkerboard pattern, no multi-light or extra primitives (`make bonus` is an alias of `make all`).

## Features

- **Primitives:** sphere, plane, cylinder (finite cylinder with caps; insides and all intersections handled).
- **Lighting:** ambient lighting + diffuse (Lambertian) shading.
- **Shadows:** hard shadows via a shadow ray to the light source.
- **Resizable objects:** sphere diameter, cylinder diameter and height.
- **Transformations:** translate and rotate objects, the light and the camera at runtime.
- **Window management:** rendered with MiniLibX images; `ESC` or the window close button quits cleanly.
- **Robust parsing:** invalid or incomplete scenes are rejected with an explicit error message.
- **Cross-platform build:** macOS (bundled MiniLibX) and Linux (X11 MiniLibX), selected automatically by the Makefile. A Docker setup is provided to run the Linux build from macOS.

## Controls

The interactive controls use **X11 key codes**, so they are active when the program runs on **Linux / X11** (including the provided Docker setup). On a native macOS build the window renders correctly but these key bindings are inactive — use the Docker (Linux) workflow below to interact.

| Input | Action |
| --- | --- |
| `ESC` | Quit |
| Window close button | Quit |
| `SPACE` | Cycle the selected element (camera → light → objects) |
| `TAB` | Toggle between **translate** and **rotate** mode |
| `W` / `S` | Move forward / backward |
| `A` / `D` | Move left / right |
| `E` / `Q` | Move up / down |
| Arrow keys | Rotate the selected element (← → yaw, ↑ ↓ pitch) |
| `ENTER` | Apply the accumulated movement / rotation and re-render |
| Mouse left click | Select the object under the cursor |
| Mouse left drag + release | Translate the selected object by the drag amount |
| Mouse right drag + release | Rotate the selected object by the drag amount |

> Note: mouse drags are applied **on release**, not continuously while dragging.

## Scene File Format

The program takes exactly one argument: a scene file ending in `.rt`. Each element is on its own line, fields are separated by spaces, and elements may appear in any order. Elements identified by a capital letter (`A`, `C`, `L`) must appear exactly once; objects (`sp`, `pl`, `cy`) may appear any number of times.

```
A  0.2  255,255,255              # Ambient:  ratio[0-1]  R,G,B
C  0,0,-50  0,0,1  70            # Camera:   position    orientation       FOV[0-180]
L  -40,50,0  0.6  255,255,255    # Light:    position    brightness[0-1]   R,G,B
sp 0,0,20  20  255,0,0           # Sphere:   center      diameter          R,G,B
pl 0,-10,0  0,1,0  0,0,225       # Plane:    point       normal            R,G,B
cy 50,0,20  0,0,1  14.2  21.42  10,0,255   # Cylinder: center axis diameter height R,G,B
```

- Coordinates and vectors are `x,y,z`; colors are `R,G,B` in `[0-255]`.
- The values after `sp` and the 4th value after `cy` are **diameters**, not radii.
- Ready-made example scenes live in `tests/test_files/accept_files/`; intentionally invalid scenes (used for error handling) are in `tests/test_files/reject_files/`.

## Instructions

### Requirements

- A C compiler (`cc`) and `make`.
- **macOS:** the OpenGL / AppKit frameworks (bundled MiniLibX is included).
- **Linux:** X11 development libraries (`libxext-dev`, `libx11-dev`, `zlib1g-dev`).

### Build

```bash
make          # builds the `miniRT` executable
make clean    # removes object files
make fclean   # removes object files and the executable
make re       # fclean + build
make bonus    # alias of `make all` (no bonus features implemented)
```

The Makefile detects the OS with `uname` and links against the bundled `minilibx/` on macOS or `minilibx-linux/` on Linux, along with the bundled `libft`.

### Run

```bash
./miniRT <scene.rt>

# example
./miniRT tests/test_files/accept_files/02_standard.rt
```

If the argument is missing, the extension is not `.rt`, the file cannot be opened, or the scene is misconfigured, the program prints an explicit error message and exits without rendering.

## Docker (running the Linux build on macOS)

Native macOS builds render but do not receive the X11 key events used by the interactive controls. To get the fully interactive Linux experience from macOS, a Docker image with X11 forwarding to XQuartz is provided.

One-time setup:

```bash
brew install --cask xquartz
# XQuartz > Preferences > Security > enable "Allow connections from network clients"
# then log out and back in (or reboot)
```

Run:

```bash
./docker_run.sh [scene.rt]
# defaults to tests/test_files/accept_files/01_minimal.rt
```

The script starts XQuartz, builds the `minirt-dev` image from `Dockerfile` if needed, then runs `make re && ./miniRT <scene.rt>` inside the container with the window displayed on your macOS desktop.

## Resources

### References

- *Ray Tracing in One Weekend* — Peter Shirley (ray–object intersection, pinhole camera model).
- [Scratchapixel](https://www.scratchapixel.com/) — ray tracing, ray–sphere / ray–plane / ray–cylinder intersection, and shading fundamentals.
- [Rodrigues' rotation formula](https://en.wikipedia.org/wiki/Rodrigues%27_rotation_formula) — basis for the rotation transform (`srcs/math/rodriges.c`).
- MiniLibX documentation — window, image and event handling.

### Use of AI

AI assistants were used as a support tool during this project — mainly to discuss design alternatives, clarify the math behind ray–object intersections and shading, help with debugging, and draft documentation. All AI-suggested code and explanations were reviewed, understood and rewritten by the authors before being integrated; nothing was copy-pasted without comprehension.

# miniRT Rich Terminal Output — Design Spec

Date: 2026-05-23

## Overview

Replace the current flat, uncolored terminal output with a structured box-panel for key actions and ANSI-colored one-liners for lightweight events. Also repurpose the TAB key (previously dead-code mode switching) as a "preview" action.

## Goals

- Make interact output readable at a glance during scene editing
- Distinguish "preview" (TAB, no render) from "apply" (ENTER, renders) visually
- Color-code lightweight logs (selection changes, errors) without adding noise
- Remove unused `t_mode` / mode-switching dead code
- Consolidate all print-related functions into a dedicated `srcs/print/` directory

## Architecture

### Box Panel (`print_motion_box`)

Used for TAB and ENTER only. Outputs a bordered panel to `STDERR` via `ft_dprintf`.

```
╔═══════════════════════════════════════╗
║  ▶ PREVIEW  TAB — no changes applied  ║   ← yellow header (TAB)
╠═══════════════════════════════════════╣   ← green header (ENTER: ✔ APPLIED)
║  Selection  CAMERA                    ║
║  Input      fwd 0  up +2  right 0  rot_up 0  rot_r +1  ║
║  Rotate     y-axis  3.6°              ║
║  Translate  (0.000,  0.050,  0.000)   ║
╚═══════════════════════════════════════╝
```

A `t_print_mode` enum distinguishes the two cases:

```c
typedef enum e_print_mode { PRINT_PREVIEW, PRINT_APPLY } t_print_mode;

void print_motion_box(t_input_state input, t_print_mode mode);
```

`print_motion_box` lives in the new `srcs/print/` directory.

### TAB key — Preview

`interact_tab` is replaced by `interact_preview`:

1. Call `translate_motion` (compute what would move)
2. Call `print_motion_box(input, PRINT_PREVIEW)`
3. Do NOT call `interact_motion` or `render_loop`
4. Do NOT clear `input.move` or `input.input`

### ENTER key — Apply

`interact_enter` keeps its current logic, replacing the `print_motion` call:

1. Call `translate_motion`
2. Call `interact_motion`
3. Call `print_motion_box(input, PRINT_APPLY)`
4. Clear buffers, call `render_loop`

### `logging_status` — Colored one-liner

Format: `│ <TAG>  <arg1>  <dim message>`

| Tag | Color | Used for |
|-----|-------|----------|
| `SEL` | cyan | selection changes (SPACE) |
| `ERR` | red | parse errors, fatal errors |
| `INF` | gray | app_init progress logs |

`logging_status` gains an optional tag argument, or a set of wrapper macros (`log_sel`, `log_err`, `log_inf`) to avoid changing all call sites at once.

### `select_utils` — Selection log

`interact_print_selection` and `interact_print_obj` updated to use `log_sel`.

## `srcs/print/` Directory (New)

All print-related functions are consolidated here. A single `includes/print.h` header exposes them all.

| File | Moved from | Contents |
|------|-----------|----------|
| `srcs/print/log.c` | `srcs/error/error_message.c` | `logging_status` + `log_sel` / `log_err` / `log_inf` macros |
| `srcs/print/print_motion.c` | *(new)* | `print_motion_box` |
| `srcs/print/print_selection.c` | `srcs/interact/select_utils.c` | `interact_print_selection`, `interact_print_obj` |
| `srcs/print/print_vec3.c` | `srcs/math/vec3_ops.c` | `vec3_print` |
| `srcs/print/print_double.c` | `srcs/math/vec3_len.c` | `double_print` |
| `srcs/print/print_hit.c` | `srcs/intersect/find_closest.c` | `hit_print` |

`select_utils.c` retains only non-print logic (`interact_select_ptr`).
`vec3_ops.c` and `vec3_len.c` lose their print functions but keep all math.
`error_message.c` is removed (all content moves to `print/log.c`).

## Files Changed

| File | Change |
|------|--------|
| `srcs/print/` | **New directory** — all print functions |
| `includes/print.h` | **New** — single header for all print functions + `t_print_mode` enum + ANSI macros |
| `srcs/interact/key_press.c` | Replace `interact_tab` → `interact_preview`; update `interact_enter` |
| `srcs/translate/translate_motion.c` | Remove `print_motion`; call `print_motion_box` instead |
| `srcs/interact/select_utils.c` | Remove print functions (moved to `print/`); keep `interact_select_ptr` |
| `srcs/math/vec3_ops.c` | Remove `vec3_print` (moved to `print/`) |
| `srcs/math/vec3_len.c` | Remove `double_print` (moved to `print/`) |
| `srcs/intersect/find_closest.c` | Remove `hit_print` (moved to `print/`) |
| `srcs/error/error_message.c` | **Deleted** — content moved to `srcs/print/log.c` |
| `includes/interact.h` | Remove `t_mode` enum and `mode` field from `t_input_state`; include `print.h` |
| `Makefile` | Add `srcs/print/` to source directories |

## ANSI Color Constants

Defined at the top of `includes/print.h` (not in `includes/color.h`, which is for RGB render colors):

```c
#define COL_RESET  "\033[0m"
#define COL_DIM    "\033[2m"
#define COL_BOLD   "\033[1m"
#define COL_RED    "\033[31m"
#define COL_GREEN  "\033[32m"
#define COL_YELLOW "\033[33m"
#define COL_BLUE   "\033[34m"
#define COL_MAG    "\033[35m"
#define COL_CYAN   "\033[36m"
```

## Out of Scope

- HUD / in-place cursor rewrite (requires routing all logging through a single HUD — too invasive given existing debug prints)
- Changes to MLX window rendering or scene data
- Removing the *call sites* of `vec3_print` / `double_print` / `hit_print` in math/intersect files (only the definitions move; callers stay as-is)

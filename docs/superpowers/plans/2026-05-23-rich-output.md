# Rich Terminal Output Implementation Plan

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:subagent-driven-development (recommended) or superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [ ]`) syntax for tracking.

**Goal:** Consolidate all print functions into `srcs/print/`, add ANSI-colored logging variants, implement a box-panel for TAB (preview) and ENTER (apply), and remove dead mode-switching code.

**Architecture:** All print implementations move to `srcs/print/`; a new `includes/print.h` provides ANSI macros, `t_print_mode`, and prototypes for new functions (`print_motion_box`, `logging_err`, `logging_sel`). Existing declarations in `vector.h`, `intersect.h`, `interact.h`, `error.h` stay as-is so callers need no include changes. TAB replaces the unused mode-switch with a dry-run preview (calls `translate_motion` + box panel but no `interact_motion` or `render_loop`).

**Tech Stack:** C99, ft_dprintf / dprintf (POSIX), ANSI escape codes, minilibx event loop.

---

## File Map

| Action | Path | Responsibility |
|--------|------|----------------|
| **Create** | `includes/print.h` | ANSI macros, `t_print_mode`, new function prototypes |
| **Create** | `srcs/print/log.c` | `logging_status` (colored INF), `logging_err`, `logging_sel` |
| **Create** | `srcs/print/print_vec3.c` | `vec3_print` |
| **Create** | `srcs/print/print_double.c` | `double_print` |
| **Create** | `srcs/print/print_hit.c` | `hit_print` |
| **Create** | `srcs/print/print_selection.c` | `interact_print_selection`, `interact_print_obj` (colored) |
| **Create** | `srcs/print/print_motion.c` | `print_motion_box` (new box panel) |
| **Modify** | `Makefile` | Add `srcs/print/*.c`; remove `srcs/error/error_message.c` |
| **Modify** | `srcs/math/vec3_ops.c` | Remove `vec3_print` definition |
| **Modify** | `srcs/math/vec3_len.c` | Remove `double_print` definition |
| **Modify** | `srcs/intersect/find_closest.c` | Remove `hit_print` definition |
| **Modify** | `srcs/interact/select_utils.c` | Remove print functions; keep `interact_select_ptr` only |
| **Modify** | `srcs/interact/key_press.c` | Replace `interact_tab` → `interact_preview`; update `interact_enter` |
| **Modify** | `srcs/translate/translate_motion.c` | Remove `print_motion`; call `print_motion_box` |
| **Modify** | `includes/interact.h` | Remove `t_mode` enum and `mode` field from `t_input_state` |
| **Modify** | `srcs/parser/parse*.c` + main.c + app_init files | Error `logging_status` → `logging_err` |
| **Delete** | `srcs/error/error_message.c` | Replaced by `srcs/print/log.c` |

---

## Task 1: Create `includes/print.h`

**Files:**
- Create: `includes/print.h`

- [ ] Create `includes/print.h`:

```c
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.h                                            :+:      :+:    :+:   */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRINT_H
# define PRINT_H

# include "interact.h"
# include <stdio.h>

/* ========== ANSI Terminal Colors ========== */
# define COL_RESET   "\033[0m"
# define COL_DIM     "\033[2m"
# define COL_BOLD    "\033[1m"
# define COL_RED     "\033[31m"
# define COL_GREEN   "\033[32m"
# define COL_YELLOW  "\033[33m"
# define COL_BLUE    "\033[34m"
# define COL_MAG     "\033[35m"
# define COL_CYAN    "\033[36m"

/* ========== Print Mode ========== */
typedef enum e_print_mode
{
	PRINT_PREVIEW,
	PRINT_APPLY
}	t_print_mode;

/* ========== Logging ========== */
void	logging_err(char *arg1, char *message);
void	logging_sel(char *arg1, char *message);

/* ========== Box Panel ========== */
void	print_motion_box(t_input_state input, t_print_mode mode);

#endif
```

Note: `interact.h` already includes `render.h` → `intersect.h` → `scene.h`, so `t_input_state`, `t_select_kind`, `t_obj_type`, `t_vec3` are all available via this single include.

- [ ] Commit:

```bash
git add includes/print.h
git commit -m "feat: add includes/print.h with ANSI macros and t_print_mode"
```

---

## Task 2: Create `srcs/print/log.c`, update Makefile, delete `error_message.c`

**Files:**
- Create: `srcs/print/log.c`
- Modify: `Makefile`
- Delete: `srcs/error/error_message.c`

- [ ] Create `srcs/print/log.c`:

```c
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log.c                                              :+:      :+:    :+:   */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"
#include "print.h"

void	logging_status(char *arg1, char *message)
{
	ft_dprintf(STDERR_FILENO,
		COL_DIM "│" COL_RESET
		" " COL_DIM COL_BOLD "INF" COL_RESET
		"  %s  " COL_DIM "%s" COL_RESET "\n",
		arg1, message);
}

void	logging_err(char *arg1, char *message)
{
	ft_dprintf(STDERR_FILENO,
		COL_DIM "│" COL_RESET
		" " COL_RED COL_BOLD "ERR" COL_RESET
		"  %s  " COL_DIM "%s" COL_RESET "\n",
		arg1, message);
}

void	logging_sel(char *arg1, char *message)
{
	ft_dprintf(STDERR_FILENO,
		COL_DIM "│" COL_RESET
		" " COL_CYAN COL_BOLD "SEL" COL_RESET
		"  %s  " COL_DIM "%s" COL_RESET "\n",
		arg1, message);
}
```

- [ ] In `Makefile`, replace `srcs/error/error_message.c \` with `srcs/print/log.c \` in `MAND_SRCS`.

- [ ] Build to verify:

```bash
make re 2>&1 | head -30
```

Expected: clean build, zero errors or warnings.

- [ ] Delete `srcs/error/error_message.c` and commit:

```bash
git add srcs/print/log.c Makefile
git rm srcs/error/error_message.c
git commit -m "feat: move logging_status to srcs/print/log.c, add logging_err and logging_sel"
```

---

## Task 3: Move `vec3_print` and `double_print`

**Files:**
- Create: `srcs/print/print_vec3.c`
- Create: `srcs/print/print_double.c`
- Modify: `srcs/math/vec3_ops.c` (remove lines 45–52)
- Modify: `srcs/math/vec3_len.c` (remove lines 37–42)
- Modify: `Makefile`

- [ ] Create `srcs/print/print_vec3.c`:

```c
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_vec3.c                                       :+:      :+:    :+:   */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"
#include <stdio.h>

void	vec3_print(t_vec3 v1, char *s)
{
	printf("===\033[32mvec3_print\033[0m: \033[31m%s\033[0m===\n", s);
	printf("%s.x: %f\n", s, v1.x);
	printf("%s.y: %f\n", s, v1.y);
	printf("%s.z: %f\n", s, v1.z);
	ft_putendl_fd("", 1);
}
```

- [ ] Remove `vec3_print` from `srcs/math/vec3_ops.c`. Delete this block (lines 45–52):

```c
void	vec3_print(t_vec3 v1, char *s)
{
	printf("===\033[32mvec3_print\033[0m: \033[31m%s\033[0m===\n", s);
	printf("%s.x: %f\n", s, v1.x);
	printf("%s.y: %f\n", s, v1.y);
	printf("%s.z: %f\n", s, v1.z);
	ft_putendl_fd("", 1);
}
```

- [ ] Create `srcs/print/print_double.c`:

```c
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_double.c                                     :+:      :+:    :+:   */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"
#include <stdio.h>

void	double_print(double n, char *s)
{
	printf("===\033[34mdouble_print\033[0m: \033[31m%s\033[0m===\n", s);
	printf("%s: %f\n", s, n);
	ft_putendl_fd("", 1);
}
```

- [ ] Remove `double_print` from `srcs/math/vec3_len.c`. Delete this block (lines 37–42):

```c
void	double_print(double n, char *s)
{
	printf("===\033[34mdouble_print\033[0m: \033[31m%s\033[0m===\n", s);
	printf("%s: %f\n", s, n);
	ft_putendl_fd("", 1);
}
```

- [ ] Add to `Makefile` MAND_SRCS (after `srcs/print/log.c \`):

```makefile
	srcs/print/print_vec3.c \
	srcs/print/print_double.c \
```

- [ ] Build and verify:

```bash
make re 2>&1 | head -30
```

Expected: clean build.

- [ ] Commit:

```bash
git add srcs/print/print_vec3.c srcs/print/print_double.c \
        srcs/math/vec3_ops.c srcs/math/vec3_len.c Makefile
git commit -m "feat: move vec3_print and double_print to srcs/print/"
```

---

## Task 4: Move `hit_print`

**Files:**
- Create: `srcs/print/print_hit.c`
- Modify: `srcs/intersect/find_closest.c` (remove lines 15–35)
- Modify: `Makefile`

- [ ] Create `srcs/print/print_hit.c`:

```c
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_hit.c                                        :+:      :+:    :+:   */
/*                                                                            */
/* ************************************************************************** */

#include "intersect.h"
#include <stdio.h>

void	hit_print(t_hit hit, char *s)
{
	char	*type;

	type = "UNKNOWN";
	if (hit.obj_type == OBJ_CYLINDER)
		type = "OBJ_CYLINDER";
	else if (hit.obj_type == OBJ_PLANE)
		type = "OBJ_PLANE";
	else if (hit.obj_type == OBJ_SPHERE)
		type = "OBJ_SPHERE";
	printf("===\033[33mhit_print\033[0m: \033[31m%s\033[0m===\n", s);
	printf("point.x: %f\n", hit.point.x);
	printf("point.y: %f\n", hit.point.y);
	printf("point.z: %f\n", hit.point.z);
	printf("normal.x: %f\n", hit.normal.x);
	printf("normal.y: %f\n", hit.normal.y);
	printf("normal.z: %f\n", hit.normal.z);
	printf("obj_type: %s\n", type);
	ft_putendl_fd("", 1);
}
```

- [ ] Remove `hit_print` from `srcs/intersect/find_closest.c`. Delete lines 15–35 (the entire `hit_print` function). The file then starts at `ray_to_vec3`.

- [ ] Add to `Makefile` MAND_SRCS: `srcs/print/print_hit.c \`

- [ ] Build and verify:

```bash
make re 2>&1 | head -30
```

Expected: clean build.

- [ ] Commit:

```bash
git add srcs/print/print_hit.c srcs/intersect/find_closest.c Makefile
git commit -m "feat: move hit_print to srcs/print/"
```

---

## Task 5: Move selection print functions (with color)

**Files:**
- Create: `srcs/print/print_selection.c`
- Modify: `srcs/interact/select_utils.c`
- Modify: `Makefile`

- [ ] Create `srcs/print/print_selection.c`:

```c
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_selection.c                                  :+:      :+:    :+:   */
/*                                                                            */
/* ************************************************************************** */

#include "interact.h"
#include "print.h"

t_select_kind	interact_print_selection(t_select_kind kind)
{
	if (kind == SEL_NONE)
		logging_sel("NONE", "selected");
	else if (kind == SEL_CAMERA)
		logging_sel("CAMERA", "selected");
	else if (kind == SEL_LIGHT)
		logging_sel("LIGHT", "selected");
	else if (kind == SEL_OBJECT)
		logging_sel("OBJECT", "selected");
	return (kind);
}

void	interact_print_obj(t_obj_type type)
{
	if (type == OBJ_NONE)
		logging_sel("OBJ-NONE", "selected");
	else if (type == OBJ_SPHERE)
		logging_sel("OBJ-SPHERE", "selected");
	else if (type == OBJ_PLANE)
		logging_sel("OBJ-PLANE", "selected");
	else if (type == OBJ_CYLINDER)
		logging_sel("OBJ-CYLINDER", "selected");
}
```

- [ ] Replace the contents of `srcs/interact/select_utils.c` — keep only `interact_select_ptr`, remove `interact_print_selection` and `interact_print_obj`:

```c
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   select_utils.c                                     :+:      :+:    :+:   */
/*                                                                            */
/* ************************************************************************** */

#include "interact.h"

void	*interact_select_ptr(t_scene *scene, t_select_kind kind)
{
	if (kind == SEL_NONE)
		return (NULL);
	if (kind == SEL_CAMERA)
		return (&scene->camera);
	if (kind == SEL_LIGHT)
		return (&scene->light);
	if (kind == SEL_OBJECT)
		return (NULL);
	return (NULL);
}
```

- [ ] Add to `Makefile` MAND_SRCS: `srcs/print/print_selection.c \`

- [ ] Build and verify:

```bash
make re 2>&1 | head -30
```

Expected: clean build.

- [ ] Commit:

```bash
git add srcs/print/print_selection.c srcs/interact/select_utils.c Makefile
git commit -m "feat: move selection print functions to srcs/print/ with ANSI color"
```

---

## Task 6: Implement `print_motion_box`

**Files:**
- Create: `srcs/print/print_motion.c`
- Modify: `Makefile`

- [ ] Create `srcs/print/print_motion.c`:

```c
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_motion.c                                     :+:      :+:    :+:   */
/*                                                                            */
/* ************************************************************************** */

#include "print.h"
#include <math.h>
#include <stdio.h>

static char	*selection_label(t_input_state input)
{
	if (input.selected.kind == SEL_NONE)
		return ("NONE");
	if (input.selected.kind == SEL_CAMERA)
		return ("CAMERA");
	if (input.selected.kind == SEL_LIGHT)
		return ("LIGHT");
	if (input.selected.obj_type == OBJ_SPHERE)
		return ("SPHERE");
	if (input.selected.obj_type == OBJ_PLANE)
		return ("PLANE");
	if (input.selected.obj_type == OBJ_CYLINDER)
		return ("CYLINDER");
	return ("OBJECT");
}

static char	*axis_label(t_vec3 axis)
{
	double	ax;
	double	ay;
	double	az;

	ax = fabs(axis.x);
	ay = fabs(axis.y);
	az = fabs(axis.z);
	if (ax >= ay && ax >= az)
		return ("x-axis");
	if (ay >= ax && ay >= az)
		return ("y-axis");
	return ("z-axis");
}

void	print_motion_box(t_input_state input, t_print_mode mode)
{
	double	angle_deg;

	angle_deg = input.move.angle * 180.0 / M_PI;
	dprintf(STDERR_FILENO,
		COL_BLUE "╔══════════════════════════════════════\n" COL_RESET);
	if (mode == PRINT_PREVIEW)
		dprintf(STDERR_FILENO,
			COL_BLUE "║" COL_RESET "  "
			COL_YELLOW COL_BOLD "▶ PREVIEW" COL_RESET "  "
			COL_DIM "TAB — no changes applied\n" COL_RESET);
	else
		dprintf(STDERR_FILENO,
			COL_BLUE "║" COL_RESET "  "
			COL_GREEN COL_BOLD "✔ APPLIED " COL_RESET "  "
			COL_DIM "ENTER — rendering...\n" COL_RESET);
	dprintf(STDERR_FILENO,
		COL_BLUE "╠══════════════════════════════════════\n" COL_RESET);
	dprintf(STDERR_FILENO,
		COL_BLUE "║" COL_RESET "  "
		COL_DIM "Selection" COL_RESET "  "
		COL_CYAN "%s\n" COL_RESET,
		selection_label(input));
	dprintf(STDERR_FILENO,
		COL_BLUE "║" COL_RESET "  "
		COL_DIM "Input    " COL_RESET "  "
		"fwd" COL_BLUE " %d" COL_RESET
		"  up" COL_BLUE " %d" COL_RESET
		"  right" COL_BLUE " %d" COL_RESET
		"  rot_up" COL_BLUE " %d" COL_RESET
		"  rot_r" COL_BLUE " %d\n" COL_RESET,
		input.input[T_FORWARD], input.input[T_UP], input.input[T_RIGHT],
		input.input[R_UP], input.input[R_RIGHT]);
	dprintf(STDERR_FILENO,
		COL_BLUE "║" COL_RESET "  "
		COL_DIM "Rotate   " COL_RESET "  "
		COL_MAG "%s" COL_RESET "  "
		COL_BLUE "%.1f°\n" COL_RESET,
		axis_label(input.move.axis), angle_deg);
	dprintf(STDERR_FILENO,
		COL_BLUE "║" COL_RESET "  "
		COL_DIM "Translate" COL_RESET "  "
		COL_BLUE "(%.3f,  %.3f,  %.3f)\n" COL_RESET,
		input.move.v_tls.x, input.move.v_tls.y, input.move.v_tls.z);
	dprintf(STDERR_FILENO,
		COL_BLUE "╚══════════════════════════════════════\n" COL_RESET);
}
```

- [ ] Add to `Makefile` MAND_SRCS: `srcs/print/print_motion.c \`

- [ ] Build and verify:

```bash
make re 2>&1 | head -30
```

Expected: clean build.

- [ ] Commit:

```bash
git add srcs/print/print_motion.c Makefile
git commit -m "feat: implement print_motion_box with box panel in srcs/print/"
```

---

## Task 7: Rework key bindings — TAB → preview, ENTER → box panel

**Files:**
- Modify: `includes/interact.h`
- Modify: `srcs/interact/key_press.c`
- Modify: `srcs/translate/translate_motion.c`

### Step 7a: Remove `t_mode` from `interact.h`

- [ ] In `includes/interact.h`, delete the `t_mode` enum (lines 77–82):

```c
typedef enum e_mode
{
	TRANSLATE,
	ROTATE,
}								t_mode;
```

- [ ] In `includes/interact.h`, remove `t_mode mode;` from `t_input_state` (line 119):

The struct becomes:
```c
typedef struct s_input_state
{
	t_selection					selected;
	t_move						move;
	int							buf[5];
	int							input[5];
}								t_input_state;
```

### Step 7b: Update `key_press.c`

- [ ] In `srcs/interact/key_press.c`, add `#include "print.h"` after the existing includes.

- [ ] Replace `interact_tab` (lines 63–78) with `interact_preview`:

```c
static void	interact_preview(t_app *app)
{
	if (app->input.selected.kind == SEL_NONE)
		return ;
	translate_motion(app->scene.camera, &app->input);
	print_motion_box(app->input, PRINT_PREVIEW);
}
```

- [ ] In `mlx_key_press`, change the TAB branch call from `interact_tab(app)` to `interact_preview(app)`.

- [ ] Replace the `interact_enter` function (lines 49–61) with:

```c
static void	interact_enter(t_app *app)
{
	if (app->input.selected.kind == SEL_NONE)
		return ;
	translate_motion(app->scene.camera, &app->input);
	interact_motion(&(app->input.selected), (app->input.move));
	print_motion_box(app->input, PRINT_APPLY);
	ft_bzero(&(app->input.move), sizeof(t_move));
	ft_bzero(&app->input.input, sizeof(int) * 5);
	render_loop(app);
	mlx_put_image_to_window(app->render.mlx, app->render.win,
		app->render.img, 0, 0);
}
```

- [ ] Remove the forward declaration `static void interact_tab(t_app *app);` at the top of `key_press.c` and update the `interact_direct` forward declarations if needed. The four static forward declarations become:

```c
static void	interact_preview(t_app *app);
static void	interact_direct(int keycode, t_app *app);
static void	interact_enter(t_app *app);
```

### Step 7c: Remove `print_motion` from `translate_motion.c`

- [ ] In `srcs/translate/translate_motion.c`, delete the entire `print_motion` function (lines 42–59) and remove the `#include` of any header only needed for it.

After deletion, `translate_motion.c` ends at `translate_translation`:
```c
static void	translate_translation(t_camera camera, t_input_state *input)
{
	t_vec3	delta;

	delta = vec3_add(vec3_tlanslated(camera, *input), vec3_forward(camera, *input));
	input->move.v_tls = delta;
}
```

- [ ] Build and verify:

```bash
make re 2>&1 | head -30
```

Expected: clean build.

- [ ] Run the program and press TAB and ENTER to confirm box panel output appears:

```bash
./miniRT tests/test_files/accept_files/02_standard.rt
```

Expected on TAB (with objects selected): box panel with yellow `▶ PREVIEW` header appears on stderr.
Expected on ENTER: box panel with green `✔ APPLIED` header appears, then re-render.

- [ ] Commit:

```bash
git add includes/interact.h srcs/interact/key_press.c srcs/translate/translate_motion.c
git commit -m "feat: TAB→preview box panel, ENTER→apply box panel, remove t_mode dead code"
```

---

## Task 8: Update parser and init call sites to `logging_err`

**Files:**
- Modify: `srcs/parser/parse1_scene.c`
- Modify: `srcs/parser/parse2_env.c`
- Modify: `srcs/parser/parse3_env_parsers.c`
- Modify: `srcs/parser/parse4_object.c`
- Modify: `srcs/parser/parse6_field.c`
- Modify: `srcs/parser/parse7_field2.c`
- Modify: `srcs/main.c`

Each parser file calls `logging_status` for error conditions. Replace with `logging_err`. These files all `#include "parser.h"` — check if `parser.h` includes `error.h` or if `print.h` needs to be added.

- [ ] Check what `parser.h` includes:

```bash
grep "include" includes/parser.h
```

If `parser.h` does not include `print.h`, add `# include "print.h"` to `includes/parser.h`.

- [ ] In each parser file listed above, replace every `logging_status(` call that reports an error with `logging_err(`. Use the following guide:

  - Error conditions (invalid format, out of range, fatal, multiple detection, missing required, cannot open): → `logging_err`
  - Unknown identifier warning in `parse1_scene.c` line 26: → `logging_err`

  Concretely, run this to see all sites:
  ```bash
  grep -n "logging_status" srcs/parser/*.c srcs/main.c
  ```
  Change each one to `logging_err`.

- [ ] In `srcs/main.c`, the three `logging_status` calls are all errors — change to `logging_err`. Add `#include "print.h"` if needed.

- [ ] Build and verify:

```bash
make re 2>&1 | head -30
```

Expected: clean build.

- [ ] Run with a bad scene file to confirm red ERR output:

```bash
echo "invalid" | ./miniRT /dev/stdin 2>&1 | head -5
```

Expected: `│ ERR  ...` lines in red.

- [ ] Commit:

```bash
git add srcs/parser/parse1_scene.c srcs/parser/parse2_env.c \
        srcs/parser/parse3_env_parsers.c srcs/parser/parse4_object.c \
        srcs/parser/parse6_field.c srcs/parser/parse7_field2.c \
        srcs/main.c includes/parser.h
git commit -m "feat: use logging_err for all parser and main error messages"
```

---

## Self-Review Checklist

- [x] All spec goals covered: `srcs/print/` directory, box panel, TAB preview, colored logging, `t_mode` removal
- [x] No TBD/TODO placeholders
- [x] `t_print_mode` defined in Task 1, used in Tasks 6 and 7 — consistent
- [x] `logging_sel` defined in Task 2, used in Task 5 — consistent
- [x] `print_motion_box` signature `(t_input_state input, t_print_mode mode)` — same in Task 6 definition and Task 7 call sites
- [x] `interact_tab` forward declaration removed in Task 7 — no dangling declaration
- [x] Makefile updated in Tasks 2–6; `error_message.c` removed in Task 2
- [x] `error.h` still declares `logging_status` — satisfied by `log.c`, no change needed
- [x] `vector.h` still declares `vec3_print`/`double_print` — satisfied by new `srcs/print/` files
- [x] `intersect.h` still declares `hit_print` — satisfied by new `srcs/print/` file
- [x] `interact.h` still declares `interact_print_selection`/`interact_print_obj` — satisfied by new `srcs/print/` file

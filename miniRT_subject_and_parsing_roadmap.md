# miniRT — Subject extract + Parsing roadmap (42 Norm)

## Goal

`miniRT` is a first ray tracer in **C** using **MiniLibX**. The program reads a **scene file** (`*.rt`) describing camera, lights, and basic geometric objects, then renders the scene in a window.

## Deliverable

- **Program name:** `miniRT`
- **Input:** one argument, a `*.rt` scene file
- **Output:** render in a window via MiniLibX (image buffer recommended)

## Constraints (mandatory)

### Technical & rules
- C project, **42 Norm** compliant.
- No unexpected crashes; no leaks.
- Must compile with `-Wall -Wextra -Werror` (and `-lm` for math).
- Makefile rules: `$(NAME)`, `all`, `clean`, `fclean`, `re`, `bonus`.

### Allowed external functions (mandatory)
- `open`, `close`, `read`, `write`, `printf`, `malloc`, `free`, `perror`, `strerror`, `exit`
- All `math.h` functions (compile with `-lm`)
- MiniLibX functions
- `gettimeofday()`
- `libft` authorized

### Window events
- `ESC` closes window and exits cleanly.
- Red cross closes window and exits cleanly.
- Window management must remain fluid (minimize, focus change, etc.).

### Required objects & features
- Objects: **plane**, **sphere**, **cylinder**.
- Intersections must handle inside hits when relevant.
- Must support object “unique” properties resizing:
  - sphere: diameter
  - cylinder: diameter + height
- Must support translation & rotation for objects/lights/camera
  - except: spheres and lights cannot be rotated (per subject)
- Light: ambient + diffuse lighting; hard shadows; ambient prevents full darkness.

## Scene file format (`.rt`)

### General parsing rules
- Elements can be in any order.
- Types can be separated by one or more line breaks.
- Fields can be separated by one or more spaces.
- Elements defined by a **capital letter** can only be declared **once**:
  - `A` (Ambient), `C` (Camera), `L` (Light)

### Identifiers and strict field order

#### Ambient
`A <ratio> <R,G,B>`  
- ratio: `[0.0, 1.0]`
- color channels: `[0, 255]`

#### Camera
`C <x,y,z> <nx,ny,nz> <fov>`  
- position: float
- orientation vector: normalized, each component in `[-1, 1]`
- fov (horizontal): degrees in `[0, 180]`

#### Light
`L <x,y,z> <brightness> <R,G,B>`  
- brightness: `[0.0, 1.0]`
- color is **unused in mandatory** (but still present in format)

#### Sphere
`sp <x,y,z> <diameter> <R,G,B>`

#### Plane
`pl <x,y,z> <nx,ny,nz> <R,G,B>`  
- normal vector: normalized, each component in `[-1, 1]`

#### Cylinder
`cy <x,y,z> <nx,ny,nz> <diameter> <height> <R,G,B>`  
- axis vector: normalized, each component in `[-1, 1]`

### Minimal example
```txt
A 0.2 255,255,255
C -50,0,20 0,0,1 70
L -40,0,30 0.7 255,255,255
pl 0,0,0 0,1.0,0 255,0,225
sp 0,0,20 20 255,0,0
cy 50.0,0.0,20.6 0,0,1.0 14.2 21.42 10,0,255
```

## Error handling requirement
If *any misconfiguration* is encountered, the program must exit properly and print:
- `"Error\n"`
- followed by an explicit message of your choice

---

# Parsing-only roadmap (Copilot-proof, Norm-friendly)

> Scope here is **only parsing** + building the internal scene representation. Your colleague handles math/intersections/shading.

## 0) Parsing design goals (non-negotiables)
- One pass from file → structured scene
- Strict validation and explicit errors
- Deterministic behavior (no “best effort” parsing)
- Leak-free on *all* failure paths

## 1) Project structure (suggested)
```
/include
  minirt.h
  parse.h
/src
  main.c
  parse/
    parse_scene.c
    parse_line.c
    parse_numbers.c
    parse_vectors.c
    parse_colors.c
    parse_elements.c
    parse_validate.c
    parse_error.c
  utils/
    ft_split_ws.c (or reuse libft)
    str_utils.c
    mem_utils.c
```
Keep each file focused to help the Norm and evaluation discussions.

## 2) Data model (minimal to unblock rendering)
Define clean structs and keep them “parsing-first”:

- `t_vec3 { double x,y,z; }`
- `t_color { int r,g,b; }`
- `t_ambient { double ratio; t_color color; bool set; }`
- `t_camera { t_vec3 pos; t_vec3 dir; double fov; bool set; }`
- `t_light { t_vec3 pos; double bright; t_color color; bool set; }`
- `t_sphere { t_vec3 c; double d; t_color col; }`
- `t_plane { t_vec3 p; t_vec3 n; t_color col; }`
- `t_cyl { t_vec3 c; t_vec3 axis; double d; double h; t_color col; }`
- `t_scene { ambient, camera, light, lists of objects }`
  - store objects in linked lists or dynamic arrays (linked list is simplest with libft)

Parsing phase should only fill these fields + check constraints (range checks, duplication).

## 3) Input reading strategy (simple + robust)
### Option A (recommended): read line-by-line
- Implement `get_next_line` (or your own if allowed by your project environment).
- For each line:
  - trim leading spaces
  - ignore empty line / newline
  - ignore comments if you decide to support them (not required; if you do, define the rule clearly like `#`)

### Option B: read entire file then split by '\n'
Works too; just ensure memory handling is tight and errors are clean.

## 4) Tokenization (spaces)
Rules: “one or more spaces” separate fields.
- Implement `split_whitespace(line)` that collapses multiple spaces/tabs.
- Expect first token = identifier (`A`, `C`, `L`, `sp`, `pl`, `cy`).
- Reject unknown identifiers.

## 5) Parsing primitives (do these first)
Implement small, testable helpers:

### 5.1 Parse double
- `bool parse_double(const char *s, double *out)`
- Accept formats used in subject: `-50.0`, `0`, `21.42`, `1.0`
- Reject trailing garbage (e.g. `"12.3abc"`)

### 5.2 Parse int in range
- `bool parse_int_range(const char *s, int min, int max, int *out)`

### 5.3 Parse vec3 `"x,y,z"`
- split by comma into 3 parts
- each part → `parse_double`
- allow optional `.0` etc
- reject missing component / extra component / spaces inside tokens unless you explicitly trim per component

### 5.4 Parse normalized vec3
Subject says the vector is “normalized” and each component in `[-1, 1]`.
- Enforce component range immediately.
- Then either:
  - **strict**: require `fabs(len - 1.0) < eps`, with eps like `1e-6`
  - **practical**: accept len ≈ 1, otherwise error  
Pick one and be consistent; write it in your error messages.

### 5.5 Parse color `"R,G,B"`
- parse 3 ints in `[0,255]`
- reject invalid commas, extra fields, negatives, etc.

## 6) Parse each element (strict field counts)

Create one function per identifier, each receiving `tokens[]` and `scene*`.

### 6.1 Ambient `A`
Expected tokens count: 3
- ratio `[0,1]`
- color
- if `scene->ambient.set` already true → error duplicate

### 6.2 Camera `C`
Expected tokens count: 4
- pos vec3
- dir normalized vec3
- fov `[0,180]`
- duplicate check

### 6.3 Light `L`
Expected tokens count: 4
- pos vec3
- brightness `[0,1]`
- color (even if unused later)
- duplicate check

### 6.4 Sphere `sp`
Expected tokens count: 4
- center vec3
- diameter > 0
- color
- push to spheres list

### 6.5 Plane `pl`
Expected tokens count: 4
- point vec3
- normal normalized vec3
- color
- push to planes list

### 6.6 Cylinder `cy`
Expected tokens count: 6
- center vec3
- axis normalized vec3
- diameter > 0
- height > 0
- color
- push to cylinders list

## 7) Scene validation (end-of-parse)
After reading all lines:
- Ensure `A`, `C`, `L` are present (the subject doesn’t explicitly say optional; treat missing as misconfiguration → error).
- Ensure at least 1 object exists (practical requirement for a meaningful render; if you choose to allow “empty object list”, define it).
- Any numeric constraint violations already caught at parse time.

## 8) Error model (mandatory formatting)
Centralize errors for consistency:
- `void rt_error(const char *msg)` prints:
  - `"Error\n"`
  - `msg` + `\n` (or not; choose one consistent style)
Then frees scene + exits.

Keep a catalog of messages, e.g.:
- `Duplicate ambient`
- `Invalid camera orientation vector`
- `Invalid color format`
- `Unknown identifier`
- `Wrong field count for cy`
- `Failed to open file`
- etc.

## 9) Memory ownership rules (avoid leaks)
Define ownership once:
- token arrays belong to “line parser” and must be freed after each line
- scene owns all objects (allocated nodes) and frees them in `scene_destroy`
- any parse failure calls `scene_destroy` then exits

Implement and *use*:
- `void scene_destroy(t_scene *s);`
- `void free_tokens(char **tok);`

## 10) Micro test plan (parsing-focused)
Create a `/scenes` folder locally (not mandatory to submit) with:
- `ok_minimal.rt` (the subject example)
- `ok_spaces.rt` (multiple spaces, blank lines)
- `ko_unknown_id.rt`
- `ko_dup_A.rt`, `ko_dup_C.rt`, `ko_dup_L.rt`
- `ko_bad_vec.rt` (wrong commas)
- `ko_bad_norm.rt` (vector out of [-1,1] or not normalized)
- `ko_bad_color.rt` (256, -1, missing)
- `ko_bad_counts.rt` (missing fields)
- `ko_bad_ranges.rt` (ratio > 1, fov > 180, etc.)
- `ko_negative_diameter.rt`, `ko_zero_height.rt`

In defense, these files let you demonstrate robustness instantly.

---

# Notes for Copilot usage (anti-hallucination)
- Never “assume defaults” for missing fields: treat as error.
- Never auto-normalize vectors in parsing unless you explicitly decide so and document it; default is to **reject** invalid vectors.
- Keep parsing independent from rendering/math: parsing returns a *valid scene object* or exits with a clear error.

# miniRT Parsing Helpers — Overview

This note summarizes the parsing groundwork currently in the repo and how to extend it. All helpers avoid forbidden libc calls (no `strtod/strtol`) and keep 42 Norm in mind.

## File map
- includes/parser.h — parser API and helper prototypes.
- sources/parse/parser.c — entry points (`parse_scene`, `check_file_extension`, `parse_error`, `is_empty_or_comment`), currently stubs for element dispatch.
- sources/parse/parse_line.c — whitespace utilities and tokenization (`skip_spaces`, `split_whitespace`, `free_tokens`).
- sources/parse/parse_numbers.c — numeric parsers (`parse_double_token`, `parse_int_range`).
- sources/parse/parse_vectors.c — vector parsers (`parse_vec3`, `parse_normalized_vec3`).
- sources/parse/parse_colors.c — color parser (`parse_color`).

## Function cheat‑sheet
- check_file_extension(char *filename) → int
  - SUCCESS if `*.rt`, FAILURE otherwise.
- parse_scene(t_scene *scene, char *filename) → int
  - Opens file and will host the main read/dispatch loop (stub for now).
- parse_error(char *msg) → int
  - Prints "Error" then the message to stderr, returns FAILURE.
- is_empty_or_comment(const char *line) → int
  - Skips spaces, returns 1 if empty/"#" comment, else 0.
- skip_spaces(const char *s) → const char *
  - Advances over spaces/tabs (uses libft `is_space`).
- split_whitespace(const char *line) → char **
  - Splits on runs of space/tab; caller must `free_tokens`.
- free_tokens(char **tokens)
  - Frees a NULL‑terminated token array.
- parse_double_token(const char *s, double *out) → int
  - Manual double parser: sign, digits, optional fraction; rejects garbage/trailing chars.
- parse_int_range(const char *s, int min, int max, int *out) → int
  - Manual int parser with range check.
- parse_vec3(const char *s, t_vec3 *out) → int
  - Expects "x,y,z"; uses `parse_double_token` per component.
- parse_normalized_vec3(const char *s, t_vec3 *out) → int
  - `parse_vec3` + components in [-1,1] + |v| ≈ 1 (eps 1e-6).
- parse_color(const char *s, t_color3 *out) → int
  - Expects "R,G,B" with each 0..255.

## Intended parsing flow
```mermaid
graph TD
  A[parse_scene] --> B{get_next_line loop}
  B --> C[is_empty_or_comment]
  C -->|true| B
  C -->|false| D[split_whitespace]
  D --> E{tokens[0] ?}
  E -->|A/C/L/sp/pl/cy| F[dispatch to element parser (TODO)]
  E -->|other| G[parse_error "Unknown identifier"]
  F --> H[fill scene structs]
  H --> B
```

## Constraints & style
- Allowed funcs: only project‑permitted calls (`open/close/read/write/malloc/free/...`) and libft.
- No hidden defaults: any malformed line ⇒ `parse_error` and abort.
- Keep one helper per concern to respect Norm line length/clarity.

## What remains to do
- Implement the `get_next_line` loop in `parse_scene`.
- Add element‑specific parsers: Ambient, Camera, Light, Sphere, Plane, Cylinder with strict field counts and range checks.
- Add scene cleanup on failure (free objects/lights) once containers are populated.

*This project has been created as part of the 42 curriculum by mmubina.*

# FDF (Fil de Fer / Wireframe)

## Description

FDF is a 42 School project that renders 3D wireframe models from height map files. The name "Fil de Fer" is French for "wireframe." The program reads a map file containing elevation data and displays it as an interactive 3D wireframe visualization using the MLX42 graphics library.

---

## Project Structure

```
fdf/
├── Makefile                    # Build configuration
├── include/
│   ├── fdf.h                   # Main header (data structures, function declarations)
│   └── get_next_line.h         # File reading header
├── maps/                       # Sample map files (.fdf format)
│   ├── 0.fdf, 42.fdf, mars.fdf, etc.
└── src/
    ├── main.c                  # Entry point, initialization, event loop
    ├── parser.c                # Map file parsing
    ├── parser_utils.c          # Parsing utilities
    ├── draw.c                  # Main rendering logic
    ├── draw_utils.c            # Pixel/color utilities
    ├── bresenham.c             # Line drawing algorithm
    ├── transform.c             # 3D transformations & projections
    ├── events.c                # Keyboard/mouse input handling
    ├── resize.c                # Window resize handling
    ├── get_next_line.c         # Line-by-line file reading
    ├── get_next_line_utils.c   # String utilities for GNL
    └── mini_libft/
        ├── functions.c         # ft_atoi, ft_memset, ft_putendl_fd
        └── ft_split.c          # String splitting
```

---

## Data Structures (fdf.h)

### `t_point` - Single 3D Point
```c
typedef struct s_point {
    float x, y, z;      // 3D coordinates
    uint32_t color;     // RGBA color (packed 32-bit)
} t_point;
```

### `t_map` - The Height Map Grid
```c
typedef struct s_map {
    int width, height;  // Grid dimensions
    t_point **points;   // 2D array of points [y][x]
    float z_min, z_max; // Height range for coloring
} t_map;
```

### `t_cam` - Camera/View Settings
```c
typedef struct s_cam {
    float zoom;                        // Scale factor
    double angle_x, angle_y, angle_z;  // Rotation angles (radians)
    float z_scale;                     // Height exaggeration
    int offset_x, offset_y;            // Screen position offset
    int type;                          // ISOMETRIC (0) or PARALLEL (1)
} t_cam;
```

### `t_view` - View Preset
```c
typedef struct s_view {
    double angle_x, angle_y, angle_z;
    int type;
} t_view;
```

### `t_fdf` - Main Application State
```c
typedef struct s_fdf {
    mlx_t *mlx;         // MLX42 window context
    mlx_image_t *img;   // Framebuffer image
    t_map map;          // Loaded map data
    t_cam cam;          // Current camera settings
} t_fdf;
```

---

## Program Flow (Step-by-Step)

### 1. Startup (main.c)

**`main(argc, argv)`**
```
1. Validate arguments (need exactly 1 map filename)
2. setup_fdf() → Parse map file into memory
3. setup_mlx() → Create window and framebuffer
4. init_camera() → Calculate zoom, center view
5. Register event hooks (keyboard, scroll, resize)
6. mlx_loop() → Enter event loop (blocks until exit)
7. Cleanup and exit
```

**`setup_fdf(filename, fdf)`**
- Zeros the fdf structure
- Calls `parse_map()` to load the map
- Calls `init_z_minmax()` to find height range

**`setup_mlx(fdf)`**
- Creates 1920x1080 window via `mlx_init()`
- Creates image buffer via `mlx_new_image()`

**`init_camera(fdf)`**
- Calculates automatic zoom: `min(width / map_width, height / map_height) * 0.5`
- Centers offset at window center (960, 540)
- Sets default isometric view

---

### 2. Map Parsing (parser.c, parser_utils.c)

**Map File Format (.fdf)**
```
0  0  0  0  0
0  5  5  5  0
0  5 10  5  0
0  5  5  5  0
0  0  0  0  0
```
- Each number = Z height at that grid position
- Rows = Y coordinate, Columns = X coordinate
- Space-separated integers

**`parse_map(filename)`**
1. `open_and_allocate()` → Count lines, allocate `map->points` array
2. `read_map_lines()` → Read each line from file
3. For each line: `parse_line()` → Split by spaces, create `t_point` array
4. Return populated map

**`parse_line(line, y, width)`**
- Uses `ft_split(line, ' ')` to tokenize
- For each token: `points[i] = {x=i, y=y, z=ft_atoi(token), color=WHITE}`

**`init_z_minmax(map)`**
- Scans all points to find minimum and maximum Z values
- Stored for height-based coloring

---

### 3. Rendering Pipeline (draw.c, bresenham.c, draw_utils.c)

**`draw_map(fdf)`** - Main render function
```
1. Clear image to background color (0xFF0A0A0A - dark gray)
2. For each point (y, x) in the grid:
   a. Transform point to screen coordinates
   b. Draw line to point at (x+1, y) if exists → horizontal edge
   c. Draw line to point at (x, y+1) if exists → vertical edge
3. Result: wireframe mesh connecting all adjacent points
```

**`apply_transforms(point, fdf)`** - 3D to 2D conversion
```
1. Center point: x -= width/2, y -= height/2
2. Scale Z: z *= z_scale
3. Apply zoom: x *= zoom, y *= zoom, z *= zoom
4. Project to 2D: project_point() → applies isometric or parallel projection
5. Add screen offset: x += offset_x, y += offset_y
6. Add Z offset to Y: y -= z (height affects vertical position)
```

**`draw_line(img, p1, p2, fdf)`**
1. Get colors based on height: `get_height_color(z, z_max, z_min)`
2. Call `draw_bresenham()` for rasterization

**`draw_bresenham(img, p1, p2)`** - Bresenham Line Algorithm
```
Input: Two screen points p1, p2 with colors
1. Calculate deltas: dx = |x2-x1|, dy = |y2-y1|
2. Determine step direction: sx = ±1, sy = ±1
3. Initialize error term: err = dx - dy
4. Loop until reaching p2:
   a. Calculate color at current position (interpolate between p1.color and p2.color)
   b. put_pixel(x, y, color)
   c. Update position based on error term
   d. Adjust error term
```

**Color Functions**

`get_height_color(z, z_max, z_min)`:
- Maps Z height to grayscale intensity (0-255)
- Formula: `intensity = (z - z_min) / (z_max - z_min) * 255`
- Returns: RGB where R=G=intensity, B=255 (blue tint at low, white at high)

`interpolate_color(c1, c2, fraction)`:
- Linear interpolation between two colors
- Used for smooth color gradient along lines

`get_rgba(r, g, b, a)`:
- Packs 4 bytes into 32-bit integer: `(r << 24) | (g << 16) | (b << 8) | a`

---

### 4. Transformations & Projections (transform.c)

**Projection Types**
- `ISOMETRIC (0)`: Fixed 30-degree isometric view
- `PARALLEL (1)`: Free rotation using camera angles

**`project_point(point, fdf)`**
```c
if (type == ISOMETRIC)
    isometric(&x, &y, z);
else if (type == PARALLEL)
    rotate_x(&y, &z, angle_x);
    rotate_y(&x, &z, angle_y);
    rotate_z(&x, &y, angle_z);
```

**`isometric(x, y, z)`** - Classic Isometric Projection
```
angle = 30° = 0.523599 radians
x' = (x - y) * cos(30°)
y' = (x + y) * sin(30°) - z
```
Creates the classic "SimCity" style 3D view.

**Rotation Matrices (for PARALLEL mode)**

`rotate_x(y, z, angle)` - Rotation around X-axis:
```
y' = y * cos(angle) - z * sin(angle)
z' = y * sin(angle) + z * cos(angle)
```

`rotate_y(x, z, angle)` - Rotation around Y-axis:
```
x' = x * cos(angle) + z * sin(angle)
z' = -x * sin(angle) + z * cos(angle)
```

`rotate_z(x, y, angle)` - Rotation around Z-axis:
```
x' = x * cos(angle) - y * sin(angle)
y' = x * sin(angle) + y * cos(angle)
```

---

### 5. Event Handling (events.c, resize.c)

**`key_hook(keydata, param)`** - Keyboard Handler

| Key | Action |
|-----|--------|
| ESC | Close window |
| Arrow Up | Pan up (offset_y -= 10) |
| Arrow Down | Pan down (offset_y += 10) |
| Arrow Left | Pan left (offset_x -= 10) |
| Arrow Right | Pan right (offset_x += 10) |
| 1 | Top-down view (0, 0, 0) PARALLEL |
| 2 | Front view (90°, 0, 0) PARALLEL |
| 3 | Side view (0, 90°, -90°) PARALLEL |
| I | Isometric view (default) |

**`scroll_hook(xdelta, ydelta, param)`** - Mouse Wheel
- Scroll up: `zoom *= 1.1` (zoom in)
- Scroll down: `zoom /= 1.1` (zoom out)
- Minimum zoom: 1.0

**`resize_hook(width, height, param)`** - Window Resize
1. Delete old image buffer
2. Create new image with new dimensions
3. Recalculate offset to re-center
4. Redraw map

**`set_view(fdf, view)`** - Apply View Preset
- Copies view angles and type to camera
- Called by key_hook when switching views

---

### 6. Utility Functions

**Mini-libft (mini_libft/)**
- `ft_atoi(str)` - String to integer
- `ft_memset(ptr, val, size)` - Fill memory
- `ft_putendl_fd(str, fd)` - Print string with newline
- `ft_split(str, delim)` - Split string into array

**Get Next Line**
- `get_next_line(fd)` - Read one line from file descriptor
- Uses static buffer for efficiency across multiple calls

---

## Complete Data Flow Diagram

```
┌─────────────────────────────────────────────────────────────────┐
│                         STARTUP                                  │
├─────────────────────────────────────────────────────────────────┤
│  main() → setup_fdf() → setup_mlx() → init_camera()            │
│                ↓                                                 │
│         parse_map()                                              │
│              ↓                                                   │
│    ┌─────────────────┐                                          │
│    │  Map File (.fdf) │                                          │
│    │   0 0 0 0 0      │                                          │
│    │   0 5 5 5 0      │  →  t_map { points[][], width, height } │
│    │   0 5 10 5 0     │                                          │
│    │   0 5 5 5 0      │                                          │
│    │   0 0 0 0 0      │                                          │
│    └─────────────────┘                                          │
└─────────────────────────────────────────────────────────────────┘
                              ↓
┌─────────────────────────────────────────────────────────────────┐
│                      EVENT LOOP                                  │
├─────────────────────────────────────────────────────────────────┤
│                      mlx_loop()                                  │
│                          ↓                                       │
│    ┌──────────────┬──────────────┬──────────────┐               │
│    │  key_hook()  │ scroll_hook()│ resize_hook()│               │
│    │  (keyboard)  │ (mouse wheel)│ (window)     │               │
│    └──────┬───────┴──────┬───────┴──────┬───────┘               │
│           │              │              │                        │
│           └──────────────┼──────────────┘                        │
│                          ↓                                       │
│                    draw_map()                                    │
└─────────────────────────────────────────────────────────────────┘
                              ↓
┌─────────────────────────────────────────────────────────────────┐
│                    RENDERING PIPELINE                            │
├─────────────────────────────────────────────────────────────────┤
│  For each point in grid:                                        │
│                                                                  │
│  1. apply_transforms()                                          │
│     ├─ Center point around origin                               │
│     ├─ Scale Z by z_scale                                       │
│     ├─ Apply zoom factor                                        │
│     ├─ project_point()                                          │
│     │   ├─ ISOMETRIC: isometric() → fixed 30° projection       │
│     │   └─ PARALLEL: rotate_x/y/z() → free rotation            │
│     └─ Add screen offset                                        │
│                                                                  │
│  2. draw_line() to adjacent points                              │
│     ├─ get_height_color() → color based on Z                   │
│     └─ draw_bresenham() → rasterize line                       │
│         └─ put_pixel() → write to framebuffer                  │
└─────────────────────────────────────────────────────────────────┘
                              ↓
┌─────────────────────────────────────────────────────────────────┐
│                        OUTPUT                                    │
├─────────────────────────────────────────────────────────────────┤
│              ┌─────────────────────────┐                        │
│              │   Wireframe Display     │                        │
│              │                         │                        │
│              │      /\    /\           │                        │
│              │     /  \  /  \          │                        │
│              │    /    \/    \         │                        │
│              │   /      \     \        │                        │
│              │  /        \     \       │                        │
│              └─────────────────────────┘                        │
└─────────────────────────────────────────────────────────────────┘
```

---

## Key Algorithms Explained

### Bresenham Line Algorithm
An efficient algorithm for drawing lines using only integer arithmetic:
- Avoids expensive floating-point calculations per pixel
- Uses error accumulation to decide when to step in Y direction
- Produces optimal pixel placement for any line angle

### Isometric Projection
Projects 3D coordinates to 2D with a fixed 30° viewing angle:
- Creates the classic "2.5D" look seen in strategy games
- Simple formula that preserves relative distances
- No perspective distortion (parallel lines stay parallel)

### Height-Based Coloring
Maps elevation to color for visual depth perception:
- Lowest points appear blue-ish
- Highest points appear white
- Creates intuitive understanding of terrain height

---

## Instructions

### Compilation

```bash
# Build the project
make

# Clean object files
make clean

# Clean object files and executable
make fclean

# Full rebuild
make re
```

### Execution

```bash
# Run with a map file
./fdf maps/42.fdf
./fdf maps/mars.fdf
./fdf maps/pylone.fdf
```

---

## Controls Summary

| Input | Action |
|-------|--------|
| Arrow Keys | Pan view |
| Mouse Scroll | Zoom in/out |
| Key 1 | Top-down view |
| Key 2 | Front view |
| Key 3 | Side view |
| Key I | Isometric view |
| ESC | Exit |

---

## Resources

### References

- [MLX42 Documentation](https://github.com/codam-coding-college/MLX42) - Graphics library used for window management and rendering
- [Bresenham's Line Algorithm](https://en.wikipedia.org/wiki/Bresenham%27s_line_algorithm),
 [YouTube Video for Bresenham's Line Algo](https://www.youtube.com/watch?v=RGB-wlatStc-) - Efficient line rasterization algorithm
- [Isometric Projection](https://en.wikipedia.org/wiki/Isometric_projection) - 3D to 2D projection technique
- [3D Rotation Matrices](https://en.wikipedia.org/wiki/Rotation_matrix) - Mathematical foundation for 3D rotations
- [42 Docs - MiniLibX](https://harm-smits.github.io/42docs/libs/minilibx) - Community documentation for MiniLibX

### AI Usage

AI (Claude) was used as a learning and debugging assistant for this project:
- **Code explanation**: Understanding how rotation matrices and isometric projection work mathematically
- **Debugging**: Identifying why parallel view switching (keys 2, 3) wasn't working - the `project_point()` function was missing rotation logic for `PARALLEL` mode.
- **Code comments**: Adding explanatory comments to the rotation functions in `transform.c`

All AI-generated code was reviewed, understood, and adapted to fit the project requirements before integration.

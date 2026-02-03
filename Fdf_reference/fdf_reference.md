# FdF Quick Reference Guide

## Data Structures

### `t_point` - 3D Point
```c
struct s_point {
    float       x;      // X coordinate (column index from file)
    float       y;      // Y coordinate (row index from file)
    float       z;      // Z coordinate (elevation/height value)
    uint32_t    color;  // RGBA color (32-bit: RRGGBBAA)
};
```

### `t_map` - Height Map Grid
```c
struct s_map {
    t_point     **points;   // 2D array: points[y][x]
    int         width;      // Number of columns
    int         height;     // Number of rows
    float       z_max;      // Maximum elevation (for color gradient)
    float       z_min;      // Minimum elevation (for color gradient)
};
```

### `t_camera` - View Configuration
```c
struct s_camera {
    float       angle_x;    // Rotation angle around X-axis (radians)
    float       angle_y;    // Rotation angle around Y-axis (radians)
    float       angle_z;    // Rotation angle around Z-axis (radians)
    int         type;       // ISOMETRIC or PARALLEL
    float       zoom;       // Magnification factor (1.0 = normal)
    float       z_scale;    // Height exaggeration factor
    int         offset_x;   // Horizontal pan (pixels)
    int         offset_y;   // Vertical pan (pixels)
};
```

### `t_view` - View Preset
```c
struct s_view {
    double      angle_x;    // X rotation (radians)
    double      angle_y;    // Y rotation (radians)
    double      angle_z;    // Z rotation (radians)
    int         type;       // ISOMETRIC or PARALLEL
};
```

### `t_fdf` - Main Application State
```c
struct s_fdf {
    t_map           map;        // Height map data
    t_camera        cam;        // Camera/view settings
    mlx_t           *mlx;       // MLX window handle
    mlx_image_t     *img;       // Frame buffer
};
```

---

## File-by-File Function Reference

### `main.c` - Application Entry Point
```c
int     main(int argc, char **argv)
// Entry point. Validates args, initializes FDF and graphics, starts event loop

void    calc_camera_zoom(t_fdf *fdf)
// Calculates optimal zoom level to fit entire map in window

void    init_camera(t_fdf *fdf)
// Sets default camera to isometric view, initializes zoom and offsets

int     setup_mlx(t_fdf *fdf)
// Initializes MLX graphics window and frame buffer

int     setup_fdf(t_fdf *fdf, const char *filename)
// Parses map file and initializes map data structure
```

### `parser.c` - File Reading & Map Parsing
```c
int         count_height(const char *filename)
// Returns: Number of lines in file (map height)

t_point*    parse_line(char *line, int y, int width)
// Parses one line of map file into array of t_point
// Returns: Pointer to array of t_point, or NULL on error

int         open_and_allocate(const char *filename, t_map *map)
// Counts height, allocates 2D point array, opens file
// Returns: File descriptor, or -1 on error

int         read_map_lines(int fd, t_map *map)
// Reads all lines from file descriptor, parses into t_map
// Returns: 1 on success, 0 on failure

static void cleanup_on_error(t_map *map, int y, char *line)
// Helper: Frees allocated memory in case of parse error
```

### `parser_utils.c` - Parsing Utilities
```c
void        free_split_safe(char **split)
// Safely deallocates string array from ft_split()

void        init_z_minmax(t_map *map)
// Scans all points, finds and sets z_max and z_min

void        free_map(t_map *map)
// Deallocates entire 2D point grid

int         count_width(char *line)
// Counts space-separated values in a line
// Returns: Number of columns

int         is_valid_number(const char *str)
// Validates that string is a valid integer (with optional +/- sign)
// Returns: 1 if valid, 0 if invalid
```

### `get_next_line.c` - Line Reading
```c
char*       get_next_line(int fd)
// Reads next line from file descriptor
// Returns: String with newline included, or NULL at EOF
// Note: Uses static buffer for persistence between calls

static char*    read_to_buffer(int fd, char *remainder, char *buffer)
// Helper: Reads from fd into buffer, appends to remainder

static char*    update_remainder(char *line_buffer)
// Helper: Removes extracted line from buffer, keeps rest

static char*    extract_line(char *remainder)
// Helper: Extracts first line (up to \n) from buffer
```

### `get_next_line_utils.c` - String Utilities
```c
char*       ft_strchr(const char *s, int c)
// Finds first occurrence of character c in string s
// Like standard strchr()

char*       ft_strdup(const char *src)
// Duplicates string
// Like standard strdup()

ssize_t     ft_strlen(const char *s)
// Returns length of string
// Like standard strlen()

char*       ft_strjoin(char *s1, char const *s2)
// Joins two strings into new allocation
// Frees s1 after joining
```

### `draw.c` - Main Rendering
```c
t_point     apply_transforms(t_point p, t_fdf *fdf)
// Complete transformation pipeline:
//   1. Center point to map origin
//   2. Scale Z by z_scale
//   3. Multiply all by zoom
//   4. Project from 3D to 2D via project_point()
//   5. Add camera offsets
// Returns: Transformed 2D screen point

uint32_t    get_rgba(int r, int g, int b, int a)
// Packs RGBA components into 32-bit color
// Returns: 0xRRGGBBAA format

void        clear_image(mlx_image_t *img)
// Fills entire frame buffer with dark background color (0xFF0A0A0A)

void        draw_map(t_fdf *fdf)
// Main rendering function:
//   1. Clears screen
//   2. For each point in grid:
//      - Transform to screen space
//      - Draw line to right neighbor (if exists)
//      - Draw line to bottom neighbor (if exists)
// Creates complete wireframe visualization
```

### `draw_utils.c` - Drawing Utilities
```c
void        put_pixel(mlx_image_t *img, int x, int y, uint32_t color)
// Writes single pixel to frame buffer
// Performs bounds checking (safe for any x, y)

uint32_t    get_height_color(float z, float z_max, float z_min)
// Maps elevation value to blue gradient color
// Formula: ratio = (z - z_min) / (z_max - z_min)
//          r = 50 + 205 * ratio
//          g = 50 + 205 * ratio
//          b = 255
// Returns: 32-bit RGBA color

float       get_fraction(float x1, float x2, float x)
// Calculates interpolation weight along a line
// Returns: (x - x1) / (x2 - x1), or 0.0 if x1 == x2

uint32_t    interpolate_color(uint32_t c1, uint32_t c2, float fraction)
// Blends two colors by fraction
// Formula: result = c1 + (c2 - c1) * fraction (per channel)
// fraction = 0.0 → pure c1, fraction = 1.0 → pure c2
// Returns: Interpolated 32-bit color
```

### `bresenham.c` - Line Rasterization
```c
void        draw_line(t_fdf *fdf, t_point p1, t_point p2)
// High-level line drawing
//   1. Get colors for both endpoints based on Z value
//   2. Call draw_bresenham() to rasterize the line

void        init_bresenham(int *v, t_point p1, t_point p2, int *xy)
// Initializes Bresenham algorithm variables:
//   v[0] = |dx|, v[1] = -|dy|, v[2] = sign_x, v[3] = sign_y, v[4] = error
//   xy[0] = start_x, xy[1] = start_y

void        step_bresenham(int *v, int *xy, t_point p2)
// Steps one pixel along the line using Bresenham error term
// Updates xy[] to next pixel position

void        draw_bresenham(t_fdf *fdf, t_point p1, t_point p2)
// Main Bresenham algorithm implementation
//   1. Initialize Bresenham state
//   2. Loop while not at endpoint:
//      - Calculate interpolation fraction along line
//      - Interpolate color between endpoint colors
//      - Write pixel to frame buffer
//      - Step to next pixel
```

### `transform.c` - 3D Transformations
```c
void        isometric(float *x, float *y, float z)
// Applies isometric projection (30° fixed angle)
// Modifies x and y in place
// Formula:
//   x' = (x - y) * cos(30°) = (x - y) * 0.866
//   y' = (x + y) * sin(30°) - z = (x + y) * 0.5 - z

static void rotate_x(float *y, float *z, float angle)
// Rotates point around X-axis (pitch)
// Modifies y and z in place

static void rotate_y(float *x, float *z, float angle)
// Rotates point around Y-axis (yaw)
// Modifies x and z in place

static void rotate_z(float *x, float *y, float angle)
// Rotates point around Z-axis (roll)
// Modifies x and y in place

t_point     project_point(t_point p, t_fdf *fdf)
// Dispatches to correct projection based on camera type:
//   If ISOMETRIC: calls isometric()
//   If PARALLEL: applies rotation matrices (X, Y, Z)
// Returns: Projected 2D point (z still present but ignored)
```

### `events.c` - User Input Handling
```c
void        set_view(t_fdf *f, t_view view)
// Applies view preset: sets angle_x, angle_y, angle_z, and type

static t_view   make_view(double x, double y, double z, int type)
// Creates a view structure with given parameters
// Helper function for event handlers

static void handle_keys(mlx_key_data_t keydata, t_fdf *f)
// Handles non-ESC key presses:
//   Arrow keys: adjust offset_x/y (pan camera)
//   1, 2, 3, I: switch projection views

void        key_hook(mlx_key_data_t keydata, void *param)
// Called on key press/repeat
// Processes input and triggers redraw

void        scroll_hook(double xdelta, double ydelta, void *param)
// Called on mouse wheel scroll
// Multiplies/divides zoom by 1.1
// Enforces minimum zoom of 1.0

void        resize_hook(int32_t width, int32_t height, void *param)
// Called when window is resized
// Recreates frame buffer at new size
// Updates camera offsets to new center
```

### `resize.c` - Window Management & Parsing Wrapper
```c
void        resize_hook(int32_t width, int32_t height, void *param)
// [Same as in events.c - handles window resize]

t_map       parse_map(const char *filename)
// High-level map parsing coordinator:
//   1. Allocate and open file
//   2. Read all lines
//   3. Close file
// Returns: Populated t_map structure
```

---

## Key Constants & Macros

```c
#define BUFFER_SIZE    1024       // Size of read buffer for get_next_line
#define WIN_WIDTH      1920       // Default window width (pixels)
#define WIN_HEIGHT     1080       // Default window height (pixels)
#define PARALLEL       0          // Camera type constant
#define ISOMETRIC      1          // Camera type constant
```

---

## Algorithm Summary

### Bresenham Line Algorithm
**Time:** O(max(|dx|, |dy|))  
**Space:** O(1)

```
Initialize:
  v[0] = |dx|, v[1] = -|dy|
  v[2] = sign(dx), v[3] = sign(dy)
  v[4] = v[0] + v[1]  (error term)

Loop:
  Plot pixel at (x, y)
  error_2x = 2 * v[4]
  If error_2x >= v[1]: x += v[2]; v[4] += v[1]
  If error_2x <= v[0]: y += v[3]; v[4] += v[0]
  Until x == end_x AND y == end_y
```

### Height-based Color Gradient
```
ratio = (z - z_min) / (z_max - z_min)  // 0.0 to 1.0

R = 50 + (205 * ratio)      // 50 to 255
G = 50 + (205 * ratio)      // 50 to 255
B = 255                     // Always max

Result: Dark blue (50,50,255) at lowest points
        Light blue/white (255,255,255) at highest points
```

### Isometric Projection
```
x' = (x - y) * cos(30°)
y' = (x + y) * sin(30°) - z

Where 30° = 0.523599 radians
cos(30°) = 0.866025
sin(30°) = 0.5
```

---

## Typical Values

| Variable | Typical Range | Notes |
|----------|---------------|-------|
| zoom | 1.0 - 200.0 | 1.0 = normal size |
| z_scale | 0.1 - 5.0 | Exaggerates or dampens elevation |
| angle_x | 0 - 2π | Pitch (up/down rotation) |
| angle_y | 0 - 2π | Yaw (left/right rotation) |
| angle_z | 0 - 2π | Roll (twist rotation) |
| offset_x | 0 - WIN_WIDTH | Pan horizontally |
| offset_y | 0 - WIN_HEIGHT | Pan vertically |

---

## Memory Management

**Allocated in:**
- `setup_fdf()`: t_map.points (2D point array)
- `get_next_line()`: Static buffer for file reading
- `ft_strjoin()`: Temporary strings during parsing

**Deallocated in:**
- `free_map()`: All points and 2D array
- Program exit: MLX window and image

**Memory leaks to avoid:**
- Not freeing point array if parsing fails
- Not closing file descriptors on error
- Not calling mlx_terminate() before exit

---

## Common Tasks

### Adding a New View Preset
```c
// In events.c, in handle_keys():
if (keydata.key == MLX_KEY_V)
    set_view(f, make_view(0.785398, 0.785398, 0, PARALLEL));
    // 0.785398 rad = 45 degrees
```

### Changing Color Scheme
```c
// In draw_utils.c, modify get_height_color():
// Example: Red-Yellow gradient instead of blue
ratio = (z - z_min) / (z_max - z_min);
rgb[0] = 255;           // Always max red
rgb[1] = (uint8_t)(205 * ratio);  // Green ramps up
rgb[2] = 0;             // No blue
```

### Adjusting Auto-Zoom
```c
// In main.c, in calc_camera_zoom():
// Make zoom calculation more/less aggressive
fdf->cam.zoom = (WIN_WIDTH * 0.7) / dist_x;  // Change 0.7
// Higher value = bigger zoom, more of map visible
```

---

## Debugging Tips

1. **No map appears?**
   - Check file format (numbers separated by spaces)
   - Verify z_min != z_max (crashes color calculation)
   - Ensure window is large enough

2. **Distorted view?**
   - Verify z_scale calculation is correct
   - Check that rotation angles are in radians (0-2π)
   - Test with simpler preset views (1, 2, 3, I keys)

3. **Slow rendering?**
   - Large maps (>1000x1000 points) will be slow
   - Zoom affects rendering time (more pixels to draw)
   - Profile Bresenham loop and color interpolation

4. **Colors wrong?**
   - z_min and z_max might be incorrectly calculated
   - Check get_height_color() gradient formula
   - Verify interpolate_color() blending math

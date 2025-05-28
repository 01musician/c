local ffi = require("ffi")

-- Define the C functions and types
ffi.cdef[[
typedef struct {
    int x;
    int y;
} Point;

int add(int a, int b);
void print_point(Point p);
]]

-- Load the shared library
local mylib = ffi.load("./clib.so")

-- Call the C function
local result = mylib.add(5, 7)
print("Result:", result)

-- Create and manipulate a C struct
local point = ffi.new("Point")
point.x = 3
point.y = 4
mylib.print_point(point)


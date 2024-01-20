-- Example 1: Pack an integer and print in hex
local packedInt = string.pack(">I4", 0x12345678)
print("Packed Integer:", string.format("%02X %02X %02X %02X", packedInt:byte(1, #packedInt)))

-- Example 2: Pack a string and print in hex
local packedString = string.pack("c8", "LuaHex")
print("Packed String:", packedString:byte(1, #packedString))

-- Example 3: Pack a floating-point number and print in hex
local packedFloat = string.pack("f", 3.14)
print("Packed Float:", packedFloat:byte(1, #packedFloat))

-- Example 4: Pack multiple values and print in hex
local packedMulti = string.pack("I4c8f", 9876, "Packed", 2.718)
print("Packed Multi:", packedMulti:byte(1, #packedMulti))


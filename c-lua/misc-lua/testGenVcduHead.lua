-- Example values
local version = 1       -- 2 bits
local vcid = 17         -- 6 bits
local ssc = 123456      -- 24 bits

-- Combine Version + VCID into 1 byte
-- Version in top 2 bits, VCID in lower 6 bits
local first_byte = (version << 6) | (vcid & 0x3F)

-- Pack SSC as 3 bytes (24-bit big-endian)
local ssc_bytes = string.pack(">I3", ssc)  -- > = big-endian, I3 = 3-byte integer

-- Combine header bytes
local header = string.char(first_byte) .. ssc_bytes

-- Optional: simple checksum (XOR of all bytes)
local crc = 0
for i = 1, #header do
    crc = crc ~ header:byte(i)
end

header = header .. string.char(crc)

-- Write to file
local f = assert(io.open("vcdu.bin", "wb"))
f:write(header)
f:close()

print("VCDU header generated, length =", #header)


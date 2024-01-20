-- Define your binary structure
local binaryStructure = {
    {name = "integerField", type = "int32"},
    {name = "stringField", type = "string", length = 8}
}

-- Function to serialize Lua table to binary data
function serialize(data)
    local result = ""
    for _, field in ipairs(binaryStructure) do
        if field.type == "int32" then
            result = result .. string.pack("<I4", data[field.name] or 0)
        elseif field.type == "string" then
            result = result .. string.pack("c" .. field.length, data[field.name] or "")
        end
    end
    return result
end

-- Function to deserialize binary data to Lua table
function deserialize(data)
    local result = {}
    local offset = 1
    for _, field in ipairs(binaryStructure) do
        if field.type == "int32" then
            result[field.name], offset = string.unpack("<I4", data, offset)
        elseif field.type == "string" then
            result[field.name], offset = string.unpack("c" .. field.length, data, offset)
        end
    end
    return result
end

-- Example usage
local data = {
    integerField = 42,
    stringField = "Hello"
}

-- Serialize the data
local binaryData = serialize(data)
print("binary")
print(binaryData)

-- Deserialize the binary data
local decodedData = deserialize(binaryData)

-- Print the result
for key, value in pairs(decodedData) do
    print(key, value)
end


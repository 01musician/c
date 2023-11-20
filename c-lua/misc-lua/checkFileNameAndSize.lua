function isFileMatch(filename, regexPattern)
    local match = string.match(filename, regexPattern)
    return match ~= nil
end

function isFileSizeGreater(filePath, sizeThreshold)
    local file = io.open(filePath, "rb")
    
    if file then
        local fileSize = file:seek("end")
        file:close()

        local fileSizeKB = fileSize / 1024

        return fileSizeKB > sizeThreshold
    else
        return false  -- Unable to open the file
    end
end

-- Example usage
local filename = "checkFileNameAndSize.lua"
local regexPattern = "^check.*%.lua$"
local sizeThresholdKB = 15

if isFileMatch(filename, regexPattern) and isFileSizeGreater(filename, sizeThresholdKB) then
    print("File matches the pattern and has a size greater than 15kB.")
else
    print("File does not match the pattern or its size is not greater than 15kB.")
end


        -- Check if the filename matches the regular expression and if the size is greater than the threshold
        -- Check if the filename matches the regular expression and if the size is greater than the threshold
        -- Check if the filename matches the regular expression and if the size is greater than the threshold
        -- Check if the filename matches the regular expression and if the size is greater than the threshold
        -- Check if the filename matches the regular expression and if the size is greater than the threshold
        -- Check if the filename matches the regular expression and if the size is greater than the threshold
        -- Check if the filename matches the regular expression and if the size is greater than the threshold
function isFileValid(filePath)
    local regexPattern = "^check.*%.lua$"
    local sizeThresholdKB = 1

    local file = io.open(filePath, "rb")

    if file then
        local fileSize = file:seek("end")
        file:close()

        local fileSizeKB = fileSize / 1024
        local filename = string.match(filePath, "([^/\\]+)$")  -- Extract the filename from the path

        -- Check if the filename matches the regular expression and if the size is greater than the threshold
        return filename and string.match(filename, regexPattern) and fileSizeKB > sizeThresholdKB
    else
        return false  -- Unable to open the file
    end
end

-- Example usage
local filePath = "checkFileValid.lua"

if isFileValid(filePath) then
    print("File is valid: matches the pattern and has a size greater than 1kB.")
else
    print("File is not valid: does not match the pattern or its size is not greater than 1kB.")
end


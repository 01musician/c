local lfs = require("lfs")

-- relpath: relative path from root
-- return 1 to include in hash, 0 to skip
function isValidate(relpath)
    local attr = lfs.attributes(relpath)
    if not attr then
        print("Warning: cannot access " .. relpath)
        return 0
    end

    if attr.mode == "directory" then
        return 1  -- skip directories, or return 1 if you want to hash directory names
    else
	    if relpath:match("%.c$") then
		    return 1
	    else
		    return 0
	    end
    end
end


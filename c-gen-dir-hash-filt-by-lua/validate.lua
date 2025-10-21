-- Only hash files ending with ".txt"
function isValidate(relpath)
    if relpath:match("%.c$") then
        return 1
    else
        return 0
    end
end


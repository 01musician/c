function fibonacci(n)
    if n < 2 then
        return n
    else
        return fibonacci(n - 1) + fibonacci(n - 2)
    end
end

local start = os.clock()
print(fibonacci(35))
local finish = os.clock()

print("Execution time: " .. (finish - start) .. " seconds")


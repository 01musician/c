-- Sample table with unsorted numbers
local unsortedTable = {5, 2, 8, 1, 7, 3}

-- Print the unsorted table
print("Unsorted Table:")
for _, value in ipairs(unsortedTable) do
    print(value)
end

-- Custom comparison function for sorting in descending order
local function customCompare(a, b)
    return a > b
end

-- Use table.sort with the custom comparison function
table.sort(unsortedTable, customCompare)

-- Print the sorted table
print("\nSorted Table (Descending Order):")
for _, value in ipairs(unsortedTable) do
    print(value)
end

local function customCompareA(a, b)
    return a < b
end


-- Use table.sort with the custom comparison function
table.sort(unsortedTable, customCompareA)

print("\nSorted Table (Ascending Order):")
for _, value in ipairs(unsortedTable) do
    print(value)
end



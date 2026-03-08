-- parser.lua

-- 定义第二个字段的 <string, int, int> 规则数组 (适合 20 条左右的规模)
local t2_rules = {
    {"AAAA", 1, 1},
    {"BBBB", 2, 2},
    {"CCCC", 3, 3}
    -- 在这里继续添加你的其他规则...
}

-- 定义第三个字段的 <string, int> 规则数组 (适合 20 条左右的规模)
local t3_rules = {
    {"AAAB", 1},
    {"BBBC", 2},
    {"CCCD", 3}
    -- 在这里继续添加你的其他规则...
}

function parse_filename(filename)
    -- 提取前三个以 '_' 分隔的 token
    local t1, t2, t3 = string.match(filename, "^([^_]+)_([^_]+)_([^_]+)")

    -- 1. 若第一个 token 不为 06，或者格式不匹配，直接返回 0, 0, 0
    if not t1 or t1 ~= "06" then
        return 0, 0, 0
    end

    local v1, v2, v3 = 0, 0, 0
    local t2_matched = false

    -- 2. 针对第二个字段的数组开展判断
    for _, rule in ipairs(t2_rules) do
        if t2 == rule[1] then
            v1 = rule[2]
            v2 = rule[3]
            t2_matched = true
            break
        end
    end

    -- 若不存在相等的 string，则直接返回 0, 0, 0
    if not t2_matched then
        return 0, 0, 0
    end

    -- 3. 针对第三个字段的数组开展判断
    for _, rule in ipairs(t3_rules) do
        if t3 == rule[1] then
            v3 = rule[2]
            break
        end
    end

    -- 返回最终的三元组
    return v1, v2, v3
end

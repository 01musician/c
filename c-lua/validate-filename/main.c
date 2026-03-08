#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 引入 Lua 头文件
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>

// 处理单个文件名的函数
void process_filename(lua_State *L, const char *filename) {
    // 1. 将 Lua 中的函数压入栈顶
    lua_getglobal(L, "parse_filename");
    if (!lua_isfunction(L, -1)) {
        fprintf(stderr, "错误: Lua 脚本中未找到 'parse_filename' 函数\n");
        lua_pop(L, 1);
        return;
    }

    // 2. 将待处理的文件名作为参数压入栈顶
    lua_pushstring(L, filename);

    // 3. 执行调用：传入 1 个参数，期望返回 3 个结果，不使用自定义错误处理
    if (lua_pcall(L, 1, 3, 0) != 0) {
        fprintf(stderr, "Lua 执行错误: %s\n", lua_tostring(L, -1));
        lua_pop(L, 1); // 弹出错误信息
        return;
    }

    // 4. 获取返回的 3 个整数结果
    // 此时栈顶是第三个返回值(-1)，往下依次是第二个(-2)和第一个(-3)
    int v1 = lua_tointeger(L, -3);
    int v2 = lua_tointeger(L, -2);
    int v3 = lua_tointeger(L, -1);

    // 5. 打印结果
    printf("文件名: %-25s -> 三元组: (%d, %d, %d)\n", filename, v1, v2, v3);

    // 6. 清理栈上的 3 个返回值，保持栈平衡
    lua_pop(L, 3);
}

int main(int argc, char **argv) {
    // 初始化 Lua 状态机
    lua_State *L = luaL_newstate();
    if (!L) {
        fprintf(stderr, "无法创建 Lua 状态机\n");
        return 1;
    }
    
    // 打开 Lua 标准库（如 string 等）
    luaL_openlibs(L);

    // 加载并执行 Lua 脚本文件
    if (luaL_dofile(L, "parser.lua") != 0) {
        fprintf(stderr, "加载 Lua 脚本失败: %s\n", lua_tostring(L, -1));
        lua_close(L);
        return 1;
    }

    // 如果通过命令行传入了参数，则处理传入的文件名
    if (argc > 1) {
        for (int i = 1; i < argc; i++) {
            process_filename(L, argv[i]);
        }
    } else {
        // 否则运行预设的测试用例验证逻辑
        printf("--- 开始运行预设测试用例 ---\n");
        
        // 测试 1: 完全匹配
        process_filename(L, "06_AAAA_BBBC_test1.log"); // 预期: (1, 1, 2)
        process_filename(L, "06_CCCC_CCCD_test2.log"); // 预期: (3, 3, 3)
        
        // 测试 2: 第一个 token 不是 06
        process_filename(L, "07_AAAA_BBBC_test3.log"); // 预期: (0, 0, 0)
        
        // 测试 3: 第二个 token 在数组中找不到
        process_filename(L, "06_XXXX_BBBC_test4.log"); // 预期: (0, 0, 0)
        
        // 测试 4: 第三个 token 在数组中找不到 (第三个元素应为初始值0)
        process_filename(L, "06_BBBB_YYYY_test5.log"); // 预期: (2, 2, 0)
        
        // 测试 5: 文件名格式不符合要求
        process_filename(L, "invalid_filename.log");   // 预期: (0, 0, 0)
    }

    // 清理并关闭 Lua 状态机
    lua_close(L);
    return 0;
}

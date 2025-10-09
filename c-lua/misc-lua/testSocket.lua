local socket = require "socket"
print("LuaSocket version:", socket._VERSION)

-- test DNS lookup
local ip = socket.dns.toip("baidu.com")
print("baidu.com ->", ip)


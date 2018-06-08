-- This file was automatically generated for the LuaDist project.

package="luaposix"
version="5.1.15-1"
-- LuaDist source
source = {
  tag = "5.1.15-1",
  url = "git://github.com/LuaDist-testing/luaposix.git"
}
-- Original source
-- source = {
--   url = "https://github.com/downloads/rrthomas/luaposix/luaposix-5.1.15.tar.gz",
--   md5 = "c492541a768302fb67ad14a294306f3a",
--   dir = "luaposix-5.1.15"
-- }
description = {
  summary = "Lua bindings for POSIX (including curses)",
  detailed = [[
      A library binding various POSIX APIs, including curses.
      POSIX is the IEEE Portable Operating System Interface standard.
      luaposix is based on lposix and lcurses.
   ]],
  homepage = "http://github.com/rrthomas/luaposix/",
  license = "MIT/X11"
}
dependencies = {
  "lua >= 5.1"
}
build = {
  type = "command",
  build_command = "LUA=$(LUA) CPPFLAGS=-I$(LUA_INCDIR) ./configure --prefix=$(PREFIX) --libdir=$(LIBDIR) --datadir=$(LUADIR)",
  install_command = "make install"
}
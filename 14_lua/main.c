#include <stdio.h>
#include <string.h>
#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"

int main(void)
{
  char *buff = "a = 1 + 1;";
  int error;
  asm("WTO   'Before luaL_newstate'");
  lua_State *L = luaL_newstate();
  asm("WTO   'Before luaL_openlibs'");
  luaL_openlibs(L);
  asm("WTO   'Before luaL_loadstring'");
  error = luaL_loadstring(L, buff) || lua_pcall(L, 0, 0, 0);
  if (error)
  {
    fprintf(stderr, "%s", lua_tostring(L, -1));
    lua_pop(L, 1);
  }
  asm("WTO   'lua_close'");
  lua_close(L);
  return 0;
}

/*
 * POSIX library for Lua 5.1/5.2.
 * (c) Gary V. Vaughan <gary@vaughan.pe>, 2013-2014
 * (c) Reuben Thomas <rrt@sc3d.org> 2010-2013
 * (c) Natanael Copa <natanael.copa@gmail.com> 2008-2010
 * Clean up and bug fixes by Leo Razoumov <slonik.az@gmail.com> 2006-10-11
 * Luiz Henrique de Figueiredo <lhf@tecgraf.puc-rio.br> 07 Apr 2006 23:17:49
 * Based on original by Claudio Terra for Lua 3.x.
 * With contributions by Roberto Ierusalimschy.
 * With documentation from Steve Donovan 2012
 */
/***
 Retrieve File System Information.

 Where supported by the underlying system, query the file system.  If the
 module loads, but there is no kernel support, then `posix.sys.statvfs.version`
 will be set, but the unsupported APIs will be `nil`.

@module posix.sys.statvfs
*/

#include <config.h>

#if defined HAVE_STATVFS

#include <sys/statvfs.h>

#include "_helpers.c"


/***
Files system information record.
@table PosixStatvfs
@int f_bsize file system block size
@int f_frsize fundamental file system block size
@int f_blocks number of *f_frsize* sized blocks in file system
@int f_bfree number of free blocks
@int f_bavail number of free blocks available to non-privileged process
@int f_files number of file serial numbers
@int f_ffree number of free file serial numbers
@int f_favail number of free file serial numbers available
@int f_fsid file system id
@int f_flag flag bits
@int f_namemax maximum filename length
*/
static int
pushstatvfs(lua_State *L, struct statvfs *sv)
{
	if (!sv)
		return lua_pushnil(L), 1;

	lua_createtable(L, 0, 11);

	setnumberfield(sv, f_bsize);
	setnumberfield(sv, f_frsize);
	setnumberfield(sv, f_blocks);
	setnumberfield(sv, f_bfree);
	setnumberfield(sv, f_bavail);
	setnumberfield(sv, f_files);
	setnumberfield(sv, f_ffree);
	setnumberfield(sv, f_favail);
	setnumberfield(sv, f_fsid);
	setnumberfield(sv, f_flag);
	setnumberfield(sv, f_namemax);

	settypemetatable("PosixStatvfs");
	return 1;
}


/***
Get file system statistics.
@function statvfs
@string path any path within the mounted file system
@treturn PosixStatvfs information about file system containing *path*
@see statvfs(3)
@usage for a, b in pairs (P.statvfs "/") do print (a, b) end
*/
static int
Pstatvfs(lua_State *L)
{
	struct statvfs s;
	const char *path = luaL_checkstring(L, 1);
	checknargs(L, 1);
	if (statvfs(path, &s) == -1)
		return pusherror(L, path);
	return pushstatvfs(L, &s);
}


static const luaL_Reg posix_sys_statvfs_fns[] =
{
	LPOSIX_FUNC( Pstatvfs		),
	{NULL, NULL}
};


/***
Constants.
@section constants
*/

/***
Statvfs constants.
Any constants not available in the underlying system will be `nil` valued.
@table posix.sys.statvfs
@int ST_RDONLY read-only file system
@int ST_NOSUID does not support `S_ISUID` nor `S_ISGID` file mode bits
@usage
  -- Print statvfs constants supported on this host.
  for name, value in pairs (require "posix.sys.statvfs") do
    if type (value) == "number" then
      print (name, value)
     end
  end
*/


LUALIB_API int
luaopen_posix_sys_statvfs(lua_State *L)
{
	luaL_register(L, "posix.sys.statvfs", posix_sys_statvfs_fns);
	lua_pushliteral(L, "posix.sys.statvfs for " LUA_VERSION " / " PACKAGE_STRING);
	lua_setfield(L, -2, "version");

	LPOSIX_CONST( ST_RDONLY		);
	LPOSIX_CONST( ST_NOSUID		);

	return 1;
}
#endif

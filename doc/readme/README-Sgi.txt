BETA for SGI.
=============

1. requirements
---------------

1.1   You must run IRIX 5.3 or 6.2 (32 bit).
      If you run IRIX 5.3, you must have installed patch 410 from SGI
      in order to fix the linker to generate pure ELF binaries.
      If you have not applied this patch, the linker will fail 
      like this:

        Unknown flag: -woff

1.2   You cannot link applications, that specify external OBJFILEs
      compiled with gcc. You must use cc for external object files.
      If you get an error like:

        ld: FATAL 2: Internal: at ../commonlib/ld3264/relocate.c \
        merge_ext returns nil during relocation

      this may be caused by an attempt to link a gcc-produced file 
      into your application.
      If you use make files invoked via the MAKE property in a 
      BETA fragment, you should use $(CC) instead of a hardcoded
      C compiler name. The BETA compiler sets CC to a proper default
      value on alle UNIX platforms.

1.3   After linking shared objects, the LD_LIBRARY_PATH should be set
      so that it includes the directory, where the shared object files
      reside. The compiler will tell which directory this is.
      If you get an error like

        793:./foo: rld: Fatal Error: cannot map soname 'foo1..gso' \
        using any of the filenames /usr/lib/foo1..gso:/lib/foo1..gso:\
        /lib/cmplrs/cc/foo1..gso:/usr/lib/cmplrs/cc/foo1..gso: \
        -- either the file does not exist or the file is not mappable \
        (with reason indicated in previous msg)

      when running you application (here "foo"), this may be caused by
      LD_LIBRARY_PATH not being set correctly.

2. limitations
--------------

2.1   Lazy Fetch in persistence is not implemented.
      This means that the following demos fail:
         demo/persistentstore/largeRead
         demo/persistentstore/crossloc

2.2   Check for suspend involving callbacks is not done.
      If you do a suspend in a callback situation the program is 
      likely to crash.

2.3   It is uncertain if valhalla (v2.2) will work for executables
      that contain shared object files.

2.4   The following runtime errors may not always result in correct 
      dumps:
         Repetition subrange out of range
         Text parameter to C routine too big (max. 1000 bytes)

2.5   Do not use the 'current' notation in fragment paths.
      E.g. use '~beta/basiclib/v1.6/betaenv' instead of 
      '~beta/basiclib/current/betaenv'.
      You may get linker errors, if you use the 'current' notation.

3. Disclaimer
-------------

The implementation is not yet optimal, since focus has been on
functionality and not on performance until now.  Several optimizations
are planned for future releases.

Startup time for SGIbeta and SGIvalhalla are quite significant.  This
is due to the dynamic linker, and may be fixed in a future version.


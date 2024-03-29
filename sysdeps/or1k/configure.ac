GLIBC_PROVIDES dnl See aclocal.m4 in the top level source directory.
# Local configure fragment for sysdeps/or1k.

# We check to see if the compiler and flags are selecting
# hard-float so we can use shlib-versions to select the
# appropriate name for the dynamic linker via %ifdef.
AC_CACHE_CHECK([whether the compiler has hard-float enabled],
  [libc_cv_or1k_hard_float],
  [AC_EGREP_CPP(yes,[#ifdef __or1k_hard_float__
		      yes
		     #endif
  ], libc_cv_or1k_hard_float=yes, libc_cv_or1k_hard_float=no)])
if test $libc_cv_or1k_hard_float = yes; then
  AC_DEFINE(HAVE_OR1K_HARD_FLOAT)
  LIBC_CONFIG_VAR([default-abi], [hard])
else
  LIBC_CONFIG_VAR([default-abi], [soft])
fi

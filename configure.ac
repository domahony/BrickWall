dnl Process this file with autoconf to produce a configure script.

AC_PREREQ(2.59)
AC_INIT(Bricks, 1.0)

AC_CANONICAL_SYSTEM
AM_INIT_AUTOMAKE()

AC_PROG_CXX

SDL_LDFLAGS=`sdl2-config --libs`
AC_SUBST([SDL_LDFLAGS])
MAGICK_LDFLAGS=`pkg-config --libs Magick++`
AC_SUBST([MAGICK_LDFLAGS])
GL_LDFLAGS=`pkg-config --libs gl`
AC_SUBST([GL_LDFLAGS])
BULLET_CFLAGS=`pkg-config --cflags bullet`
BULLET_LDFLAGS=`pkg-config --libs bullet`

AC_SUBST([BULLET_LDFLAGS])
AC_SUBST([BULLET_CFLAGS])

GEOTIFF_CFLAGS=-I/usr/include/geotiff
GEOTIFF_LDFLAGS='-lgeotiff -ltiff'
AC_SUBST([GEOTIFF_CFLAGS])
AC_SUBST([GEOTIFF_LDFLAGS])

AC_CONFIG_FILES(Makefile src/Makefile)
AC_OUTPUT


AUTOMAKE_OPTIONS = gnu

lib_LTLIBRARIES = libtgcl.la

AM_CFLAGS = -g -std=c99 -Wall -arch x86_64

libtgcl_la_LDFLAGS = -version-info 0:0:0
libtgcl_la_SOURCES = class_ArrayElement_i.c class_Array_i.c class_String_i.c
libtgcl_la_includedir = $(includedir)/tgcl
libtgcl_la_include_HEADERS = class_Array.h class_ArrayElement.h class_String.h
noinst_HEADERS = class_ArrayElement_i.h class_Array_i.h class_String_i.h dependencies.h

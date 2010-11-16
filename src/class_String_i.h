/*
 *  Copyright 2010  Trey Dempsey
 *
 *  libtgcl is distributed under the terms of the GNU
 *  Lesser General Public License.
 * 
 *  This file is part of libtgcl.
 *
 *  libtgcl is free software: you can redistribute it
 *  and/or modify it under the terms of the GNU Lesser General Public
 *  License as published by the Free Software Foundation, either
 *  version 3 of the License, or (at your option) any later version.
 *
 *  libtgcl is distributed in the hope that it will be
 *  useful, but WITHOUT ANY WARRANTY; without even the implied
 *  warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *  See the GNU Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public
 *  License along with libtgcl.  If not, see
 *  <http://www.gnu.org/licenses/>.
 ***********************************************************************/

#ifndef _CLASS_STRING_I_H_
#define _CLASS_STRING_I_H_

#include <errno.h>
#include <stdlib.h>
#include <string.h>

#include "class_String.h"


/* Class Methods */
int                   class_String(void);
String *              new_String(char * cstr, size_t length);
String *              alloc_String(size_t size);

/* Instance Methods */
static String *       String_init(String * self, char * cstr, size_t size, size_t length);
static String *       String_free(String * self);

static String *       String_set_blk_size(String * self, size_t new_blk_size);

static void           String_Array_free(void * string);
static String *       String_append(String * self, String * other);
static String *       String_append_cstr(String * self, char * cstr, size_t append_length);
static String *       String_append_slice(String * self, String * other, size_t slice_length);
static size_t         String_chomp(String * self);
static int            String_compare(String * self, String * other);
static int            String_compare_cstr(String * self, char * other, size_t other_length);
static int            String_comparen(String * self, String * other, size_t compare_length);
static String *       String_dup(String * self);
static String *       String_downcase(String * self);
static String *       String_each_line(String * self);
static size_t         String_eol(String * self);
static String *       String_extend(String * self, size_t add);
static unsigned char  String_hex_to_byte(String * self);
static int            String_ishex(String * self);
static String *       String_join(String * self, Array * array, String * separator);
static String *       String_ltrim(String * self);
static String *       String_rtrim(String * self);
static String *       String_slice(String * self, String * other, size_t slice_length);
static Array *        String_split(String * self, String * delimiter);
static int            String_to_i(String * self);
static String *       String_truncate(String * self);
static String *       String_upcase(String * self);
static size_t         String_utf8_length(String * self);


/* Global Variables */
String *              null_String = NULL;

static String         _null_String;
static char           _null_String_string[] = "\0";
static StringMethods  String_methods;


#define UTF8_ONEMASK ((size_t)(-1) / 0xFF)

#endif /* not _CLASS_STRING_I_H_ */

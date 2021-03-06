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

#ifndef _CLASS_STRING_H_
#define _CLASS_STRING_H_

/* Dependencies */
#include <class_Array.h>


/* Class Instance */
typedef struct String {
  struct String **        handle;
  char *                  string;
  size_t                  size;
  size_t                  length;
  size_t                  position;
  size_t                  blk_size;

  struct String *         _line;

  /* Instance Methods */
  struct StringMethods *  m;
} String;


typedef struct StringMethods {
  String *      (*init)(String * self, char * cstr, size_t size, size_t length);
  String *      (*free)(String * self);

  /* Properties */
  String *      (*set_blk_size)(String * self, size_t new_blk_size);

  /* Instance Methods */
  void          (*Array_free)(void * string);
  String *      (*append)(String * self, String * other);
  String *      (*append_cstr)(String * self, char * cstr, size_t append_length);
  String *      (*append_slice)(String * self, String * other, size_t slice_length);
  size_t        (*chomp)(String * self);
  int           (*compare)(String * self, String * other);
  int           (*compare_cstr)(String * self, char * other, size_t other_length);
  int           (*comparen)(String * self, String * other, size_t compare_length);
  String *      (*dup)(String * self);
  String *      (*downcase)(String * self);
  String *      (*each_line)(String * self);
  size_t        (*eol)(String * self);
  String *      (*extend)(String * self, size_t add);
  unsigned char (*hex_to_byte)(String * self);
  int           (*ishex)(String * self);
  String *      (*join)(String * self, Array * array, String * separator);
  String *      (*ltrim)(String * self);
  String *      (*rtrim)(String * self);
  String *      (*slice)(String * self, String * other, size_t slice_length);
  Array *       (*split)(String * self, String * delimiter);
  int           (*to_i)(String * self);
  String *      (*truncate)(String * self);
  String *      (*upcase)(String * self);
  size_t        (*utf8_length)(String * self);
  int           (*utf8_valid)(String * self);
} StringMethods;


#ifndef _CLASS_STRING_I_H_
extern int      class_String(void);
extern String * new_String(char * cstr, size_t length);
extern String * alloc_String(size_t size);

extern String * null_String;
#endif /* not _CLASS_STRING_I_H_ */

#endif /* not _CLASS_STRING_H_ */

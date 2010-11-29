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

#include "dependencies.h"
#include "class_Array_i.h"

/*
 * Class Methods
 ***************/

int
class_Array(void)
{
  if(null_Array == NULL) {
    /* Dependencies */
    class_ArrayElement();

    /* Methods */
    Array_methods.init            = Array_init;
    Array_methods.free            = Array_free;

    Array_methods.append          = Array_append;
    Array_methods.append_element  = Array_append_element;
    Array_methods.compare         = Array_compare;
    Array_methods.concat          = Array_concat;
    Array_methods.difference      = Array_difference;
    Array_methods.dup             = Array_dup;
    Array_methods.each            = Array_each;
    Array_methods.extend          = Array_extend;
    Array_methods.get             = Array_get;
    Array_methods.include         = Array_include;
    Array_methods.intersection    = Array_intersection;
    Array_methods.join            = Array_join;
    Array_methods.last            = Array_last;
    Array_methods.reset_each      = Array_reset_each;
    Array_methods.repetition      = Array_repetition;
    Array_methods.set             = Array_set;

    /* Special vars */
    null_Array                    = &_null_Array;
    null_Array->handle            = &null_Array;
    null_Array->m                 = &Array_methods;
    Array_init(null_Array);
  }

  return 1;
}


Array *
new_Array(void)
{
  Array * self;

  if(null_Array == NULL) {
    class_Array();
  }

  self = alloc_Array();
  self->m->init(self);

  return self;
}


Array *
alloc_Array(void)
{
  Array ** handle;

  /* Allocate */
  handle = malloc(sizeof(Array *));
  if(handle == NULL) {
    handle = null_Array->handle;
    goto error;
  }

  *handle = malloc(sizeof(Array));
  if(*handle == NULL) {
    free(handle);
    handle = null_Array->handle;
    goto error;
  }
  memset(*handle, 0, sizeof(Array));
  (*handle)->handle = handle;
  (*handle)->m = &Array_methods;

error:

  if(errno == ENOMEM) {
    perror("alloc_Array()");
  }

  return *handle;
}


static Array *
Array_init(Array * self)
{
  /* Variables */
  self->blk_size = 64;
  self->length = 0;
  self->position = 0;
  self->current_element = null_ArrayElement;
  self->auto_free = NULL;

  if(self != null_Array) {
    self->size = self->blk_size;
    self->elements = malloc(self->blk_size * sizeof(ArrayElement *));
    if(self->elements == NULL) {
      self->elements = null_ArrayElement->handle;
      goto error;
    }

    for(self->position = 0; self->position < self->size; self->position++) {
      self->elements[self->position] = null_ArrayElement;
    }
  }
  else {
    self->size = 0;
    self->elements = null_ArrayElement->handle;
  }

error:

  if(errno == ENOMEM) {
    perror("Array_init()");
  }

  return self;
}


static Array *
Array_free(Array * self)
{
  int i;

  if(self != null_Array) {
    if(self->auto_free != NULL) {
      for(i = 0; i < self->length; i++) {
        self->auto_free(self->elements[i]->data);
        self->elements[i]->data = NULL;
      }
    }

    for(i = 0; i < self->size; i++) {
      self->elements[i]->m->free(self->elements[i]);
    }
    free(self->elements);
    free(self->handle);
    free(self);
  }

  return null_Array;
}


/*
 * Public Instance Methods
 *************************/

static Array *
Array_append(Array * self, void * data)
{
  ArrayElement * new_element;

  if(self != null_Array) {
    if((self->length + 1) >= self->size) {
      self->m->extend(self, 1);
    }

    new_element = new_ArrayElement(data);

    self->elements[self->length] = new_element;
    self->length++;
  }

  return self;
}


static Array *
Array_append_element(Array * self, ArrayElement * element)
{
  if(self != null_Array) {
    if((self->length + 1) >= self->size) {
      self->m->extend(self, 1);
    }

    self->elements[self->length] = element;
    self->length += 1;
  }

  return self;
}


static int
Array_compare(Array * self, Array * other)
{
  /* TODO Complete */
  return (self == other) ? 1 : 0;
}


static Array *
Array_concat(Array * self, Array * other)
{
  if(self != null_Array) {
    other->m->reset_each(other);
    while(other->m->each(other) != null_ArrayElement) {
      self->m->append_element(self, other->current_element->m->dup(other->current_element));
    }
  }

  return self;
}


static Array *
Array_difference(Array * self, Array * other)
{
  Array * new_array;

  if(self != null_Array) {
    new_array = new_Array();

    self->m->reset_each(self);
    while(self->m->each(self) != null_ArrayElement) {
      if(other->m->include(other, self->current_element) == null_ArrayElement) {
        new_array->m->append(new_array, self->current_element->m->dup(self->current_element));
      }
    }

    return new_array;
  }
  else {
    return null_Array;
  }
}


static Array *
Array_dup(Array * self)
{
  Array * new_array;

  new_array = new_Array();
  if(self != null_Array) {
    new_array->blk_size = self->blk_size;
    new_array->auto_free = self->auto_free;
    self->m->reset_each(self);
    while(self->m->each(self) != null_ArrayElement) {
      new_array->m->append_element(new_array, self->current_element->m->dup(self->current_element));
    }

    return new_array;
  }
  else {
    return null_Array;
  }
}


static ArrayElement *
Array_each(Array * self)
{
  if(self != null_Array
     && self->length > 0) {
    if(self->position >= self->length) {
      self->position = -1;
      self->current_element = null_ArrayElement;
    }
    else {
      self->position++;
      self->current_element = self->elements[self->position];
    }

    return self->current_element;
  }
  else {
    return null_ArrayElement;
  }
}


static Array *
Array_extend(Array * self, size_t add)
{
  size_t          new_size;
  ArrayElement ** extended;
  int             i;

  if(add < 1) {
    return self;
  }

  if(self != null_Array) {
    if(self->blk_size == 0) {
      new_size = self->size + add;
    }
    else {
      new_size = (self->size + add) / self->blk_size;
      new_size = (((self->size + add) % self->blk_size) == 0) ? new_size : new_size + 1;
      new_size = new_size * self->blk_size;
    }

    extended = realloc(self->elements, new_size * sizeof(ArrayElement *));
    if(extended == NULL) {
      perror("Array_extend()\n");
    }
    else {
      self->elements = extended;

      /* Initialize the new elements to null_ArrayElement */
      for(i = self->size; i < new_size; i++) {
        self->elements[i] = null_ArrayElement;
      }

      self->size = new_size;
    }
  }

  return self;
}


static ArrayElement *
Array_get(Array * self, size_t index)
{
  if(self != null_Array
     && index >= 0
     && index < self->length) {
    return self->elements[index];
  }
  else {
    return null_ArrayElement;
  }
}


static ArrayElement *
Array_include(Array * self, ArrayElement * element)
{
  if(self != null_Array) {
    self->m->reset_each(self);
    while(self->m->each(self) != null_ArrayElement) {
      if(self->current_element->m->compare(self->current_element, element)) {
        break;
      }
    }
  }

  return self->current_element;
}


static Array *
Array_intersection(Array * self, Array * other)
{
  Array * new_array;

  if(self != null_Array) {
    new_array = new_Array();

    self->m->reset_each(self);
    while(self->m->each(self) != null_ArrayElement) {
      if(other->m->include(other, self->current_element) != null_ArrayElement) {
        new_array->m->append(new_array, self->current_element->m->dup(self->current_element));
      }
    }

    return new_array;
  }
  else {
    return null_Array;
  }
}


static void *
Array_join(Array * self, void * target, void * (*block)(Array * array, ArrayElement * element, void * target))
{
  void * r = NULL;

  if(self != null_Array) {
    self->m->reset_each(self);
    while(self->m->each(self) != null_ArrayElement) {
      r = block(self, self->current_element, target);
    }
    
    return r;
  }
  else {
    return self;
  }
}


static ArrayElement *
Array_last(Array * self)
{
  ArrayElement * last = null_ArrayElement;

  if(self != null_Array && self->length > 0) {
    last = self->elements[self->length - 1];
  }

  return last;
}


static Array *
Array_reset_each(Array * self)
{
  if(self != null_Array) {
    self->current_element = null_ArrayElement;
    self->position = -1;
  }

  return self;
}


static Array *
Array_repetition(Array * self, int times)
{
  Array * new_array;
  ArrayElement * element;
  int i, new_length;

  if(self != null_Array) {
    new_array = new_Array();
    new_length = self->length * times;

    self->m->reset_each(self);
    for(i = 0; i < new_length; i++) {
      element = self->m->each(self);
      if(element == null_ArrayElement) {
        element = self->m->each(self);
      }
      new_array->m->append(new_array, element->m->dup(element));
    }

    return new_array;
  }
  else {
    return null_Array;
  }
}


static Array *
Array_set(Array * self, size_t index, ArrayElement * element)
{
  if(self != null_Array
     && index >= 0
     && index < self->length) {

    if(self->auto_free != NULL
       && self->elements[index] != null_ArrayElement) {
      self->auto_free(self->elements[index]->data);
      self->elements[index]->data = NULL;
    }
    self->elements[index]->m->free(self->elements[index]);

    self->elements[index] = element;
  }

  return self;
}

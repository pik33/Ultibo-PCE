/*****************************************************************************
 * libini                                                                    *
 *****************************************************************************/

/*****************************************************************************
 * File name:     src/libini/value.c                                         *
 * Created:       2001-08-24 by Hampa Hug <hampa@hampa.ch>                   *
 * Last modified: 2004-02-16 by Hampa Hug <hampa@hampa.ch>                   *
 * Copyright:     (C) 2001-2004 Hampa Hug <hampa@hampa.ch>                   *
 *****************************************************************************/

/*****************************************************************************
 * This program is free software. You can redistribute it and / or modify it *
 * under the terms of the GNU General Public License version 2 as  published *
 * by  the Free Software Foundation.                                         *
 *                                                                           *
 * This program is distributed in the hope  that  it  will  be  useful,  but *
 * WITHOUT  ANY   WARRANTY,   without   even   the   implied   warranty   of *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU  General *
 * Public License for more details.                                          *
 *****************************************************************************/

/* $Id$ */


#include "libini.h"


ini_val_t *ini_val_new (const char *name)
{
  ini_val_t *val;

  val = (ini_val_t *) malloc (sizeof (ini_val_t));
  if (val == NULL) {
    return (NULL);
  }

  val->name = (char *) malloc (strlen (name) + 1);
  if (val->name == NULL) {
    free (val);
    return (NULL);
  }

  strcpy (val->name, name);

  val->next = NULL;
  val->type = INI_VAL_LNG;
  val->val.lng = 0;

  return (val);
}

static
void ini_val_del_val (ini_val_t *val)
{
  if (val->type == INI_VAL_STR) {
    free (val->val.str);
    val->val.str = NULL;
  }
}

void ini_val_del (ini_val_t *val)
{
  if (val != NULL) {
    if (val->next != NULL) {
      ini_val_del (val->next);
    }

    ini_val_del_val (val);

    free (val->name);
    free (val);
  }
}

const char *ini_val_get_name (const ini_val_t *val)
{
  return (val->name);
}

ini_type_t ini_val_get_type (const ini_val_t *val)
{
  return (val->type);
}

ini_val_t *ini_val_get_next (const ini_val_t *val)
{
  return (val->next);
}

ini_val_t *ini_val_find_next (const ini_val_t *val, const char *name)
{
  if (val != NULL) {
    val = val->next;
  }

  while (val != NULL) {
    if (strcmp (val->name, name) == 0) {
      return ((ini_val_t *) val);
    }

    val = val->next;
  }

  return (NULL);
}

void ini_val_set_lng (ini_val_t *val, long v)
{
  ini_val_del_val (val);

  val->type = INI_VAL_LNG;
  val->val.lng = v;
}

void ini_val_set_dbl (ini_val_t *val, double v)
{
  ini_val_del_val (val);

  val->type = INI_VAL_DBL;
  val->val.dbl = v;
}

void ini_val_set_str (ini_val_t *val, const char *v)
{
  ini_val_del_val (val);

  val->type = INI_VAL_STR;

  val->val.str = malloc (strlen (v) + 1);
  if (val->val.str == NULL) {
    return;
  }

  strcpy (val->val.str, v);
}

int ini_val_get_lng (const ini_val_t *val, long *v)
{
  if (val->type != INI_VAL_LNG) {
    return (1);
  }

  *v = val->val.lng;

  return (0);
}

int ini_val_get_dbl (const ini_val_t *val, double *v)
{
  if (val->type != INI_VAL_DBL) {
    return (1);
  }

  *v = val->val.dbl;

  return (0);
}

const char *ini_val_get_str (const ini_val_t *val)
{
  if (val->type != INI_VAL_STR) {
    return (NULL);
  }

  return (val->val.str);
}

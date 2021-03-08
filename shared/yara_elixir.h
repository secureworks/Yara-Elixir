#pragma once

#include <errno.h>
#include <stdio.h>
#include <yara.h>
#include <erl_nif.h>

// Wraps the Yara initializer
extern int init_yara();

// Wraps the Yara finalizer
extern int destroy_yara();

void debug(const char *errstr, ...);

#define debug_func_start debug("%s:%d (%s)\n", __FILE__, __LINE__, __func__)

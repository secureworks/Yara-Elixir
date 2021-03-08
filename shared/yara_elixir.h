#pragma once

#include <stdio.h>
#include <yara.h>
#include <erl_nif.h>

// Wraps the Yara initializer
extern int init_yara();

// Wraps the Yara finalizer
extern int destroy_yara();

void debug(const char *errstr, ...);

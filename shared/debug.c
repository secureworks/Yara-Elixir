#include "yara_elixir.h"

#ifdef DEBUG
void debug(const char *errstr, ...) {
    va_list ap;
    va_start(ap, errstr);
    vfprintf(stderr, errstr, ap); 
    va_end(ap);
}
#else
void debug(const char *errstr, ...) {
}
#endif

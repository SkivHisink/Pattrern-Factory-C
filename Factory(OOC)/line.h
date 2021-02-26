#ifndef __line_h
#define __line_h

#include "point.h"

struct Line {
	const void* class;
	struct Point begin;
	struct Point end;
};

extern const void* Line;

#endif

#ifndef __rect_h
#define __rect_h

#include "point.h"

struct Rect {
	const void* class;
	struct Point begin;
	struct Point end;
};

extern const void* Rect;

#endif

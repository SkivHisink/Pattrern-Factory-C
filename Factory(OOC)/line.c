#include <stdio.h>
#include "line.h"
#include "new.h"

static void* Line_ctor(void* _self, va_list* app) {
	struct Line * self = _self;
	self->begin.x = va_arg(*app, int);
	self->begin.y = va_arg(*app, int);
	self->end.x = va_arg(*app, int);
	self->end.y = va_arg(*app, int);
	return self;
}

#define x(p)  (((struct Line*)(p)) -> begin.x)
#define y(p)  (((struct Line*)(p)) -> begin.y)
#define x1(p) (((struct Line*)(p)) -> end.x)
#define y1(p) (((struct Line*)(p)) -> end.y)

static void Line_draw(const void* _self)
{
	const struct Line* self = _self;
	printf("line at (%d, %d), (%d, %d)\n", x(self), y(self), x1(self), y1(self));
}

static const struct Class _Line = {
	sizeof(struct Line),      // size
	Line_ctor,                // ctor
	0,                          // dtor
	Line_draw                 // draw
};

const void* Line = &_Line;

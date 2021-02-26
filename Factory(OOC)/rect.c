#include <stdio.h>
#include "rect.h"
#include "new.h"
#include "point.h"
static void* Rect_ctor(void* _self, va_list* app) {
	struct Rect* self = _self;
	self->begin.x = va_arg(*app, int);
	self->begin.y = va_arg(*app, int);
	self->end.x = va_arg(*app, int);
	self->end.y = va_arg(*app, int);
	//self->begin = (struct Point*)malloc(sizeof(struct Point));
	//self->end = (struct Point*)malloc(sizeof(struct Point));
	return self;
}

#define x(p)  (((struct Rect*)(p)) -> begin.x)
#define y(p)  (((struct Rect*)(p)) -> begin.y)
#define x1(p) (((struct Rect*)(p)) -> end.x)
#define y1(p) (((struct Rect*)(p)) -> end.y)

static void Rect_draw(const void* _self)
{
	const struct Rect* self = _self;
	printf("rect at (%d, %d), (%d, %d)\n", x(self), y(self), x1(self), y1(self));
}

static const struct Class _Rect = {
	sizeof(struct Rect),      // size
	Rect_ctor,                // ctor
	0,                          // dtor
	Rect_draw                 // draw
};

const void* Rect = &_Rect;

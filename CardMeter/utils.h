#ifndef UTILS_H_
#define UTILS_H_

#define _SET(B, b)		(B) |= 1<<(b)
#define _CLR(B, b)		(B) &= ~(1<<(b))
#define _TOG(B, b)		(B) ^= 1<<(b)
#define _CHG(B, b, v)	(B) = ((B) & ~(1<<(b))) | ((v)<<(b))
#define _GET(B, b)		(((B)>>(b)) & 1)

#define _MIN(a,b)   (((a)<(b)) ?  (a):(b))
#define _MAX(a,b)   (((a)>(b)) ?  (a):(b))
#define _ABS(a)     (((a)< 0 ) ? -(a):(a))
#define _CLIP(min, v, max)	_MIN(_MAX(v, min), max)


#endif /* UTILS_H_ */
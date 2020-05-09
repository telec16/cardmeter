#ifndef UTILS_H_
#define UTILS_H_

typedef enum{FALSE=0, TRUE} boolean;

#define _SET_PIN(p)		_SET((*((p).port)).OUT, ((p).pin))
#define _CLR_PIN(p)		_CLR((*((p).port)).OUT, ((p).pin))
#define _TOG_PIN(p)		_TOG((*((p).port)).OUT, ((p).pin))
#define _CHG_PIN(p, v)	_CHG((*((p).port)).OUT, ((p).pin), v)
#define _GET_PIN(p)		_GET((*((p).port)).IN, ((p).pin))

#define _SET(B, b)		(B) |= 1<<(b)
#define _CLR(B, b)		(B) &= ~(1<<(b))
#define _TOG(B, b)		(B) ^= 1<<(b)
#define _CHG(B, b, v)	(B) = ((B) & ~(1<<(b))) | ((v)<<(b))
#define _GET(B, b)		(((B)>>(b)) & 1)

#define _MIN(a,b)   (((a)<(b)) ?  (a):(b))
#define _MAX(a,b)   (((a)>(b)) ?  (a):(b))
#define _ABS(a)     (((a)< 0 ) ? -(a):(a))
#define _CLIP(min, v, max)	_MIN(_MAX(v, min), max)


#define _SW1	_GET(PORTB.IN, 0)
#define _SW2	_GET(PORTB.IN, 1)
#define _SW3	_GET(PORTB.IN, 2)
#define _SW4	_GET(PORTB.IN, 3)

#endif /* UTILS_H_ */
#ifndef __JIN_UTILS_H
#define __JIN_UTILS_H

#define min(a,b)                (((a) < (b)) ? (a) : (b)) 
#define max(a,b)                (((a) > (b)) ? (a) : (b)) 
#define clamp(a, mi,ma)            min(max(a,mi),ma)       

#define within(a,min,max)        (a >= min && a <= max)
#define without(a,min,max)        (a < min || a > max)

#endif
/**
* 
*/
#ifndef JIN_LIL_ENDIAN && JIN_BIG_ENDIAN  

#define JIN_LIL_ENDIAN  2
#define JIN_BIG_ENDIAN  4

#endif

#ifndef JIN_BYTEORDER
#ifdef __linux__
#include <endian.h>
#define JIN_BYTEORDER  __BYTE_ORDER
#else /* __linux__ */
#if defined(__hppa__) || \
    defined(__m68k__) || defined(mc68000) || defined(_M_M68K) || \
    (defined(__MIPS__) && defined(__MISPEB__)) || \
    defined(__ppc__) || defined(__POWERPC__) || defined(_M_PPC) || \
    defined(__sparc__)
#define JIN_BYTEORDER   JIN_BIG_ENDIAN
#else
#define JIN_BYTEORDER   JIN_LIL_ENDIAN
#endif
#endif /* __linux__ */
#endif /* !SDL_BYTEORDER */
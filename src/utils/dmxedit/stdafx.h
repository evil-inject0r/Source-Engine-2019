#pragma once

#include <stdio.h>

#if _MSC_VER < 1900
	#define stdin  (&__iob_func()[0])
	#define stdout (&__iob_func()[1])
	#define stderr (&__iob_func()[2])
#else
	#define stdin  (__acrt_iob_func(0))
	#define stdout (__acrt_iob_func(1))
	#define stderr (__acrt_iob_func(2))
#endif // _MSC_VER < 1900
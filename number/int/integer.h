#if INT_MAX < 3000
	typedef short integer
#elif INT_MAX <= 10000
	typedef int integer
#else
	typedef long integer
#endif

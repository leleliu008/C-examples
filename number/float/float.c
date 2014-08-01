/* 测试float.h头文件中定义的宏 */

#include<stdio.h>
#include<float.h>

int main() {
	printf("sizeof(float) = %d\n", sizeof(float));
	printf("FLT_MAX = %e\n", FLT_MAX);
	printf("FLT_MIN = %e\n", FLT_MIN);
	printf("FLT_MAX_EXP = %d\n", FLT_MAX_EXP);
	printf("FLT_MIN_EXP = %d\n", FLT_MIN_EXP);
	printf("FLT_MAX_10_EXP = %d\n", FLT_MAX_10_EXP);
	printf("FLT_MIN_10_EXP = %d\n", FLT_MIN_10_EXP);
	printf("FLT_EPSILON = %e\n", FLT_EPSILON);
	printf("FLT_MANT_DIG = %d\n", FLT_MANT_DIG);
	printf("FLT_DIG = %d\n", FLT_DIG);
	printf("FLT_RADIX = %d\n", FLT_RADIX);
	printf("FLT_ROUNDS = %d\n", FLT_ROUNDS);
	printf("\n");

	printf("sizeof(double) = %d\n", sizeof(double));
	printf("DBL_MAX = %e\n", DBL_MAX);
	printf("DBL_MIN = %e\n", DBL_MIN);
	printf("DBL_MAX_EXP = %d\n", DBL_MAX_EXP);
	printf("DBL_MIN_EXP = %d\n", DBL_MIN_EXP);
	printf("DBL_MAX_10_EXP = %d\n", DBL_MAX_10_EXP);
	printf("DBL_MIN_10_EXP = %d\n", DBL_MIN_10_EXP);
	printf("DBL_EPSILON = %e\n", DBL_EPSILON);
	printf("DBL_MANT_DIG = %d\n", DBL_MANT_DIG);
	printf("DBL_DIG = %d\n", DBL_DIG);
	printf("\n");

	printf("sizeof(long double) = %d\n", sizeof(long double));
	printf("LDBL_MAX = %le\n", LDBL_MAX);
	printf("LDBL_MIN = %le\n", LDBL_MIN);
	printf("LDBL_MAX_EXP = %d\n", LDBL_MAX_EXP);
	printf("LDBL_MIN_EXP = %d\n", LDBL_MIN_EXP);
	printf("LDBL_MAX_10_EXP = %d\n", LDBL_MAX_10_EXP);
	printf("LDBL_MIN_10_EXP = %d\n", LDBL_MIN_10_EXP);
	printf("LDBL_EPSILON = %e\n", LDBL_EPSILON);
	printf("LDBL_MANT_DIG = %d\n", LDBL_MANT_DIG);
	printf("LDBL_DIG = %d\n", LDBL_DIG);

	return 0;
}

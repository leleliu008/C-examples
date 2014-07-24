//根据条件编译定义统一的类型
#ifdef XX
typedef int Integer
#elif xx
typedef int Integer
#else
typedef long Integer
#endif

//简化结构体、共用体、枚举类型的使用
typedef struct {
	char name[10];
	int age;
	char sex;
} Person;

typedef union {
	int x;
	char y;
} XX;

//定义bool类型
typedef enum {
	false,
	true
} bool;

//定义数组类型
typedef int ARRAY_INT_10[10]

//定义字符串类型
typedef char* String


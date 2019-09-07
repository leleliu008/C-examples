//使用gdb调试，测试共用体的字节对齐问题
#pragma pack(1)
typedef union {
	char* a;
	char b[10];
} XX;

int main() {
	XX x;
	char a = 65;
	x.a = &a;
	//在这里设置断点

	x.b[0] = 'A';
	x.b[1] = 'B';
	x.b[2] = 'C';
	x.b[3] = 'D';
	x.b[4] = '\0';
	//在这里设置断点
	
	return 0;
}

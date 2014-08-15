#include<unistd.h>
#include<stdio.h>

int main(int argc, char * argv[]) {
	char ch;
		
	while(-1 != (ch = getopt(argc, argv, "a:bcd"))) {
		switch(ch) {
			case 'a':
				printf("%s\n", "a");
				if(NULL != optarg) {
					printf("value of option a is %s\n", optarg);
				}
				break;
			case 'b':
				printf("%s\n", "b");
				break;
			case 'c':
				printf("%s\n", "c");
				break;
			case 'd':
				printf("%s\n", "d");
				break;
			default:
				break;
		}
	}
	
	return 0;
}

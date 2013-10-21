#include "libhello.h"
#include "main1.h"
int main(){
	printf("test libhello:\n");
	hello(",i am main and link libhello to generate hello");
	printf("test main1:\n");
	main1();
	return 0;
}

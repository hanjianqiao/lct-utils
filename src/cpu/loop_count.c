#include <stdio.h>
#include <stdlib.h>

int main(){
	int count = 100000000;
	int loop = 0;
	while(1){
		for(int i = 0; i < count; i++){
			// do nothing
		}
		printf("loop: %d\n", loop++);
	}
	return 0;
}

#include<stdio.h>

int 
main(void )
{
	FILE *fp;
	fp = fopen("fopen", "w+");
	int  data[15] = {1,23,45,65,6576,57,8,768,};
	if(fwrite(data, sizeof(float), 10, fp) != 10)
		printf("fwrite error");
	int res[15];

	fread(res, sizeof(float), 10, fp);
	for(int i = 1; i < 10; i++)
		printf("% 5i", res[i]);

}

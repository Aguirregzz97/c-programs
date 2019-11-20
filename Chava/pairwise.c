#include <stdio.h>

int main(){
	static const char filename[] = "input.txt";
  FILE *file = fopen(filename, "r");
	char line[256]; /* or other suitable maximum line size */
	int n;
	fscanf(file, "%d", &n);
	int i,a[n];
	for(i=0;i<n;i++){
    fscanf(file, "%d", &a[i]);
	}
	int po = 1;
	long long res=0;
	while(po<=1000000000){
		long long count = 0;
		for(i=0;i<n;i++){
			if((a[i]&po)){
				count++;
			}
		}
		res+=((count - 1) * count) / 2 * po;
		po <<= 1;
	}
	fclose(file);
  file = fopen("output.txt", "w+");
  fprintf(file, "%lld\n", res);
  fclose(file);
	
	return 0;
}
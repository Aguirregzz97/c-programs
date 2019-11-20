#include <stdio.h>

int mo[400000], re[400000][3];

void cre(int r, int l1,int l2){
	if(l1==l2){
		re[r][0]=1;
		return;
	}
	int m =(l1+l2)/2;
	re[r][0] = l2-l1+1;
	cre(r<<1,l1,m);
	cre((r<<1)+1,m+1,l2);
}

void add(int r, int l1,int l2, int q1,int q2,int q){
	if(q1>l2 || q2< l1){
		return;
	}
	if(q1<=l1&&q2>=l2){
		mo[r] = (mo[r]+q)%3;
		return;
	}
	int m=(l1+l2)/2;
	int le= r<<1;
	int ri = le|1;
	add(le,l1,m,q1,q2,q);
	add(ri,m+1,l2,q1,q2,q);
	int i;
	for(i=0;i<3;i++){
		re[r][(i+mo[le])%3]=re[le][i];
	}
	for(i=0;i<3;i++){
		re[r][(i+mo[ri])%3]+=re[ri][i];
	}
}

int que(int r, int l1,int l2, int q1,int q2){
	if(q1>l2 || q2< l1){
		return 0;
	}
	if(q1<=l1&&q2>=l2){
		return re[r][(3-mo[r])%3];
	}
	int m=(l1+l2)/2;
	int le= r<<1;
	int ri = le|1;
	if(mo[r]){
		add(le,l1,m,l1,m,mo[r]);
		add(ri,m+1,l2,m+1,l2,mo[r]);
		int i;
		for(i=0;i<3;i++){
			re[r][(i+mo[le])%3]=re[le][i];
		}
		for(i=0;i<3;i++){
			re[r][(i+mo[ri])%3]+=re[ri][i];
		}
		mo[r]=0;
	}
	return que(le,l1,m,q1,q2) + que(ri,m+1,l2,q1,q2);
}
int main(){
	static const char filename[] = "input.txt";
  FILE *file = fopen(filename, "r");
	char line[256]; /* or other suitable maximum line size */
	int n,q,t,l,r;
	fscanf(file, "%d %d",&n,&q);
	cre(1,0,n-1);
  int results[q];
  int i = 0;
	while(q--){
		fscanf(file, "%d %d %d",&t,&l,&r);
		if(t){
			results[i++] = que(1,0,n-1,l,r);
		}
		else {
			add(1,0,n-1,l,r,1);
		}
	}
	fclose(file);
  file = fopen("results.txt", "w+");
  int j = 0;
  for (; j < i; j++) {
    sprintf(line, "%d", results[j]);
    char *tmp = line;
    printf("%s", tmp);
    fprintf(file, "%s\n", tmp);
  }	
  fclose(file);
	return 0;
}
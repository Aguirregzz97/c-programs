#include <stdio.h>
#include <fcntl.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#define RUNNING_DIR	"/github/c-programs/Fiacro/"
#define LOCK_FILE	"exampled.lock"
#define LOG_FILE	"lista.txt"

int mo[400000], re[400000][3];


void log_message(char *filename, char *message) {
	FILE *logfile;

	logfile=fopen(filename,"a");
	if(!logfile) return;
	fprintf(logfile,"%s\n",message);
	fclose(logfile);
}

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

static void signalHandler(int sig) {

	switch(sig) {
		case SIGUSR1:
    	  log_message(LOG_FILE,"USR1 signal catched");
        	static const char filename[] = "input.txt";
          FILE *file = fopen(filename, "r");
          char line[256]; /* or other suitable maximum line size */
          int n,q,t,l,r;
          fscanf(file, "%d %d",&n,&q);
          cre(1,0,n-1);
          int results[100000];
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
          file = fopen("output.txt", "w+");
          int j = 0;
          for (; j < i; j++) {
            sprintf(line, "%d", results[j]);
            char *tmp = line;
            printf("%s", tmp);
            log_message(LOG_FILE, tmp);
            fprintf(file, "%s\n", tmp);
          }	
          fclose(file);
			break;
		case SIGUSR2:
			log_message(LOG_FILE,"USR2 signal catched");
			exit(0);
			break;
	}
}

void daemonize() {
	int i,lfp;
	char str[10];

//	if(getppid()!=1) return; /* already a daemon */
	i=fork();
	if (i<0) exit(1); /* fork error */
	if (i>0) exit(0); /* parent exits */
	/* child (daemon) continues */
	setsid(); /* obtain a new process group */
	for (i=getdtablesize();i>=0;--i) close(i); /* close all descriptors */
	i=open("/dev/null",O_RDWR); dup(i); dup(i); /* handle standart I/O */
	umask(027); /* set newly created file permissions */
	chdir(RUNNING_DIR); /* change running directory */
	lfp=open(LOCK_FILE,O_RDWR|O_CREAT,0640);
	if (lfp<0) exit(1); /* can not open */
	if (lockf(lfp,F_TLOCK,0)<0) exit(0); /* can not lock */
	/* first instance continues */
	sprintf(str,"%d\n",getpid());
	write(lfp,str,strlen(str)); /* record pid to lockfile */
	signal(SIGCHLD,SIG_IGN); /* ignore child */
	signal(SIGTSTP,SIG_IGN); /* ignore tty signals */
	signal(SIGTTOU,SIG_IGN);
	signal(SIGTTIN,SIG_IGN);
	signal(SIGUSR1,signalHandler); /* catch hangup signal */
	signal(SIGUSR2,signalHandler); /* catch kill signal */
}

int main() {
	int i=0;
	FILE *arch;
	daemonize();
	while(1) {
		arch=fopen("lista.txt","a+");
		if(arch==NULL)
			return(1);
		i++;
		fprintf(arch,"%i.- I'm printing this to a file \n",i);
		fclose(arch);
		sleep(5);
	} /* run */
	return(0);
}


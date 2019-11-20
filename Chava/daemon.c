#include <stdio.h>
#include <fcntl.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#define RUNNING_DIR	"/github/c-programs/Fiacro/"
#define LOCK_FILE	"exampled.lock"
#define LOG_FILE	"lista.txt"


void log_message(char *filename, char *message) {
	FILE *logfile;

	logfile=fopen(filename,"a");
	if(!logfile) return;
	fprintf(logfile,"%s\n",message);
	fclose(logfile);
}

static void signalHandler(int sig) {

	switch(sig) {
		case SIGUSR1:
    	  log_message(LOG_FILE,"USR1 signal catched");
        	static const char filename[] = "input.txt";
          FILE *file = fopen(filename, "r");
          char line[256]; /* or other suitable maximum line size */
          int n;
          fscanf(file, "%d", &n);
          int i,a[1000];
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


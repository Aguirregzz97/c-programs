// Andres Aguirre Gonzalez
// A01039656
// Num factorial

#include <stdio.h>
#include <fcntl.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#define RUNNING_DIR	"/github/c-programs/P15/"
#define LOCK_FILE	"exampled.lock"
#define LOG_FILE	"lista.txt"

// Prints info in log file
void log_message(char *filename, char *message) {
	FILE *logfile;

	logfile=fopen(filename,"a");
	if(!logfile) return;
	fprintf(logfile,"%s\n",message);
	fclose(logfile);
}

// Handler of kill signal
static void signalHandler(int sig) {
	switch(sig) {
		case SIGUSR1:
			  log_message(LOG_FILE,"USR1 signal catched");
        int exponente[1000000];
      	int size;
        int t;
        static const char filename[] = "input.txt";
        FILE *file = fopen(filename, "r");
        char line[256]; /* or other suitable maximum line size */
        fgets(line, sizeof line, file);
        t = atoi(line);
        size = t;
        int i;
        int z = 0;
        int results[2];
        while (t--) {
        int n;
        fgets(line, sizeof line, file);
        n = atoi(line);
        memset(exponente, 0, sizeof exponente);
        while (n--) {
          int a;
          fgets(line, sizeof line, file);
          a = atoi(line);
          int r = sqrt(a);
          for (i=2; i<=r; i++) {
            if(a % i == 0) {
              while (a % i == 0) {
                a /= i;
                exponente[i] ++;
              }
              r = sqrt(a);
            }
          }
          if (a > 1) exponente[a] ++;
        }
        long long res = 1;
        for(i=2; i<1000000; i++){
          res *= (exponente[i] + 1);
        }
        results[z] = res;
        z++;
      }
      fclose(file);
      file = fopen("results.txt", "w+");
      for (int r = 0; r < size; r++) {
        sprintf(line, "%d", results[r]);
        char *tmp = line;
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


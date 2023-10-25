#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include "rsleep.h"

int pv = 5;

void coup(int sig){
	pv--;

	if(pv == 0){
		std::cout << getpid() << " est mort." << std::endl;
	}
	else{
		std::cout << "pv restants de " << getpid() << " = "  <<  pv << std::endl;
	}
}

void attaque(pid_t adversaire){
	/*sigset_t pv;
	sigfillset(&pv);

	sigdelset(&pv, SIGINT);*/

	signal(SIGINT, coup);
	int status;
	waitpid(adversaire, &status, WNOHANG);
	if(!WIFEXITED(status)){
		if(kill(adversaire, SIGINT) < 0)
			return;
	}
	else{
		return;
	}
	randsleep();
}

void defense(){
	signal(SIGINT, SIG_IGN);
	randsleep();
}

void combat(pid_t adversaire){
	while (pv > 0){
		defense();
		attaque(adversaire);
	}
}

int main () {
/*
	for (int i=1, j=N; i<=N && j==N; i++ ) {
		if(fork()!=0){
			nbfils++;
			//std::cout << "+1 fils" << std::endl;
			break;
		}
		else{
			nbfils = 0;
		}
		std::cout << " i:j " << i << ":" << j << std::endl;
		for (int k=1; k<=i && j==N ; k++) {
			if ( fork() == 0) {
				nbfils = 0;
				j=0;
				std::cout << " k:j " << k << ":" << j << std::endl;
			}
			else{
				nbfils++;
			}
		}
	}

	std::cout << "nb fils " << nbfils << std::endl;
	for(int i=0; i < nbfils; i++){
		wait(nullptr);
	}

	return 0;
	// il en faut 9 (1, 2, 3, 3)*/
}

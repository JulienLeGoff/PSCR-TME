#include <iostream>
#include <unistd.h>
#include <sys/wait.h>

int main () {
	int nbfils = 0;
	const int N = 3;
	std::cout << "main pid=" << getpid() << std::endl;

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
	// il en faut 9 (1, 2, 3, 3)
}

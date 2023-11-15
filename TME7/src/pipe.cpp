#include <iostream>
#include <sys/types.h>
#include <sys/wait.h>
#include <vector>
#include <string.h>



int main(int argc, char *argv[]) {
	// get command line arguments
	int pipePosition = -1;
	char* const* c_argv = (char*const*)argv;
	std::vector<char*> cmd1;
	std::vector<char*> cmd2;

	if(argc < 4) {
		std::cout << "Pas assez de paramètres" << std::endl;
		exit(1);
	}

	for(int i = 1; i < argc; ++i) {
		if(strcmp(argv[i], "|") == 0)
			pipePosition = i;

		if(pipePosition == -1)
			cmd1.push_back(argv[i]);
		else if(i > pipePosition)
			cmd2.push_back(argv[i]);
	}

	char* const* c_argv_cmd1 = (char*const*)cmd1.data();
	char* const* c_argv_cmd2 = (char*const*)cmd2.data();

	// création du pipe
	int tube[2];
	if(pipe(tube) == -1) {
		perror("Echec à la création du pipe");
		exit(1);
	}

	if(fork() != 0) { // père
		// exécution de la première commande (écriture dans le tube)
		if(dup2(tube[1], STDOUT_FILENO) == -1) {
			perror("Echec dup2 dans le père");
			exit(1);
		}

		close(tube[0]);
		close(tube[1]);

		if(execv(cmd1[0], c_argv_cmd1) == -1) {
			perror("Echec execv dans le père");
			exit(1);
		}
	}
	else { // fils
		// exécution de la deuxième commande (lecture dans le tube)
		if(dup2(tube[0], STDIN_FILENO) == -1) {
			perror("Echec dup2 dans le fils");
			exit(1);
		}

		close(tube[0]);
		close(tube[1]);

		if(execv(cmd2[0], c_argv_cmd2) == -1) {
			perror("Echec execv dans le fils");
			exit(1);
		}
	}
	return 0;
}

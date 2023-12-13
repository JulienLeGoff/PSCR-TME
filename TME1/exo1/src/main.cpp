#include "List.h"
#include <string>
#include <iostream>
#include <cstring>

int main () {

	std::string abc = "abc";
	char * str = new char [3];
	str[0] = 'a';
	str[1] = 'b';
	str[2] = 'c';
	size_t i = 0;

	if (! strcmp (str, abc.c_str())) {
		std::cout << "Equal !";
	}

	pr::List list;
	list.push_front(abc);
	list.push_front(abc);

	std::cout << "Liste : " << list << std::endl;
	std::cout << "Taille : " << list.size() << std::endl;

	// Affiche à l'envers
	// FAUTE : i est un unsigned int, donc i >= 0 est toujours vrai
	// on change >= en > pour que la boucle s'arrête
	// on retire le -1 dans i=list.size() car il est déjà à la bonne valeur
	// on ajoute dans List[i] un -1

	for (i= list.size() ; i > 0 ; i--) {
		std::cout << "elt " << i << ": " << list[i-1] << std::endl;
	}

	// liberer les char de la chaine
	// FAUTE : pas besoin de delete les char, ils sont dans un tableau
	/*for (char *cp = str ; *cp ; cp++) {
		delete cp;
	}*/

	// et la chaine elle meme
	// FAUTE : str est un tableau, il faut delete []
	delete [] str;

	// FAUTE : pas de return 0 dans main
	return 0;
}

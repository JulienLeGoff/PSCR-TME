#include <iostream>
#include <fstream>
#include <regex>
#include <chrono>

bool contient(std::vector<std::string> l, std::string mot){
	for(std::string m : l){
		if (mot == m){
			return true;
		}
	}
	return false;
}

int main () {
	using namespace std;
	using namespace std::chrono;

	ifstream input = ifstream("WarAndPeace.txt");

	auto start = steady_clock::now();
	cout << "Parsing War and Peace" << endl;

	size_t nombre_lu = 0;
	// prochain mot lu
	string word;
	// une regex qui reconnait les caractères anormaux (négation des lettres)
	regex re( R"([^a-zA-Z])");

	//vector<string> motsDiff = {};
	vector<pair<string,int>> motsDiff = {};

	while (input >> word) {
		// élimine la ponctuation et les caractères spéciaux
		word = regex_replace ( word, re, "");
		// passe en lowercase
		transform(word.begin(),word.end(),word.begin(),::tolower);

		/*if(!contient(motsDiff, word)){
			motsDiff.emplace_back(word);
		}*/

		bool trouve = false;
		for(pair<string,int> m : motsDiff){
			if (word == m.first){
				m.second++;
				trouve = true;
				break;
			}
		}
		if(!trouve){
			motsDiff.emplace_back(word,0);
		}

		// word est maintenant "tout propre"
		if (nombre_lu % 100 == 0)
			// on affiche un mot "propre" sur 100
			cout << nombre_lu << ": "<< word << endl;
		nombre_lu++;
	}
	input.close();


	cout << "Finished Parsing War and Peace" << endl;

	auto end = steady_clock::now();
    cout << "Parsing took "
              << duration_cast<milliseconds>(end - start).count()
              << "ms.\n";

    cout << "Found a total of " << nombre_lu << " words." << endl;
    cout << "Found a total of " << motsDiff.size() << " differents words." << endl;

    for(pair<string,int> m : motsDiff){
		if (m.first == "war" || m.first == "peace" || m.first == "toto"){
			cout << "Nombre de " << m.first << " = " << m.second << "." << endl;
		}
	}

    return 0;
}



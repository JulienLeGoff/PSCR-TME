#include "Banque.h"

using namespace std;

const int NB_THREAD = 10;
const int NB_COMPTES = 10;
const int SOLDE_INIT = 100;

void transferts_random(pr::Banque *b){
	int i,j,m;
	for(int i = 0; i < 1000; ++i){
		i = rand()%b->size();
		j = rand()%b->size();
		m = rand()%100 + 1;

		b->transfert(i, j, m);

		auto r = ::rand() % 20000 ; // 0 to 20 sec
		std::this_thread::sleep_for (std::chrono::milliseconds(r));
	}
}

int main () {
	vector<thread> threads;
	// TODO : creer des threads qui font ce qui est demandé

	threads.reserve(NB_THREAD);

	::srand(::time(nullptr));

	pr::Banque bq(NB_COMPTES, SOLDE_INIT);


	for (int i = 0; i < NB_THREAD; ++i) {
		threads.emplace_back(transferts_random, &bq);
	}


	for (auto & t : threads) {
		t.join();
	}

	// TODO : tester solde = NB_THREAD * JP
	return 0;
}

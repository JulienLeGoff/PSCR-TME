#include "Banque.h"

#include <iostream>

using namespace std;

namespace pr {

	void Banque::transfert(size_t deb, size_t cred, unsigned int val) {
		Compte & debiteur = comptes[deb];
		Compte & crediteur = comptes[cred];
		if (debiteur.debiter(val)) {
			crediteur.crediter(val);
		}
	}

	void Banque::lock_comptes() const {
		for (const Compte &compte : comptes) {
			compte.lock();
		}
	}

	void Banque::unlock_comptes() const {
		for (const Compte &compte : comptes) {
			compte.unlock();
		}
	}

	size_t Banque::size() const {
		return comptes.size();
	}

	bool Banque::comptabiliser (int attendu) const {
		int bilan = 0;
		int id = 0;
		for (const auto & compte : comptes) {
			if (compte.getSolde() < 0) {
				cout << "Compte " << id << " en négatif : " << compte.getSolde() << endl;
			}
			bilan += compte.getSolde();
			id++;
		}
		if (bilan != attendu) {
			cout << "Bilan comptable faux : attendu " << attendu << " obtenu : " << bilan << endl;
		}
		return bilan == attendu;
	}

	void Banque::transfertSur(size_t deb, size_t cred, size_t val) {
		Compte &debiteur = comptes[deb]; 
		Compte &crediteur = comptes[cred]; 

		if (deb < cred) {
			debiteur.lock();
			crediteur.lock();
		}

		if(debiteur.debiter(val)) {
			crediteur.crediter(val);
		}
		
		debiteur.unlock();
		crediteur.unlock();
	}


}

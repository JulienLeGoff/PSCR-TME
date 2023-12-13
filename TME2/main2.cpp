#include "utils.hpp"
#include "HashMap.hpp"
#include <vector>
#include <string>
#include <cassert>
#include <iostream>

using namespace std;
using namespace pr;

int main2() { 
    /*vector<string> v; 

    v.push_back("pomme"); 
    v.push_back("poire"); 
    v.push_back("pomme"); 

    assert(v.size() == count(v.begin(), v.end())); 
    assert(2 == countIfEqual(v.begin(), v.end(),"pomme")); 
    assert(1 == countIfEqual(v.begin(), v.end(),"poire")); */

    HashMap<string, int> m(100); 

    m.put("pomme", 5); 
    m.put("poire", 2); 
    m.put("pomme", 14); 

    vector<HashMap<string, int>::Entry> v;

    for (auto &e : m) {
        v.push_back(e);
    }
    

    sort(v.begin(), v.end(), [](const HashMap<string, int>::Entry &a, const HashMap<string, int>::Entry &b) {
        return a.value > b.value;
    });

    for (auto &e : v) {
        cout << e.key << " : " << e.value << endl;
    }

    return 0; 
}
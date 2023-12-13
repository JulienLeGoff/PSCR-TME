/*
 * HashMap.h
 *
 *  Created on: 27 sept. 2023
 *      Author: 21304302
 */

#pragma once
#include <forward_list>
#include <vector>
#include <stddef.h>

	template <typename K, typename V>

class HashMap {

	public:
		class Entry {
		public:
			const K key;
			V value;
			Entry(const K & key, const V & value): key(key), value(value){};
	};
	private:
		typedef std::vector<std::forward_list<Entry>> buckets_t;
		buckets_t buckets;
		size_t s;
	public:
		HashMap(size_t size): buckets(size), s(0) {
			for (size_t i = 0; i < size; ++i) {
				buckets.push_back(std::forward_list<Entry>());
			}
		}

		V* get(const K & key) {
			size_t h = std::hash<K>()(key);
			size_t target = h % buckets.size();
			for (Entry &entry : buckets[target]) {
				if (entry.key == key) {
					return &entry.value;
				}
			}
			return nullptr;
		}

		bool put(const K &key, const V &value) {
			size_t h = std::hash<K>()(key);
			size_t target = h % buckets.size();
			for(Entry &entry : buckets[target]) {
				if (entry.key == key) {
					entry.value = value;
					return true;
				}
			}
			s++;
			buckets[target].emplace_front(key, value);
			return false;
		}

		size_t size() const {return s;}

		void grow() {
			HashMap other(buckets.size()*2);
			for (auto & list : buckets) {
				for(Entry & entry : list) {
					other.put(entry.key, entry.value);
				}
			}
			buckets = other.buckets;
		}

	class iterator {
		typename buckets_t::iterator buckend;
		typename buckets_t::iterator vit;
		typename std::forward_list<Entry>::iterator lit;

	public :
		iterator(const typename buckets_t::iterator buckend, typename buckets_t::iterator &vit, const typename std::forward_list<Entry>::iterator &lit) : buckend(buckend), vit(vit), lit(lit) {}

		iterator & operator++() {
			++lit;
			if (lit == vit->end()) {
				++vit;
				while (vit != buckend && vit->empty()) {
					++vit;
				}
				if (vit != buckend) {
					lit = vit->begin();
				}
			}
			return *this;
		}

		Entry & operator*() {
			return *lit;
		}

		bool operator==(const iterator & other) const {
			return vit == other.vit && lit == other.lit;
		}

		bool operator!=(const iterator & other) const {
			return !(*this == other);
		}
	};
	iterator begin(){
		typename buckets_t::iterator vit = buckets.begin();
		while (vit != buckets.end() && vit->empty()) {
			++vit;
		}
		if (vit != buckets.end()) {
			return iterator(buckets.end(), vit, vit->begin());
		}
		return end();
	}

	iterator end(){
		return iterator(buckets.end(), buckets.end(), buckets.front().end(););
	}
};


// skiplist.h
#include <memory>
#include <random>
#include <stdlib.h>
#include "skiplistnode.h"

template<typename T, typename K>
class skiplist {
private:
	const double PROBABILLITY = 0.5;
	const int MAX_LEVEL = 36;

	using value_type = T;
	using key_type = K;
	using node = skiplistnode<value_type, key_type>;
	using nodeptr = node*;
	using forward_table = nodeptr*;

	/// <summary>
	/// Static state so we initialize srand only once per application lifetime
	/// </summary>
	inline static bool srand_initialized = false;
	/// <summary>
	/// Current level of this skip list instance
	/// </summary>
	int level;

	nodeptr head;

	// -- random level begin
	void initialize_srand_if_necessary() {
		if (srand_initialized) return;
		srand((unsigned)time(0));
		srand_initialized = true;
	}

	double get_random_value() {
		double value = rand() / (RAND_MAX + 1.);
		return value;
	}

	int get_random_level() {
		int new_level = 1;
		while (get_random_value() < PROBABILLITY) {
			new_level++;
		}
		int min = new_level > MAX_LEVEL ? MAX_LEVEL : new_level;
		return min;
	}
	// -- random level end

public:
	skiplist() : level(0), head(nullptr) {
		initialize_srand_if_necessary();
	};
	~skiplist() { };

	value_type get(key_type key) {
		nodeptr x = head;
		if (x->get_key() == key)
			return x->get_value();

		for (int i = level; i >= 1; i--) {
			while (x->get_forward(i) != nullptr && x->get_forward(i)->get_key() < key) {
				x = x->get_forward(i);
			}
		}
		x = x->get_forward(1);
		if (x == nullptr)
			return T{};

		return x->get_key() == key ? x->get_value() : T{};
	}


	void insert(key_type key, value_type value) {
		forward_table update = new nodeptr[MAX_LEVEL];
		nodeptr x = head;
		if (x == nullptr) {
			head = new node(key, value, 1);
			return;
		}


		for (int i = level; i >= 1; i--) {
			while (x->get_forward(i) != nullptr && x->get_forward(i)->get_key() < key) {
				x = x->get_forward(i);
			}
			update[i] = x;
		}
		x = x->get_forward(1);

		// update node value because given key already exists
		if (x != nullptr && x->get_key() == key) {
			x->set_value(value);
		}
		// key not found -> insert new node
		else {
			int new_level = get_random_level();
			if (new_level > level) {
				for (int i = level + 1; i <= new_level; i++) {
					update[i] = head;
				}
				level = new_level;
			}

			x = new node(key, value, level);
			for (int i = 1; i <= new_level; i++) {
				x->set_forward(i, update[i]->get_forward(i));
				update[i]->set_forward(i, x);
			}
		}
		delete[] update;
	}

	void remove(key_type key) {
		forward_table update = new nodeptr[MAX_LEVEL]{};
		nodeptr x = head;
		if (x == nullptr)
			return;

		for (int i = level; i <= 0; i++) {
			while (x->get_forward(i) != nullptr && x->get_forward(i)->get_key() < key) {
				x = x->get_forward(i);
			}
			update[i] = x;
		}
		x = x->get_forward(1);
		if (x->get_key() == key) {
			for (int i = 1; i <= level; i++) {
				if (update[i] == nullptr || update[i]->get_forward(i) == nullptr || x->get_forward(i) == nullptr ||
					update[i]->get_forward(i) != x->get_forward(i)) {
					break;
				}
				update[i]->set_forward(i, x->get_forward(i));
			}
			delete x;
			x = nullptr;
			while (level > 1 && head->get_forward(level) == nullptr) {
				level--;
			}
			delete[] update;
		}
	}
};

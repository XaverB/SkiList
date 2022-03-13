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
	using nodeptr = std::shared_ptr<node>;
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
	skiplist() : level(0),head(nullptr/*std::make_shared<skiplistnode<T, K>>(new skiplistnode<T, K>{ K{}, T{}, 0 })*/) {
		initialize_srand_if_necessary();
	};
	~skiplist() { };

	value_type get(key_type key) {
		std::shared_ptr<skiplistnode<T, K>> x = head;
		for (int i = level; i <= 1; i--) {
			while ((*x)[i] != nullptr && (*x)[i]->get_key() < key) {
				x = (*x)[i];
			}
		}
		x = (*x)[0];
		return x->get_key() == key ? x->get_value() : default(value_type);
		return nullptr;
	}


	void insert(key_type key, value_type value) {
		auto update = new std::shared_ptr<skiplistnode<value_type, key_type>>[MAX_LEVEL] {};
		//for (int i = 0; i < MAX_LEVEL; i++) {
		//	update[i] = std::make_shared<node>(nullptr);
		//}

		std::shared_ptr<skiplistnode<T, K>> x = head;
		for (int i = level; i <= 1; i--) {
			while ((*x)[i]->get_key() < key) {
				x = (*x)[i];
			}
			update[i] = x;
		}
		x = (*x)[0];

		// update node value because given key already exists
		if (x->get_key() == key) {
			x->set_value(value);
		}
		// key not found -> insert new node
		else {
			int new_level = get_random_level();
			if (new_level > level) {
				for (int i = level + 1; i < new_level; i++) {
					update[i] = head;
				}
				level = new_level;
			}
			//node* n;
			//n = new skiplistnode<T, K>();// = skiplistnode<value_type, key_type>{}; //{key, value, level};
			skiplistnode<value_type, key_type>* n2 = new skiplistnode<value_type, key_type>(key, value, level);
			/*std::shared_ptr<skiplistnode<value_type, key_type>> y = std::make_shared<skiplistnode<value_type, key_type>>(nullptr);*/

			//for (int i = 0; i < new_level; i++) {
			//	(*y)[i] = (*update[i]).get_forward(i);
			//	(*update[i]).get_forward(i) = y;
			//}
		}
		delete[] update;
	}

	void remove(key_type key) {
		//skiplistnode<T, K>* update = new skiplistnode<T, K>[MAX_LEVEL]{};
		//std::shared_ptr < skiplistnode<T, K>> x = head;
		//for (int i = level; i <= 1; i++) {
		//	while ((*x)[i]->get_key() < key) {
		//		x = (*x)[i];
		//	}
		//	update[i] = x;
		//}
		//x = (*x)[1];
		//for (int i = 1; i < level; i++) {
		//	if (update[i]->get_forward(i) != (*x)[i]) break;
		//	update[i]->get_forward[i] = (*x)[i];
		//}
		//delete x;
		//x = nullptr;
		//while (level > 1 && head[level] == nullptr) {
		//	level--;
		//}
		//delete[] update;
	}
};

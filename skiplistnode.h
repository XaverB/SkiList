// skiplistnode.h
#pragma once
#include <memory>
#include <cassert>

template<typename T, typename K>
class skiplistnode {
private:
	const int MAX_LEVEL = 36;

	using value_type = T;
	using key_type = K;
	using node = skiplistnode<value_type, key_type>;
	using nodeptr = std::shared_ptr<node>;
	using forward_table = nodeptr*;

	int level;
	value_type value{ default };
	key_type key{ default };

	forward_table forward;

	void init_forwards() {
		forward = new std::shared_ptr<skiplistnode<value_type, key_type>>[MAX_LEVEL] {};
		for (int i = 0; i < MAX_LEVEL; i++) {
			forward[i] = std::make_shared<node>(nullptr/*K{}, T{}, 0*/);
		}
	}

public:
	skiplistnode() : value(T{}), key(K{}), level(0) {
		init_forwards();
	}

	skiplistnode(K key, T value, int level) : value(value), key(key), level(level)
	{
		init_forwards();
	}

	~skiplistnode() {
		for (int i = 0; i < MAX_LEVEL; i++) {
			forward[i] = nullptr;
		}
		delete[] forward;
	}

	value_type get_value() const { return value; }
	key_type get_key() const { return key; }
	void set_value(value_type value) { this->value = value; }

	nodeptr get_forward(int forward_index) {
		assert(forward_index <= MAX_LEVEL);
		return forward[forward_index];
	}

	nodeptr operator[](int forward_index) {
		return get_forward(forward_index);
	}
};
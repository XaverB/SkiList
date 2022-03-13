#include <iostream>
#include "skiplist.h"
#include "utils.h"

using std::cout;
using std::endl;

template<typename T>
void assert_equals(T a, T b) {
	if (a != b) {
		cout << "ASSERT ERROR. " << a << " != " << b << endl;
	}
}

void test_list() {
	skiplist<int, int> list;

	list.insert(1, 1);
	list.insert(2, 2);
	list.insert(3, 3);
	list.insert(4, 4);

	assert_equals(list.get(1), 1);
	assert_equals(list.get(2), 2);
	assert_equals(list.get(3), 3);
	assert_equals(list.get(4), 4);
}

int main() {
	RUN(test_list());
	return 0;
}
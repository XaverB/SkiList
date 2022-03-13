#include <iostream>
#include "skiplist.h"
#include "utils.h"

using std::cout;
using std::endl;

void test_list() {
	cout << "=== test_list ===" << endl;
	skiplist<int, int> list;

	list.insert(1, 1);
	list.insert(2, 2);
	list.insert(3, 3);
	list.insert(4, 4);


}

int main() {
	RUN(test_list());
	return 0;
}
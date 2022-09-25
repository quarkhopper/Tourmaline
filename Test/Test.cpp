#include <iostream>
#include <string>
#include <functional>
#include <vector>

using namespace std;


class Handlers
{
public:
	static void generic_handler(string print_me) {
		cout << print_me << endl;
	}
};

auto cb0 = []() {
	Handlers::generic_handler("called from cb0");
};

auto cb1 = []() {
	Handlers::generic_handler("called from cb1");
};


int main() {
	vector<function<void()>> vec;
	vec.push_back(cb0);
	vec.push_back(cb1);

	for(auto& op : vec) {
		op();
	}
}


#include <iostream>
#include <memory>
using namespace std;

namespace c11_smart_ptr_weaklock{
	void observe(std::weak_ptr<int> weak)
	{
		if (auto observe = weak.lock()) { //像偷看值一样
			std::cout << "\tobserve() able to lock weak_ptr<>, value=" << *observe << "\n";
		} else {
			std::cout << "\tobserve() unable to lock weak_ptr<>\n";
		}
	}

	int main(int argc, char* argv[])
	{
		std::weak_ptr<int> weak;
		std::cout << "weak_ptr<> not yet initialized\n";
		observe(weak);

		{
			auto shared = std::make_shared<int>(42);
			weak = shared;
			std::cout << "weak_ptr<> initialized with shared_ptr.\n";
			observe(weak);
		}

		std::cout << "shared_ptr<> has been destructed due to scope exit.\n";
		observe(weak);

		return 0;
	}
}

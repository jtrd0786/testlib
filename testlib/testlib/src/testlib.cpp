#include "base/testlib_base.h"


void run_test()
{
	std::cout << "--- run_test()";

	void test_Function();
	test_Function();
}

int main(int argc, const char* argv[])
{
	run_test();

	return 0;
}
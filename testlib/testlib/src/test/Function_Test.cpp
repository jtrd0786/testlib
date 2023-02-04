#include "../function/Function.h"

namespace test {


template<size_t N> class Test_Function_Selector { public: using Function = void; };
template<> class Test_Function_Selector<0>		{ public: using Function = Function_T<void(int, float), 32, s_kAlignment, true>; };
template<> class Test_Function_Selector<1>		{ public: using Function = std::function<void(int, float)>; };

template<size_t N>
class Test_Function
{
	using Function = typename Test_Function_Selector<N>::Function;

	struct Test
	{
		void test(int a, float b)
		{
			printf("Test::test(int, float): %d, %f \n", a, b);
		}

		size_t aaa = 100;
	};

	// same function but output by return
	static Function create_test2()
	{
		Function test_func;
		static Test test;
		Test* p =  &test;
		{
			size_t aabb = 12;
			size_t aabb2 = 120;

			auto task = [p, aabb, aabb2](int a, float b) { p->test(a, b); printf("task v0: %llu, v1: %llu \n", aabb, aabb2); };
			test_func = task;

			size_t aabb3 = 10; (void)aabb3;

		}
		{
			size_t aabb = 13;
			size_t aabb2 = 130;

			auto task = [p, aabb, aabb2](int a, float b) { p->test(a, b); printf("task v0: %llu, v1: %llu \n", aabb, aabb2); };
			test_func = task;

			size_t aabb3 = 10; (void)aabb3;

		}
		{
			size_t aabb = 14;
			size_t aabb2 = 140;

			auto task = [p, aabb, aabb2](int a, float b) { p->test(a, b); printf("task v0: %llu, v1: %llu \n", aabb, aabb2); };
			test_func = task;

			size_t aabb3 = 10; (void)aabb3;

		}
		return test_func;
	}

	// same function but output by reference
	static void create_test3(Function& func)
	{
		static Test test;
		Test* p =  &test;
		{
			size_t aabb = 12;
			size_t aabb2 = 120;

			auto task = [p, aabb, aabb2](int a, float b) { p->test(a, b); printf("task v0: %llu, v1: %llu \n", aabb, aabb2); };
			func = task;

			size_t aabb3 = 10; (void)aabb3;

		}
		{
			size_t aabb = 13;
			size_t aabb2 = 130;

			auto task = [p, aabb, aabb2](int a, float b) { p->test(a, b); printf("task v0: %llu, v1: %llu \n", aabb, aabb2); };
			func = task;

			size_t aabb3 = 10; (void)aabb3;

		}
		{
			size_t aabb = 14;
			size_t aabb2 = 140;

			auto task = [p, aabb, aabb2](int a, float b) { p->test(a, b); printf("task v0: %llu, v1: %llu \n", aabb, aabb2); };
			func = task;

			size_t aabb3 = 10; (void)aabb3;

		}
	}

public:
	void test()
	{
		if (N == 0) { printf("\n Function = Function_T<void(int, float), 32, s_kAlignment, true>;"); }
		else		{ printf("\n Function = std::function<void(int, float)>;"); }

		Function test_func;
		Test test_struct;
		{
			{
				int i = 2; float f = 10.0f;
				size_t aabb = 10;
				size_t aabb2 = 100;
				auto task = [&test_struct, aabb, aabb2](int a, float b) { test_struct.test(a, b); printf("task v0: %llu, v1: %llu \n", aabb, aabb2); };

				Function test_func2 = task;
				//test_func = task;
				printf("sizeof(task): %llu \n", sizeof(task));

				size_t aabb3 = 10; (void)aabb3;

				test_func = create_test2();		// same function but output by return
				create_test3(test_func2);		// same function but output by reference
				
				test_func (1, 1.0f);
				test_func2(1, 1.0f);

				task(i, f);
				//Function test_func2 = Test2::create();
				size_t aabb4 = 10; (void)aabb4;
			}

			#if 0
			Function func6 = [&test_struct](int a, float b) { test_struct.test(a, b); };
			func6(5, 10.0f);
			Function func7 = func6;
			Function func8;
			if (func6)
			{
				printf("if func6\n");
			}
			if (!func8)
			{
				printf("if func8\n");
			}
			if (func8 == nullptr)
			{
				printf("if func8\n");
			}
			#endif // 0
		}
	}
};

}

void test_Function()
{
	using namespace test;
	{
		Test_Function<0> t;
		t.test();
	}
	{
		Test_Function<1> t;
		t.test();
	}
}
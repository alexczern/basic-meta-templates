#include <cassert>
#include <typeinfo>
#include <type_traits>

namespace bmt
{
	template <LikeLogger Logger_T>
	template <template <typename...> typename PackAlgorithms_VT>
	int LibTester<Logger_T>::test_PackAlgorithms()
	{
		Subtester tester(log, "bmt::LibTester::test_PackAlgorithms");
		using Example = PackAlgorithms_VT<
			int, double, int, double,
			float, unsigned int, unsigned int,
			float, int, float, int
		>;
		static_assert(Example::size::value == Example::size_v);
		static_assert(Example::size_v == 11);

	#if 1 // test nested "type_identity" template types.
		using SignedPackHolder = typename Example::copy_if<std::is_signed>::type;
		static_assert(std::is_same_v<
			SignedPackHolder, typename Example::copy_if_t<std::is_signed>
		>);
		static_assert(std::is_same_v<
			typename SignedPackHolder::place_t<PackHolder>,
			PackHolder<int, double, int, double, float, float, int, float, int>
		>);

		using TransformedPackHolder = typename Example::transform<custom_transformer>::type;
		static_assert(std::is_same_v<
			TransformedPackHolder, typename Example::transform_t<custom_transformer>
		>);
		static_assert(std::is_same_v<
			typename TransformedPackHolder::place_t<PackHolder>,
			PackHolder<
				float, int, float, int,
				float, unsigned int, unsigned int,
				float, float, float, float
			>
		>);

		using FoundedType = typename Example::find_if<std::is_unsigned>::type;
		static_assert(std::is_same_v<
			FoundedType, typename Example::find_if_t<std::is_unsigned>
		>);
		static_assert(std::is_same_v<
			FoundedType, unsigned int
		>);
	#endif
	#if 1 // test "any_of_v", "all_of_v", "none_of_v"
		static_assert(Example::template any_of_v<std::is_void> == false);
		static_assert(Example::template any_of_v<std::is_class> == false);
		static_assert(Example::template any_of_v<std::is_object> == true);
		static_assert(Example::template any_of_v<std::is_fundamental> == true);
		static_assert(Example::template any_of_v<std::is_signed> == true);

		static_assert(Example::template all_of_v<std::is_void> == false);
		static_assert(Example::template all_of_v<std::is_class> == false);
		static_assert(Example::template all_of_v<std::is_object> == true);
		static_assert(Example::template all_of_v<std::is_fundamental> == true);
		static_assert(Example::template all_of_v<std::is_signed> == false);

		static_assert(Example::template none_of_v<std::is_void> == true);
		static_assert(Example::template none_of_v<std::is_class> == true);
		static_assert(Example::template none_of_v<std::is_object> == false);
		static_assert(Example::template none_of_v<std::is_fundamental> == false);
		static_assert(Example::template none_of_v<std::is_signed> == false);
	#endif // test "any_of_v", "all_of_v", "none_of_v"
	#if 1 // (depends on previous test) test "any_of", "all_of", "none_of"
		static_assert(std::type_identity_t<
			typename Example::any_of<std::is_void>
		>::value == Example::template any_of_v<std::is_void>);
		static_assert(std::type_identity_t<
			typename Example::any_of<std::is_class>
		>::value == Example::template any_of_v<std::is_class>);
		static_assert(std::type_identity_t<
			typename Example::any_of<std::is_object>
		>::value == Example::template any_of_v<std::is_object>);
		static_assert(std::type_identity_t<
			typename Example::any_of<std::is_fundamental>
		>::value == Example::template any_of_v<std::is_fundamental>);
		static_assert(std::type_identity_t<
			typename Example::any_of<std::is_signed>
		>::value == Example::template any_of_v<std::is_signed>);

		static_assert(std::type_identity_t<
			typename Example::all_of<std::is_void>
		>::value == Example::template all_of_v<std::is_void>);
		static_assert(std::type_identity_t<
			typename Example::all_of<std::is_class>
		>::value == Example::template all_of_v<std::is_class>);
		static_assert(std::type_identity_t<
			typename Example::all_of<std::is_object>
		>::value == Example::template all_of_v<std::is_object>);
		static_assert(std::type_identity_t<
			typename Example::all_of<std::is_fundamental>
		>::value == Example::template all_of_v<std::is_fundamental>);
		static_assert(std::type_identity_t<
			typename Example::all_of<std::is_signed>
		>::value == Example::template all_of_v<std::is_signed>);

		static_assert(std::type_identity_t<
			typename Example::none_of<std::is_void>
		>::value == Example::template none_of_v<std::is_void>);
		static_assert(std::type_identity_t<
			typename Example::none_of<std::is_class>
		>::value == Example::template none_of_v<std::is_class>);
		static_assert(std::type_identity_t<
			typename Example::none_of<std::is_object>
		>::value == Example::template none_of_v<std::is_object>);
		static_assert(std::type_identity_t<
			typename Example::none_of<std::is_fundamental>
		>::value == Example::template none_of_v<std::is_fundamental>);
		static_assert(std::type_identity_t<
			typename Example::none_of<std::is_signed>
		>::value == Example::template none_of_v<std::is_signed>);

	#endif
	#if 1 // test ::template contains
		static_assert(Example::template contains_v<int> == true);
		static_assert(std::type_identity_t<
			typename Example::contains<int>
		>::value == Example::template contains_v<int>);
		static_assert(Example::template contains_v<float> == true);
		static_assert(std::type_identity_t<
			typename Example::contains<float>
		>::value == Example::template contains_v<float>);
		static_assert(Example::template contains_v<double> == true);
		static_assert(std::type_identity_t<
			typename Example::contains<double>
		>::value == Example::template contains_v<double>);
		static_assert(Example::template contains_v<unsigned int> == true);
		static_assert(std::type_identity_t<
			typename Example::contains<unsigned int>
		>::value == Example::template contains_v<unsigned int>);
		static_assert(Example::template contains_v<short> == false);
		static_assert(std::type_identity_t<
			typename Example::contains<short>
		>::value == Example::template contains_v<short>);
		static_assert(Example::template contains_v<char> == false);
		static_assert(std::type_identity_t<
			typename Example::contains<char>
		>::value == Example::template contains_v<char>);
	#endif
	#if 1 // test ::template includes
		static_assert(Example::template includes_v<int, unsigned int, float, double> == true);
		static_assert(std::type_identity_t<
			typename Example::includes<int, unsigned int, float, double>
		>::value == Example::template includes_v<int, unsigned int, float, double>);

		static_assert(Example::template includes_v<int, unsigned int, float, double, short> == false);
		static_assert(std::type_identity_t<
			typename Example::includes<int, unsigned int, float, double, short>
		>::value == Example::template includes_v<int, unsigned int, float, double, short>);

		static_assert(Example::template includes_v<short, char, bool> == false);
		static_assert(std::type_identity_t<
			typename Example::includes<short, char, bool>
		>::value == Example::template includes_v<short, char, bool>);

		using IncludesTest0 = SignedPackHolder::template place_t<Example::template includes>;
		static_assert(IncludesTest0::value == true);
		static_assert(
			IncludesTest0::value == Example::template includes_v<
				int, double, int, double, float, float, int, float, int
			>
		);
	#endif
	#if 1 // test ::template partly_includes
		static_assert(Example::template partly_includes_v<int, unsigned int, float, double> == true);
		static_assert(std::type_identity_t<
			typename Example::partly_includes<int, unsigned int, float, double>
		>::value == Example::template partly_includes_v<int, unsigned int, float, double>);

		static_assert(Example::template partly_includes_v<int, unsigned int, float, double, short> == true);
		static_assert(std::type_identity_t<
			typename Example::partly_includes<int, unsigned int, float, double, short>
		>::value == Example::template partly_includes_v<int, unsigned int, float, double, short>);

		static_assert(Example::template partly_includes_v<short, char, bool> == false);
		static_assert(std::type_identity_t<
			typename Example::partly_includes<short, char, bool>
		>::value == Example::template partly_includes_v<short, char, bool>);

		using PartlyIncludesTest0 = SignedPackHolder::template place_t<Example::template partly_includes>;
		static_assert(PartlyIncludesTest0::value == true);
		static_assert(
			PartlyIncludesTest0::value == Example::template partly_includes_v<
				int, double, int, double, float, float, int, float, int
			>
		);
	#endif
	#if 1 // test ::template equal
		static_assert(Example::template equal_v<short, char, bool> == false);
		static_assert(std::type_identity_t<
			typename Example::equal<short, char, bool>
		>::value == Example::template equal_v<short, char, bool>);

		static_assert(Example::template equal_v<
			int, double, int, double,
			float, unsigned int, unsigned int,
			float, int, float, int
		> == true);
		static_assert(
			std::type_identity_t<
				typename Example::equal<
					int, double, int, double,
					float, unsigned int, unsigned int,
					float, int, float, int
				>
			>::value == Example::template equal_v<
				int, double, int, double,
				float, unsigned int, unsigned int,
				float, int, float, int
			>);

		using EqualTest0 = SignedPackHolder::template place_t<Example::template equal>;
		static_assert(EqualTest0::value == false);
		static_assert(
			EqualTest0::value == Example::template equal_v<
				int, double, int, double, float, float, int, float, int
			>
		);
	#endif
	#if 1 // test ::template count
		static_assert(Example::template count_v<int> == 4);
		static_assert(std::type_identity_t<
			typename Example::count<int>
		>::value == Example::template count_v<int>);
		static_assert(Example::template count_v<double> == 2);
		static_assert(std::type_identity_t<
			typename Example::count<double>
		>::value == Example::template count_v<double>);
		static_assert(Example::template count_v<float> == 3);
		static_assert(std::type_identity_t<
			typename Example::count<float>
		>::value == Example::template count_v<float>);
		static_assert(Example::template count_v<unsigned int> == 2);
		static_assert(std::type_identity_t<
			typename Example::count<unsigned int>
		>::value == Example::template count_v<unsigned int>);
		static_assert(Example::template count_v<short> == 0);
		static_assert(std::type_identity_t<
			typename Example::count<short>
		>::value == Example::template count_v<short>);
		static_assert(Example::template count_v<char> == 0);
		static_assert(std::type_identity_t<
			typename Example::count<char>
		>::value == Example::template count_v<char>);
	#endif
	#if 1 // test ::template index_of
		static_assert(Example::template index_of_v<int> == 0);
		static_assert(std::type_identity_t<
			typename Example::index_of<int>
		>::value == Example::template index_of_v<int>);

		static_assert(Example::template index_of_v<int, 1> == 2);
		static_assert(std::type_identity_t<
			typename Example::index_of<int, 1>
		>::value == Example::template index_of_v<int, 1>);

		static_assert(Example::template index_of_v<double> == 1);
		static_assert(std::type_identity_t<
			typename Example::index_of<double>
		>::value == Example::template index_of_v<double>);

		static_assert(Example::template index_of_v<float> == 4);
		static_assert(std::type_identity_t<
			typename Example::index_of<float>
		>::value == Example::template index_of_v<float>);

		static_assert(Example::template index_of_v<float, 1> == 7);
		static_assert(std::type_identity_t<
			typename Example::index_of<float, 1>
		>::value == Example::template index_of_v<float, 1>);

	#endif
	#if 1 // test ::template type_of
		static_assert(std::is_same_v<
			int,
			typename Example::type_of_t<0>
		>);
		static_assert(std::is_same_v<
			typename Example::type_of<0>::type,
			typename Example::type_of_t<0>
		>);

		static_assert(std::is_same_v<
			double,
			typename Example::type_of_t<1>
		>);
		static_assert(std::is_same_v<
			typename Example::type_of<1>::type,
			typename Example::type_of_t<1>
		>);

		static_assert(std::is_same_v<
			float,
			typename Example::type_of_t<4>
		>);
		static_assert(std::is_same_v<
			typename Example::type_of<4>::type,
			typename Example::type_of_t<4>
		>);

		static_assert(std::is_same_v<
			unsigned int,
			typename Example::type_of_t<6>
		>);
		static_assert(std::is_same_v<
			typename Example::type_of<6>::type,
			typename Example::type_of_t<6>
		>);

		static_assert(std::is_same_v<
			int,
			typename Example::type_of_t<10>
		>);
		static_assert(std::is_same_v<
			typename Example::type_of<10>::type,
			typename Example::type_of_t<10>
		>);

		static_assert(std::is_same_v<
			std::nullptr_t,
			typename Example::type_of_t<11>
		>);
		static_assert(std::is_same_v<
			typename Example::type_of<11>::type,
			typename Example::type_of_t<11>
		>);


	#endif
	#if 1 //test run-time static methods
		bool found_error = false;
		size_t counter = 0;
		Example::template indexedForEach(
			[&counter, &found_error]<size_t index, typename ItemType>
			{
				if(counter != index)
					found_error = true;
				++counter;
			}
		);
		tester.check_assert(false == found_error);
		tester.check_assert(counter == 11);
		counter = 0;

		Example:: template forEach(
			[&counter] <typename ItemType> { ++counter; }
		);
		tester.check_assert(counter == 11);
		counter = 0;

		auto floatLambda = [&counter]<typename ItemType>
			{
				++counter;
				if constexpr(std::is_same_v<ItemType, float>)
					return true;
				else
					return false;
			};
		auto fundamentalLambda = [&counter]<typename ItemType>
			{
				++counter;
				if constexpr(std::is_fundamental_v<ItemType>)
					return true;
				else
					return false;
			};
		auto classLambda = [&counter]<typename ItemType>
			{
				++counter;
				if constexpr(std::is_class_v<ItemType>)
					return true;
				else
					return false;
			};

		tester.check_assert(true == Example::anyOf(floatLambda));
		tester.check_assert(counter == 5); counter = 0;
		tester.check_assert(true == Example::anyOf(fundamentalLambda));
		tester.check_assert(counter == 1); counter = 0;
		tester.check_assert(false == Example::anyOf(classLambda));
		tester.check_assert(counter == 11); counter = 0;

		tester.check_assert(false == Example::allOf(floatLambda));
		tester.check_assert(counter == 1); counter = 0;
		tester.check_assert(true == Example::allOf(fundamentalLambda));
		tester.check_assert(counter == 11); counter = 0;
		tester.check_assert(false == Example::allOf(classLambda));
		tester.check_assert(counter == 1); counter = 0;

		tester.check_assert(false == Example::noneOf(floatLambda));
		tester.check_assert(counter == 5); counter = 0;
		tester.check_assert(false == Example::noneOf(fundamentalLambda));
		tester.check_assert(counter == 1); counter = 0;
		tester.check_assert(true == Example::noneOf(classLambda));
		tester.check_assert(counter == 11); counter = 0;
	#endif
		if (tester.fail())
			return -1;
		else
			return 0;
	}
}

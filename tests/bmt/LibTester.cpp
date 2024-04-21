#include <iostream>
#include <concepts>
#include <source_location>
#include <bmt/bmt.hpp>

namespace bmt
{
	template <typename Logger_T, typename T>
	concept LikeTagOfLogger =
		requires(Logger_T l)
		{
			T(l, "str");
		};
	template <typename T>
	concept LikeLogger =
		requires(T log, int i, const char *str){
			typename T::TagType;
			requires LikeTagOfLogger<T, typename T::TagType>;
			{ log.tag("str") } -> std::same_as<typename T::TagType>;
			log.template info(str, i, str);
			log.template warning(str, i, str);
			log.template debug(str, i, str);
			log.template trace(str, i, str);
			log.template error(str, i, str);
			log.template fatal(str, i, str);
		};
	template <LikeLogger Logger_T>
	class LibTester
	{
		Logger_T &log;
		int tab_count = 0;
		bool has_error = false;
		void check_result(
			int code,
			const std::source_location location = std::source_location::current()
		)
		{
			if (code == 0)
				log.info("[OK]", "[RETURN CODE: ", code, "]");
			else
			{
				log.error("[BAD]", "[RETURN CODE: ", code, "]");
				has_error = true;
			}
		}
		struct Subtester
		:	public Logger_T::TagType
		{
			Logger_T &r_log;
			bool has_error = false;
			Subtester(Logger_T &l, const char *name)
			:	Logger_T::TagType(l, name),
				r_log(l)
			{}
			void check_assert(
				bool a, const std::source_location location = std::source_location::current()
			)
			{
				if (false == a)
				{
					r_log.error("[BAD][CHECK_ASSERT][",
						location.file_name(), '(',
						location.line(), ':', location.column(), ")]");
					has_error = true;
				}
			}
			bool fail() { return has_error; };
		};
	public:
		//~ template <typename T>
		//~ struct custom_transformer;

		template <template <typename...> typename PackHolder_VT>
		int test_PackHolder();
		template <template <typename...> typename PackAlgorithms_VT>
		int test_PackAlgorithms();
		template <template <typename...> typename TypesPack_VT>
		int test_TypesPack();
		template <template <typename, typename> typename TypedMap_T>
		int test_TypedMap();
		template <template <typename, typename> typename TypedMultiMap_T>
		int test_TypedMultiMap();
		template <template <typename...> typename ItemsTuple_T>
		int test_ItemsTuple();
		template <template <typename, template<typename>typename> typename TypedHeteroMap_T>
		int test_TypedHeteroMap();
		template <template <typename...> typename UnitedTypes_T>
		int test_UnitedTypes();


		LibTester(Logger_T &l)
		:	log(l) {}
		int start()
		{
			auto t = log.tag("bmt::LibTester::start");
			check_result(test_PackHolder<PackHolder>());
			check_result(test_PackAlgorithms<PackAlgorithms>());
			check_result(test_TypesPack<TypesPack>());
			check_result(test_TypedMap<TypedMap>());
			check_result(test_TypedMultiMap<TypedMultiMap>());
			check_result(test_ItemsTuple<ItemsTuple>());
			check_result(test_TypedHeteroMap<containers::TypedHeteroMap>());
			check_result(test_UnitedTypes<containers::UnitedTypes>());
			if (has_error)
				return -1;
			return 0;
		}
	};
	template <typename T>
	struct custom_transformer
	{
		using type = T;
	};
	template <>
	struct custom_transformer<int>
	{
		using type = float;
	};
	template <>
	struct custom_transformer<double>
	{
		using type = int;
	};
}

#include "test_PackHolder.cpp"
#include "test_PackAlgorithms.cpp"
#include "test_TypesPack.cpp"
#include "test_TypedMap.cpp"
#include "test_TypedMultiMap.cpp"
#include "test_ItemsTuple.cpp"
#include "test_TypedHeteroMap.cpp"
#include "test_UnitedTypes.cpp"

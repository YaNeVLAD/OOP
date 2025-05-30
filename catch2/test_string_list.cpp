#include "catch2.h"

#include <tuple>

using TestTypes = std::tuple<int, std::string>;

TEMPLATE_TEST_CASE("List Basic Operations - ", "[List][Basic]", int, std::string)
{
	using ValueType = TestType;

	SECTION("Default Constructor")
	{
		List<ValueType> list;
		REQUIRE(list.Empty());
		REQUIRE(list.Size() == 0);
		REQUIRE(list.Begin() == list.End());
		REQUIRE(list.cbegin() == list.cend());
	}

	SECTION("Size Constructor")
	{
		size_t size = GENERATE(0, 1, 5);
		List<ValueType> list(size);
		REQUIRE(list.Size() == size);
		REQUIRE(list.Empty() == (size == 0));

		for (const auto& val : list)
		{
			REQUIRE(val == ValueType{});
		}
	}

	SECTION("Initializer List Constructor")
	{
		SECTION("Empty list")
		{
			List<ValueType> list{};
			REQUIRE(list.Empty());
			REQUIRE(list.Size() == 0);
		}

		SECTION("Non-empty list")
		{
			List<ValueType> list = { TestType{ 1 }, TestType{ 2 }, TestType{ 3 } };
			REQUIRE(!list.Empty());
			REQUIRE(list.Size() == 3);

			auto it = list.Begin();
			REQUIRE(*it == TestType{ 1 });
			++it;
			REQUIRE(*it == TestType{ 2 });
			++it;
			REQUIRE(*it == TestType{ 3 });
			++it;
			REQUIRE(it == list.End());
		}
	}

	SECTION("PushFront and PopFront")
	{
		List<ValueType> list;
		REQUIRE(list.Empty());

		list.PushFront(TestType{ 10 });
		REQUIRE(!list.Empty());
		REQUIRE(list.Size() == 1);
		REQUIRE(list.Front() == TestType{ 10 });
		REQUIRE(list.Back() == TestType{ 10 });

		list.PushFront(TestType{ 20 });
		REQUIRE(list.Size() == 2);
		REQUIRE(list.Front() == TestType{ 20 });
		REQUIRE(list.Back() == TestType{ 10 });

		list.PopFront();
		REQUIRE(list.Size() == 1);
		REQUIRE(list.Front() == TestType{ 10 });
		REQUIRE(list.Back() == TestType{ 10 });

		list.PopFront();
		REQUIRE(list.Empty());
		REQUIRE(list.Size() == 0);
		REQUIRE(list.Begin() == list.End());

		// Pop from empty list - should not crash or change state
		list.PopFront();
		REQUIRE(list.Empty());
		REQUIRE(list.Size() == 0);
	}

	SECTION("PushBack and PopBack")
	{
		List<ValueType> list;
		REQUIRE(list.Empty());

		list.PushBack(TestType{ 100 });
		REQUIRE(!list.Empty());
		REQUIRE(list.Size() == 1);
		REQUIRE(list.Front() == TestType{ 100 });
		REQUIRE(list.Back() == TestType{ 100 });

		list.PopBack();
		REQUIRE(list.Empty());
		REQUIRE(list.Size() == 0);
		REQUIRE(list.Begin() == list.End());

		// Pop from empty list - should not crash or change state
		list.PopBack();
		REQUIRE(list.Empty());
		REQUIRE(list.Size() == 0);
	}

	SECTION("Front and Back access")
	{
		List<ValueType> list = { TestType{ 1 }, TestType{ 2 }, TestType{ 3 } };

		// Non-const access
		REQUIRE(list.Front() == TestType{ 1 });
		REQUIRE(list.Back() == TestType{ 3 });

		list.Front() = TestType{ 11 };
		list.Back() = TestType{ 33 };
		REQUIRE(list.Front() == TestType{ 11 });
		REQUIRE(list.Back() == TestType{ 33 });

		// Const access
		const List<ValueType>& constList = list;
		REQUIRE(constList.Front() == TestType{ 11 });
		REQUIRE(constList.Back() == TestType{ 33 });

		// Testing Front/Back on empty list will trigger assert in debug.
		// Assuming asserts are enabled for testing, we don't explicitly test
		// calling Front/Back on an empty list as it's undefined behavior
		// according to the list's internal asserts.
	}

	SECTION("Clear")
	{
		List<ValueType> list = { TestType{ 1 }, TestType{ 2 }, TestType{ 3 } };
		REQUIRE(!list.Empty());
		REQUIRE(list.Size() == 3);

		list.Clear();
		REQUIRE(list.Empty());
		REQUIRE(list.Size() == 0);
		REQUIRE(list.Begin() == list.End());

		// Clearing an already empty list should be safe
		list.Clear();
		REQUIRE(list.Empty());
		REQUIRE(list.Size() == 0);
	}

	SECTION("Size and Empty")
	{
		List<ValueType> list;
		REQUIRE(list.Empty());
		REQUIRE(list.Size() == 0);

		list.PushBack(TestType{ 1 });
		REQUIRE(!list.Empty());
		REQUIRE(list.Size() == 1);

		list.PushFront(TestType{ 2 });
		REQUIRE(!list.Empty());
		REQUIRE(list.Size() == 2);

		list.PopBack();
		REQUIRE(!list.Empty());
		REQUIRE(list.Size() == 1);

		list.PopFront();
		REQUIRE(list.Empty());
		REQUIRE(list.Size() == 0);
	}
}

TEMPLATE_TEST_CASE("List Copy and Move - ", "[List][CopyMove]", int, std::string)
{
	using ValueType = TestType;

	SECTION("Copy Constructor")
	{
		List<ValueType> original = { TestType{ 1 }, TestType{ 2 }, TestType{ 3 } };
		List<ValueType> copy = original;

		REQUIRE(copy.Size() == original.Size());
		REQUIRE(!copy.Empty());

		auto originalIt = original.Begin();
		auto copyIt = copy.Begin();
		while (originalIt != original.End())
		{
			REQUIRE(*originalIt == *copyIt);
			++originalIt;
			++copyIt;
		}
		REQUIRE(copyIt == copy.End());

		// Verify independence
		original.PushBack(TestType{ 4 });
		REQUIRE(original.Size() == 4);
		REQUIRE(copy.Size() == 3); // Copy should not be affected
		REQUIRE(original.Back() == TestType{ 4 });
		REQUIRE(copy.Back() == TestType{ 3 });

		copy.PushFront(TestType{ 0 });
		REQUIRE(copy.Size() == 4);
		REQUIRE(original.Size() == 4);
		REQUIRE(copy.Front() == TestType{ 0 });
		REQUIRE(original.Front() == TestType{ 1 });
	}

	SECTION("Copy Assignment Operator")
	{
		List<ValueType> original = { TestType{ 1 }, TestType{ 2 }, TestType{ 3 } };
		List<ValueType> destination = { TestType{ 99 }, TestType{ 98 } };

		destination = original; // Assignment

		REQUIRE(destination.Size() == original.Size());
		REQUIRE(!destination.Empty());

		auto originalIt = original.Begin();
		auto destIt = destination.Begin();
		while (originalIt != original.End())
		{
			REQUIRE(*originalIt == *destIt);
			originalIt++;
			destIt++;
		}
		REQUIRE(destIt == destination.End());

		// Verify independence
		original.PushBack(TestType{ 4 });
		REQUIRE(original.Size() == 4);
		REQUIRE(destination.Size() == 3); // Destination should not be affected

		// Test self-assignment
		List<ValueType> selfAssignList = { TestType{ 5 }, TestType{ 6 } };
		selfAssignList = selfAssignList;
		REQUIRE(selfAssignList.Size() == 2);
		REQUIRE(selfAssignList.Front() == TestType{ 5 });
		REQUIRE(selfAssignList.Back() == TestType{ 6 });
	}

	SECTION("Move Constructor")
	{
		List<ValueType> original = { TestType{ 1 }, TestType{ 2 }, TestType{ 3 } };
		List<ValueType> movedList = std::move(original);

		// Verify movedList state
		REQUIRE(movedList.Size() == 3);
		REQUIRE(!movedList.Empty());
		REQUIRE(movedList.Front() == TestType{ 1 });
		REQUIRE(movedList.Back() == TestType{ 3 });

		// Verify original state (should be empty and valid)
		REQUIRE(original.Empty());
		REQUIRE(original.Size() == 0);
		REQUIRE(original.Begin() == original.End());
	}

	SECTION("Move Assignment Operator")
	{
		List<ValueType> original = { TestType{ 1 }, TestType{ 2 }, TestType{ 3 } };
		List<ValueType> destination = { TestType{ 99 }, TestType{ 98 } };

		destination = std::move(original); // Move assignment

		// Verify destination state
		REQUIRE(destination.Size() == 3);
		REQUIRE(!destination.Empty());
		REQUIRE(destination.Front() == TestType{ 1 });
		REQUIRE(destination.Back() == TestType{ 3 });

		// Verify original state (should be empty and valid)
		REQUIRE(original.Empty());
		REQUIRE(original.Size() == 0);
		REQUIRE(original.Begin() == original.End());

		// Test self-move assignment
		List<ValueType> selfMoveList = { TestType{ 5 }, TestType{ 6 } };
		selfMoveList = std::move(selfMoveList);
		REQUIRE(selfMoveList.Size() == 2);
		REQUIRE(selfMoveList.Front() == TestType{ 5 });
		REQUIRE(selfMoveList.Back() == TestType{ 6 });
	}
}

TEMPLATE_TEST_CASE("List Insert and Erase - ", "[List][InsertErase]", int, std::string)
{
	using ValueType = TestType;

	SECTION("Insert")
	{
		List<ValueType> list;

		SECTION("Insert at Begin() on empty list (should become the only element)")
		{
			auto it = list.Insert(list.Begin(), TestType{ 10 });
			REQUIRE(list.Size() == 1);
			REQUIRE(list.Front() == TestType{ 10 });
			REQUIRE(list.Back() == TestType{ 10 });
			REQUIRE(*it == TestType{ 10 });
			REQUIRE(it == list.Begin());
		}

		SECTION("Insert at End() on empty list (should become the only element)")
		{
			auto it = list.Insert(list.End(), TestType{ 10 });
			REQUIRE(list.Size() == 1);
			REQUIRE(list.Front() == TestType{ 10 });
			REQUIRE(list.Back() == TestType{ 10 });
			REQUIRE(*it == TestType{ 10 });
			REQUIRE(it == list.Begin()); // For size 1 list, begin and the inserted element's iterator are the same
			auto nextIt = it;
			++nextIt;
			REQUIRE(nextIt == list.End());
		}

		list = { TestType{ 1 }, TestType{ 3 } }; // List is now {1, 3}

		SECTION("Insert at Begin() on non-empty list")
		{
			auto it = list.Insert(list.Begin(), TestType{ 0 }); // Insert 0 at the front
			REQUIRE(list.Size() == 3);
			REQUIRE(list.Front() == TestType{ 0 });
			REQUIRE(list.Back() == TestType{ 3 });
			REQUIRE(*it == TestType{ 0 });
			REQUIRE(it == list.Begin());

			// Verify order
			auto current = list.Begin();
			REQUIRE(*current == TestType{ 0 });
			++current;
			REQUIRE(*current == TestType{ 1 });
			++current;
			REQUIRE(*current == TestType{ 3 });
			++current;
			REQUIRE(current == list.End());
		}

		SECTION("Insert at End() on non-empty list")
		{
			auto it = list.Insert(list.End(), TestType{ 4 }); // Insert 4 at the back
			REQUIRE(list.Size() == 3);
			REQUIRE(list.Front() == TestType{ 1 });
			REQUIRE(list.Back() == TestType{ 4 });
			REQUIRE(*it == TestType{ 4 });

			auto next_it = it;
			++next_it;
			REQUIRE(next_it == list.End()); // Returned iterator points to the inserted element

			// Verify order
			auto current = list.Begin();
			REQUIRE(*current == TestType{ 1 });
			++current;
			REQUIRE(*current == TestType{ 3 });
			++current;
			REQUIRE(*current == TestType{ 4 });
			++current;
			REQUIRE(current == list.End());
		}

		SECTION("Insert in the middle")
		{
			auto itTo3 = std::next(list.Begin()); // Iterator to element 3
			auto it = list.Insert(itTo3, TestType{ 2 }); // Insert 2 before 3
			REQUIRE(list.Size() == 3);
			REQUIRE(list.Front() == TestType{ 1 });
			REQUIRE(list.Back() == TestType{ 3 });
			REQUIRE(*it == TestType{ 2 }); // Returned iterator points to the inserted element

			// Verify order
			auto current = list.Begin();
			REQUIRE(*current == TestType{ 1 });
			++current;
			REQUIRE(*current == TestType{ 2 });
			++current;
			REQUIRE(*current == TestType{ 3 });
			++current;
			REQUIRE(current == list.End());
		}

		SECTION("Insert with rvalue")
		{
			List<ValueType> rvalue_list;
			auto it = rvalue_list.Insert(rvalue_list.End(), TestType{ 50 });
			REQUIRE(rvalue_list.Size() == 1);
			REQUIRE(*it == TestType{ 50 });
		}
	}

	SECTION("Erase")
	{
		List<ValueType> list = { TestType{ 1 }, TestType{ 2 }, TestType{ 3 }, TestType{ 4 } };

		SECTION("Erase at Begin()")
		{
			auto it = list.Erase(list.Begin());
			REQUIRE(list.Size() == 3);
			REQUIRE(list.Front() == TestType{ 2 });
			REQUIRE(list.Back() == TestType{ 4 });
			REQUIRE(*it == TestType{ 2 });

			// Verify order
			auto current = list.Begin();
			REQUIRE(*current == TestType{ 2 });
			++current;
			REQUIRE(*current == TestType{ 3 });
			++current;
			REQUIRE(*current == TestType{ 4 });
			++current;
			REQUIRE(current == list.End());
		}

		SECTION("Erase at End() (should do nothing)")
		{
			auto it = list.Erase(list.End());
			REQUIRE(list.Size() == 4);
			REQUIRE(it == list.End());
		}

		SECTION("Erase in the middle")
		{
			auto itTo3 = std::next(list.Begin(), 2);
			auto it = list.Erase(itTo3);
			REQUIRE(list.Size() == 3);
			REQUIRE(list.Front() == TestType{ 1 });
			REQUIRE(list.Back() == TestType{ 4 });
			REQUIRE(*it == TestType{ 4 });

			// Verify order
			auto current = list.Begin();
			REQUIRE(*current == TestType{ 1 });
			++current;
			REQUIRE(*current == TestType{ 2 });
			++current;
			REQUIRE(*current == TestType{ 4 });
			++current;
			REQUIRE(current == list.End());
		}

		SECTION("Erase the last element")
		{
			auto itTo4 = std::prev(list.End());
			auto it = list.Erase(itTo4);
			REQUIRE(list.Size() == 3);
			REQUIRE(list.Front() == TestType{ 1 });
			REQUIRE(list.Back() == TestType{ 3 });
			REQUIRE(it == list.End());

			// Verify order
			auto current = list.Begin();
			REQUIRE(*current == TestType{ 1 });
			++current;
			REQUIRE(*current == TestType{ 2 });
			++current;
			REQUIRE(*current == TestType{ 3 });
			++current;
			REQUIRE(current == list.End());
		}

		SECTION("Erase the only element")
		{
			List<ValueType> singleElementList = { TestType{ 100 } };
			auto it = singleElementList.Erase(singleElementList.Begin());
			REQUIRE(singleElementList.Empty());
			REQUIRE(singleElementList.Size() == 0);
			REQUIRE(it == singleElementList.End());
		}

		SECTION("Erase from empty list (should do nothing)")
		{
			List<ValueType> emptyList;
			auto it = emptyList.Erase(emptyList.Begin());
			REQUIRE(emptyList.Empty());
			REQUIRE(emptyList.Size() == 0);
			REQUIRE(it == emptyList.End());

			it = emptyList.Erase(emptyList.End());
			REQUIRE(emptyList.Empty());
			REQUIRE(emptyList.Size() == 0);
			REQUIRE(it == emptyList.End());
		}
	}

	SECTION("EmplaceFront and EmplaceBack")
	{
		List<ValueType> list;
		REQUIRE(list.Empty());

		list.EmplaceBack(TestType{ 1 });
		REQUIRE(list.Size() == 1);
		REQUIRE(list.Back() == TestType{ 1 });

		list.EmplaceFront(TestType{ 0 });
		REQUIRE(list.Size() == 2);
		REQUIRE(list.Front() == TestType{ 0 });

		if constexpr (std::is_same_v<ValueType, std::string>)
		{
			list.EmplaceBack("hello");
			REQUIRE(list.Size() == 3);
			REQUIRE(list.Back() == "hello");

			list.EmplaceFront("world");
			REQUIRE(list.Size() == 4);
			REQUIRE(list.Front() == "world");
		}
	}
}

TEMPLATE_TEST_CASE("List Iterator Functionality - ", "[List][Iterator]", int, std::string)
{
	using ValueType = TestType;
	List<ValueType> list;

	SECTION("Empty list iterators")
	{
		auto it = list.Begin();
		auto cit = list.cbegin();

		REQUIRE(it == list.End());
		REQUIRE(cit == list.cend());
		// Dereferencing end() or begin() on empty list should trigger assert in debug.
		// Incrementing/Decrementing end() or begin() on empty list should also trigger assert.
	}

	SECTION("Single element list iterators")
	{
		list.PushBack(TestType{ 10 });
		auto it = list.Begin();
		auto cit = list.cbegin();

		REQUIRE(it == list.Begin());
		REQUIRE(it != list.End());
		REQUIRE(cit == list.cbegin());
		REQUIRE(cit != list.cend());

		REQUIRE(*it == TestType{ 10 });
		REQUIRE(*cit == TestType{ 10 });

		if constexpr (std::is_same_v<ValueType, std::string>)
		{
			REQUIRE(it->size() > 0);
			REQUIRE(cit->size() > 0);
		}

		++it;
		REQUIRE(it == list.End());

		++cit;
		REQUIRE(cit == list.cend());

		--it;
		REQUIRE(it == list.Begin());

		--cit;
		REQUIRE(cit == list.cbegin());
	}

	SECTION("Multiple elements list iterators")
	{
		list = { TestType{ 1 }, TestType{ 2 }, TestType{ 3 } };

		SECTION("Forward iteration (ListIterator)")
		{
			auto it = list.Begin();
			REQUIRE(*it == TestType{ 1 });
			++it;
			REQUIRE(*it == TestType{ 2 });
			++it;
			REQUIRE(*it == TestType{ 3 });
			++it;
			REQUIRE(it == list.End());
		}

		SECTION("Forward iteration (ConstListIterator)")
		{
			auto cit = list.cbegin();
			REQUIRE(*cit == TestType{ 1 });
			++cit;
			REQUIRE(*cit == TestType{ 2 });
			++cit;
			REQUIRE(*cit == TestType{ 3 });
			++cit;
			REQUIRE(cit == list.cend());
		}

		SECTION("Backward iteration (ListIterator)")
		{
			auto it = list.End();
			--it;
			REQUIRE(*it == TestType{ 3 });
			--it;
			REQUIRE(*it == TestType{ 2 });
			--it;
			REQUIRE(*it == TestType{ 1 });
			// Decrementing past Begin() will trigger assert in debug.
		}

		SECTION("Backward iteration (ConstListIterator)")
		{
			auto cit = list.cend();
			--cit;
			REQUIRE(*cit == TestType{ 3 });
			--cit;
			REQUIRE(*cit == TestType{ 2 });
			--cit;
			REQUIRE(*cit == TestType{ 1 });
			// Decrementing past cbegin() will trigger assert in debug.
		}

		SECTION("Pre and post increment/decrement")
		{
			auto it = list.Begin();
			REQUIRE(*(it++) == TestType{ 1 });
			REQUIRE(*it == TestType{ 2 });

			REQUIRE(*(++it) == TestType{ 3 });
			REQUIRE(*it == TestType{ 3 });

			auto endIt = list.End();
			--endIt;
			REQUIRE(*(endIt--) == TestType{ 3 });

			REQUIRE(*(--endIt) == TestType{ 1 });
			REQUIRE(*endIt == TestType{ 1 });
		}

		SECTION("Iterator equality and inequality")
		{
			auto it1 = list.Begin();
			auto it2 = list.Begin();
			auto it3 = std::next(list.Begin());
			auto cit1 = list.cbegin();
			auto cit2 = list.cbegin();

			REQUIRE(it1 == it2);
			REQUIRE(cit1 == cit2);

			REQUIRE(it1 != it3);
			REQUIRE(it1 != list.End());
			REQUIRE(it3 != list.End());
		}

		SECTION("Dereferencing and arrow operator")
		{
			auto it = list.Begin();
			REQUIRE(*it == TestType{ 1 });
			if constexpr (std::is_same_v<ValueType, std::string>)
			{
				REQUIRE(it->length() > 0);
			}

			auto cit = list.cbegin();
			REQUIRE(*cit == TestType{ 1 });
			if constexpr (std::is_same_v<ValueType, std::string>)
			{
				REQUIRE(cit->length() > 0);
			}

			// Can modify through ListIterator
			*it = TestType{ 11 };
			REQUIRE(list.Front() == TestType{ 11 });

			// Cannot modify through ConstListIterator (compile error)
			//*cit = TestType{ 11 };
		}
	}
}

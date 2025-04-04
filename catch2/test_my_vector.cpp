#include "catch2.h"

#include <algorithm>

/////////////////////////////////////////////////////
//
//	ALLOCATOR TESTS
//
/////////////////////////////////////////////////////

TEST_CASE("Allocator static asserts for forbidden types must not compile")
{
	// details::Allocator<const int> v1;
	// details::Allocator<void()> v2;
	// details::Allocator<int&> v3;
}

TEST_CASE("Allocator correctly reallocates elements")
{
	details::Allocator<std::string> alloc;
	std::string* oldBlock = alloc.Allocate(2);
	new (&oldBlock[0]) std::string("first");
	new (&oldBlock[1]) std::string("second");

	std::string* newBlock = alloc.Reallocate(oldBlock, 2, 3);
	REQUIRE(newBlock != nullptr);
	REQUIRE(newBlock[0] == "first");
	REQUIRE(newBlock[1] == "second");

	newBlock[0].~basic_string();
	newBlock[1].~basic_string();
	alloc.Free(newBlock, 3);
}

/////////////////////////////////////////////////////
//
//	CONTAINER BASE TESTS
//
/////////////////////////////////////////////////////

TEST_CASE("ContainerBase constructors and assignment work as intended")
{
	details::ContainerBase<int> original;
	original.EmplaceBack(1);
	original.EmplaceBack(2);

	SECTION("Copy constructor")
	{
		details::ContainerBase<int> copy(original);
		REQUIRE(copy.Size() == 2);
		REQUIRE(copy.Begin()[0] == 1);
		REQUIRE(copy.Begin()[1] == 2);
	}

	SECTION("Move constructor")
	{
		details::ContainerBase<int> moved(std::move(original));
		REQUIRE(moved.Size() == 2);
		REQUIRE(original.Size() == 0);
	}

	SECTION("Copy assignment")
	{
		details::ContainerBase<int> copy;
		copy = original;
		REQUIRE(copy.Size() == 2);
	}

	SECTION("Move assignment")
	{
		details::ContainerBase<int> moved;
		moved = std::move(original);
		REQUIRE(moved.Size() == 2);
		REQUIRE(original.Size() == 0);
	}
}

TEST_CASE("ContainerBase correctly manages elements")
{
	details::ContainerBase<int> container;

	SECTION("EmplaceBack adds elements")
	{
		container.EmplaceBack(42);
		REQUIRE(container.Size() == 1);
		REQUIRE(container.Begin()[0] == 42);
	}

	SECTION("Resize changes size")
	{
		container.Resize(5);
		REQUIRE(container.Size() == 5);
		container.Resize(3);
		REQUIRE(container.Size() == 3);
	}

	SECTION("Reserve increases capacity")
	{
		container.Reserve(10);
		REQUIRE(container.Capacity() >= 10);
	}

	SECTION("PopBack decreases size")
	{
		container.EmplaceBack(1);
		container.PopBack();
		REQUIRE(container.Size() == 0);
	}

	SECTION("Clear removes all elements")
	{
		container.EmplaceBack(1);
		container.Clear();
		REQUIRE(container.Size() == 0);
	}
}

namespace
{

std::ostringstream g_logStream;

const std::string CONSTRUCTED_MSG = "Constructed";
const std::string COPIED_MSG = "Copied";
const std::string MOVED_MSG = "Moved";
const std::string DESTROYED_MSG = "Destroyed";

void Log(const std::string& message)
{
	g_logStream << message << "\n";
}

struct LogData
{
	size_t constructed = 0;
	size_t copied = 0;
	size_t moved = 0;
	size_t destroyed = 0;
};

LogData AnalyzeLog()
{
	LogData data;
	auto& [constructed, copied, moved, destroyed] = data;

	std::istringstream iss(g_logStream.str());
	std::string line;

	while (std::getline(iss, line))
	{
		if (line == CONSTRUCTED_MSG)
		{
			++constructed;
		}
		else if (line == COPIED_MSG)
		{
			++copied;
		}
		else if (line == MOVED_MSG)
		{
			++moved;
		}
		else if (line == DESTROYED_MSG)
		{
			++destroyed;
		}
	}

	return data;
}

struct TrackedObject
{
	TrackedObject() { Log(CONSTRUCTED_MSG); }

	TrackedObject(const TrackedObject&)
	{
		Log(COPIED_MSG);
	}

	TrackedObject(TrackedObject&&) noexcept
	{
		Log(MOVED_MSG);
	}

	~TrackedObject()
	{
		Log(DESTROYED_MSG);
	}
};

struct NonMovableTrackedObject
{
	NonMovableTrackedObject() { Log(CONSTRUCTED_MSG); }

	NonMovableTrackedObject(const NonMovableTrackedObject& other)
	{
		Log(COPIED_MSG);
	}

	NonMovableTrackedObject(NonMovableTrackedObject&&) = delete;

	~NonMovableTrackedObject()
	{
		Log(DESTROYED_MSG);
	}
};

} // namespace

TEST_CASE("ContainerBase correctly handles TrackedObject (with move)")
{
	g_logStream.str("");

	{
		details::ContainerBase<TrackedObject> container;

		container.EmplaceBack();
		container.EmplaceBack();
		container.EmplaceBack();
	}

	auto data = AnalyzeLog();

	REQUIRE(data.constructed == 3);
	REQUIRE(data.moved == 2);
	REQUIRE(data.destroyed == 5);
}

TEST_CASE("ContainerBase correctly handles NonMovableTrackedObject (copy fallback)")
{
	g_logStream.str("");

	{
		details::ContainerBase<NonMovableTrackedObject> container;

		container.EmplaceBack();
		container.EmplaceBack();
		container.EmplaceBack();
	}

	auto data = AnalyzeLog();

	REQUIRE(data.constructed == 3);
	REQUIRE(data.copied == 2);
	REQUIRE(data.destroyed == 5);
}

/////////////////////////////////////////////////////
//
//	ITERATABLE TESTS
//
/////////////////////////////////////////////////////

TEST_CASE("Iteratable provides correct iterators")
{
	Vector<int> vec = { 1, 2, 3 };

	SECTION("Const iterators")
	{
		const Vector<int>& constVec = vec;
		REQUIRE(*constVec.begin() == 1);
		REQUIRE(constVec.end() - constVec.begin() == 3);
	}

	SECTION("Reverse iterators")
	{
		auto rit = vec.rbegin();
		REQUIRE(*rit == 3);
		++rit;
		REQUIRE(*rit == 2);
	}

	SECTION("Range-based for")
	{
		int sum = 0;
		for (auto& val : vec)
		{
			sum += val;
		}
		REQUIRE(sum == 6);
	}

	SECTION("STL Algorithm compatibility")
	{
		Vector<std::string> output;
		output.Resize(3);
		Vector<std::string> expected = { "3", "2", "1" };

		std::transform(vec.begin(), vec.end(), output.begin(), [](int val) {
			return std::to_string(val);
		});

		std::reverse(output.begin(), output.end());

		REQUIRE(output == expected);
	}
}

/////////////////////////////////////////////////////
//
//	VECTOR TESTS
//
/////////////////////////////////////////////////////

TEST_CASE("Vector specific methods work as intended")
{
	Vector<int> vec;

	SECTION("Initializer list constructor")
	{
		Vector<int> vec{ 1, 2, 3 };
		REQUIRE(vec.Size() == 3);
	}

	SECTION("PushBack adds elements")
	{
		vec.PushBack(1);
		vec.PushBack(2);
		vec.PushBack(3);
		REQUIRE(vec[0] == 1);
		REQUIRE(vec[1] == 2);
		REQUIRE(vec[2] == 3);
	}

	SECTION("Operator[] throws on out of range")
	{
		REQUIRE_THROWS_AS(vec[vec.Size() + 1], std::out_of_range);
	}
}

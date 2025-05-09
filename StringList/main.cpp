#include <iostream>
#include <list>

#include "StringList.h"

#define CONST_PRINT 1

#if CONST_PRINT
void Print(const StringList& list)
{
	std::cout << "Front: " << list.Front() << std::endl;
	for (const auto& val : list)
	{
		std::cout << val << std::endl;
	}
	std::cout << "Back: " << list.Back() << std::endl;
}
#else
void Print(StringList& list)
{
	list.Front() = "changed";
	list.Back() = "changed too";
	std::cout << "Front: " << list.Front() << std::endl;
	for (const auto& val : list)
	{
		std::cout << val << std::endl;
	}
	std::cout << "Back: " << list.Back() << std::endl;
}
#endif

int main()
{
	List<int> list(0);

#if 0
	std::list<std::string> stl = { "123", "456", "789" };
	stl.emplace_back("abiba");
	stl.emplace_front("aboba");
	StringList sl;

	sl.PushBack("aboba");
	sl.PushBack("abiba");
	sl.PushFront("aboba");
	sl.PushBack("abiba");
	auto it = sl.begin();
	++it;
	std::string s = "ssss";
	sl.Insert(it, s);
	sl.PushBack(s);
	sl.EmplaceFront("1234");
	std::cout << "----------------\n";

	for (auto rit = sl.rbegin(); rit != sl.rend(); ++rit)
	{
		std::cout << *rit << std::endl;
	}

	std::cout << "----------------\n";
	sl.Erase(--it);

	Print(sl);
	std::cout << std::endl;

	std::cout << "Hello World!" << std::endl;
#endif
}

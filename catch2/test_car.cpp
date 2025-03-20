#include "catch2.h"

void RunTestCase(const std::vector<std::string>& commands, const std::string& expectedOutput)
{
	std::ostringstream output;
	CarController controller(output);

	for (const auto& command : commands)
	{
		controller.ExecuteCommand(command);
	}

	REQUIRE(expectedOutput == output.str());
}

TEST_CASE("Engine On and Off", "[Car]")
{
	RunTestCase({ "EngineOn", "EngineOff" }, "");
	RunTestCase({ "EngineOn", "SetGear 1", "EngineOff" }, "Car must be stopped and in neutral gear\n");
}

TEST_CASE("Set Gear", "[Car]")
{
	RunTestCase({ "EngineOn", "SetGear 10" }, "Invalid gear\n");
	RunTestCase({ "SetGear 1" }, "Cannot set gear while engine is off\n");
	RunTestCase({ "EngineOn", "SetGear 1", "SetSpeed 25", "SetGear 4" }, "Unsuitable current speed\n");
	RunTestCase({ "EngineOn", "SetGear 1", "SetSpeed 25", "SetGear -1" }, "Cannot reverse while moving\n");
	RunTestCase({ "EngineOn", "SetGear 1" }, "");
}

TEST_CASE("Set Speed", "[Car]")
{
	RunTestCase({ "EngineOn", "SetGear 1", "SetSpeed -5" }, "Speed cannot be negative\n");
	RunTestCase({ "SetSpeed 10" }, "Cannot set speed while engine is off\n");
	RunTestCase({ "EngineOn", "SetSpeed 15" }, "Cannot accelerate on neutral\n");
	RunTestCase({ "EngineOn", "SetGear 1", "SetSpeed 40" }, "Speed is out of gear range\n");
	RunTestCase({ "EngineOn", "SetGear 1", "SetSpeed 20" }, "");
}

TEST_CASE("Speed limits for each gear", "[Car]")
{
	RunTestCase({ "EngineOn", "SetGear -1", "SetSpeed 0" }, "");
	RunTestCase({ "EngineOn", "SetGear -1", "SetSpeed 20" }, "");
	RunTestCase({ "EngineOn", "SetGear -1", "SetSpeed 21" }, "Speed is out of gear range\n");

	RunTestCase({ "EngineOn", "SetGear 1", "SetSpeed 0" }, "");
	RunTestCase({ "EngineOn", "SetGear 1", "SetSpeed 30" }, "");
	RunTestCase({ "EngineOn", "SetGear 1", "SetSpeed 31" }, "Speed is out of gear range\n");

	RunTestCase({ "EngineOn", "SetGear 1", "SetSpeed 20", "SetGear 2", "SetSpeed 19" }, "Speed is out of gear range\n");
	RunTestCase({ "EngineOn", "SetGear 1", "SetSpeed 20", "SetGear 2", "SetSpeed 20" }, "");
	RunTestCase({ "EngineOn", "SetGear 1", "SetSpeed 20", "SetGear 2", "SetSpeed 50" }, "");
	RunTestCase({ "EngineOn", "SetGear 1", "SetSpeed 20", "SetGear 2", "SetSpeed 51" }, "Speed is out of gear range\n");

	RunTestCase({ "EngineOn", "SetGear 1", "SetSpeed 20", "SetGear 2", "SetSpeed 30", "SetGear 3", "SetSpeed 29" }, "Speed is out of gear range\n");
	RunTestCase({ "EngineOn", "SetGear 1", "SetSpeed 20", "SetGear 2", "SetSpeed 30", "SetGear 3", "SetSpeed 30" }, "");
	RunTestCase({ "EngineOn", "SetGear 1", "SetSpeed 20", "SetGear 2", "SetSpeed 30", "SetGear 3", "SetSpeed 60" }, "");
	RunTestCase({ "EngineOn", "SetGear 1", "SetSpeed 20", "SetGear 2", "SetSpeed 30", "SetGear 3", "SetSpeed 61" }, "Speed is out of gear range\n");

	RunTestCase({ "EngineOn", "SetGear 1", "SetSpeed 20", "SetGear 2", "SetSpeed 40", "SetGear 4", "SetSpeed 39" }, "Speed is out of gear range\n");
	RunTestCase({ "EngineOn", "SetGear 1", "SetSpeed 20", "SetGear 2", "SetSpeed 40", "SetGear 4", "SetSpeed 40" }, "");
	RunTestCase({ "EngineOn", "SetGear 1", "SetSpeed 20", "SetGear 2", "SetSpeed 40", "SetGear 4", "SetSpeed 90" }, "");
	RunTestCase({ "EngineOn", "SetGear 1", "SetSpeed 20", "SetGear 2", "SetSpeed 40", "SetGear 4", "SetSpeed 91" }, "Speed is out of gear range\n");

	RunTestCase({ "EngineOn", "SetGear 1", "SetSpeed 20", "SetGear 2", "SetSpeed 30", "SetGear 3", "SetSpeed 50", "SetGear 5", "SetSpeed 49" }, "Speed is out of gear range\n");
	RunTestCase({ "EngineOn", "SetGear 1", "SetSpeed 20", "SetGear 2", "SetSpeed 30", "SetGear 3", "SetSpeed 50", "SetGear 5", "SetSpeed 50" }, "");
	RunTestCase({ "EngineOn", "SetGear 1", "SetSpeed 20", "SetGear 2", "SetSpeed 30", "SetGear 3", "SetSpeed 50", "SetGear 5", "SetSpeed 150" }, "");
	RunTestCase({ "EngineOn", "SetGear 1", "SetSpeed 20", "SetGear 2", "SetSpeed 30", "SetGear 3", "SetSpeed 50", "SetGear 5", "SetSpeed 151" }, "Speed is out of gear range\n");
}

TEST_CASE("Test direction", "[Car]")
{
	RunTestCase({ "EngineOn", "SetGear -1", "SetSpeed 5", "SetSpeed 0", "Info" },
		"Engine: on\nDirection: standing still\nSpeed: 0\nGear: -1\n");

	RunTestCase({ "EngineOn", "SetGear 1", "SetSpeed 15", "SetSpeed 0", "Info" },
		"Engine: on\nDirection: standing still\nSpeed: 0\nGear: 1\n");

	RunTestCase({ "EngineOn", "SetGear 1", "SetSpeed 15", "Info" },
		"Engine: on\nDirection: forward\nSpeed: 15\nGear: 1\n");

	RunTestCase({ "EngineOn", "SetGear -1", "SetSpeed 15", "SetGear 0", "SetSpeed 5", "Info" },
		"Engine: on\nDirection: backward\nSpeed: 5\nGear: 0\n");
}

TEST_CASE("Full Valid Sequence", "[Car]")
{
	RunTestCase(
		{ "EngineOn", "SetGear 1", "SetSpeed 20", "SetGear 2", "SetSpeed 30", "SetGear 3", "SetSpeed 50", "SetGear 4",
			"SetSpeed 60", "SetGear 5", "SetSpeed 80", "SetGear 4", "SetSpeed 40",
			"SetGear 2", "SetSpeed 20", "SetGear 1", "SetSpeed 0", "SetGear 0", "EngineOff" },
		"");
}

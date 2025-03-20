#include "catch2.h"

void RunTestCase(const std::vector<std::string>& commands, const std::string& expectedOutput)
{
	std::istringstream input;
	std::ostringstream output;
	CarController controller(input, output);

	for (const auto& command : commands)
	{
		controller.ExecuteCommand(command);
	}

	REQUIRE(output.str() == expectedOutput);
}

TEST_CASE("Engine On and Off")
{
	RunTestCase({ "EngineOn", "EngineOff" }, "");
	RunTestCase({ "EngineOn", "SetGear 1", "EngineOff" }, "Car must be stopped and in neutral gear\n");
}

TEST_CASE("Set Gear")
{
	RunTestCase({ "EngineOn", "SetGear 10" }, "Invalid gear\n");
	RunTestCase({ "SetGear 1" }, "Cannot set gear while engine is off\n");
	RunTestCase({ "EngineOn", "SetGear 1", "SetSpeed 25", "SetGear 4" }, "Unsuitable current speed\n");
	RunTestCase({ "EngineOn", "SetGear 1", "SetSpeed 25", "SetGear -1" }, "Cannot reverse while moving\n");
	RunTestCase({ "EngineOn", "SetGear 1" }, "");
}

TEST_CASE("Set Speed")
{
	RunTestCase({ "EngineOn", "SetGear 1", "SetSpeed -5" }, "Speed cannot be negative\n");
	RunTestCase({ "SetSpeed 10" }, "Cannot set speed while engine is off\n");
	RunTestCase({ "EngineOn", "SetSpeed 15" }, "Cannot accelerate on neutral\n");
	RunTestCase({ "EngineOn", "SetGear 1", "SetSpeed 40" }, "Speed is out of gear range\n");
	RunTestCase({ "EngineOn", "SetGear 1", "SetSpeed 20" }, "");
}

TEST_CASE("Neutral Gear Behavior")
{
	RunTestCase({ "EngineOn", "SetGear 1", "SetSpeed 20", "SetGear 0", "SetSpeed 30" }, "Cannot accelerate on neutral\n");
}

TEST_CASE("Full Valid Sequence")
{
	RunTestCase(
		{ "EngineOn", "SetGear 1", "SetSpeed 20", "SetGear 2", "SetSpeed 30", "SetGear 3", "SetSpeed 50", "SetGear 4",
			"SetSpeed 60", "SetGear 5", "SetSpeed 80", "SetGear 4", "SetSpeed 40",
			"SetGear 2", "SetSpeed 20", "SetGear 1", "SetSpeed 0", "SetGear 0", "EngineOff" },
		"");
}

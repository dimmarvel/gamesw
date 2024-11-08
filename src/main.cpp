#include <Engine/Core/GameObserver.hpp>
#include <Engine/Core/Map.hpp>
#include <Engine/Core/Settings.hpp>
#include <Engine/Renderer/TextRenderer.hpp>
#include <IO/Commands/CreateMap.hpp>
#include <IO/Commands/March.hpp>
#include <IO/Commands/SpawnHunter.hpp>
#include <IO/Commands/SpawnSwordsman.hpp>
#include <IO/Events/MapCreated.hpp>
#include <IO/Events/MarchEnded.hpp>
#include <IO/Events/MarchStarted.hpp>
#include <IO/Events/UnitAttacked.hpp>
#include <IO/Events/UnitDied.hpp>
#include <IO/Events/UnitMoved.hpp>
#include <IO/Events/UnitSpawned.hpp>
#include <IO/System/CommandParser.hpp>
#include <IO/System/EventLog.hpp>
#include <IO/System/PrintDebug.hpp>
#include <fstream>
#include <iostream>

int main(int argc, char** argv)
{
	using namespace sw;

	if (argc != 2)
	{
		throw std::runtime_error("Error: No file specified in command line argument");
	}

	std::ifstream file(argv[1]);
	if (!file)
	{
		throw std::runtime_error("Error: File not found - " + std::string(argv[1]));
	}

	try
	{
		auto renderer = std::make_unique<engine::TextRenderer>();
		engine::Settings settings{5, 5, file};
		std::shared_ptr<engine::GameObserver> game
			= std::make_shared<engine::GameObserver>(settings, std::move(renderer));
		game->start();
		return EXIT_SUCCESS;
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << '\n';
		return EXIT_FAILURE;
	}
}

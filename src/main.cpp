#include <Engine/Core/GameObserver.hpp>
#include <Engine/Core/Settings.hpp>
#include <Engine/Renderer/TextRenderer.hpp>
#include <fstream>

int main(int argc, char** argv)
{
	using namespace sw;

	try
	{
		if (argc != 2)
		{
			throw std::runtime_error("Error: No file specified in command line argument");
		}

		std::ifstream file(argv[1]);
		if (!file)
		{
			throw std::runtime_error("Error: File not found - " + std::string(argv[1]));
		}

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

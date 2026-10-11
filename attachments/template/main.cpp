#include <cstdint>
#include <memory>
#if defined(__INTELLISENSE__) || !defined(USE_CPP20_MODULES)
# if(WIN32)
#	include <C:/VulkanSDK/1.4.363.0/include/vulkan/vulkan_raii.hpp>
#	include <C:/glfw-3.5.1.bin.WIN64/include/GLFW/glfw3.h>
#else
#	include <GLFW/glfw3.h>
#	include<vulkan/vulkan_raii.hpp>
#endif
#else
import vulkan_hpp;
#endif

#include <cstdlib>
#include <iostream>
#include <stdexcept>

//Linux build command:
//cd ~/Applications/Vulkan-Tutorial/attachments/template && cmake -S . -B build -G Ninja -DSLANGC_EXECUTABLE="$(command -v slangc)" && cmake --build build && ./build/VulkanTutorial/VulkanTutorial

const uint32_t WIDTH  = 800;
const uint32_t HEIGHT = 600;

class HelloTriangleApplication
{
  public:
	void run()
	{
		initWindow();
		initVulkan();
		mainLoop();
		cleanup();
	}

  private:
	GLFWwindow *window = nullptr;

	void initWindow()
	{
		glfwInit();

		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
		glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

		window = glfwCreateWindow(WIDTH, HEIGHT, "Vulkan", nullptr, nullptr);
	}

	void initVulkan()
	{
	}

	void mainLoop()
	{
		while (!glfwWindowShouldClose(window))
		{
			glfwPollEvents();
		}
	}

	void cleanup()
	{
		glfwDestroyWindow(window);

		glfwTerminate();
	}
};

int main()
{
	try
	{
		HelloTriangleApplication app;
		app.run();
	}
	catch (const std::exception &e)
	{
		std::cerr << e.what() << std::endl;
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}

#include <cstdint>
#include <memory>
#	define VULKAN_HPP_NO_STRUCT_CONSTRUCTORS
#	define VULKAN_HPP_DISPATCH_LOADER_DYNAMIC 1
#	include<vulkan/vulkan_raii.hpp>
#if defined(__INTELLISENSE__) || !defined(USE_CPP20_MODULES)
# if(WIN32)
#	include <C:/VulkanSDK/1.4.363.0/include/vulkan/vulkan_raii.hpp>
#	include <C:/glfw-3.5.1.bin.WIN64/include/GLFW/glfw3.h>
#else
#	include <GLFW/glfw3.h>
#endif
#else
import vulkan_hpp;
#endif
#define VK_USE_PLATFORM_WIN32_KHR
#define GLFW_INCLUDE_VULKAN
#define GLFW_EXPOSE_NATIVE_WIN32
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
		createInstance();
		mainLoop();
		cleanup();
	}

  private:
	GLFWwindow *window = nullptr;
	//communication portal between th os and the vulkan api, used to create a surface for rendering
	vk::raii::SurfaceKHR surface = nullptr;
	//the vulkan context, which is used to manage the vulkan instance and other vulkan objects
	vk::raii::Context  context;
	//the vulkan instance, which is the connection between the application and the vulkan library
	vk::raii::Instance instance = nullptr;
	//Instance of the application wide information, such as the application name and version, the engine name and version, and the API version

	void initWindow()
	{
		glfwInit();

		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
		glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

		window = glfwCreateWindow(WIDTH, HEIGHT, "Vulkan", nullptr, nullptr);
	}

	void createInstance() {
		uint32_t glfwExtentionCount = 0;
		auto glfw_Extentsions = glfwGetRequiredInstanceExtensions(&glfwExtentionCount);
		auto extesionsProperties = context.enumerateInstanceExtensionProperties();
		for (uint32_t i = 0; i < glfwExtentionCount; ++i) {
			if (std::ranges::none_of(
				extesionsProperties,
				[glfw_Extentsion = glfw_Extentsions[i]]
				(auto const& extensionProperty) {
					return strcmp(extensionProperty.extensionName, glfw_Extentsion) == 0;
				} )) {
				throw std::runtime_error{"GLFW required extension not supported by Vulkan: " + std::string{glfw_Extentsions[i]}};
				}
		}
		vk::ApplicationInfo appInfo = {
			.pApplicationName   = "Hello Triangle",
			.applicationVersion = VK_MAKE_VERSION( 1, 0, 0 ),
			.pEngineName        = "No Engine",
			.engineVersion      = VK_MAKE_VERSION( 1, 0, 0 ),
			.apiVersion         = vk::ApiVersion14};

		const vk::InstanceCreateInfo createInfo = {
			.pApplicationInfo = &appInfo
		};
		
		vk::InstanceCreateInfo instanceCreateInfo = {
			.pApplicationInfo = &appInfo,
			.enabledExtensionCount = glfwExtentionCount,
			.ppEnabledExtensionNames = glfw_Extentsions,
		};

		instance = vk::raii::Instance(context, createInfo);
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

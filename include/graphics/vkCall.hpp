/*
*   name: include/graphics/vkNullCall.hpp
*   origin: Citrus Engine
*   purpose: Provide preprocessor defines for Vulkan call wrappers
*   author: https://github.com/ComradeYellowCitrusFruit
*   license: LGPL-3.0-only
*/

#ifndef CITRUS_ENGINE_VULKAN_CALLS_HPP__
#define CITRUS_ENGINE_VULKAN_CALLS_HPP__

#include <vulkan.h>
#include <cstdint>
#include "../graphics/vkGlobals.hpp"
#include "../core/extensions.h"

namespace engine
{
namespace internals
{
	namespace Vulkan
	{
		typedef VkResult (*vkFuncPtr_t)(...);

		// TODO: Redo this cause apparently there are a fuck ton of errors

		/*  Make a call to a Vulkan device function.
		*   All of the arguments after func will be passed in order to the function being called
		*   @param func Function to call
		*   @param device Device to call the function on
		*   @return Returns the function's return value
		*/
		#define vkDeviceCall(func, device, ...)  __VA_ARGS_FIX__((*(vkFuncPtr_t)vkGetDeviceProcAddr(__STRINGIFY_(func)))(__VA_ARGS__))

		/*  Make a call to a Vulkan instance function.
		*   All of the arguments after func will be passed in order to the function being called
		*   @param func Function to call
		*   @param instance Instance to call the function on
		*   @return Returns the function's return value
		*/
		#define vkInstanceCall(func, instance, ...) __VA_ARGS_FIX__((*(vkFuncPtr_t)vkGetInstanceProcAddr(instance, __STRINGIFY_(func)))(__VA_ARGS__))

		/*  Make a call to a Vulkan function that doesn't take an instance or device in the function call.
		*   All of the arguments after func will be passed in order to the function being called
		*   @param func Function to call
		*   @return Returns the function's return value
		*/
		#define vkNullCall(func, ...) __VA_ARGS_FIX__((*(vkFuncPtr_t)vkGetInstanceProcAddr(VK_NULL_HANDLE, __STRINGIFY__(func))(__VA_ARGS__)))
	};
};
};

#endif
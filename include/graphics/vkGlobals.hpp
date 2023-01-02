/*
*	This file is part of the Citrus Engine.
*
*	The Citrus Engine is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
*
*	The Citrus Engine is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.
*
*	You should have received a copy of the GNU Lesser General Public License along with the Citrus Engine. If not, see <https://www.gnu.org/licenses/>	
*/

#ifndef CITRUS_ENGINE_VULKAN_GLOBALS_HPP__
#define CITRUS_ENGINE_VULKAN_GLOBALS_HPP__

#include <vulkan.h>

#ifdef _WIN32

#include <Windows.h>
typedef HMODULE dllptr_t;

#elif defined(__unix__)

typedef void* dllptr_t;

#endif

#include "include/graphics/vkCall.hpp"

#ifndef VULKAN_VERSION
#define VULKAN_VERSION VK_VERSION_1_0
#endif

namespace engine
{
namespace internals
{
	namespace Vulkan
	{
		typedef PFN_vkVoidFunction (vkGIPA_t)(VkInstance, const char*);
		typedef PFN_vkVoidFunction (vkGDPA_t)(VkDevice, const char*);

		// The address of the Vulkan library
		extern dllptr_t libvulkan;

		// Good ol' vkGetInstanceProcAddr
		extern vkGIPA_t vkGetInstanceProcAddr;
		// Good ol' vkGetDeviceProcAddr
		extern vkGDPA_t vkGetDeviceProcAddr;
		
		extern VkAllocationCallbacks allocCallbacks;
		extern VkInstance instance;
		extern VkDevice device;
	};
};
};

#endif
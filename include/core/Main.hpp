/*
*	name: include/core/Main.hpp
*	origin: Citrus Engine
*	purpose: Provide the main engine functions
*	author: https://github.com/ComradeYellowCitrusFruit
*	license: LGPL-3.0-only
*/

#ifndef CITRUS_ENGINE_MAIN_FUNCTIONS_HPP__
#define CITRUS_ENGINE_MAIN_FUNCTIONS_HPP__

#ifdef __STDC_NO_THREADS__

#error The Citrus Engine requires threads.h

#endif

#include <threads.h>
#include <ctime>
#include <csetjmp>
#include "core/extensions.h"

WEAK NO_INLINE void realMain();

namespace engine
{
	namespace internals
	{
		namespace Vulkan
		{
			NEVER_INLINE int vkDraw();
		}

		extern bool usingVulkan;
		extern int frameRate;
		extern jmp_buf buf;

		extern thrd_t render;
		extern thrd_t phys;
		extern thrd_t audio;
		extern thrd_t gameplay;

		// Making these functions weak aliases is INCREDIBLY useful for modding

		// Render the scene, and draw the UI
		NEVER_INLINE WEAK ALIAS(engine::internals::Vulkan::vkDraw)
		int draw();
		// Step the physics simulation, and call all physics triggered functions
		NEVER_INLINE
		int physmain();
		// Perform audio operations
		NEVER_INLINE
		int mix();

		// Run the gameplay code
		NEVER_INLINE
		int gameplayMain();
	};
};

#endif
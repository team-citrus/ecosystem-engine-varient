/*
*   name: include/core/json.hpp
*   origin: Citrus Engine
*   purpose: Provide nlohmann/json while hiding internals
*   author: Niels Lohmann
*   license: MIT
*/
#ifndef CITRUS_ENGINE_JSON_PARSER_HPP__
#define CITRUS_ENGINE_JSON_PARSER_HPP__

#include <string>
#include "../core/vector.hpp"
#include "../core/pair.hpp"

#define NLOHMANN_JSON_NAMESPACE_BEGIN                \
    namespace engine                                 \
    {                                                \ 
    namespace internals                              \
    {                                                \
	inline namespace nlohmann						 \
	{												 \
    inline namespace NLOHMANN_JSON_NAMESPACE_CONCAT( \
                NLOHMANN_JSON_ABI_TAGS,              \
                NLOHMANN_JSON_NAMESPACE_VERSION)     \
    {

#define NLOHMANN_JSON_NAMESPACE_END                                     \
    }  /* namespace (inline namespace) NOLINT(readability/namespace) */ \
    }  /* namespace nlohmann */											\
    }  /* namespace internals */                                        \
	}  /* namespace engine */

#include <nlohmann/json.hpp>

#undef NLOHMANN_JSON_NAMESPACE_BEGIN
#undef NLOHMANN_JSON_NAMESPACE_END

namespace engine
{
	using JSon = internals::json;
    // APPARENTLY ACCORDING TO MY IDE THERE IS A FUCKING ERROR HERE THAT JUST WONT FUCKING GO AWAY, AND THIS COMMENT SHUTS IT THE FUCK UP, SO DONT FUCK WITH IT
}

#endif
/*
*   name: include/core/mesh.hpp
*   origin: Citrus Engine
*   purpose: Provide a class for meshes that should work for most things
*   author: https://github.com/ComradeYellowCitrusFruit
*   license: LGPL-3.0-only
*/

#ifndef CITRUS_ENGINE_MESH_HPP__
#define CITRUS_ENGINE_MESH_HPP__

#include <cstddef>
#include "core/rustints.h"
#include "core/transform.hpp"
#include "core/component.hpp"

namespace engine
{   
	using IndexBuffer = Vector<size_t>;

	namespace internals
	{
		class meshBufferHandle
		{
			int flags;
			size_t refs;
			public:
			meshBufferHandle(const char *meshName);

			// Index buffer, useful for to save memory,
			IndexBuffer indexBuffer;

			// The actual vertices.
			Vector<Vertex> verts;

			// Vertex groups
			IndexBuffer *vertexGroups;
			size_t groupCount;
			
			meshBufferHandle &getNew(const char *meshName, int flags);
			meshBufferHandle &getNew(int flags);
			void removeRef();
		};
	}

	class Vertex
	{
		public:
		Float3 pos;
		Float2 uv;

		// TODO: Vertex normals?
		// TODO: Methods... maybe?
	}

	class Face
	{
		public:
		Vertex &a;
		Vertex &b;
		Vertex &c;

		// TODO: Face normals?
		// TODO: Methods... maybe?
	};

	class Mesh
	{
		internals::meshBufferHandle &buf; // Mesh buffers will be used to save memory by pointing them to the same buffer until a write/non-RO access occurs, then creating a new one.
		
		public:

		// Creates an uninitalized mesh
		Mesh(); 
		// Loads mesh, and returns this class.
		Mesh(const char *name); 

		Face &indexFace(size_t i);
		Vertex &operator[](size_t i)
		{
			return buf.verts[i];
		}

		// TODO: Stuff
	};

	class MeshRenderer : Component
	{
		public:
		Mesh mesh;

		// TODO: settings and materials and shaders
	}

	using Tri = Face;
	using Vert = Vertex;
	using Model = Mesh;

	// TODO: iterators
}

#endif
#pragma once
#include "gl core/core shader.h"
#include "system/camera_3d.h"
#include <memory>
#include "gl core/vertex_buffer.h"


namespace wizm {


	struct alignas(16) Cluster
	{
		glm::vec4 minPoint;
		glm::vec4 maxPoint;
		unsigned int count;
		unsigned int lightIndices[100];
	};


	class compute_cluster {
	public:
		compute_cluster(std::shared_ptr<core_gl_shader>& shader, std::shared_ptr<camera_core_3d> camera, framebuffer_spec& spec)
			: m_shader(shader), m_camera(camera), m_spec(spec)
		{
			
		}

	public:

		void update() {

			m_shader->use_shader(); 
			m_shader->setFloat("zNear", m_camera->get_near());
			m_shader->setFloat("zFar", m_camera->get_far());
			m_shader->setMat4("inverseProjection", glm::inverse(m_camera->get_projection_matrix()));
			m_shader->setUVec3("gridSize", { gridSizeX, gridSizeY, gridSizeZ });
			m_shader->setUVec2("screenDimensions", { m_spec.Width, m_spec.Height });

			glDispatchCompute(gridSizeX, gridSizeY, gridSizeZ);
			glMemoryBarrier(GL_SHADER_STORAGE_BARRIER_BIT);

		
		}

	private:
		std::shared_ptr<core_gl_shader> m_shader;
		std::shared_ptr<camera_core_3d> m_camera;
		unsigned int clusterGridSSBO;

		framebuffer_spec& m_spec;

		unsigned int gridSizeX = 12;
		unsigned int gridSizeY = 12;
		unsigned int gridSizeZ = 24;
		unsigned int numClusters = gridSizeX * gridSizeY * gridSizeZ;


		



	};

}
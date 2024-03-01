#include "other utils/grid2d.h"

namespace wizm {

	//////////////////////////////////////////////////////////////////////////
	// DEFAULT CONSTRUCTOR
	//////////////////////////////////////////////////////////////////////////

	//-----------------------------------------------------------------------

	core_grid::core_grid(core_3d_camera* camera)
		:m_camera(camera)
	{


		position = glm::vec3(0.0f);

		/*shdr = new core_gl_shader("vrtx_shdr.txt", "frgmnt_shdr.txt");*/

		texture = new core_gl_texture("grid.png");

		draw_data = new core_arr_vertex_buffer(vertices, indices);
		draw_data->create_attrib_arr(0, 3, 5 * sizeof(float), 0);
		draw_data->create_attrib_arr(1, 2, 5 * sizeof(float), (3 * sizeof(float)));
		draw_data->create_buffer();
	}
	
	//-----------------------------------------------------------------------

	void core_grid::update_grid_pos()
	{
// 		position = glm::vec3(m_camera->GetPosition()[0],
//  			0, m_camera->GetPosition()[2]);
	}

	//-----------------------------------------------------------------------


	void core_grid::draw_grid()
	{
		texture->bind_texture();
		draw_data->bind_buffer();
		draw_data->draw_buffer(5);
	}

}



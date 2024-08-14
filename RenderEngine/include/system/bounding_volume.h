#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <array>

namespace wizm
{
	class bounding_volume {
    public:
        glm::vec3 min_point, min_point_local;
        glm::vec3 max_point, max_point_local;

        bounding_volume() : min_point(glm::vec3(std::numeric_limits<float>::max())),
            max_point(glm::vec3(std::numeric_limits<float>::lowest())) {}

        bounding_volume(const glm::vec3& min_point, const glm::vec3& max_point)
            : min_point(min_point), max_point(max_point) {}


        glm::vec3 get_center() const {
            return (min_point + max_point) / 2.0f;
        }

        glm::vec3 get_size() const {
            return max_point - min_point;
        }

        bool ray_intersect(glm::vec3 ray_dir, glm::vec3 ray_origin) const {
            float tmin = (min_point.x - ray_origin.x) / ray_dir.x;
            float tmax = (max_point.x - ray_origin.x) / ray_dir.x;

            if (tmin > tmax) std::swap(tmin, tmax);

            float tymin = (min_point.y - ray_origin.y) / ray_dir.y;
            float tymax = (max_point.y - ray_origin.y) / ray_dir.y;

            if (tymin > tymax) std::swap(tymin, tymax);

            if ((tmin > tymax) || (tymin > tmax))
                return false;

            if (tymin > tmin)
                tmin = tymin;

            if (tymax < tmax)
                tmax = tymax;

            float tzmin = (min_point.z - ray_origin.z) / ray_dir.z;
            float tzmax = (max_point.z - ray_origin.z) / ray_dir.z;

            if (tzmin > tzmax) std::swap(tzmin, tzmax);

            if ((tmin > tzmax) || (tzmin > tmax))
                return false;

            if (tzmin > tmin)
                tmin = tzmin;

            if (tzmax < tmax)
                tmax = tzmax;

            return true;



        }

        bool intersects(const bounding_volume& other) const {
            return (min_point.x <= other.max_point.x && max_point.x >= other.min_point.x) &&
                (min_point.y <= other.max_point.y && max_point.y >= other.min_point.y) &&
                (min_point.z <= other.max_point.z && max_point.z >= other.min_point.z);
        }

	}; 
}
#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


namespace wizm
{
	class bounding_volume {
    public:
        glm::vec3 minPoint;
        glm::vec3 maxPoint;

        bounding_volume() : minPoint(glm::vec3(std::numeric_limits<float>::max())),
            maxPoint(glm::vec3(std::numeric_limits<float>::lowest())) {}

        bounding_volume(const glm::vec3& minPoint, const glm::vec3& maxPoint)
            : minPoint(minPoint), maxPoint(maxPoint) {}

        void expandToInclude(const glm::vec3& point) {
            minPoint = glm::min(minPoint, point);
            maxPoint = glm::max(maxPoint, point);
        }

        void expandToInclude(const bounding_volume& other) {
            expandToInclude(other.minPoint);
            expandToInclude(other.maxPoint);
        }

        glm::vec3 getCenter() const {
            return (minPoint + maxPoint) / 2.0f;
        }

        glm::vec3 getSize() const {
            return maxPoint - minPoint;
        }

        bool intersects(const bounding_volume& other) const {
            // Check for overlap on all axes
            return (minPoint.x <= other.maxPoint.x && maxPoint.x >= other.minPoint.x) &&
                (minPoint.y <= other.maxPoint.y && maxPoint.y >= other.minPoint.y) &&
                (minPoint.z <= other.maxPoint.z && maxPoint.z >= other.minPoint.z);
        }

	}; 
}
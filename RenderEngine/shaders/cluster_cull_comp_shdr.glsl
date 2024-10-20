#version 460 core

#define LOCAL_SIZE 128
layout(local_size_x = LOCAL_SIZE, local_size_y = 1, local_size_z = 1) in;

struct PointLight
{
        vec4 position;       
        float constant; 
        float linear;        
        float quadratic;     
        float padding1;      

        vec4 ambient;        
        vec4 diffuse;        
        vec4 specular;       

        float radius;       
        float padding2[3];
};


struct Cluster
{
    vec4 minPoint;
    vec4 maxPoint;
    uint count;
    uint pointLightIndices[100];
    uint spotLightIndices[100];
};

layout(std430, binding = 1) restrict buffer clusterSSBO
{
    Cluster clusters[];
};

layout(std430, binding = 2) restrict buffer pointLightSSBO
{
    PointLight pointLight[];
};

uniform mat4 viewMatrix;

bool sphereAABBIntersection(vec3 center, float radius, vec3 aabbMin, vec3 aabbMax) {
    vec3 closestPoint = clamp(center, aabbMin, aabbMax);
    float distanceSquared = dot(closestPoint - center, closestPoint - center);
    return distanceSquared <= (radius * radius);
}

bool test_pointlightAABB(uint i, Cluster cluster) {
    if (pointLight[i].radius == 0.0) return false;

    vec3 center = vec3(viewMatrix * pointLight[i].position);
    vec3 aabbMin = cluster.minPoint.xyz;
    vec3 aabbMax = cluster.maxPoint.xyz;

    return sphereAABBIntersection(center, pointLight[i].radius, aabbMin, aabbMax);
}

void main() {
    uint pointlightCount = pointLight.length();
    uint index = gl_WorkGroupID.x * LOCAL_SIZE + gl_LocalInvocationID.x;

    if (index >= clusters.length()) return;

    Cluster cluster = clusters[index];
    cluster.count = 0;

    for (uint i = 0; i < pointlightCount; ++i) {
        if (test_pointlightAABB(i, cluster) && cluster.count < 100) {
            cluster.pointLightIndices[cluster.count] = i;
            cluster.count++;
        }
    }

    clusters[index] = cluster;
}

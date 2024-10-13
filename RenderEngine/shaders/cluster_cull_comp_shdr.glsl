#version 460 core

#define LOCAL_SIZE 128
layout(local_size_x = LOCAL_SIZE, local_size_y = 1, local_size_z = 1) in;

struct PointLight
{
    vec4 position;
    float constant;
    float linear;
    float quadratic;
	
    vec4 ambient;
    vec4 diffuse;
    vec4 specular;

    float radius;
};

struct SpotLight {
    vec4 position;
    vec4 direction;
    float cutOff;
    float outerCutOff;
    float distance;
  
    float constant;
    float linear;
    float quadratic;
  
    vec4 ambient;
    vec4 diffuse;
    vec4 specular;       
};

struct Cluster
{
    vec4 minPoint;
    vec4 maxPoint;
    uint count;
    uint lightIndices[100];
};

layout(std430, binding = 1) restrict buffer clusterSSBO
{
    Cluster clusters[];
};

layout(std430, binding = 2) restrict buffer pointLightSSBO
{
    PointLight pointLight[];
};

layout(std430, binding = 3) restrict buffer spotLightSSBO
{
    SpotLight spotLight[];
};


uniform mat4 viewMatrix;

bool test_pointlightAABB(uint i, Cluster c);
bool testSpotlightAABB(uint i, Cluster cluster);

// each invocation of main() is a thread processing a cluster
void main()
{
    uint pointlightCount = pointLight.length();
    uint spotLightCount = spotLight.length();

    uint index = gl_WorkGroupID.x * LOCAL_SIZE + gl_LocalInvocationID.x;
    Cluster cluster = clusters[index];

    cluster.count = 0;

    for (uint i = 0; i < pointlightCount; ++i)
    {
        if (test_pointlightAABB(i, cluster) && cluster.count < 100)
        {
            cluster.lightIndices[cluster.count] = i;
            cluster.count++;
        }
    }

    for (uint i = 0; i < spotLightCount; ++i)
    {
        if (testSpotlightAABB(i, cluster) && cluster.count < 100)
        {
            cluster.lightIndices[cluster.count] = i + 1000; // Offset the index for spotlights.
            cluster.count++;
        }
    }


    clusters[index] = cluster;
}

bool sphereAABBIntersection(vec3 center, float radius, vec3 aabbMin, vec3 aabbMax)
{
   
    vec3 closestPoint = clamp(center, aabbMin, aabbMax);
   
    float distanceSquared = dot(closestPoint - center, closestPoint - center);

    return distanceSquared <= radius * radius;
}


bool test_pointlightAABB(uint i, Cluster cluster)
{
    vec3 center = vec3(viewMatrix * pointLight[i].position);
    float radius = pointLight[i].radius;

    vec3 aabbMin = cluster.minPoint.xyz;
    vec3 aabbMax = cluster.maxPoint.xyz;

    return sphereAABBIntersection(center, radius, aabbMin, aabbMax);
}


bool testSpotlightAABB(uint i, Cluster cluster) 
{
    vec3 lightPosition = vec3(viewMatrix * spotLight[i].position);
    vec3 lightDirection = normalize(vec3(viewMatrix * spotLight[i].direction));
    float cutOff = cos(spotLight[i].cutOff); 
    float outerCutOff = cos(spotLight[i].outerCutOff);
    float radius = spotLight[i].distance;

    vec3 aabbMin = cluster.minPoint.xyz;
    vec3 aabbMax = cluster.maxPoint.xyz;

    
    if (!sphereAABBIntersection(lightPosition, radius, aabbMin, aabbMax)) {
        return false;
    }



    for (int j = 0; j < 8; ++j) 
    {
        vec3 corner = vec3(
            (j & 1) != 0 ? aabbMin.x : aabbMax.x,
            (j & 2) != 0 ? aabbMin.y : aabbMax.y,
            (j & 4) != 0 ? aabbMin.z : aabbMax.z
        );

        vec3 lightToCorner = normalize(corner - lightPosition);
        float angleCosine = dot(lightDirection, lightToCorner);

        
        if (angleCosine > outerCutOff) {
            return true;
        }
    }


    return false;
}


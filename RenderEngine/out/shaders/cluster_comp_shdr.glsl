#version 460 core
layout(local_size_x = 1, local_size_y = 1, local_size_z = 1) in;

struct Cluster
{
    vec4 minPoint;
    vec4 maxPoint;
    uint point_count;
    uint spot_count;
    uint pad1;
    uint pad2;
    uint pointLightIndices[100];
    uint spotLightIndices[100];
};


layout(std430, binding = 1) restrict buffer clusterSSBO {
    Cluster clusters[];
};

uniform float zNear;
uniform float zFar;

uniform mat4 inverseProjection;
uniform uvec3 gridSize;
uniform uvec2 screenDimensions;


vec4 clipToView(vec4 clip);
vec3 screenToView(vec2 screenCoord);

vec3 lineIntersectionWithZPlane(vec3 startPoint, vec3 endPoint, float zDistance)
{
    vec3 direction = endPoint - startPoint;
    vec3 normal = vec3(0.0, 0.0, -1.0);
    float t = (zDistance - dot(normal, startPoint)) / dot(normal, direction);
    return startPoint + t * direction; 
}


void main()
{
    uint tileIndex = gl_WorkGroupID.x + (gl_WorkGroupID.y * gridSize.x) +
            (gl_WorkGroupID.z * gridSize.x * gridSize.y);
    vec2 tileSize = screenDimensions / gridSize.xy;

    vec2 minTile_screenspace = gl_WorkGroupID.xy * tileSize;
    vec2 maxTile_screenspace = (gl_WorkGroupID.xy + 1) * tileSize;

    vec3 minTile = screenToView(minTile_screenspace);
    vec3 maxTile = screenToView(maxTile_screenspace);

    float planeNear = zNear * pow(zFar / zNear, gl_WorkGroupID.z / float(gridSize.z));
    float planeFar =  zNear * pow(zFar / zNear, (gl_WorkGroupID.z + 1) / float(gridSize.z));

    vec3 minPointNear = lineIntersectionWithZPlane(vec3(0, 0, 0), minTile, planeNear);
    vec3 minPointFar = lineIntersectionWithZPlane(vec3(0, 0, 0), minTile, planeFar);
    vec3 maxPointNear = lineIntersectionWithZPlane(vec3(0, 0, 0), maxTile, planeNear);
    vec3 maxPointFar = lineIntersectionWithZPlane(vec3(0, 0, 0), maxTile, planeFar);

    clusters[tileIndex].minPoint = vec4(min(minPointNear, minPointFar), 0.0);
    clusters[tileIndex].maxPoint = vec4(max(maxPointNear, maxPointFar), 0.0);

}

vec3 screenToView(vec2 screenCoord)
{
    vec4 ndc = vec4(screenCoord / screenDimensions * 2.0 - 1.0, -1.0, 1.0);
    return clipToView(ndc);
}

vec4 clipToView(vec4 clip){
    vec4 view = inverseProjection * clip;
    view = view / view.w;
    return view;
}

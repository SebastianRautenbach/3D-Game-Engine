#version 460 core
layout(local_size_x = 1, local_size_y = 1, local_size_z = 1) in;

struct Cluster
{
    vec4 minPoint;
    vec4 maxPoint;
    uint count;
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

    vec3 minNear = minTile * planeNear / minTile.z;
    vec3 minFar  = minTile * planeFar  / minTile.z;
    vec3 maxNear = maxTile * planeNear / maxTile.z;
    vec3 maxFar  = maxTile * planeFar  / maxTile.z;

    vec3 minPointAABB = min(min(minNear, minFar),min(maxNear, maxFar));
    vec3 maxPointAABB = max(max(minNear, minFar),max(maxNear, maxFar));

    clusters[2 * tileIndex + 0].minPoint = vec4(minPointAABB, 1.0);
    clusters[2 * tileIndex + 1].maxPoint = vec4(maxPointAABB, 1.0);
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

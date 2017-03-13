#version 430
uniform float roll;
uniform writeonly image2D destTex;
layout (local_size_x = 16, local_size_y = 16) in;
void main() {
    ivec2 pos = ivec2(gl_GlobalInvocationID.xy);
    float val=0.5+0.5*sin((pos.x+pos.y)/30.0+roll);
    imageStore(destTex, pos, vec4(val, val, val, 1.0f));
}

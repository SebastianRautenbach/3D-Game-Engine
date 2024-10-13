#version 460 core

in float depth;

void main() {
  
   if (depth >= gl_FragCoord.z) {
      discard;
   }
}

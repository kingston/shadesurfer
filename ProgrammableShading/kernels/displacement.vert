// displacement.vert

/*
 This GLSL vertex shader performs displacement mapping
 using an analytical displacement function.
 */

// This 'varying' vertex output can be read as an input
// by a fragment shader that makes the same declaration.
varying vec2 texPos;
varying vec3 modelPos;
varying vec3 lightSource;
varying vec3 normal;

varying float displacement;

float h(float u, float v)
{
    float PI = 3.14159265358979323846264;
    float s = 0.01; // max displacement
    float a = 20.0; // frequency
    return s * cos(a * 2.0 * PI * u) * cos(a * 2.0 * PI * v);
}

void main()
{
    // Tell the fragment shader we have done vertex displacement
    displacement = 1.0;
    
	normal = gl_Normal.xyz;
	modelPos = gl_Vertex.xyz;
    
    // Copy the standard OpenGL texture coordinate to the output.
    texPos = gl_MultiTexCoord0.xy;
    
	/* Our fancy displacement function */
    float height = h(texPos.x, texPos.y);
    modelPos += height * normal;
    
    float delta = 0.000001;
    float dhdu = (h(texPos.x + delta, texPos.y) - height) / delta;
    float dhdv = (h(texPos.x, texPos.y + delta) - height) / delta;
    normal = cross(normalize(vec3(1, dhdu, 0)), normalize(vec3(0, -dhdv, -1)));
    
    // Render the shape using modified position.
    gl_Position = gl_ProjectionMatrix * gl_ModelViewMatrix *  vec4(modelPos,1);
    
    // we may need this in the fragment shader...
    modelPos = (gl_ModelViewMatrix * vec4(modelPos,1)).xyz;
    
	// send the normal to the fragment shader
	normal = (gl_NormalMatrix * normal);
    
    // pass the light source position to the fragment shader
    lightSource = gl_LightSource[0].position.xyz;
}

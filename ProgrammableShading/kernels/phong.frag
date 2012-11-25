// phong.frag

/*
  This fragment implements the Phong Reflection model.
*/

// The input image we will be filtering in this kernel.
uniform sampler2D normalTex;

varying vec3 modelPos;    // fragment position in model space
varying vec2 texPos;      // fragment position in texture space
varying vec3 lightSource; // light source position in model space
varying vec3 normal;	  // fragment normal in model space

varying float displacement;

float max(float v1, float v2)
{
    return v1 > v2 ? v1 : v2;
}

void main()
{
    // Sample from the normal map, if we're not doing displacement mapping
    vec3 N;
	if (displacement < 0.0)
		N = 2.*texture2D(normalTex, texPos).xyz - 1.;
	else
		N = normal;

    vec3 C = vec3(0.0, 0.0, 0.0); // camera position

    vec3 ambientColor  = gl_LightSource[0].ambient.xyz;
    vec3 diffuseColor  = gl_LightSource[0].diffuse.xyz;
    vec3 specularColor = gl_LightSource[0].specular.xyz;

    vec3 materialColor = gl_FrontMaterial.ambient.xyz;
    vec3 materialSpec  = gl_FrontMaterial.specular.xyz;
    float shininess    = gl_FrontMaterial.shininess;

	/* Code for Phong reflectance model here */
    vec3 normalizedNormal = normalize(N);
    vec3 surfaceToLightSource = normalize(lightSource - modelPos);
    vec3 reflectionDirection = normalize(reflect(surfaceToLightSource, normalizedNormal));
    vec3 surfaceToViewer = normalize(C - modelPos);
    vec3 finalColor = ambientColor * materialColor +
                      max(0.0, dot(normalizedNormal, surfaceToLightSource)) * diffuseColor * materialColor +
                      pow(max(0.0, dot(reflectionDirection, surfaceToViewer)), shininess) * specularColor * materialSpec;

    gl_FragColor = vec4(finalColor, 1.0);
}

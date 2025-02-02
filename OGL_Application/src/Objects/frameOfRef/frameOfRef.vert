#version 450 core
//frameofref
//uniform mat4 transformMatrix;
//layout (location = 11) uniform float length_;

//in vec4 vertices;
uniform mat4 modelviewM;
uniform mat4 transfM;
uniform float AOscale;

flat out int index;

void main(){

    float L = 10.0f*AOscale;

     const vec4 vertices[6] = vec4[6](
                //asse x
     	   	    vec4(0.0,0.0,0.0,1.0),
		        vec4(L,0.0,0.0,1.0),
                    //asse y
                vec4(0.0,0.0,0.0,1.0),
                vec4(0.0,L,0.0,1.0),
                        //asse z
                vec4(0.0,0.0,0.0,1.0),
                vec4(0.0,0.0,L,1.0));


			   index = gl_VertexID;
     gl_Position = modelviewM*transfM*vertices[gl_VertexID];
	 
}
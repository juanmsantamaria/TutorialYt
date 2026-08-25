//vertices en los sombreadores de fragmentos
const char* vertexShaderSource = "#version 330 core //indicamos la version de GLSL que vamos a usar
layout (location = 0) in vec3 aPos;
void main() //manda la tarjeta grafica
{\
   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0); //asigna la posicion de los vertices a la variable gl_Position
}
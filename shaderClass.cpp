#include"shaderClass.h"

// Lee un archivo de texto y devuelve un string con todo su contenido
std::string get_file_contents(const char* filename)
{
	std::ifstream in(filename, std::ios::binary);
	if (in)
	{
		std::string contents;
		in.seekg(0, std::ios::end);
		contents.resize(in.tellg());
		in.seekg(0, std::ios::beg);
		in.read(&contents[0], contents.size());
		in.close();
		return(contents);
	}
	throw(errno);
}

// Constructor que construye el Programa de Shader a partir de 2 shaders
Shader::Shader(const char* vertexFile, const char* fragmentFile)
{
	// Lee vertexFile y fragmentFile y almacena las cadenas
	std::string vertexCode = get_file_contents(vertexFile);
	std::string fragmentCode = get_file_contents(fragmentFile);

	// Convierte las cadenas de código del shader en arreglos
	const char* vertexSource = vertexCode.c_str();
	const char* fragmentSource = fragmentCode.c_str();

	// Crea el objeto Vertex Shader y lo agarra
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	// Adjunta el código fuente del Vertex Shader al objeto Vertex Shader
	glShaderSource(vertexShader, 1, &vertexSource, NULL);
	// Compila el Vertex Shader a código máquina
	glCompileShader(vertexShader);

	// Crea el objeto Fragment Shader y obtiene su referencia
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	// Adjunta el código fuente del Fragment Shader al objeto Fragment Shader
	glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
	// Compila el Fragment Shader a código máquina
	glCompileShader(fragmentShader);

	// Create Shader Program Object and get its reference
	ID = glCreateProgram();
	//Adjunta los shaders de Vértices y Fragmentos al Programa de Shader
	glAttachShader(ID, vertexShader);
	glAttachShader(ID, fragmentShader);
	//Enlaza (linkea) todos los shaders juntos en el Programa de Shader
	glLinkProgram(ID);

	// Elimina los objetos Vertex Shader
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

}

// Activates the Shader Program
void Shader::Activate()
{
	glUseProgram(ID);
}

// Deletes the Shader Program
void Shader::Delete()
{
	glDeleteProgram(ID);
}
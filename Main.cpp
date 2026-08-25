#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
//incluimos librerias de OpenGL y GLFW para poder crear una ventana y renderizar gráficos en ella.




int main()
{
	//inicializamos GLFW y creamos una ventana de 800x800 píxeles con el título "Youtube"
    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); //decimos que version de open gl usamos
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); //version menor
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //introducimos profile, un paquete de funciones. perfil core para usar funciones modernas.

    GLfloat vertices[] = //usamos el float de open gl para designar la ubicacion de los vertices
    {
		-0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, // vertice izquierdo
		 0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, // vertice derecho
		 0.0f,  0.5f * float(sqrt(3)) * 2 / 3, 0.0f,  // vertice superior, generamos un triangulo equilatero
		 -0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f, // vertice inferior
		0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f, // vertice inferior derecho
		0.0f, -0.5f * float(sqrt(3)) / 3, 0.0f // vertice inferior izquierdo
    };

	GLuint indices[] = //indices para dibujar el triangulo
	{
		0, 3, 5,
		3, 2, 4,
		5, 4 , 1
	};

    GLFWwindow * window = glfwCreateWindow(800, 800, "Youtube", NULL, NULL); //especificaciones de la ventana (ancho, alto, título, pantalla completa )
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl; //error message 
		glfwTerminate(); //finalizamos el gfwl
        return -1;
    }
    glfwMakeContextCurrent(window); //reconoce la ventana como item 


	gladLoadGL(); //confirmamos que glad se ha cargado correctamente y podemos usar las funciones de OpenGL


	glViewport(0, 0, 800, 800); //limitar la ventana a 800x800

	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER); //creamos un shader de tipo vertice
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL); //asignamos el codigo 
    	glCompileShader(vertexShader); //compilamos el shader

		GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER); //creamos un shader usando el tipo de shader de fragmento
        glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL); //asignamos el codigo del shader 
        glCompileShader(fragmentShader); //compilamos el shader

		GLuint shaderProgram = glCreateProgram(); //creamos un programa de shader

		glAttachShader(shaderProgram, vertexShader); //asignamos el shader de vertice al programa
		glAttachShader(shaderProgram, fragmentShader); //asignamos el shader de fragmento al programa

        glLinkProgram(shaderProgram);

		glDeleteShader(vertexShader); //eliminamos el shader de vertice)
		glDeleteShader(fragmentShader); //eliminamos el shader de fragmento)




        GLuint VAO, VBO, EBO;

        glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO); //generamos un buffer de vertices
		glGenBuffers(1, &EBO); //generamos un buffer de indices

        glBindVertexArray(VAO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO); //asignamos el buffer de vertices

        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); 

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0); //asignamos el buffer de vertices al shader)
		glEnableVertexAttribArray(0); //activamos el buffer de vertices

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO); //asignamos el buffer de indices
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW); //llenamos el buffer de indices

		glBindBuffer(GL_ARRAY_BUFFER, 0); //desasignamos el buffer de vertices)
		glBindVertexArray(0); //desasignamos el buffer de vertices)
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); //desasignamos el buffer de indices)



	glClearColor(0.02f, 0.10f, 0.30f, 1.0f); //establecemos el fondo de la ventana a un color azul, se consigue diviediendo los indices rgb entre 255 y el ultimo valor alfa determina la transparencia de 1 opaco a 0 transparente
	glClear(GL_COLOR_BUFFER_BIT); //determinamos el el buffer con color
	glfwSwapBuffers(window); //intercambiamos el buffer frontal con el trasero para ver el color designado

    while (!glfwWindowShouldClose(window)) //ciclo para que no se cierre el codigo
    {
		glClearColor(0.02f, 0.10f, 0.30f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glUseProgram(shaderProgram); //usamos el programa de shader)
		glBindVertexArray(VAO); //asignamos el buffer de vertices)
		glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0); //dibujamos el triangulo)
		glfwSwapBuffers(window); //intercambiamos el buffer frontal con el trasero para ver el color designado
		glfwPollEvents(); //funcion para que la ventana no se cierre y pueda recibir eventos


        glfwPollEvents();
    }

	glDeleteVertexArrays(1, &VAO); //eliminamos el buffer de vertices
	glDeleteBuffers(1, &VBO); //eliminamos el buffer de vertices)
	glDeleteBuffers(1, &EBO); //eliminamos el buffer de indices)
	glDeleteProgram(shaderProgram); //eliminamos el programa de shader)

    glfwDestroyWindow(window);//funcion para destruir ventana
    glfwTerminate();
    return 0;
}
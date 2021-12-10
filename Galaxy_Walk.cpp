#define _CRT_SECURE_NO_WARNINGS
#define STB_IMAGE_IMPLEMENTATION
#include "shader.h"


using namespace std;

//glm::vec3 cameraPos = glm::vec3(0.0f, 10.0, 0.0f);
glm::vec3 cameraPos = glm::vec3(0.0f, 0.0, 5.0f);
//glm::vec3 cameraTarget = glm::vec3(0.0f, 0.0, 0.0f);
//
//glm::vec3 cameraDirection = glm::normalize(cameraPos - cameraTarget);
glm::vec3 cameraDirection = glm::vec3(0.0f, 0.0, 0.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

glm::vec3 lightpos = glm::vec3(0,5,0);
glm::vec3 lightcolor = glm::vec3(1, 1, 1);
glm::vec3 sunpos = glm::vec3(0,0, 0);
GLuint g_window_w = 1000;
GLuint g_window_h = 1000;

float sizeX, sizeY, sizeZ;
GLuint VAO[3], CUB;
GLuint VBO_position[3];
GLuint VBO_normal[3];
GLuint VBO_color[3];

float vertices[] = {
	-3.0f, -3.0f, -1.0f, 0.0, 0.0, 1.0, 0.0, 0.0,//plane
	3.0f, -3.0f, -1.0f, 0.0, 0.0, 1.0, 1.0, 0.0,
	3.0f, 3.0f, -1.0f, 0.0, 0.0, 1.0, 1.0, 1.0,
	-3.0f, 3.0f, -1.0f, 0.0, 0.0, 1.0, 0.0, 1.0,

	-0.5f, -0.5f, 0.5f, 0.0, 0.0, 1.0, 0.0, 0.0,//front
	0.5f, -0.5f, 0.5f, 0.0, 0.0, 1.0, 1.0, 0.0,
	0.5f, 0.5f, 0.5f, 0.0, 0.0, 1.0, 1.0, 1.0,
	0.5f, 0.5f, 0.5f, 0.0, 0.0, 1.0, 1.0, 1.0,
	-0.5f, 0.5f, 0.5f, 0.0, 0.0, 1.0, 0.0, 1.0,
	-0.5f, -0.5f, 0.5f, 0.0, 0.0, 1.0, 0.0, 0.0,

	-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0, 0.0,//back
	0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0, 0.0,
	0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0, 1.0,
	0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0, 1.0,
	-0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0, 1.0,
	-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0, 0.0,

	-0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 0.0, 0.0,//left
	-0.5f, 0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 1.0, 0.0,
	-0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 1.0, 1.0,
	-0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 1.0, 1.0,
	-0.5f, -0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 0.0, 1.0,
	-0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 0.0, 0.0,

	0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 0.0, 0.0,//right
	0.5f, 0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 1.0, 0.0,
	0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 1.0, 1.0,
	0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 1.0, 1.0,
	0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 0.0, 1.0,
	0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 0.0, 0.0,

	-0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 0.0, 0.0,//bottom
	0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 1.0, 0.0,
	0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 1.0, 1.0,
	0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 1.0, 1.0,
	-0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 0.0, 1.0,
	-0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 0.0, 0.0,

	-0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0, 0.0,//top
	0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0, 0.0,
	0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0, 1.0,
	0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0, 1.0,
	-0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0, 1.0,
	-0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0, 0.0,
};
int polygon_mode = 2;
unsigned int texture[7];
BITMAPINFO* bmp;

void Display();
void Reshape(int w, int h);
void Keyboard(unsigned char key, int x, int y);
void InitBuffer();
void InitTexture();

int main(int argc, char** argv)
{
	// create window using freeglut
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(g_window_w, g_window_h);
	glutInitWindowPosition(0, 0);

	glutCreateWindow("Computer Graphics");
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		std::cerr << "Unable to initialize GLEW ... exiting" << std::endl;
		exit(EXIT_FAILURE);
	}
	else
	{
		std::cout << "GLEW OK\n";
	}


	GLuint vShader[4];
	GLuint fShader[4];

	vShader[0] = MakeVertexShader("vertex.glsl", 0);			// Sun
	fShader[0] = MakeFragmentShader("fragment.glsl", 0);

	// shader Program
	s_program[0] = glCreateProgram();
	glAttachShader(s_program[0], vShader[0]);
	glAttachShader(s_program[0], fShader[0]);
	glLinkProgram(s_program[0]);
	checkCompileErrors(s_program[0], "PROGRAM");

	InitBuffer();
	InitTexture();
	// callback functions
	glutDisplayFunc(Display);
	glutReshapeFunc(Reshape);
	glutKeyboardFunc(Keyboard);

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);


	// freeglut 윈도우 이벤트 처리 시작. 윈도우가 닫힐때까지 후한루프 실행.
	glutMainLoop();

	return 0;
}

int loadObj(const char* filename)
{
	FILE* objFile;

	fopen_s(&objFile, filename, "rb");

	if (objFile == NULL) {
		printf("Impossible to open the file !\n");
		return false;
	}
	while (1) {

		char lineHeader[128];
		// read the first word of the line
		int res = fscanf(objFile, "%s", lineHeader);
		if (res == EOF)
			break; // EOF = End Of File. Quit the loop.
		if (strcmp(lineHeader, "v") == 0) {
			glm::vec3 vertex;
			fscanf(objFile, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);

			if (vertex.x < minX) minX = vertex.x;
			if (vertex.y < minY) minY = vertex.y;
			if (vertex.z < minZ) minZ = vertex.z;
			if (vertex.x > maxX) maxX = vertex.x;
			if (vertex.y > maxY) maxY = vertex.y;
			if (vertex.z > maxZ) maxZ = vertex.z;
			sumX += vertex.x;
			sumY += vertex.y;
			sumZ += vertex.z;

			temp_vertices.push_back(vertex);
		}
		else if (strcmp(lineHeader, "vt") == 0) {
			glm::vec2 uv;
			fscanf(objFile, "%f %f\n", &uv.x, &uv.y);
			temp_uvs.push_back(uv);
		}
		else if (strcmp(lineHeader, "vn") == 0) {
			glm::vec3 normal;
			fscanf(objFile, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
			temp_normals.push_back(normal);
		}
		else if (strcmp(lineHeader, "f") == 0) {
			std::string vertex1, vertex2, vertex3;
			unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
			int matches = fscanf(objFile, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2]);
			if (matches != 9) {
				printf("File can't be read by our simple parser : ( Try exporting with other options\n");
				return false;
			}
			vertexIndices.push_back(vertexIndex[0]);
			vertexIndices.push_back(vertexIndex[1]);
			vertexIndices.push_back(vertexIndex[2]);
			uvIndices.push_back(uvIndex[0]);
			uvIndices.push_back(uvIndex[1]);
			uvIndices.push_back(uvIndex[2]);
			normalIndices.push_back(normalIndex[0]);
			normalIndices.push_back(normalIndex[1]);
			normalIndices.push_back(normalIndex[2]);
		}
	}

	std::cout << "minX: " << minX << " minY: " << minY << " minZ: " << minZ << std::endl;
	std::cout << "maxX: " << maxX << " maxY: " << maxY << " maxZ: " << maxZ << std::endl;

	aveX = sumX / vertexIndices.size();
	aveY = sumY / vertexIndices.size();
	aveZ = sumZ / vertexIndices.size();
	scaleX = (1.0 - maxX) * 10 + 1;
	scaleY = (1.0 - maxY) * 10 + 1;
	scaleZ = (1.0 - maxZ) * 10 + 1;

	if (scaleX > scaleY) {
		if (scaleY > scaleZ)
			scaleAll = scaleZ;
		else
			scaleAll = scaleY;
	}
	else if (scaleX < scaleY) {
		if (scaleX < scaleZ)
			scaleAll = scaleX;
		else
			scaleAll = scaleZ;
	}
	std::cout << "aveX: " << aveX << " aveY: " << aveY << " aveZ: " << aveZ << std::endl;

	for (unsigned int i = 0; i < vertexIndices.size(); i++) {
		unsigned int vertexIndex = vertexIndices[i];
		glm::vec3 vertex = temp_vertices[vertexIndex - 1];
		outvertex.push_back(vertex);
	}
	for (unsigned int i = 0; i < uvIndices.size(); i++) {
		unsigned int uvIndex = uvIndices[i];
		glm::vec2 vertex = temp_uvs[uvIndex - 1];
		outuv.push_back(vertex);
	}
	for (unsigned int i = 0; i < normalIndices.size(); i++) {
		unsigned int normalIndex = normalIndices[i];
		glm::vec3 vertex = temp_normals[normalIndex - 1];
		outnormal.push_back(vertex);
	}

	return outvertex.size();
}
int loadObj_normalize_center(const char* filename)
{
	FILE* objFile;

	fopen_s(&objFile, filename, "rb");

	if (objFile == NULL) {
		printf("Impossible to open the file !\n");
		return false;
	}
	while (1) {

		char lineHeader[128];
		// read the first word of the line
		int res = fscanf(objFile, "%s", lineHeader);
		if (res == EOF)
			break; // EOF = End Of File. Quit the loop.
		if (strcmp(lineHeader, "v") == 0) {
			glm::vec3 vertex;
			fscanf(objFile, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);

			if (vertex.x < minX) minX = vertex.x;
			if (vertex.y < minY) minY = vertex.y;
			if (vertex.z < minZ) minZ = vertex.z;
			if (vertex.x > maxX) maxX = vertex.x;
			if (vertex.y > maxY) maxY = vertex.y;
			if (vertex.z > maxZ) maxZ = vertex.z;
			sumX += vertex.x;
			sumY += vertex.y;
			sumZ += vertex.z;

			temp_vertices.push_back(vertex);
		}
		else if (strcmp(lineHeader, "vt") == 0) {
			glm::vec2 uv;
			fscanf(objFile, "%f %f\n", &uv.x, &uv.y);
			temp_uvs.push_back(uv);
		}
		else if (strcmp(lineHeader, "vn") == 0) {
			glm::vec3 normal;
			fscanf(objFile, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
			temp_normals.push_back(normal);
		}
		else if (strcmp(lineHeader, "f") == 0) {
			std::string vertex1, vertex2, vertex3;
			unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
			int matches = fscanf(objFile, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2]);
			if (matches != 9) {
				printf("File can't be read by our simple parser : ( Try exporting with other options\n");
				return false;
			}
			vertexIndices.push_back(vertexIndex[0]);
			vertexIndices.push_back(vertexIndex[1]);
			vertexIndices.push_back(vertexIndex[2]);
			uvIndices.push_back(uvIndex[0]);
			uvIndices.push_back(uvIndex[1]);
			uvIndices.push_back(uvIndex[2]);
			normalIndices.push_back(normalIndex[0]);
			normalIndices.push_back(normalIndex[1]);
			normalIndices.push_back(normalIndex[2]);
		}
	}

	std::cout << "minX: " << minX << " minY: " << minY << " minZ: " << minZ << std::endl;
	std::cout << "maxX: " << maxX << " maxY: " << maxY << " maxZ: " << maxZ << std::endl;

	aveX = sumX / vertexIndices.size();
	aveY = sumY / vertexIndices.size();
	aveZ = sumZ / vertexIndices.size();
	scaleX = maxX - minX;
	scaleY = maxY - minY;
	scaleZ = maxZ - minZ;

	glm::vec3 temp;

	std::cout << "aveX: " << aveX << " aveY: " << aveY << " aveZ: " << aveZ << std::endl;

	std::cout << "scaleX: " << scaleX << " scaleY: " << scaleY << " scaleZ: " << scaleZ << std::endl;

	for (unsigned int i = 0; i < vertexIndices.size(); i++) {
		unsigned int vertexIndex = vertexIndices[i];
		temp = temp_vertices[vertexIndex - 1];
		temp.x = temp.x - minX;
		temp.y = temp.y - minY;
		temp.z = temp.z - minZ;

		temp.x = ((temp.x * 2.0f) / scaleX) - 1.0f;
		temp.y = ((temp.y * 2.0f) / scaleY) - 1.0f;
		temp.z = ((temp.z * 2.0f) / scaleZ) - 1.0f;

		outvertex.push_back(temp);
		//glm::vec3 vertex = temp_vertices[vertexIndex - 1];
		//outvertex.push_back(vertex);
	}
	for (unsigned int i = 0; i < uvIndices.size(); i++) {
		unsigned int uvIndex = uvIndices[i];
		glm::vec2 vertex = temp_uvs[uvIndex - 1];
		outuv.push_back(vertex);
	}
	for (unsigned int i = 0; i < normalIndices.size(); i++) {
		unsigned int normalIndex = normalIndices[i];
		glm::vec3 vertex = temp_normals[normalIndex - 1];
		outnormal.push_back(vertex);
	}

	return outvertex.size();
}
GLubyte* LoadDIBitmap(const char* filename, BITMAPINFO** info)
{
	FILE* fp;
	GLubyte* bits;
	int bitsize, infosize;
	BITMAPFILEHEADER header;
	//--- 바이너리 읽기 모드로 파일을 연다
	if ((fp = fopen(filename, "rb")) == NULL)
		return NULL;
	//--- 비트맵 파일 헤더를 읽는다.
	if (fread(&header, sizeof(BITMAPFILEHEADER), 1, fp) < 1) {
		fclose(fp); return NULL;
	}
	//--- 파일이 BMP 파일인지 확인한다.
	if (header.bfType != 'MB') {
		fclose(fp); return NULL;
	}
	//--- BITMAPINFOHEADER 위치로 간다.
	infosize = header.bfOffBits - sizeof(BITMAPFILEHEADER);
	//--- 비트맵 이미지 데이터를 넣을 메모리 할당을 한다.
	if ((*info = (BITMAPINFO*)malloc(infosize)) == NULL) {
		fclose(fp); return NULL;
	}
	//--- 비트맵 인포 헤더를 읽는다.
	if (fread(*info, 1, infosize, fp) < (unsigned int)infosize) {
		free(*info);
		fclose(fp); return NULL;
	}
	//--- 비트맵의 크기 설정
	if ((bitsize = (*info)->bmiHeader.biSizeImage) == 0)
		bitsize = ((*info)->bmiHeader.biWidth * (*info)->bmiHeader.biBitCount + 7) / 8.0 * abs((*info)->bmiHeader.biHeight);
	//--- 비트맵의 크기만큼 메모리를 할당한다.
	if ((bits = (unsigned char*)malloc(bitsize)) == NULL) {
		free(*info);
		fclose(fp); return NULL;
	}
	//--- 비트맵 데이터를 bit(GLubyte 타입)에 저장한다.
	if (fread(bits, 1, bitsize, fp) < (unsigned int)bitsize) {
		free(*info); free(bits);
		fclose(fp); return NULL;
	}
	fclose(fp);
	return bits;
}
void InitTexture()
{
	//--- plane
	glGenTextures(1, texture);
	glBindTexture(GL_TEXTURE_2D, texture[0]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	unsigned char* data = LoadDIBitmap("plane.bmp", &bmp);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, 1024, 1024, 0, GL_BGR, GL_UNSIGNED_BYTE, data);
	//--- texture 1
	//glBindTexture(GL_TEXTURE_2D, texture[1]);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//unsigned char* data1 = LoadDIBitmap("texture.bmp", &bmp);
	//glTexImage2D(GL_TEXTURE_2D, 0, 3, 1024, 1024, 0, GL_BGR, GL_UNSIGNED_BYTE, data1);
	////--- texture 2
	//glBindTexture(GL_TEXTURE_2D, texture[2]);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//unsigned char* data2 = LoadDIBitmap("texture1.bmp", &bmp);
	//glTexImage2D(GL_TEXTURE_2D, 0, 3, 1024, 1024, 0, GL_BGR, GL_UNSIGNED_BYTE, data2);

	//glBindTexture(GL_TEXTURE_2D, texture[3]);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//unsigned char* data3 = LoadDIBitmap("texture2.bmp", &bmp);
	//glTexImage2D(GL_TEXTURE_2D, 0, 3, 1024, 1024, 0, GL_BGR, GL_UNSIGNED_BYTE, data3);
	////--- texture 2
	//glBindTexture(GL_TEXTURE_2D, texture[4]);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//unsigned char* data4 = LoadDIBitmap("texture3.bmp", &bmp);
	//glTexImage2D(GL_TEXTURE_2D, 0, 3, 1024, 1024, 0, GL_BGR, GL_UNSIGNED_BYTE, data4);

	//glBindTexture(GL_TEXTURE_2D, texture[5]);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//unsigned char* data5 = LoadDIBitmap("texture4.bmp", &bmp);
	//glTexImage2D(GL_TEXTURE_2D, 0, 3, 1024, 1024, 0, GL_BGR, GL_UNSIGNED_BYTE, data5);
	////--- texture 2
	//glBindTexture(GL_TEXTURE_2D, texture[6]);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//unsigned char* data6 = LoadDIBitmap("texture5.bmp", &bmp);
	//glTexImage2D(GL_TEXTURE_2D, 0, 3, 1024, 1024, 0, GL_BGR, GL_UNSIGNED_BYTE, data6);

	glUseProgram(s_program[0]);
	int tLocation = glGetUniformLocation(s_program[0], "texture1"); //--- outTexture 유니폼 샘플러의 위치를 가져옴
	glUniform1i(tLocation, 0);
}
void InitBuffer()
{

	glGenVertexArrays(1, &CUB);
	GLuint VBO;
	glGenBuffers(1, &VBO);

	//glUseProgram(s_program[0]);
	glBindVertexArray(CUB);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0); //--- 위치 속성
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float))); //--- 노말값 속성
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float))); //--- 텍스처 좌표 속성
	glEnableVertexAttribArray(2);

	num_Triangle = loadObj_normalize_center("sphere.obj");

	//// 5.1. VAO 객체 생성 및 바인딩
	glGenVertexArrays(3, VAO);
	glGenBuffers(3, VBO_position);
	glGenBuffers(3, VBO_normal);
	glGenBuffers(3, VBO_color);

	// 2 triangles for quad floor
	glUseProgram(s_program[0]);
	glBindVertexArray(VAO[0]);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_position[0]);
	glBufferData(GL_ARRAY_BUFFER, outvertex.size() * sizeof(glm::vec3), &outvertex[0], GL_STATIC_DRAW);
	GLint pAttribute = glGetAttribLocation(s_program[0], "vPos");
	glVertexAttribPointer(pAttribute, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
	glEnableVertexAttribArray(pAttribute);

	glBindBuffer(GL_ARRAY_BUFFER, VBO_normal[0]);
	glBufferData(GL_ARRAY_BUFFER, outnormal.size() * sizeof(glm::vec3), &outnormal[0], GL_STATIC_DRAW);
	GLint nAttribute = glGetAttribLocation(s_program[0], "vNormal");
	glVertexAttribPointer(nAttribute, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
	glEnableVertexAttribArray(nAttribute);


	unsigned int lightPosLocation = glGetUniformLocation(s_program[0], "lightPos");
	unsigned int lightColorLocation = glGetUniformLocation(s_program[0], "lightColor");
	glUniform3f(lightPosLocation, lightpos.x, lightpos.y, lightpos.z);
	glUniform3f(lightColorLocation, lightcolor.x, lightcolor.y, lightcolor.z);



	glEnable(GL_DEPTH_TEST);
}

void Display()
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glUseProgram(s_program[0]);
	glBindVertexArray(CUB);
	glActiveTexture(GL_TEXTURE0);
	glEnable(GL_DEPTH_TEST);

	//if (polygon_mode == 1)
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	//else if (polygon_mode == 2)
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	//*************************************************************************
	// Drawing circle
	//cameraDirection = glm::normalize(cameraPos - cameraTarget);


	/*glUseProgram(s_program[0]);
	glBindVertexArray(VAO[0]);*/



	unsigned int modelloc = glGetUniformLocation(s_program[0], "model");
	unsigned int viewloc = glGetUniformLocation(s_program[0], "view");
	unsigned int projloc = glGetUniformLocation(s_program[0], "projection");

	unsigned int lightPosLocation = glGetUniformLocation(s_program[0], "lightPos");
	unsigned int lightColorLocation = glGetUniformLocation(s_program[0], "lightColor");
	unsigned int objColorLocation = glGetUniformLocation(s_program[0], "objectColor");
	unsigned int viewPosLocation = glGetUniformLocation(s_program[0], "viewPos");
	glm::mat4 model = glm::scale(glm::mat4(1.0f), glm::vec3(0.5,0.5,0.5));

	//glm::mat4 model = glm::scale(glm::mat4(1.0f), glm::vec3(0.5,1 , 0.5));
	glm::mat4 sun = glm::scale(glm::mat4(1.0f), glm::vec3(1,1,1)) * model;

	glm::mat4 mercury = glm::translate(glm::mat4(1.0f), glm::vec3(-0.5-0.1, 0, 0)) * glm::scale(glm::mat4(1.0f), glm::vec3(0.04, 0.04, 0.04)) * model;
	glm::mat4 venus= glm::translate(glm::mat4(1.0f), glm::vec3(-0.5-0.3, 0, 0)) * glm::scale(glm::mat4(1.0f), glm::vec3(0.1, 0.1, 0.1)) * model;
	glm::mat4 earth = glm::translate(glm::mat4(1.0f), glm::vec3(-0.55-0.5, 0, 0)) * glm::scale(glm::mat4(1.0f), glm::vec3(0.105, 0.105, 0.105)) * model;
	glm::mat4 mars = glm::translate(glm::mat4(1.0f), glm::vec3(-0.7-0.5, 0, 0)) * glm::scale(glm::mat4(1.0f), glm::vec3(0.058, 0.058, 0.058)) * model;

	glm::mat4 jupiter = glm::translate(glm::mat4(1.0f), glm::vec3(-0.7-0.5, 0, 0)) * glm::scale(glm::mat4(1.0f), glm::vec3(0.5,0.5,0.5)) * model;
	glm::mat4 saturn = glm::translate(glm::mat4(1.0f), glm::vec3(-0.5-1.4, 0, 0)) * glm::scale(glm::mat4(1.0f), glm::vec3(0.5, 0.5, 0.5)) * model;
	glm::mat4 uranus = glm::translate(glm::mat4(1.0f), glm::vec3(-1.7-0.5,0,0)) * glm::scale(glm::mat4(1.0f), glm::vec3(0.2,0.2,0.2)) * model;
	glm::mat4 neptune = glm::translate(glm::mat4(1.0f), glm::vec3(-1.9-0.5,0,0)) * glm::scale(glm::mat4(1.0f), glm::vec3(0.2, 0.2, 0.2)) * model;




	glm::mat4 view = glm::lookAt(cameraPos, cameraDirection, cameraUp);

	glm::mat4 pTransform = glm::mat4(1.0f);
	pTransform = glm::perspective(glm::radians(45.0f), 1.0f, 1.0f, -1.0f);
	pTransform = glm::translate(pTransform, glm::vec3(0.0, 0.0, -5.0f));
	glUniformMatrix4fv(projloc, 1, GL_FALSE, &pTransform[0][0]);
	/*glm::mat4 projection = glm::mat4(1.0f);

	projection = glm::perspective(glm::radians(glm::degrees(120.0f)), 1.0f, 0.1f, 100.0f);*/

	glUniformMatrix4fv(modelloc, 1, GL_FALSE, &model[0][0]);
	glUniformMatrix4fv(viewloc, 1, GL_FALSE, &view[0][0]);
	//glUniformMatrix4fv(projloc, 1, GL_FALSE, &projection[0][0]);


	glUniform3f(lightPosLocation, sunpos.x, sunpos.y, sunpos.z);
	glUniform3f(lightColorLocation, lightcolor.x, lightcolor.y, lightcolor.z);

	glUniform3f(objColorLocation, 1.0, 0.0, 0.0);
	glUniform3f(viewPosLocation, cameraPos.x, cameraPos.y, cameraPos.z);

	//sun
	glUniformMatrix4fv(modelloc, 1, GL_FALSE, &sun[0][0]);

	//glDrawArrays(GL_TRIANGLES, 0, num_Triangle);


	////mercury
	//glUniform3f(objColorLocation, 0.0, 1.0, 0.0);
	//glUniformMatrix4fv(modelloc, 1, GL_FALSE, &mercury[0][0]);
	//glDrawArrays(GL_TRIANGLES, 0, num_Triangle);

	////venus
	//glUniform3f(objColorLocation, 0.0, 0.0, 1.0);
	//glUniformMatrix4fv(modelloc, 1, GL_FALSE, &venus[0][0]);
	//glDrawArrays(GL_TRIANGLES, 0, num_Triangle);

	////earth
	//glUniform3f(objColorLocation, 0.0, 1.0, 1.0);
	//glUniformMatrix4fv(modelloc, 1, GL_FALSE, &earth[0][0]);
	//glDrawArrays(GL_TRIANGLES, 0, num_Triangle);


	////mars
	//glUniform3f(objColorLocation, 1.0, 0.0, 1.0);
	//glUniformMatrix4fv(modelloc, 1, GL_FALSE, &mars[0][0]);
	//glDrawArrays(GL_TRIANGLES, 0, num_Triangle);

	////jupiter
	//glUniform3f(objColorLocation, 1.0, 0.0, 1.0);
	//glUniformMatrix4fv(modelloc, 1, GL_FALSE, &jupiter[0][0]);
	//glDrawArrays(GL_TRIANGLES, 0, num_Triangle);

	////satrun
	//glUniform3f(objColorLocation, 1.0, 1.0, 0.0);
	//glUniformMatrix4fv(modelloc, 1, GL_FALSE, &saturn[0][0]);
	//glDrawArrays(GL_TRIANGLES, 0, num_Triangle);

	////uranus
	//glUniform3f(objColorLocation, 1.0, 1.0, 0.0);
	//glUniformMatrix4fv(modelloc, 1, GL_FALSE, &uranus[0][0]);
	//glDrawArrays(GL_TRIANGLES, 0, num_Triangle);

	////neptune
	//glUniform3f(objColorLocation, 1.0, 1.0, 0.0);
	//glUniformMatrix4fv(modelloc, 1, GL_FALSE, &neptune[0][0]);
	//glDrawArrays(GL_TRIANGLES, 0, num_Triangle);
	glm::mat4 Plane = glm::mat4(1.0f);
	/*glUniform3f(objColorLocation, 0.0, 1.0, 1.0);*/
	glUniformMatrix4fv(modelloc, 1, GL_FALSE, &Plane[0][0]);
	glBindTexture(GL_TEXTURE_2D, texture[0]);
	glDrawArrays(GL_QUADS, 0, 4);

	glutSwapBuffers();

}
void Reshape(int w, int h)
{
	g_window_w = w;
	g_window_h = h;
	glViewport(0, 0, w, h);
}

bool timerstop = false;
void timer(int a)
{
	if (timerstop == false) {
		return;
		glutPostRedisplay();
	}
	static float r = 0.0f;
	lightpos.x = 5 * glm::sin(r);
	lightpos.z = 5 * glm::cos(r);
	r += 0.05f;


	glutPostRedisplay();
	glutTimerFunc(100, timer, 1);

}
bool timery = false;
void timer_y(int value)
{
	if (!timery) {
		return;
		glutPostRedisplay();
	}

	static float i = 0.0f;

	cameraPos.x = 5 * glm::sin(i);
	cameraPos.z = 5 * glm::cos(i);

	glm::vec3 cameraTarget = glm::vec3(0, 0, 0);
	i += 0.01f;
	cameraDirection = glm::normalize(cameraPos - cameraTarget);

	glutTimerFunc(10, timer_y, 1);
	glutPostRedisplay();

}
void Keyboard(unsigned char key, int x, int y)
{
	static float i = 0.0f;
	static int colorcount = 0;

	switch (key)
	{
	case '0':
		cameraPos.y -= 0.5f;
		cameraDirection.y -= 0.5f;
		break;
	case '9':
		cameraPos.y += 0.5f;
		cameraDirection.y += 0.5f;
		cout << cameraPos.y;

		break;
	case 'z':
		cameraPos.z += 0.1f;
		cameraDirection.z += 0.1f;

		break;
	case 'Z':
		cameraPos.z -= 0.1f;
		cameraDirection.z -= 0.1;

		break;
	case 'x':
		cameraPos.x += 0.1f;
		cameraDirection.x += 0.1f;
		break;
	case 'X':
		cameraPos.x -= 0.1f;
		cameraDirection.x -= 0.1;
		break;

	case 'y':
		timery = true;
		glutTimerFunc(10, timer_y, 1);

		break;
	case 'Y':
		timery = false;
		glutTimerFunc(10, timer_y, 1);

		break;
	case 'c':
		if (colorcount % 3 == 0) {
			lightcolor.x = 0;
			lightcolor.y = 1;
			lightcolor.z = 0.5;
			++colorcount;
		}
		else if (colorcount % 3 == 1) {
			lightcolor.x = 0;
			lightcolor.y = 0.5;
			lightcolor.z = 0.5;

			++colorcount;

		}
		else if (colorcount % 3 == 2) {
			lightcolor.x = 0.4;
			lightcolor.y = 0.11;
			lightcolor.z = 1;
			colorcount = 0;

		}
		glutPostRedisplay();
		break;
	case 'C':
		lightcolor = glm::vec3(1.0f, 1.0f, 1.0f);

		break;

	case 'r':
		timerstop = true;
		glutTimerFunc(100, timer, 1);
		break;
	case 'R':
		timerstop = false;
		glutTimerFunc(100, timer, 1);

	default:
		break;
	}
	glutPostRedisplay();
}












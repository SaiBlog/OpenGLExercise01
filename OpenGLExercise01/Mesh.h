#ifndef MESH_H
#define MESH_H
#include <glad/glad.h>

#include<glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include"Shader.h"
#include<string>
#include<vector>

struct Vertex
{
	glm::vec3 Postion;
	glm::vec3 Normal;
	glm::vec2 TexCoords;
};

struct Texture
{
	unsigned int id;//�������ɵ�����
	std::string type;
	std::string path;
};

class Mesh
{
public:
	std::vector<Vertex>vertices;
	std::vector<unsigned int>indices;
	std::vector<Texture>textures;


	Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture>textures)
	{
		this->vertices = vertices;
		this->textures = textures;
		this->indices = indices;

		setupMesh();//����
	}

	//��������
	void Draw(Shader& shader)
	{
		//������
		unsigned int diffuseNr = 1;
		unsigned int specularNr = 1;

		//����������Ϣ
		for (unsigned int i = 0; i < textures.size(); i++)
		{
			//����ĳ������ͨ��
			glActiveTexture(GL_TEXTURE0 + i);

			//��ȡ����ı���Լ�����
			std::string number;
			std::string name = textures[i].type;
			if (name == "texture_diffuse")
			{
				number = std::to_string(diffuseNr++);
			}
			else if (name == "texture_specular")
			{
				number = std::to_string(specularNr++);
			}

			//����shader���������������
			shader.setInt(("material." + name + number).c_str(), i);
			
			//�󶨶�Ӧ������
			glBindTexture(GL_TEXTURE_2D, textures[i].id);
		}

		//��������
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
		
		//�����ֳ�
		glBindVertexArray(0);
		glActiveTexture(GL_TEXTURE0);
	}
private:
	unsigned int VAO, VBO, EBO;

	//����
	void setupMesh()
	{	
		//���������׵�����
		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
		glGenBuffers(1, &EBO);

		//�󶨵�ǰ�����VAO����
		glBindVertexArray(VAO);

		//�󶨵�ǰ����VBO������������Ӧ�Ķ�������
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

		//�󶨵�ǰ����EBO����������䶥������������
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int),
			&indices[0], GL_STATIC_DRAW);

		//���VAO��Ϣ��֪������ɫ����ν���VBO��ÿһ�����������
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));

		//������ɫ����Ӧ������
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glEnableVertexAttribArray(2);

		//�����ֳ�
		glBindVertexArray(0);
	}
};
#endif
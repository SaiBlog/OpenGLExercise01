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
	unsigned int id;//纹理生成的索引
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

		setupMesh();//绑绑绑
	}

	//绘制网格
	void Draw(Shader& shader)
	{
		//纹理编号
		unsigned int diffuseNr = 1;
		unsigned int specularNr = 1;

		//传递纹理信息
		for (unsigned int i = 0; i < textures.size(); i++)
		{
			//激活某个纹理通道
			glActiveTexture(GL_TEXTURE0 + i);

			//获取纹理的编号以及类型
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

			//设置shader材料中纹理的索引
			shader.setInt(("material." + name + number).c_str(), i);
			
			//绑定对应的纹理
			glBindTexture(GL_TEXTURE_2D, textures[i].id);
		}

		//绘制网格
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
		
		//清理现场
		glBindVertexArray(0);
		glActiveTexture(GL_TEXTURE0);
	}
private:
	unsigned int VAO, VBO, EBO;

	//绑绑绑
	void setupMesh()
	{	
		//生成三件套的索引
		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
		glGenBuffers(1, &EBO);

		//绑定当前网格的VAO索引
		glBindVertexArray(VAO);

		//绑定当前网格VBO索引并且填充对应的顶点数据
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

		//绑定当前网格EBO索引并且填充顶点索引的数据
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int),
			&indices[0], GL_STATIC_DRAW);

		//填充VAO信息告知顶点着色器如何解析VBO中每一个顶点的数据
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));

		//开启着色器对应的索引
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glEnableVertexAttribArray(2);

		//清理现场
		glBindVertexArray(0);
	}
};
#endif
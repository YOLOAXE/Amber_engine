#pragma once
#define _USE_MATH_DEFINES

#include "FastNoise.hpp"
#include <glm/glm.hpp>
#include <glm/fwd.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <vector>
#include <iostream>
#include <math.h> 
#include <cmath>
#include <string>

class Terrain
{
public:
	Terrain(unsigned int _size, float _tileSize, FastNoise::NoiseType _noiseType, float _noiseFrequency);
	Terrain(unsigned int _size, float _tileSize, FastNoise::NoiseType _noiseType, float _noiseFrequency, int seed);
	Terrain(unsigned int _size, float _tileSize, FastNoise::NoiseType _noiseType, float _noiseFrequency, int seed, int noiseOctaves, int noiseMagnitude, bool isIsland);

	std::string getTerrainConfigString();

	glm::vec3 getFirstVertexPosition();

	void increaseNoiseFrequency();
	void decreaseNoiseFrequency();

	void increaseMagnitude();
	void decreaseMagnitude();

	void increaseOctaves();
	void decreaseOctaves();

	void makeIsland();
	
	void regenerateTerrain();

	void render(unsigned int& program);
	glm::mat4 getModel();
private:
	unsigned int  VAO;
	unsigned int  VBO, EBO;

	std::vector<float> vertices;
	std::vector<unsigned int> indices;

	float fillR = 0.0f;
	float fillG = 0.0f;
	float fillB = 0.0f;

	unsigned int width;
	unsigned int height;

	int centerX;
	int centerY;
	float maxDistance;

	float tileSize;
	int seed;
	unsigned int octaves;
	int magnitude;
	float exponent = 2;

	bool isIsland = false;

	FastNoise noise;
	float noiseFrequency;
	FastNoise::NoiseType noiseType;

	std::vector<std::vector<float>> colours = {
		//  r     g     b
		{ 0.25f, 0.36f, 1.56f, }, // water
		{ 0.49f, 0.72f, 0.45f, }, // land
		{ 0.45f, 0.72f, 0.46f, }, // higher land
		{ 1.0f, 1.0f, 1.0f, } // snow
	};

	glm::mat4 model = glm::mat4(1.0f);

	void setDefaults();
	void calculateMaxDistance();

	void createTerrain();

	void generateVertices();
	void generateIndices();

	void initBuffers();

	void updateColourForHeight(unsigned int& startIndex, float& y);
	void addColourForHeight(float& y);

	void updateHeightmap(bool useNewSeed);
	
	void loadIntoShader();
};


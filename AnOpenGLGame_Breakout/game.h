#pragma once
#ifndef GAME_H
#define GAME_H
#include<GL/glew.h>
#include<GLFW/glfw3.h>
//当前游戏状态
enum GameState {
	GAME_ACTIVE,
	GAME_MENU,
	GAME_WIN
};
//包含所有游戏状态和函数
class Game {
public:
	GameState State;
	GLboolean Keys[1024];
	GLuint Width, Height;
	Game(GLuint width,GLuint height);
	~Game();
	//初始化 shader,纹理、层级
	void Init();
	//游戏循环
	void ProcessInput(GLfloat dt);
	void Update(GLfloat dt);
	void Render();
};
#endif

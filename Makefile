all:
	g++ BoneSprite.cpp Input.cpp main.cpp Sprite.cpp GameOptions.cpp Level.cpp ShaderHelp.cpp Textures.cpp -lGL -lGLU -lGLEW -lSDL2 -lpng

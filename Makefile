all:
	g++ BoneSprite.cpp Input.cpp main.cpp StatSprite.cpp Sprite.cpp GameOptions.cpp Level.cpp ShaderHelp.cpp Textures.cpp Entity.cpp -lGL -lGLU -lGLEW -lSDL2 -lpng

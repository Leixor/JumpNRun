#pragma once
class RectShape : public RectangleShape
{
public:
	RectShape(IntRect buttonRect, String texturePath);
	~RectShape();

	void unloadTextures();
	bool loadTextures();
private:
	String texturePath;
	Texture rectTexture;
};


#pragma once

template <class Drawable> class DrawableShape : public Drawable
{
public:
	DrawableShape(IntRect buttonRect);
	DrawableShape(IntRect buttonRect, String texturePath);
	DrawableShape(Vector2f position, int radius, int corners = 0);
	~DrawableShape();
	
	void setTexturePath(String path);

	void unloadTextures();
	bool loadTextures();
private:
	String* texturePath;
};

template<class Drawable>
inline DrawableShape<Drawable>::DrawableShape(IntRect buttonRect)
{
	this->setPosition(float(buttonRect.left), float(buttonRect.top));
	this->setSize(Vector2f(buttonRect.width, buttonRect.height));
}

template<class Drawable>
inline DrawableShape<Drawable>::DrawableShape(IntRect buttonRect, String texturePath)
	: Sprite(nullptr, buttonRect), texturePath(texturePath)
{
}

template<class Drawable>
inline DrawableShape<Drawable>::DrawableShape(Vector2f position, int radius, int corners = 0)
{
	this->setPosition(position.x, position.y);
	this->setRadius(float(radius));

	if (corners != 0)
	{
		this->setPointCount(corners);
	}
}

template<class Drawable>
inline DrawableShape<Drawable>::~DrawableShape()
{
}

template<class Drawable>
inline void DrawableShape<Drawable>::setTexturePath(String path)
{
	this->texturePath = path;
}

template<class Drawable>
inline void DrawableShape<Drawable>::unloadTextures()
{
	if (this->texturePath != "")
	{
		Texture* tmpTexture = new Texture();
		tmpTexture->create(1, 1);
		this->setTexture(tmpTexture);
	}
}

template<class Drawable>
inline bool DrawableShape<Drawable>::loadTextures()
{
	if (this->texturePath != nullptr)
	{
		Texture* tmpTexture = new Texture();

		if (tmpTexture->loadFromFile(this->texturePath))
		{
			this->setTexture(*tmpTexture);
			return true;
		}
		return false;
	}
	return true;
}

//#include "StandardInclude.h"
//
//Animation::Animation(AnimationHandler* sceneHandler, unsigned int millisec, string name) : handler(sceneHandler), aniDuration(millisec)
//{
//	this->updateCount = float(aniDuration / MS_PER_UPDATE);
//	this->handler->addAni(this, name);
//}
//
//Animation::~Animation()
//{
//}
//
//void Animation::run(bool loop)
//{
//	if (!this->isRunning())
//	{
//		this->loop = loop;
//		this->running = true;
//		this->timeCount = 0;
//	}
//}
//
//void Animation::stop()
//{
//	if (this->isRunning())
//	{
//		this->running = false;
//	}
//}
//
//void Animation::update()
//{
//	for (int i = 0; i < objects.size(); i++)
//	{
//		if (objects.get(i) < updateCount)
//		{
//			for (int j = 0; j < aniFunctions.size(); j++)
//			{
//				aniFunctions.getIterator(j)(objects.getIterator(i));
//			}
//		}
//		else
//		{
//			if (this->loop)
//			{
//				this->timeCount = 0;
//			}
//			else
//			{
//				this->running = false;
//			}
//		}
//	}	
//}
//
//
//void Animation::reset()
//{
//	this->timeCount = 0;
//}
//
//void Animation::addRotation(float angle, Vector2f origin)
//{
//		aniFunctions.push(this->rotate(angle, origin), updateCount);
//}
//
//void Animation::addScale(Vector2f scale, Vector2f origin)
//{
//	aniFunctions.push(this->scale(scale, origin), updateCount);
//}
//
//void Animation::addMovement(Vector2f move)
//{
//	aniFunctions.push(this->move(move, updateCount), updateCount);
//}
//
//void Animation::setRotation(float angle, Vector2f origin)
//{
//	aniFunctions.push(this->rotate(angle, origin, true), updateCount);
//}
//
//void Animation::setScale(Vector2f scale, Vector2f origin)
//{
//	aniFunctions.push(this->scale(scale, origin, true), updateCount);
//}
//
//void Animation::setMovement(Vector2f move)
//{
//	aniFunctions.push(this->move(move, true), updateCount);
//}
//
//void Animation::addAniToObject(DrawableObject * object)
//{
//	objects.push(object, 0);
//}
//
//unsigned int Animation::getTime()
//{
//	return 0;
//}
//
//function<void(DrawableObject*)> Animation::rotate(float angle, Vector2f origin, bool set)
//{
//	
//	
//	rotateOrigin = origin;
//	return [&](DrawableObject* object) {
//		if (set)
//		{
//			float cRotation = object->getRotation();
//			subAngle = float((angle - cRotation) / updateCount);
//		}
//		else
//		{
//			subAngle = float(angle / updateCount);
//		}
//		object->rotate(subAngle, rotateOrigin);
//	};
//}
//
//function<void(DrawableObject*)> Animation::scale(Vector2f scale, Vector2f origin, bool set)
//{
//	if (set) 
//	{
//		Vector2f cScale = object->getScale();
//		subScale = Vector2f(float((scale.x - cScale.x) / updateCount), float((scale.y - cScale.y) / updateCount));
//	}
//	else
//	{
//		subScale = Vector2f(float(scale.x / updateCount), float(scale.y / updateCount));
//	}
//	
//	scaleOrigin = origin;
//	return [&](DrawableObject* object) {
//		object->setScale(this->object->getScale() + subScale, scaleOrigin);
//	};
//}
//
//function<void(DrawableObject*)> Animation::move(Vector2f move, bool set)
//{
//	if (set)
//	{
//		Vector2f cPos = object->getPosition();
//		subMove = Vector2f(float((move.x - cPos.x) / updateCount), float((move.y - cPos.y) / updateCount));
//	}
//	else
//	{
//		subMove = Vector2f(float(move.x / updateCount), float(move.y / updateCount));
//	}
//	
//	return [&](DrawableObject* object) {
//		object->move(subMove);
//	};
//}

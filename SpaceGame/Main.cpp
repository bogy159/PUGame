/*****************************************************************************************
* Desc: Tutorial 02 IND_Surface
*****************************************************************************************/

#include "CIndieLib.h"
#include "IND_Surface.h"
#include "IND_Entity2d.h"
#include "IND_Animation.h"

/*
==================
Main
==================
*/
int IndieLib()
{
	bool faster = false;
	// ----- IndieLib intialization -----

	CIndieLib *mI = CIndieLib::instance();
	if (!mI->init()) return 0;

	
	// ----- Surface loading -----

	// Loading Background
	IND_Surface *mSurfaceBack = IND_Surface::newSurface();
	if (!mI->_surfaceManager->add(mSurfaceBack, "../SpaceGame/GraphicResources/Backgrounds/3.jpg", IND_OPAQUE, IND_32)) return 0;

	// Loading sprite of a star
	IND_Surface *mSurfaceStar = IND_Surface::newSurface();
	if (!mI->_surfaceManager->add(mSurfaceStar, "../SpaceGame/resources/weheartit-icon-u11493.png", IND_ALPHA, IND_32)) return 0;

	// Loading Beetleship
	IND_Surface *mSurfaceBeetle = IND_Surface::newSurface();

	// ----- Animations loading -----

	// Characters animations, we apply a color key of (0, 48, 152)
	IND_Animation *mAnimationCharacter1 = IND_Animation::newAnimation();
	if (!mI->_animationManager->addToSurface(mAnimationCharacter1, "../SpaceGame/resources/animations/character1.xml", IND_ALPHA, IND_32, 0, 48, 152)) return 0;

	// Characters animations, we apply a color key of (0, 48, 152)
	IND_Animation *mAnimationCharacter2 = IND_Animation::newAnimation();
	if (!mI->_animationManager->addToSurface(mAnimationCharacter2, "../SpaceGame/resources/animations/character2.xml", IND_ALPHA, IND_32, 0, 48, 152)) return 0;

	// Dust animation, we apply a color key of (255, 0, 255)
	IND_Animation *mAnimationDust = IND_Animation::newAnimation();
	if (!mI->_animationManager->addToSurface(mAnimationDust, "../SpaceGame/resources/animations/dust.xml", IND_ALPHA, IND_16, 255, 0, 255)) return 0;

	// ----- Set the surface and animations into 2d entities -----

	// Creating 2d entity for the background
	IND_Entity2d *mBack = IND_Entity2d::newEntity2d();
	mI->_entity2dManager->add(mBack);					// Entity adding
	mBack->setSurface(mSurfaceBack);					// Set the surface into the entity

	//star 1
	IND_Entity2d *star1 = IND_Entity2d::newEntity2d();
	mI->_entity2dManager->add(star1);
	star1->setSurface(mSurfaceStar);

	//star 2
	IND_Entity2d *star2 = IND_Entity2d::newEntity2d();
	mI->_entity2dManager->add(star2);
	star2->setSurface(mSurfaceStar);

	//star 3
	IND_Entity2d *star3 = IND_Entity2d::newEntity2d();
	mI->_entity2dManager->add(star3);
	star3->setSurface(mSurfaceStar);

	// Creating 2d entity for the Beetleship
	IND_Entity2d *mBeetle = IND_Entity2d::newEntity2d();
	mI->_entity2dManager->add(mBeetle);					// Entity adding
	mBeetle->setSurface(mSurfaceBeetle);					// Set the surface into the entity

	// Character 1
	IND_Entity2d *mPlayer1 = IND_Entity2d::newEntity2d();
	mI->_entity2dManager->add(mPlayer1);					// Entity adding
	mPlayer1->setAnimation(mAnimationCharacter1);				// Set the animation into the entity


	// Character 2
	IND_Entity2d *mPlayer2 = IND_Entity2d::newEntity2d();
	mI->_entity2dManager->add(mPlayer2);					// Entity adding
	mPlayer2->setAnimation(mAnimationCharacter2);				// Set the animation into the entity

	// Dust explosion
	IND_Entity2d *mDust = IND_Entity2d::newEntity2d();
	mI->_entity2dManager->add(mDust);					// Entity adding
	mDust->setAnimation(mAnimationDust);					// Set the animation into the entity

	// ----- Changing the attributes of the 2d entities -----

	// Beetle
	mBeetle->setBoundingRectangle("choveche", mPlayer1->getPosX(), mPlayer1->getPosY(), 120, 205);

	// Background(ramka)
	mBack->setBoundingRectangle("left", 0, 1, 1, mI->_window->getHeight()-3);
	mBack->setBoundingRectangle("right", mI->_window->getWidth() - 2, 1, 1, mI->_window->getHeight() - 3);
	mBack->setBoundingRectangle("top", 1, 0, mI->_window->getWidth() - 3, 1);
	mBack->setBoundingRectangle("bottom", 1, mI->_window->getHeight() - 2, mI->_window->getWidth() - 3, mI->_window->getHeight() - 1);

	// Player 1
	mPlayer1->setSequence(0);						// Choose sequence	
	mPlayer1->setPosition(140, 200, 0);
	mPlayer1->setMirrorX(1);						// Horizontal mirroring

	// Dust explosion
	mDust->setPosition(360, 250, 0);

	// Player 2
	mPlayer2->setSequence(0);						// Choose sequence
	mPlayer2->setPosition(550, 200, 0);
	mPlayer2->setNumReplays(3);						// The animation will be displayed 3 times

	//star 1
	star1->setPosition(mI->_window->getWidth() - mSurfaceStar->getWidth(), 0, 100);
	//star 2
	star2->setPosition(mI->_window->getWidth() - 2*mSurfaceStar->getWidth(), 0, 100);
	//star 3
	star3->setPosition(mI->_window->getWidth() - 3*mSurfaceStar->getWidth(), 0, 100);

	int health = 6;
	float mDelta;
	float mPos = 6;
	float mSpeed = 50;
	// ----- Main Loop -----
	
	while (!mI->_input->onKeyPress(IND_ESCAPE) && !mI->_input->quit())
	{
		mI->_input->update();

		if (health < 6)
		{
			star3->setShow(false);
		}
		if (health < 4)
		{
			star2->setShow(false);
		}
		if (health < 2)
		{
			star1->setShow(false);
		}

		mDelta = mI->_render->getFrameTime() / 1000.0f;

		if (mI->_input->isKeyPressed(IND_W))
		{
			mPos = mPlayer1->getPosY();
			mPos -= mSpeed * mDelta;
			mSpeed += 0.05;
			mPlayer1->setPosition(mPlayer1->getPosX(), (float)mPos, mPlayer1->getPosZ());
		}
		if (mI->_input->isKeyPressed(IND_A))
		{
			mPos = mPlayer1->getPosX();
			mPos -= mSpeed * mDelta;
			mSpeed += 0.05;
			mPlayer1->setPosition((float)mPos, mPlayer1->getPosY(), mPlayer1->getPosZ());
		}
		if (mI->_input->isKeyPressed(IND_S))
		{
			mPos = mPlayer1->getPosY();
			mPos += mSpeed * mDelta;
			mSpeed += 0.05;
			mPlayer1->setPosition(mPlayer1->getPosX(), (float)mPos, mPlayer1->getPosZ());
		}
		if (mI->_input->isKeyPressed(IND_D))
		{
			mPos = mPlayer1->getPosX();
			mPos += mSpeed * mDelta;
			mSpeed += 0.05;
			mPlayer1->setPosition((float)mPos, mPlayer1->getPosY(), mPlayer1->getPosZ());
		}

		if (mI->_input->isKeyPressed(IND_W) == false && mI->_input->isKeyPressed(IND_A) == false && mI->_input->isKeyPressed(IND_S) == false && mI->_input->isKeyPressed(IND_D) == false)
		{
			mSpeed = 50;
		}


		mBeetle->setPosition(mPlayer1->getPosX(), mPlayer1->getPosY(), 5);

		if (mI->_entity2dManager->isCollision(mBeetle, "choveche", mBack, "left"))
		{
			health = health - 1;
			mPlayer1->setPosition(34, mPlayer1->getPosY(), 100);
		}
		if (mI->_entity2dManager->isCollision(mBeetle, "choveche", mBack, "right"))
		{
			health = health - 1;
			mPlayer1->setPosition(mI->_window->getWidth() - (34 + 120), mPlayer1->getPosY(), 100);
		}
		if (mI->_entity2dManager->isCollision(mBeetle, "choveche", mBack, "top"))
		{
			health = health - 1;
			mPlayer1->setPosition(mPlayer1->getPosX(), 34, 100);
		}
		if (mI->_entity2dManager->isCollision(mBeetle, "choveche", mBack, "bottom"))
		{
			health = health - 1;
			mPlayer1->setPosition(mPlayer1->getPosX(), mI->_window->getHeight() - (34 + 205), 100);
		}


		mI->_render->beginScene();
		mI->_entity2dManager->renderEntities2d();
		mI->_render->endScene();
	}

	// ----- Free -----

	mI->end();

	return 0;
}
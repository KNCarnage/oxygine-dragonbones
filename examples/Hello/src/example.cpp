#include "oxygine-framework.h"
#include <functional>
#include "lib/Armature.h"
#include "lib/Skeleton.h"
#include "Character.h"

//#include "DragonBonesFactory.h"
using namespace oxygine;

//it is our resources
//in real project you would have more than one Resources declarations.
//It is important on mobile devices with limited memory and you would load/unload them
Resources gameResources;

class Control : public Sprite
{
public:
    Control(int col)
    {
        setResAnim(gameResources.getResAnim("controls"), col);
        setBlendMode(blend_add);
        setAnchor(0.5f, 0.5f);
        addEventListener(TouchEvent::CLICK, [&](Event*)
        {
            setColor(Color::White);
            addTween(Sprite::TweenColor(Color::Black), 300, 1, true);
        });
    }
};

const char* movies[] = { "1.mp4", "1.mp4", "1.mp4", "2.mkv", "3.avi" };

class MainActor: public Actor
{
public:
	//DragonBonesFactory factory;

    spTextField _text;
    spSprite    _button;

	spCharacter _char;

    int         _current;

	db::Skeleton sk;

	int			_currentAnim;
	int			_currentArm;

	const Armature *_arm;

	void update()
	{
		if (_arm)
		{
			if (_currentAnim >= _arm->getNumAnimations())
			{
				_currentAnim = 0;
				_currentArm++;
				_currentArm = _currentArm % sk.getArmaturesNum();
			}

			if (_currentAnim < 0)
			{				
				_currentArm--;
				_currentArm = _currentArm % sk.getArmaturesNum();
				_currentAnim = sk.getArmature(_currentArm)->getNumAnimations() - 1;
			}

			_arm = sk.getArmature(_currentArm);
			_char->setArmature(_arm);
		}		
		
		_char->setAnimation(_arm->getAnimation(_currentAnim));
	}

	MainActor() : _current(0), _currentAnim(0), _currentArm(0)
    {
		pugi::xml_document doc;
		doc.load_file("db/skeleton.xml");
		
		sk.load(doc.first_child());

		_char = new Character();
		_arm = sk.getArmature(0);
		_char->setResources(&gameResources);
		_char->setPosition(getStage()->getSize() / 2);
		_char->setScale(2);
		//_char->setScale(2);
		update();
		addChild(_char);


		spSprite sp = new Sprite;
		sp->setResAnim(gameResources.getResAnim("Zombie_polevaulter_folder/Zombie_polevaulter_pole"));
		sp->setPosition(100, 100);
		addChild(sp);
		
        //create buttons

        Vector2 pos = Vector2(getStage()->getWidth() / 2 - 130, getStage()->getHeight() - 50);


        spSprite  play = new Control(1);
		/*
        play->setPosition(pos);
        play->attachTo(this);
        play->addEventListener(TouchEvent::CLICK, [&](Event*)
        {
            //_movie->play();
        });

        pos.x += play->getWidth();
        spSprite  pause = new Control(2);
        pause->setPosition(pos);
        pause->attachTo(this);
        pause->addEventListener(TouchEvent::CLICK, [&](Event*)
        {
            //_movie->pause();
        });

        pos.x += play->getWidth();
        spSprite stop = new Control(3);
        stop->setPosition(pos);
        stop->attachTo(this);
        stop->addEventListener(TouchEvent::CLICK, [&](Event*)
        {
            //_movie->stop();
        });

		*/
		
		pos.x += play->getWidth();
		spSprite prev = new Control(0);
		prev->setPosition(pos);
		prev->attachTo(this);
		prev->addEventListener(TouchEvent::CLICK, [&](Event*)
		{
			_currentAnim--;
			update();
		});

		pos.x += play->getWidth();
		spSprite next = new Control(4);
		next->setPosition(pos);
		next->attachTo(this);
		next->addEventListener(TouchEvent::CLICK, [&](Event*)
		{
			_currentAnim++;
			update();
		});
    }

    void playNext()
    {
		/*
        _movie->setMovie(movies[_current % 3]);
        _movie->play();
		*/
    }
};
//declare spMainActor as intrusive_ptr holder of MainActor
typedef oxygine::intrusive_ptr<MainActor> spMainActor;

void example_preinit() {}

//called from entry_point.cpp
void example_init()
{
    //load xml file with resources definition
    gameResources.loadXML("res.xml");

    //MovieSprite::init();

    //lets create our client code simple actor
    //spMainActor was defined above as smart intrusive pointer (read more: http://www.boost.org/doc/libs/1_57_0/libs/smart_ptr/intrusive_ptr.html)
    spMainActor actor = new MainActor;

    //and add it to Stage as child
    getStage()->addChild(actor);
}


//called each frame from entry_point.cpp
void example_update()
{
}

//called each frame from entry_point.cpp
void example_destroy()
{
    //free previously loaded resources
    gameResources.free();
}

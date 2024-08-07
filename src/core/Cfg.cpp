#include <pch.hpp>

ResourceManager<sf::Texture, int> Cfg::textures = {};
ResourceManager<sf::Font, int> Cfg::fonts = {};
ResourceManager<sf::Music, int> Cfg::music = {};
ResourceManager<sf::SoundBuffer, int> Cfg::sounds = {};

ActionMap<int> Cfg::playerInputs = {};
int Cfg::ScrW = { 1280 };
int Cfg::ScrH = { 768 };
void Cfg::Initialize()
{
    initTextures();
    initFonts();
    initMusic();
    initSounds();
	initPlayerInputs();
 
}

void Cfg::initMusic()
{
    /*  music.load(Music::Intro, "assets/sounds/music/tetrisc.wav"); */
}

void Cfg::initSounds()
{

}

void Cfg::initTextures()
{
	textures.load((int)Textures::FlyPad, "assets/textures/platforms/fly_pad67x40.png");
	textures.load((int)Textures::PlayerAtlas, "assets/textures/actors/player/player_atlas.png");
	textures.load((int)Textures::MetalBird, "assets/textures/actors/enemies/metal_bird/metal_bird.png");
	textures.load((int)Textures::BusterShot_Normal, "assets/textures/projectiles/bullets/buster_shot/buster_shot_normal.png");

	/*textures.load((int)Textures::PlayerRun, "assets/tex/megaman/run136x140_10.png");
	textures.load((int)Textures::PlayerTransRun, "assets/tex/megaman/trans_run135x136.png");
	textures.load((int)Textures::PlayerShootStand, "assets/tex/megaman/shoot_stand120x136_2.png");
	textures.load((int)Textures::PlayerTransJump, "assets/tex/megaman/trans_jump120x184_2.png");
	textures.load((int)Textures::PlayerRise, "assets/tex/megaman/rise120x184_1.png");
	textures.load((int)Textures::PlayerTransFall, "assets/tex/megaman/trans_fall120x184_1.png");
	textures.load((int)Textures::PlayerFall, "assets/tex/megaman/fall120x184_1.png");
	textures.load((int)Textures::PlayerLand, "assets/tex/megaman/land120x184_2.png");
	textures.load((int)Textures::PlayerAtlas, "assets/tex/megaman/mm_sheet_130x160.png");
	textures.load((int)Textures::PlayerAtlas, "assets/tex/megaman/mm_atlast_left.png");
	textures.load((int)Textures::PlayerSheet, "assets/tex/megaman/mmsheet.png");

	textures.load((int)Textures::BGSpace, "assets/tex/backgrounds/space/BG1_0_4800x2700.png");
	textures.load((int)Textures::BirdSheetWSaw, "assets/tex/enemies/BirdSheet220x296_3Rows_7_9_2.png");*/
}

void Cfg::initPlayerInputs()
{
	// realtime events
	// Keyboard pressed commands
	playerInputs.map(Cfg::PlayerInputs::X, Action(sf::Keyboard::Num9));
	playerInputs.map(Cfg::PlayerInputs::Y, Action(sf::Keyboard::X));
	playerInputs.map(Cfg::PlayerInputs::A, Action(sf::Keyboard::Num0));
	playerInputs.map(Cfg::PlayerInputs::B, Action(sf::Keyboard::Space));
	playerInputs.map(Cfg::PlayerInputs::L1, Action(sf::Keyboard::Num7));
	playerInputs.map(Cfg::PlayerInputs::R1, Action(sf::Keyboard::Add));
	// menu controls
	playerInputs.map(Cfg::PlayerInputs::Start, Action(sf::Keyboard::Enter));
	playerInputs.map(Cfg::PlayerInputs::Select, Action(sf::Keyboard::Backspace));
	// direction controls
	playerInputs.map(Cfg::PlayerInputs::Up, Action(sf::Keyboard::Up));
	playerInputs.map(Cfg::PlayerInputs::Down, Action(sf::Keyboard::Down));
	playerInputs.map(Cfg::PlayerInputs::Left, Action(sf::Keyboard::Left));
	playerInputs.map(Cfg::PlayerInputs::Right, Action(sf::Keyboard::Right));

	// Joystick Controls
	// Axis mappings
	playerInputs.map(Cfg::PlayerInputs::AxisX, Action(sf::Joystick::Axis::X, Action::Type::RealTime | Action::Type::Tilted));
	playerInputs.map(Cfg::PlayerInputs::AxisY, Action(sf::Joystick::Axis::Y, Action::Type::RealTime | Action::Type::Tilted));
	playerInputs.map(Cfg::PlayerInputs::DPadX, Action(sf::Joystick::Axis::PovX, Action::Type::RealTime | Action::Type::Tilted));
	playerInputs.map(Cfg::PlayerInputs::DPadY, Action(sf::Joystick::Axis::PovY, Action::Type::RealTime | Action::Type::Tilted));
	// Button mappings
	playerInputs.map(Cfg::PlayerInputs::JoyA, Action(JoystickBtn::A, Action::Type::RealTime | Action::Type::Pressed));
	playerInputs.map(Cfg::PlayerInputs::JoyB, Action(JoystickBtn::B, Action::Type::RealTime | Action::Type::Pressed));
	playerInputs.map(Cfg::PlayerInputs::JoyX, Action(JoystickBtn::X, Action::Type::RealTime | Action::Type::Pressed));
	playerInputs.map(Cfg::PlayerInputs::JoyY, Action(JoystickBtn::Y, Action::Type::RealTime | Action::Type::Pressed));
	playerInputs.map(Cfg::PlayerInputs::JoyL1, Action(JoystickBtn::L1, Action::Type::RealTime | Action::Type::Pressed));
	playerInputs.map(Cfg::PlayerInputs::JoyR1, Action(JoystickBtn::R1, Action::Type::RealTime | Action::Type::Pressed));
	playerInputs.map(Cfg::PlayerInputs::JoyStart, Action(JoystickBtn::Start, Action::Type::RealTime | Action::Type::Pressed));
	playerInputs.map(Cfg::PlayerInputs::JoySelect, Action(JoystickBtn::Select, Action::Type::RealTime | Action::Type::Pressed));

}

void Cfg::initFonts()
{
	fonts.load((int)Fonts::Freedom, "assets/fonts/freedom.ttf");
	fonts.load((int)Fonts::FriskyPuppy, "assets/fonts/frisky_puppy.ttf");

}
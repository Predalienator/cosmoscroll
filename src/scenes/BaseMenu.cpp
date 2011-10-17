#include <cassert>

#include "BaseMenu.hpp"
#include "core/Game.hpp"
#include "core/SoundSystem.hpp"
#include "utils/Resources.hpp"


BaseMenu::BaseMenu()
{
	SetBackground(sf::Sprite(Resources::GetImage("gui/main-screen.png")));
	scrolling_background_.SetImage(Resources::GetImage("gui/background.png"));

	GetWidgetStyle().global_font = &GetMenuFont();
}


void BaseMenu::OnEvent(const sf::Event& event)
{
	// propaging events to gui
	gui::Menu::OnEvent(event);
}


void BaseMenu::Update(float frametime)
{
	static const int SPEED = 30;
	static float y = 0;
	y -= SPEED * frametime;
	if (y < 0)
	{
		y = Game::HEIGHT;
	}
	scrolling_background_.SetY(y);

	// updating gui
	gui::Menu::Update(frametime);
}


void BaseMenu::Show(sf::RenderTarget& target) const
{
	// drawing background twice for scrolling purpose
	target.Draw(scrolling_background_);
	scrolling_background_.SetCenter(0.f, scrolling_background_.GetSize().y);
	target.Draw(scrolling_background_);
	scrolling_background_.SetCenter(0.f, 0.f);

	// drawing gui
	gui::Menu::Show(target);
	target.Draw(title_);
}


void BaseMenu::OnFocus()
{
	// for user-friendly menus
	Game::GetInstance().GetApp().ShowMouseCursor(true);
	Game::GetInstance().GetApp().EnableKeyRepeat(true);
}


void BaseMenu::SetTitle(const sf::Unicode::Text& text, int y)
{
	title_.SetFont(GetMenuFont());
	title_.SetSize(40);
	title_.SetText(text);
	title_.SetX((Game::WIDTH - title_.GetRect().GetWidth()) / 2);
	title_.SetY(y);
}


const sf::String& BaseMenu::GetTitle() const
{
	return title_;
}


void BaseMenu::OnWidgetFocused()
{
	SoundSystem::GetInstance().PlaySound(Resources::GetSoundBuffer("menu-select.wav"));
}



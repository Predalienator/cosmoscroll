#include "ConfigButton.hpp"
#include "utils/MediaManager.hpp"

#define BUT_W 100
#define BUT_H 25

const sf::Image* ConfigButton::img_ = NULL;

ConfigButton::ConfigButton(gui::Menu* owner, const sf::Unicode::Text& text, int x, int y) :
	gui::Button(owner, text, x, y, BUT_W, BUT_H)
{
	if (img_ == NULL)
	{
		img_ = &GET_IMG("gui/button-config");
	}

	background_.SetImage(*img_);
	background_.SetSubRect(sf::IntRect(0, 0, BUT_W, BUT_H));
	background_.Resize(BUT_W, BUT_H);

	SetTextPadding(0, -2);
	SetAlign(gui::Align::CENTER);
	OnStateChanged(GetState());
}


void ConfigButton::OnStateChanged(gui::State::EState state)
{
	switch (state)
	{
		case gui::State::DEFAULT:
			background_.SetSubRect(sf::IntRect(0, 0, BUT_W, BUT_H));
			break;
		case gui::State::HOVERED:
			background_.SetSubRect(sf::IntRect(0, BUT_H, BUT_W, BUT_H * 2));
			break;
		case gui::State::FOCUSED:
			background_.SetSubRect(sf::IntRect(0, BUT_H * 2, BUT_W, BUT_H * 3));
			break;
		default:
			break;
	}
	gui::Button::OnStateChanged(state);
}


void ConfigButton::OnCallbackTriggered()
{
}


void ConfigButton::Render(sf::RenderTarget& target) const
{
	target.Draw(background_);
	gui::Button::Render(target);
}


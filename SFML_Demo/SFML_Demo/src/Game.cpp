#include "Game.h"
#include <iostream>

/// <summary>
/// @author RP
/// Simple demo to demonstrate an optimisation of rendering sf::Text
/// Instead of rendering each Text object separately (assuming the text is static), 
///  bake it into a RenderTexture and draw that instead.
/// We effectively reduce the number of draw calls using this method.
/// </summary>

// Updates per milliseconds
static double const MS_PER_UPDATE = 10.0;

////////////////////////////////////////////////////////////
Game::Game()
	: m_window(sf::VideoMode(ScreenSize::s_width, ScreenSize::s_height, 32), "Rendering Text", sf::Style::Default)
	
{
	m_window.setVerticalSyncEnabled(true);
	
	if (!m_font.loadFromFile("ariblk.ttf"))
	{
		throw std::exception("Cannot load font");
	}

	// Create a vector to hold a 93*93*93 sequence of sf::Text,
	//  where each sf::Text contains a 3 character sequence.
	m_texts.reserve(93 * 93 * 93);
	
	int position = 0;

	for (char a = '!'; a <= '}'; ++a)
	{
		for (char b = '!'; b <= '}'; ++b)
		{
			for (char c = '!'; c <= '}'; ++c, position += 20)
			{
				const char str[] = { a, b, c, '\0' };
				m_texts.push_back(sf::Text(str, m_font, 20));
				sf::Text& text = m_texts.back();
				text.setPosition(10 + position % (ScreenSize::s_width-20), 
					             10 + position / (ScreenSize::s_width - 20) * 10);
				text.setFillColor(sf::Color::Red);
			}
		}
	}
	setUpRenderTexture();
}

//default game loop
////////////////////////////////////////////////////////////
void Game::run()
{
	sf::Clock clock;
	sf::Int32 lag = 0;

	while (m_window.isOpen())
	{
		sf::Time dt = clock.restart();

		lag += dt.asMilliseconds();

		processEvents();

		while (lag > MS_PER_UPDATE)
		{
			update(MS_PER_UPDATE);
			lag -= MS_PER_UPDATE;
		}
		update(MS_PER_UPDATE);

		render();
	}
}

////////////////////////////////////////////////////////////
void Game::processEvents()
{
	sf::Event event;
	while (m_window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)//close window
		{
			m_window.close();
		}
		processGameEvents(event);
	}
}

////////////////////////////////////////////////////////////
void Game::processGameEvents(sf::Event& event)
{
	switch (event.key.code)
	{
		case sf::Keyboard::Escape:
			m_window.close();
			break;
		default:
			break;
	}
}

void Game::setUpRenderTexture()
{
	// Complete this...

}

void Game::update(double dt)
{
	// No-op
}

void Game::render()
{
	m_window.clear(sf::Color::Black);

	// Draw your sprite here that is set to the render texture
	// and comment out the for loop below.

	// Deliberately copying each sf::Text instance from the vector
	// Otherwise difficult to get meaningful runtime figures from the profiler
	for (sf::Text text : m_texts)
	{
		m_window.draw(text);
	}
	

	m_window.display();
}
#include "Engine.h"

// A regular RenderWindow
// RenderWindow m_Window;   
// Vector for Particles
// vector<Particle> m_particles;

// The Engine constructor
Engine::Engine() {
	VideoMode vm(VideoMode::getDesktopMode().width / 2, VideoMode::getDesktopMode().height / 2);
	m_Window(vm, "Particles", Style::Default);
}
        
// Private functions for internal use only
void Engine::input() {
	Event event;
	while (window.pollEvent(event)) {
		if (event.type == Event::Closed) {
			window.close();
		}
		if (event.type == sf::Event::MouseButtonPressed) {
			if (event.mouseButton.button == sf::Mouse::Left) {
				for (int i = 0; i < 5; i++) {
					int numPoint = rand() % (50 - 25 + 1) + 25;
					Particle thisParticle(m_Window, numPoint, Vector2i((double)event.mouseButton.x, (double)event.mouseButton.y));
					m_particles.push_back(thisParticle);
				}
			}
		}
	}
	if (Keyboard::isKeyPressed(Keyboard::Escape)) {
		window.close();
	}
}
void Engine::update(float dtAsSeconds) {
	for (auto it = m_particles.begin(); it != m_particles.end(); ) {
		if (it->getTTL() > 0.0) {
			it->update(dtAsSeconds);
			++it;
		} else {
			it = m_particles.erase(it);
		}
	}
}
void Engine::draw() {
	m_Window.clear();
	for (int i = 0; i < m_particles.size(); i++) {
		m_Window.draw(m_particles.at(i));
	}
	m_Window.display();
}

// Run will call all the private functions
void Engine::run() {
	Clock clock();

	cout << "Starting Particle unit tests..." << endl;
	Particle p(m_Window, 4, { (int)m_Window.getSize().x / 2, (int)m_Window.getSize().y / 2 });
	p.unitTests();
	cout << "Unit tests complete.  Starting engine..." << endl;

	while (m_Window.isOpen()) {
		float t;
		t = clock.restart().asSeconds();
		input();
		update(t);
		draw();
	}
}

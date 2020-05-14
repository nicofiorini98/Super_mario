#pragma once

#include <QSound>

// Singleton class
class Sounds
{
	private:

		// sounds indexed by name
		std::map< std::string, QSound* > sounds;

		Sounds();

	public:

		// singleton
		static Sounds* instance();

		// play sound of the given id
		void play(const std::string & id);
		
};
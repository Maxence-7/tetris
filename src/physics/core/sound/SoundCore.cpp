#include "SoundCore.hpp"

SoundCore::SoundCore() : SoundCore(50.f,50.f) {}

SoundCore::SoundCore(volume_t musicVol, volume_t effectVol) : m_musicVolume(musicVol), m_effectVolume(effectVol) {
    m_music.openFromFile("tetris.ogg");
    if (!m_music.openFromFile("tetris.ogg")) {
        std::cout << "Error while opening the music file" << std::endl;
        //return 0;
    }
    m_music.setVolume(musicVol);
    m_music.setLoop(true);
    m_music.play();

    // Effects managed but can't be implemented : we didn't find assets which are in the public domain 
    /*if (!m_hitBuffer.loadFromFile("hit.ogg")) {
        std::cout << "Error while opening the hit effect file" << std::endl;
        //return 0;
    }

    if (!m_deleteBuffer.loadFromFile("delete.ogg")) {
        std::cout << "Error while opening the delete effect file" << std::endl;
        //return 0;
    }

    if (!m_loseBuffer.loadFromFile("lose.ogg")) {
        std::cout << "Error while opening the lose effect file" << std::endl;
        //return 0;
    }*/
};

void SoundCore::setMusicVolume(volume_t vol) {
    m_music.setVolume(vol);
}

void SoundCore::setEffetVolume(volume_t vol) {
    m_effectVolume = vol;
}


void SoundCore::playHit() const {
    sf::Sound s;
    s.setBuffer(m_hitBuffer);
    s.setVolume(m_effectVolume);
    s.play();
}

void SoundCore::playDeleteLine() const {
    sf::Sound s;
    s.setBuffer(m_deleteBuffer);
    s.setVolume(m_effectVolume);
    s.play();
}

void SoundCore::playLose() const {
    sf::Sound s;
    s.setBuffer(m_loseBuffer);
    s.setVolume(m_effectVolume);
    s.play();
}
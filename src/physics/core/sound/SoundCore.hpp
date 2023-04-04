#pragma once
#include <SFML/Audio.hpp>
#include <iostream>
class SoundCore
{
public:
    using volume_t = float;
private:
    volume_t m_musicVolume = 50;
    volume_t m_effectVolume = 50;
    sf::Music m_music;
    sf::SoundBuffer m_hitBuffer;
    sf::SoundBuffer m_deleteBuffer;
    sf::SoundBuffer m_loseBuffer;
    
public:

    /**
     * @brief Default constructor, init both music and effect volumes to 50.f out of 100.f *
     * @attention Undefined behavior if two instances are defined.
     */
    SoundCore();

    
    /**
     * @brief Constructor for SoundCore
     * @param musicVol : Music Volume, out of 100.f 
     * @param effectVol : Effects Volume, out of 100.f
     * @attention Undefined behavior if two instances are defined.
     */
    SoundCore(volume_t musicVol, volume_t effectVol);

    ~SoundCore() = default;

    
    /**
     * @brief Change Music Volume
     * @param vol : New volume, out of 100.f.
     */
    void setMusicVolume(volume_t);

public: // Effects managed but can't be implemented : we didn't find assets which are in the public domain 
    /**
     * @brief Change Effect Volume
     * @param vol : New volume, out of 100.f.
     */
    void setEffetVolume(volume_t vol);


    
    /**
     * @brief Play Hit Sound
     */
    void playHit() const;

    /**
     * @brief Play block delete sound
     */
    void playDeleteLine() const;
    
    /**
     * @brief Play lose sound
     */
    void playLose() const ;
};
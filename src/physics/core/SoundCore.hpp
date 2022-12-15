#include "SFML/Audio/Music.hpp"


class SoundCore
{
public: 
    using Volume_t = double;
private:
    Volume_t m_musicVolume;
    Volume_t m_effectVolume;
public:
    SoundCore(/* args */);
    ~SoundCore();


};

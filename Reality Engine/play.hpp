#ifndef play_hpp
#define play_hpp

class Player {
public:
    int tick;
    int maxTicks;
    bool paused;
    
    Player();
    void update();
    double getProgress();
};

#endif /* play_hpp */

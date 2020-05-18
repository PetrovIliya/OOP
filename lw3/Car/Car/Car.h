#pragma once
#include <map>
#include <utility>

class CCar
{
public:

    enum class Direction
    {
        Ahead,
        Back,
        None
    };

    CCar();
    ~CCar();

    bool IsEngineOn() const;
    int GetSpeed() const;
    int GetGear() const;
    Direction GetDirection() const;

    bool TurnOnEngine();
    bool TurnOffEngine();

    bool SetGear(int gear);
    bool SetSpeed(int speed);
private:

    Direction m_direction;
    bool m_isEngineOn;
    int m_speed;
    int m_gear;
    
    std::pair <int, int> GetSpeedRange(const int gear) const;
    bool IsEngineStartable() const;
    bool IsEngineStopable() const;
    bool IsSpeedChangeble(const int speed) const;
    void UpdateDirection();
    bool IsSpeedInRange(std::pair<int, int> const& range, int const speed)const;
    bool IsGearChangeble(const int gear)const;
};
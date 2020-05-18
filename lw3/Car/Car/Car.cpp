#include <map>
#include <stdio.h>
#include <tchar.h>
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <iterator>
#include "Car.h"


using namespace std;

// public

CCar::CCar()
    : m_isEngineOn(false)
    , m_gear(0)
    , m_speed(0)
    , m_direction(Direction::None)
{
}


CCar::~CCar()
{
}

bool CCar::IsEngineOn() const
{
    return m_isEngineOn;
}

int CCar::GetGear() const
{
    return m_gear;
}

int CCar::GetSpeed() const
{
    return m_speed;
}

CCar::Direction  CCar::GetDirection() const
{
    return m_direction;
}

bool CCar::TurnOnEngine()
{
    if (!IsEngineStartable())
    {
        return false;
    }

    m_isEngineOn = true;
    return true;
}

bool CCar::TurnOffEngine()
{
    if (!IsEngineStopable())
    {
        return false;
    }

    m_isEngineOn = false;
    return true;
}

bool CCar::SetGear(int gear)
{
    if (IsGearChangeble(gear))
    {
        m_gear = gear;
        return true;
    }
    return false;
}

bool CCar::SetSpeed(int speed)
{
    if (IsSpeedChangeble(speed))
    {
        m_speed = speed;
        UpdateDirection();
        return true;
    }

    return false;
}

//private

bool CCar::IsEngineStartable()const
{
    return (!m_isEngineOn) && (m_speed == 0) && (m_gear == 0);
}

bool CCar::IsEngineStopable()const
{
    return m_isEngineOn && (m_speed == 0) && (m_gear == 0);
}

bool CCar::IsSpeedChangeble(const int speed)const
{
    return (m_gear == 0 && speed < m_speed) || (m_gear != 0 && IsSpeedInRange(GetSpeedRange(m_gear), speed));
}

bool CCar::IsGearChangeble(const int gear)const
{
    bool IsGearCorrect = (gear >= -1 && gear <= 5);

    bool IsSpeedInNewGearRange = IsSpeedInRange(GetSpeedRange(gear), m_speed);

    bool IsDirectionCorrect = (gear == 0) || (m_direction == Direction::None) ||
        (gear > 0 && m_direction == Direction::Ahead) ||
        (gear < 0 && m_direction == Direction::Back);

    return IsGearCorrect && IsSpeedInNewGearRange && IsDirectionCorrect;
}

pair<int, int> CCar::GetSpeedRange(const int gear)const
{
    switch (gear)
    {
        case -1:
            return { 0, 20 };
        case 0:
            return { 0, 150 };
        case 1:
            return { 0, 30 };
        case 2:
            return { 20, 50 };
        case 3:
            return { 30, 60 };
        case 4:
            return { 40, 90 };
        case 5:
            return { 50, 150 };
        default:
            return { 0, 0 };
    }
}

bool CCar::IsSpeedInRange(pair<int, int> const& range, int const speed)const
{
    return (range.first <= speed) && (speed <= range.second);
}

void CCar::UpdateDirection()
{
    if (m_speed == 0)
    {
        m_direction = Direction::None;
    }
    else if (m_gear < 0)
    {
        m_direction = Direction::Back;
    }
    else if (m_gear > 0)
    {
        m_direction = Direction::Ahead;
    }
}
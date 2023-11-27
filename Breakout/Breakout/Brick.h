#pragma once
// TODO [lpavic]: see to improve implementation

#include "GameElement.h"
#include "tinyxml2.h"

#include <iostream>

class Brick : public GameElement
{
private:
	std::string hitPoints{""};
	// TODO [lpavic]: this variable is unused (load unique sound file (.wav file) (instead of making path inside program))
	std::string hitSound{""};
	// TODO [lpavic]: this variable is unused (load unique sound file (.wav file) (instead of making path inside program))
	std::string breakSound{""};
	unsigned int breakScore{0};
	// this variable is determining which brick is going to be drawn on screen - "_" bricks and brics with hit points = 0 are not alive
	bool is_alive{false};

public:
	Brick() = default;
	Brick(const tinyxml2::XMLElement& Brick);
	Brick(const Brick&) = default;
	Brick(Brick&&) = default;
	Brick& operator =(const Brick&) = default;
	Brick& operator =(Brick&& temp);
	~Brick() = default;

	const unsigned& getBreakScore() const;
	const std::string& getBreakSound() const;
	const std::string& getHitPoints() const;
	const std::string& getHitSound() const;
	const bool& getIsAlive() const;

	void setHitPoints(const std::string hitPoints);
	void setIsAlive(const bool is_alive);
};

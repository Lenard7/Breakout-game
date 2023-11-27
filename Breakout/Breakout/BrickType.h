#pragma once

#include "tinyxml2.h"

#include <iostream>

class BrickType
{
private:
	std::string ID;
	// TODO [lpavic]: this variable is unused (load unique image (.dds file) (instead of making path inside program))
	std::string texture;
	std::string hit_points;
	// TODO [lpavic]: this variable is unused (load unique sound file (.wav file) (instead of making path inside program))
	std::string hit_sound;
	// TODO [lpavic]: this variable is unused (load unique sound file (.wav file) (instead of making path inside program))
	std::string break_sound;
	unsigned int break_score;

public:
	BrickType();
	BrickType(const tinyxml2::XMLElement& brickType);
	BrickType(const BrickType&) = default;
	BrickType(BrickType&&) = default;
	BrickType& operator =(const BrickType&) = default;
	BrickType& operator =(BrickType&& temp);
	~BrickType() = default;

	const std::string& getTexture() const;
	const std::string& getHitPoints() const;
	const std::string& getHitSound() const;
	const std::string& getBreakSound() const;
	const unsigned& getBreakScore() const;
	const std::string& getID() const;
	void setID(const std::string ID);
	void setHitPoints(const std::string hit_points);
};
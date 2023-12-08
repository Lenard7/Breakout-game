#pragma once

#include "GameElement.h"
#include "tinyxml2.h"

#include <iostream>


class Brick : public GameElement
{
private:
	unsigned break_score{0};
	// TODO [lpavic]: this variable is unused (load unique sound file (.wav file) (instead of making path inside program))
	std::string break_sound{""};
	std::string hit_points{""};
	// TODO [lpavic]: this variable is unused (load unique sound file (.wav file) (instead of making path inside program))
	std::string hit_sound{""};
	// this variable is determining which brick is going to be drawn on screen - "_" bricks and brics with hit points = 0 are not alive
	bool is_alive{false};

public:
	Brick(const tinyxml2::XMLElement& Brick);
	Brick() = default;
	Brick(const Brick&) = default;
	Brick(Brick&&) = default;
	Brick& operator =(const Brick&) = default;
	Brick& operator =(Brick&& temp) = default;
	~Brick() = default;

	inline const unsigned& getBreakScore() const { return this->break_score; }
	inline const std::string& getBreakSound() const { return this->break_sound; }
	inline const std::string& getHitPoints() const { return this->hit_points; }
	inline const std::string& getHitSound() const { return this->hit_sound; }
	inline const bool getIsAlive() const { return this->is_alive; }

	inline void setBreakScore(const unsigned& hit_points) { this->break_score = break_score; }
	inline void setBreakSound(const std::string& hit_points) { this->break_sound = break_sound; }
	inline void setHitPoints(const std::string& hit_points) { this->hit_points = hit_points; }
	inline void setHitSound(const std::string& hit_points) { this->hit_sound = hit_sound; }
	inline void setIsAlive(const bool is_alive) { this->is_alive = is_alive; }
};

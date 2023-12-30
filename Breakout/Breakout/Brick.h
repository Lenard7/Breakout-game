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
	explicit Brick(const tinyxml2::XMLElement& Brick);
	Brick() noexcept = default;
	Brick(const Brick& brick) noexcept = default;
	Brick(Brick&& brick) noexcept = default;
	Brick& operator =(const Brick& brick) noexcept = default;
	Brick& operator =(Brick&& brick) noexcept = default;
	~Brick() noexcept = default;

	inline const unsigned& getBreakScore() const noexcept { return this->break_score; }
	inline const std::string& getBreakSound() const noexcept { return this->break_sound; }
	inline const std::string& getHitPoints() const noexcept { return this->hit_points; }
	inline const std::string& getHitSound() const noexcept { return this->hit_sound; }
	inline const bool getIsAlive() const noexcept { return this->is_alive; }

	inline void setBreakScore(const unsigned& hit_points) noexcept { this->break_score = break_score; }
	inline void setBreakSound(const std::string& hit_points) noexcept { this->break_sound = break_sound; }
	inline void setHitPoints(const std::string& hit_points) noexcept { this->hit_points = hit_points; }
	inline void setHitSound(const std::string& hit_points) noexcept { this->hit_sound = hit_sound; }
	inline void setIsAlive(const bool is_alive) noexcept { this->is_alive = is_alive; }
};

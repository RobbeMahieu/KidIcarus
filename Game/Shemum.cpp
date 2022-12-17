#include "pch.h"
#include "Shemum.h"
#include "Vector2f.h"


Shemum::Shemum(float screenWidth, Texture* texture)
	: Enemy(Rectf{0,0,10,16}, screenWidth, texture, 2,4)
	, m_Speed{ 50.0f }
{
	m_Velocity = Vector2f{m_Speed,0};
}

void Shemum::Update(float elapsedSec, const Level& level) {
	if (m_State == EnemyState::alive) {
		if (IsOnGround(level)) {
			MoveHorizontal(elapsedSec, level);
			WrapX();

			if (IsAtWall(level)) {
				m_Velocity.x *= -1;
				m_Sprite.ToggleFlip();
			}
		}
		else {
			m_Velocity.y -= m_Gravity * elapsedSec;
			MoveVertical(elapsedSec, level);

		}
	}
	m_Sprite.Update(elapsedSec);
}

bool Shemum::IsAtWall(const Level& level) {

	const float delta{ (m_Velocity.x < 0) ? -1.0f : 1.0f };
	
	Translate(delta, 0);
	const bool isAtWall{ level.Collides(*this) };
	Translate(-delta, 0);
	return isAtWall;
}
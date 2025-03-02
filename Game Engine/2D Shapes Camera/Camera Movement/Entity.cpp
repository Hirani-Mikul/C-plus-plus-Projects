#include "Entity.h"

Entity::Entity(std::vector<olc::vf2d> vecModel, const olc::vf2d& pos, olc::Pixel col = olc::YELLOW) : vecModel(std::move(vecModel)), pos(pos), fScale(1.0f), col(col) {}

const olc::vf2d& Entity::GetPos() const
{
    return pos;
}

void Entity::SetPos(olc::vf2d& newPos)
{
    pos = newPos;
}

void Entity::TranslateBy(const olc::vf2d& offset)
{
    pos += offset;
}

void Entity::SetScale(float s)
{
    fScale = s;
}

float Entity::GetScale() const
{
    return fScale;
}

Drawable Entity::GetDrawable() const
{
    Drawable d(vecModel, col);
    d.Scale(fScale);
    d.Translate(pos);

    return d;
}

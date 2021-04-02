#include "Effect.h"

Effect::Effect(int m, EntityObject* e) : m_maxFame(m), m_frame(0), m_pEffectedEntity(e), m_hasEffectEnd(false) {}

Effect::~Effect() = default;

void Effect::Update()
{
	m_frame++;
	if(m_frame <= m_maxFame && m_pEffectedEntity != nullptr)
	{
		Execute();
	}
	else
	{
		m_hasEffectEnd = true;
	}
}

Type Effect::GetType() const
{
	return m_type;
}

void Effect::SetType(Type t)
{
	m_type = t;
}

void Effect::Execute() {};

bool Effect::HasEffectEnd() const{ return m_hasEffectEnd; }

void Effect::SetEffectedEntity(EntityObject* e){ m_pEffectedEntity = e; }

Stun::Stun(int m, EntityObject* e) : Effect(m,e)
{
	SetType(Type::STUN);
}

void Stun::Execute()
{
	m_pEffectedEntity->SetAccelX(0);
	m_pEffectedEntity->SetAccelY(0);
}

Freeze::Freeze(int m, EntityObject* e) : Effect(m, e)
{
	SetType(Type::FREEZE);
}

void Freeze::Execute()
{
	m_pEffectedEntity->Stop();
}

Bleed::Bleed(int m, EntityObject* e) : Effect(m, e)
{
	SetType(Type::BLEED);
	m_bleedCounter = 0;
}

void Bleed::Execute()
{
	m_bleedCounter++;
	if(m_bleedCounter >= 60)
	{
		m_bleedCounter = 0;
		m_pEffectedEntity->SetHeath(m_pEffectedEntity->GetHeath()-1);
	}
}


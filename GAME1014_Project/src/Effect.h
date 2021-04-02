#pragma once
#ifndef __Effect__
#define __Effect__
#include "EntityObject.h"

enum class Type { NONE ,STUN, BLEED, FREEZE };

class Effect
{
public:
	Effect(int m, EntityObject* e = nullptr);
	virtual ~Effect();
	virtual void Execute();
	bool HasEffectEnd() const;
	void SetEffectedEntity(EntityObject* e);
	void Update();
	Type GetType() const;

protected:
	void SetType(Type t);
	
	EntityObject* m_pEffectedEntity;
	bool m_hasEffectEnd;
	int m_frame;
	int m_maxFame;
	Type m_type;
	friend EntityObject;
};

class Stun final : public Effect
{
public:
	Stun(int m, EntityObject* e = nullptr);
	void Execute();
};

class Freeze final : public Effect
{
public:
	Freeze(int m, EntityObject* e = nullptr);
	void Execute();
};

class Bleed final : public Effect
{
public:
	Bleed(int m, EntityObject* e = nullptr);
	void Execute();
private:
	int m_bleedCounter;
};


#endif

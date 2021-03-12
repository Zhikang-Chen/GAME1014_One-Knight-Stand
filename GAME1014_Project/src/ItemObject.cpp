#include "ItemObject.h"

void ItemObject::Update()
{
	if(m_Activate && m_enable)
	{
		m_Activate = false;
		m_enable = false;
		DoesStuff();
	}
}

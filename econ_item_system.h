#ifndef ECON_ITEM_SYSTEM_H
#define ECON_ITEM_SYSTEM_H

#ifdef _WIN32
#pragma once
#endif

#include "econ_item_schema.h"

//struct baseitemcriteria_t;

class CEconItemSytem
{
public:
	void Init();
	void ParseItemSchemaFile( const char* file );
	void PostInit() {};
	void ReloadWhitelist() {};
	void ResetAttribStringCache() {};
	void GenerateRandomItem() {};
//	virtual void GenerateBaseItem( baseitemcriteria_t ) {};

	inline CEconItemSchema* GetItemSchema()	{ return m_pItemSchema; }
private:
	CEconItemSchema* m_pItemSchema;

	friend extern CEconItemSytem* ItemSystem();
	bool m_bParsed = false;
};

extern CEconItemSytem* ItemSystem();
extern CEconItemSchema* GetItemSchema();
#endif // ECON_ITEM_SYSTEM_H
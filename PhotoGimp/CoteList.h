#pragma once
#include "CoteActif.h"

struct CoteList {
private:
	CoteActif* head_cote; //Premier côté de la liste
	CoteActif* tail_cote; //Dernier côté de la liste
	int nb_cote; //Nombre de côtés de la liste

public:
	CoteList();
	CoteList(const CoteList& list);
	CoteList(CoteActif& const cote);
	~CoteList();

	void AddBeginList(CoteActif& const cote);
	void AddEndList(CoteActif& const cote);
	void AddAtPosition(CoteActif& const cote, int pos);

	void RemoveFirst();
	void RemoveLast();
	void RemoveAtPosition(int pos);
	void ClearList();

	CoteActif* GetFirst() const { return head_cote; };
	CoteActif* GetLast() const { return tail_cote; };
	CoteActif* GetAtPosition(int pos) const;
	int GetSize() const { return nb_cote; };
	bool isEmpty() const;

	CoteList operator=(CoteList& list);
};

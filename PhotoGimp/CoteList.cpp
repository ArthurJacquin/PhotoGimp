#include "CoteList.h"
#include <iostream>

CoteList::CoteList() 
{
	head_cote = tail_cote = nullptr;
	nb_cote = 0;
}

CoteList::CoteList(const CoteList& list)
{
	head_cote = tail_cote = nullptr;
	nb_cote = 0;

	CoteActif* reader = list.head_cote;
	while (reader != nullptr) 
	{
		AddEndList(*reader);
		reader = reader->GetNextCote();
	}
}

CoteList::CoteList(CoteActif& const cote)
{
	head_cote = tail_cote = &cote;
	nb_cote = 1;
}

CoteList::~CoteList()
{

}

void CoteList::AddBeginList(CoteActif& const cote)
{
	CoteActif* new_cote = &cote;
	if (new_cote == nullptr)
	{
		std::cout << u8"[SetBeginList] Le côté passé en paramètre est nul" << std::endl;
		return;
	}

	if (head_cote == nullptr)
	{
		new_cote->SetNextCote(*new_cote);
		tail_cote = head_cote = new_cote;
	}
	else 
	{
		new_cote->SetNextCote(*head_cote);
		head_cote = new_cote;
		tail_cote->SetNextCote(*head_cote);
	}
	++nb_cote;
}

void CoteList::AddEndList(CoteActif& const cote)
{
	CoteActif* new_cote = &cote;
	if (new_cote == nullptr)
	{
		std::cout << u8"[SetEndList] Le côté passé en paramètre est nul" << std::endl;
		return;
	}

	tail_cote->SetNextCote(*new_cote);
	tail_cote = new_cote;
	if (nb_cote == 0)
		tail_cote = head_cote;
	++nb_cote;
}

void CoteList::AddAtPosition(CoteActif& const cote, int pos)
{
	if (pos <= 0) 
	{
		AddBeginList(cote);
		std::cout << u8"[AddAtPosition] La position est inférieure ou égale à 0. Ajout en début de liste" << std::endl;
		return;
	}
	else if (pos >= nb_cote) 
	{
		AddEndList(cote);
		std::cout << u8"[AddAtPosition] La position est supérieure au noombre de côtés. Ajout en fin de liste" << std::endl;
		return;
	}

	CoteActif* new_cote = &cote;
	CoteActif* previous_cote = head_cote;

	if(new_cote == nullptr) 
	{
		std::cout << u8"[AddAtPosition] Le côté passé en paramètre est nul." << std::endl;
		return;
	}

	for (int i = 0; i < pos; ++i) 
	{
		previous_cote = previous_cote->GetNextCote();
	}

	new_cote->SetNextCote(*previous_cote->GetNextCote());
	previous_cote->SetNextCote(*new_cote);
	++nb_cote;
}

void CoteList::RemoveFirst()
{
	if(nb_cote <= 0) 
	{
		std::cout << u8"[RemoveFirst] La liste est vide" << std::endl;
		return;
	}

	CoteActif* to_remove = head_cote;
	head_cote = head_cote->GetNextCote();
	delete to_remove;
	--nb_cote;
	if (nb_cote == 0)
		tail_cote = nullptr;
}

void CoteList::RemoveLast()
{
	if (nb_cote <= 0)
	{
		std::cout << u8"[RemoveLast] La liste est vide" << std::endl;
		return;
	}

	if (nb_cote == 1)
	{
		delete head_cote;
		tail_cote = head_cote = nullptr;
	}
	else
	{
		CoteActif* before_last = head_cote;
		for (int i = 0; i < nb_cote - 1; ++i)
		{
			before_last = before_last->GetNextCote();
		}

		delete before_last->GetNextCote();
		before_last->SetNextCote(*head_cote);
		tail_cote = before_last;
	}

	--nb_cote;
}

void CoteList::RemoveAtPosition(int pos)
{
	if (pos >= 0 && pos < nb_cote) 
	{
		if (pos == 0)
			RemoveFirst();
		else
		{
			CoteActif* previous_cote = head_cote;
			for (int i = 0; i < pos - 1; ++i)
			{
				previous_cote = previous_cote->GetNextCote();
			}

			CoteActif* to_remove = previous_cote->GetNextCote();
			previous_cote->SetNextCote(*to_remove->GetNextCote());
			delete to_remove;
			--nb_cote;
		}
	}
}

void CoteList::ClearList()
{
	while (nb_cote > 0)
		RemoveFirst();
}

CoteActif* CoteList::GetAtPosition(int pos) const
{
	if (pos < 0 && pos >= nb_cote)
		return nullptr;

	CoteActif* target = head_cote;
	for (int i = 0; i < pos; ++i)
	{
		target = target->GetNextCote();
	}

	CoteActif* value = target;
}

bool CoteList::isEmpty() const
{
	return nb_cote > 0;
}

CoteList CoteList::operator=(CoteList& list)
{
	if (this != &list)
	{
		ClearList();

		CoteActif* reader = list.head_cote;
		while (reader != nullptr)
		{
			AddEndList(*reader);
			reader = reader->GetNextCote();
		}
	}

	return *this;
}

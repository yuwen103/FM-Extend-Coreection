//FMExtendNode.cpp
#include "FMExtendNode.h"
#include "BWTAlgorithms.h"

FMExtendNode::FMExtendNode(const std::string* pQuery, FMExtendNode* parent) : m_pQuery(pQuery),m_pParent(parent)
{
}
// Destructor, recurisvely delete the children of the node
FMExtendNode::~FMExtendNode()
{
    // Delete children
    for(FMExtendNodePtrList::iterator iter = m_children.begin(); iter != m_children.end(); ++iter)
        delete *iter;
}


FMExtendNode* FMExtendNode::createChild(const std::string& lable,int direction)
{
		
	FMExtendNode* pAdded = new FMExtendNode(m_pQuery, this);
	m_children.push_back(pAdded);
	pAdded->extendToNewNode(lable,direction,left_label,right_label);
	return pAdded;
}
		
//Extend the label of this node by 1 bp , direction left:0 right:1
void FMExtendNode::extend(const std::string& extend_bp,int direction)
{
	if(direction==0)
		left_label.append(extend_bp);
	else if(direction==1)
		right_label.append(extend_bp);
}

void FMExtendNode::extendToNewNode(const std::string& extend_bp,int direction,std::string left,std::string right)
{
	if(direction==0)
	{
		left_label=left+extend_bp;
		right_label=right;
	}
	else if(direction==1)
	{
		left_label=left;
		right_label=right+extend_bp;
	}
	
}

//Set the initial kmer by two direction extension
void FMExtendNode::SetInitial(const std::string& InitailKmer)
{
	left_label=reverse(InitailKmer);
	right_label="";
}
//Get the result of two direction extension
std::string FMExtendNode::getLeftExtend()
{return left_label;}
std::string FMExtendNode::getRightExtend()
{return right_label;}

FMExOverlapNode* FMExOverlapNode::createChild(const std::string& label,int direction)
{
	FMExOverlapNode* PAdded = new FMExOverlapNode(m_pQuery,this);
	PAdded->extendToNewNode(label,direction,this->left_label,this->right_label);
	
	PAdded->lastSeedIdx=this->lastSeedIdx;//the newest match kmer index
	PAdded->nextSeddIdx=this->nextSeddIdx;//the next check kmer index on the QueryKmerArray;
	PAdded->numOfMatchSeeds=this->numOfMatchSeeds;
		
		//not necessary temporarily
		//int Left_start_idx;
		//int Right_end_idx;
		
	PAdded->initSeedIdx=this->initSeedIdx;//the initialSeed(kmer) idx on the Query
	PAdded->tempMismathCount=this->tempMismathCount;
	PAdded->insertion_count=this->insertion_count;
	PAdded->deletion_count=this->deletion_count;
	PAdded->mismatch_count=this->mismatch_count;
		
	PAdded->mismatch_vector=this->mismatch_vector;
	PAdded->deletion_vector=this->deletion_vector;
	PAdded->Insertion_vector=this->Insertion_vector;
	
	m_children.push_back(PAdded);
	
	return PAdded;
}







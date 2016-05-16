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
	if(direction==0)
		left_label+=lable;
	else if(direction==1)
		right_label+=lable;
		
	FMExtendNode* pAdded = new FMExtendNode(m_pQuery, this);
	return pAdded;
}
		
//Extend the label of this node by 1 bp
void FMExtendNode::extend(const std::string& extend_bp,int direction)
{
	if(direction==0)
		left_label+=extend_bp;
	else if(direction==1)
		right_label+=extend_bp;
}
//Set the initial kmer by two direction extension
void FMExtendNode::SetInitial(const std::string& InitailKmer)
{
	left_label=InitailKmer;
	right_label="";
}
//Get the result of two direction extension
std::string FMExtendNode::getLeftExtend()
{return left_label;}
std::string FMExtendNode::getRightExtend()
{return right_label;}
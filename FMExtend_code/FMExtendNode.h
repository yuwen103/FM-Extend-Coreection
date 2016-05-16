//FMExtendNode.h

#ifndef FMEXTENDNODE_H
#define FMEXTENDNODE_H

#include <list>
#include "BWT.h"
#include "BWTAlgorithms.h"

class FMExtendNode;
typedef std::list<FMExtendNode*> FMExtendNodePtrList;
//indel is pair<align_kmer_match_index,the size of error>
typedef std::pair <int,int> indel;
typedef std::vector<indel> indel_vct;

// Base class represent search nodes for all sorts of applications using FM-index walk
class FMExtendNode
{
    public:

        //
        // Functions
        //
        FMExtendNode(const std::string* pQuery, FMExtendNode* parent);
        ~FMExtendNode();
		//Add a child node to this node when extend 2 more possibility with the given label
		//return a pointer to the create node
		FMExtendNode* createChild(const std::string& lable,int direction);
		
		//Extend the label of this node by 1 bp
		void extend(const std::string& extend_bp,int direction);
		//Set the initial kmer by two direction extension
		void SetInitial(const std::string& InitailKmer);
		//Get the result of two direction extension
		std::string getLeftExtend();
		std::string getRightExtend();
		//change the curr_extend_str when find Indel(small insertion/deletion)
		//adjust_byInsertion
		//adjust_byDeletion
    private:
		//Data
		
		// Left/Right lable is the extend string not include initial seed(kmer) 
		std::string left_label;
		std::string right_label;
        
	protected:
		//Data
		//In my method m_pQuery may be not necessary
		const std::string* m_pQuery;
		FMExtendNode* m_pParent;
		FMExtendNodePtrList m_children;
       
};


//
// TDexOverlapNode for implementation of overlap computation using FM-index walk
//
class FMExOverlapNode : public FMExtendNode
{
    public:
		//Functions
		FMExOverlapNode(const std::string* pQuery,FMExOverlapNode* parent):FMExtendNode(pQuery,parent)
		{
		}
		~FMExOverlapNode(){};
		FMExOverlapNode* createChild(const std::string& label,int direction);
		
		//Data
		BWTIntervalPair currIntervalPair;//two direction extend need the Interval pair
		size_t lastSeedIdx;//the newest match kmer index
		size_t nextSeddIdx;//the next check kmer index on the QueryKmerArray;
		size_t numOfMatchSeeds;
		
		//not necessary temporarily
		//int Left_start_idx;
		//int Right_end_idx;
		
		int initSeedIdx;//the initialSeed(kmer) idx on the Query
		int tempMismathCount;
		int insertion_count;
		int deletion_count;
		int mismatch_count;
		
		indel_vct mismatch_vector;
		indel_vct deletion_vector;
		//std::vector<Insertion> Insertion_vct; 
		
		
};

// leaves of TDexOverlapNode
typedef std::list<FMExOverlapNode*> FMEONodePtrList;

#endif

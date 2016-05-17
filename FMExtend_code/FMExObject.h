#ifndef FMEXOBJECT_H
#define FMEXOBJECT_H

class Insertion
{
	public:
		//pre-kmer position on the Query
		int match_idx;
		int insert_size;
		std::string preKmer;
		std::string insertion_str;
};

#endif
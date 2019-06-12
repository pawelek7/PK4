#ifndef NoCopyNoMove_hpp
#define NoCopyNoMove_hpp

/*
A class that delete "copy" and "move" methods.

@author
Pawel Salicki
*/

class NoCopyNoMove
{
public:
	NoCopyNoMove() = default;
	virtual ~NoCopyNoMove() = default;

	//no copyable
	NoCopyNoMove(const NoCopyNoMove &) = delete;
	NoCopyNoMove& operator=(const NoCopyNoMove &) = delete;

	//no movable
	NoCopyNoMove(NoCopyNoMove &&) = delete;
	NoCopyNoMove & operator=(NoCopyNoMove &&) = delete;
};

#endif // !NoCopyNoMove_hpp

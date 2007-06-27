// -*- mode: c++; c-indent-level: 4; c++-member-init-indent: 8; comment-column: 35; -*-

// "moSimpleMoveTabuList.h"

// (c) OPAC Team, LIFL, 2003-2007

/* LICENCE TEXT 
   
   Contact: paradiseo-help@lists.gforge.inria.fr
*/

#ifndef __moSimpleMoveTabuList_h
#define __moSimpleMoveTabuList_h

#include <list>
#include <iterator>

#include "moTabuList.h"

//! Class describing a move tabu list with a limited memory.
template <class M>
class moSimpleMoveTabuList: public moTabuList < M >
{
  
public:
  
  //! Alias for the type
  typedef typename M::EOType EOT;

  //! Constructor
  /*
    \param __size The maximum size of the move tabu list.
   */
  moSimpleMoveTabuList(unsigned int __size): maxSize(__size)
  {
    currentSize=0;
  }

  //! Function that indicates if, in a given state, the _move is tabu or not.
  /*!
    \param __move A given moMove.
    \param __sol A solution.
    \return true or false.
  */
  bool
  operator () (const M & __move, const EOT & __sol) 
  {
    typename std::list<M>::iterator it;
    
    it=tabuList.begin();
    while(it!=tabuList.end()&&(!((*it)==__move)))
      {
	it++;
      }
    
    return it!=tabuList.end();
  }
  
  void
  add (const M & __move, const EOT & __sol)
  {
    if(currentSize!=0)
      {
	// Useful in the case of a move has been kept thanks to the moAspirCrit.
	// In this case, the move can already be in the tabuList.
	removeMove(__move);
      }

    tabuList.push_back(__move);
    
    if(currentSize==maxSize)
      {
	tabuList.erase(tabuList.begin());
      }
    else
      {
	currentSize++;
      }
  }
  
  void
  update ()
  {
    //nothing to do
  }

  void
  init ()
  {
    //nothing to do
  }

private:
  
  //! Procedure that removes a given move from the tabu list (if it is into, else do nothing).
  /*!
    \param __move A given moMove.
  */
  void
  removeMove(const M & __move)
  {
    typename std::list<M>::iterator it;
    
    it=tabuList.begin();
    while(it!=tabuList.end()&&(!((*it)==__move)))
      {
	it++;
      }

    if(it!=tabuList.end())
      {
	tabuList.erase(it);
      }
  }

  //! The maximum size of the tabu list.
  unsigned int maxSize;

  //! The current size of the tabu list.
  unsigned int currentSize;
  
  //! The move tabu list.
  std::list<M> tabuList;
};

#endif

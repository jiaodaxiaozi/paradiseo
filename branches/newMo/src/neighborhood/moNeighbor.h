/*
  <moNeighbor.h>
  Copyright (C) DOLPHIN Project-Team, INRIA Lille - Nord Europe, 2006-2010

  Sébastien Verel, Arnaud Liefooghe, Jérémie Humeau

  This software is governed by the CeCILL license under French law and
  abiding by the rules of distribution of free software.  You can  use,
  modify and/ or redistribute the software under the terms of the CeCILL
  license as circulated by CEA, CNRS and INRIA at the following URL
  "http://www.cecill.info".

  As a counterpart to the access to the source code and  rights to copy,
  modify and redistribute granted by the license, users are provided only
  with a limited warranty  and the software's author,  the holder of the
  economic rights,  and the successive licensors  have only  limited liability.

  In this respect, the user's attention is drawn to the risks associated
  with loading,  using,  modifying and/or developing or reproducing the
  software by the user in light of its specific status of free software,
  that may mean  that it is complicated to manipulate,  and  that  also
  therefore means  that it is reserved for developers  and  experienced
  professionals having in-depth computer knowledge. Users are therefore
  encouraged to load and test the software's suitability as regards their
  requirements in conditions enabling the security of their systems and/or
  data to be ensured and,  more generally, to use and operate it in the
  same conditions as regards security.
  The fact that you are presently reading this means that you have had
  knowledge of the CeCILL license and that you accept its terms.

  ParadisEO WebSite : http://paradiseo.gforge.inria.fr
  Contact: paradiseo-help@lists.gforge.inria.fr
*/

#ifndef _moNeighbor_h
#define _moNeighbor_h

//EO inclusion
#include <EO.h>
#include <eoObject.h>
#include <eoPersistent.h>

/**
 * Container of the neighbor informations
 */
template< class EOT , class Fitness >
class moNeighbor : public eoObject, public eoPersistent
{
public:

    /**
     * Default Constructor
     */
    moNeighbor(){}

    /**
     * Copy Constructor
     * @param _neighbor to copy
     */
    moNeighbor(const moNeighbor<EOT, Fitness>& _neighbor) {
    	repFitness = _neighbor.fitness();
    }
 
    /**
     * Assignment operator
     * @param _neighbor the neighbor to assign
     * @return a neighbor equal to the other
     */
    virtual moNeighbor<EOT, Fitness>& operator=(const moNeighbor<EOT, Fitness>& _neighbor) {
    	repFitness = _neighbor.fitness();
    	return (*this);
    }
 
    /**
     * Move a solution
     * @param _solution the related solution
     */
    virtual void move(EOT & _solution) = 0 ;

    /**
     * Get the fitness of the neighbor
     * @return fitness of the neighbor
     */
    const Fitness& fitness() const {
    	return repFitness;
    }
    

    /**
     * Get fitness as reference, useful when fitness is set in a multi-stage way, e.g., MOFitness gets performance information, is subsequently ranked
     * @return fitness as reference of the neighbor
     */
    Fitness& fitnessReference() {
    	return repFitness;
    }

    /**
     * Set fitness. At the same time, validates it.
     * @param _fitness new fitness value.
     */
    void fitness(const Fitness& _fitness){
	    repFitness = _fitness;
	}
    
    /**
     * Return the class id.
     * @return the class name as a std::string
     */
    virtual std::string className() const { return "moNeighbor"; }
    
    /**
     * Read object.
     * Calls base class, just in case that one had something to do.
     * The read and print methods should be compatible and have the same format.
     * In principle, format is "plain": they just print a number
     * @param _is a std::istream.
     */
    virtual void readFrom(std::istream& _is) {
		_is >> repFitness;
    }

    /**
     * Write object. Called printOn since it prints the object _on_ a stream.
     * @param _os A std::ostream.
     */
    virtual void printOn(std::ostream& _os) const {
		_os << repFitness << ' ' ;
    }
    
protected:
    // minimal information on the neighbor : fitness
    Fitness repFitness ;

};

#endif

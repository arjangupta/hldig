//
// HtVectorGeneric.h
//
// HtVector: A Vector class which holds objects of type GType.
//           (A vector is an array that can expand as necessary)
//           This class is very similar in interface to the List class
//
// Part of the ht://Dig package   <http://www.htdig.org/>
// Copyright (c) 1999 The ht://Dig Group
// For copyright details, see the file COPYING in your distribution
// or the GNU Public License version 2 or later 
// <http://www.gnu.org/copyleft/gpl.html>
//
// $Id: HtVectorGeneric.h,v 1.1.2.1 1999/12/09 10:50:01 bosc Exp $
//
//
//  #ifndef	_HtVectorGeneric_h_
//#define	_HtVectorGeneric_h_


// HOWTO use:
// let's say you have a class called Zozo (that has to have an 
// empty constructor Zozo::Zozo() )
// You want to use vectors of Zozo's (called HtVector_Zozo )
//
// In every file you use it you must include its declaration:
//
// #define GType Zozo
// #define HtVectorGType HtVector_Zozo
// #include "HtVectorGeneric.h"
//
// Then you can use it:  
// HtVector_Zozo vect;
// Zozo a,b,c;
// vect.push_back(a);
// vect.push_back(b);
// vect[0]=c;
//
// Somewhere in some .cc file you have to
//
// #define GType Zozo
// #define HtVectorGType HtVector_Zozo
// #include "HtVectorGenericCode.h"
//
//
// Notes: 
// *If you include the declaration more 
// than once in the same scope you will get
// errors (HtVector_Zozo : already declared)
// 
// *Bounds checking is on by default, this should be
// changed (it's performance critical), if your'e
// out of bounds an error is printed on cerr
// but the prg doesnt stop (maybe it should?)
//
// *vectors containing pointers DO NOT FREE
// them, this is deliberate
//

#include "Object.h"

class HtVectorGType : public Object
{
public:
    //
    // Constructor/Destructor
    //
    HtVectorGType();
    HtVectorGType(int capacity);
    ~HtVectorGType();

    //
    // Add() will append an Object to the end of the vector
    //
    void	Add(const GType &);
      

    //
    // Insert() will insert an object at the given position.  If the
    // position is larger than the number of objects in the vector, the
    // object is appended; no new objects are created between the end
    // of the vector and the given position.
    //
    void	Insert(const GType &, int position);

    // *** this is obsolete in HtVectorGeneric ** use: vector[position]=value;
//      void	Assign(GType , int position);


    //
    // Remove the object at the given position
    // (in some sense, the inverse of Insert)
    //
    void		RemoveFrom(int position);

    // Release is obsolete since no deletions of pointers contained in 
    //  the vector is done
    //      void	Release();

    //
    // Destroy() will delete all the objects in the vector.
    // Warning: no deletions of pointers contained in 
    // the vector are done (that's up to you)
    // 
    void	       Destroy();

    //
    // Vector traversal (a bit redundant since you can use [])
    //
    void	       Start_Get()		{current_index = -1;}
    GType &            Get_Next();
    GType &            Get_First();
    GType &            Last()			{return Nth(element_count-1);}

    //
    // Direct access to vector items. To assign new objects, use
    // Insert() or Add() or Assign()
    //
    GType &            Nth(int n)			{CheckBounds(n);return data[n];}
    const GType &      Nth(int n) const			{CheckBounds(n);return data[n];}
    GType &            operator[] (int n)		{return Nth(n);}
    const GType &      operator[] (int n) const		{return Nth(n);}

    //
    // Access to the number of elements
    //
    int			Count() const		{return element_count;}
    int			IsEmpty()		{return element_count==0;}

   
    //
    // Accesses wich involve finding an element (only possible if
    // we can compare two elements)
    //
#ifndef HTVECTORGENERIC_NOTCOMPARABLE
    //
    // Get the index number of an object.  If the object is not found,
    // returns -1
    //
    int			Index(const GType &);
    GType &             Next(const GType &current);
    GType &             Previous(const GType &current);

    //
    // Find the given object in the vector and remove it from the vector.
    // The object will NOT be deleted.  If the object is not found,
    // NOTOK will be returned, else OK.
    //
    void		         Remove(const GType &);
#endif

    //
    // Deep copy member function
    //
    HtVectorGType		*Copy() const;

    //
    // Vector Assignment
    //
    HtVectorGType		&operator= (HtVectorGType *vector) {return *this = *vector;}
    HtVectorGType		&operator= (const HtVectorGType &vector);


protected:    
    //
    // Many functions used to check for NULL (Object *) pointers , this is no longer possible
    // this error checking should be made optional!
    // 
    void CheckBounds(const int n) const {if(n<0 || n>=element_count){cerr << "HtVectorGType::CheckBounds: out of bounds!!" << endl;}}
    //
    // The actual internal data array
    GType              *data;

    //
    // For traversal it is nice to know where we are...
    //
    int			current_index;

    //
    // It's nice to keep track of how many things we contain...
    // as well as how many slots we've declared
    //
    int			element_count;
    int			allocated;

    //
    // Protected function to ensure capacity
    //
    void                 Allocate(int ensureCapacity);


    //
    // STL like accesors
    //
 public:
    int          	size()  const             {return Count();}
    void	        push_back(const GType &v) {Add( v);}

    GType *             begin()                   {return(data);}
    const GType *       begin() const             {return(data);}
    GType *             end()                     {return(data+element_count);}
    const GType *       end()   const             {return(data+element_count);}

    GType &             back()			  {return Nth(element_count-1);}
    const GType &       back()	const		  {return Nth(element_count-1);}
    void                pop_back()                {RemoveFrom(size()-1);}

// TODO: erase  clear resize insert(...) and many others

};

//  #endif


#ifdef  HTVECTORGENERIC_NOTCOMPARABLE
#undef  HTVECTORGENERIC_NOTCOMPARABLE
#endif
#undef HtVectorGType
#undef GType
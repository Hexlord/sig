/*=======================================================================
   Copyright (c) 2018-2019 Marcelo Kallmann.
   This software is distributed under the Apache License, Version 2.0.
   All copies must contain the full copyright notice licence.txt located
   at the base folder of the distribution. 
  =======================================================================*/

# ifndef GS_MANAGER_H
# define GS_MANAGER_H

/** \file gs_manager.h 
 * Generic way to manage classes */

# include <sig/gs_input.h>
# include <sig/gs_output.h>
# include <sig/gs_shareable.h>

/*! Generic way to allocate, write, read and compare classes */
class GsManagerBase : public GsShareable
 { protected :
	virtual ~GsManagerBase() {};

   public : // callbacks
	virtual void* alloc ()=0;
	virtual void* alloc ( const void* obj )=0;
	virtual void free ( void* obj )=0;
	virtual void output ( GsOutput& /*o*/, const void* /*obj*/ ) { }
	virtual void input ( GsInput& /*i*/, void* /*obj*/ ) { }
	virtual int compare ( const void* /*obj1*/, const void* /*obj2*/ ) { return 0; }
};

/*! Example of an implementation of a MyData class to be automatically
	managed with GsManager<MyData> :
class MyData
{  public :
	MyData ();
	MyData ( const MyData& d );
   ~MyData ();
	friend GsOutput& operator<< ( GsOutput& out, const MyData& d );
	friend GsInput& operator>> ( GsInput& inp, MyData& d );
	static int compare ( const MyData* d1, const MyData* d2 );
};*/
 
template <class X>
class GsManager : public GsManagerBase
 { protected :
	virtual ~GsManager<X> () {}

   public :
	virtual void* alloc () { return (void*) new X; }

	virtual void* alloc ( const void* obj ) { return (void*) new X(*((X*)obj)); }

	virtual void free ( void* obj ) { delete (X*) obj; }

	virtual void output ( GsOutput& o, const void* obj ) { o<<*((const X*)obj); }

	virtual void input ( GsInput& i, void* obj ) { i>>*((X*)obj); }

	virtual int compare ( const void* obj1, const void* obj2 )
	{	return X::compare ( (const X*)obj1, (const X*)obj2 ); }
};

//============================== end of file ===============================

# endif  // GS_MANAGER_H

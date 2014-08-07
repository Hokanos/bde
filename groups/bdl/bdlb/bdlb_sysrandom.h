// bdlb_sysrandom.h                                                   -*-C++-*-
#ifndef INCLUDED_BDLB_SYSRANDOM
#define INCLUDED_BDLB_SYSRANDOM

#ifndef INCLUDED_BSLS_IDENT
#include <bsls_ident.h>
#endif
BSLS_IDENT("$Id: $")

//@PURPOSE: Provide a universal interface to a system random number generator.
//
//@CLASSES:
//  bdlb::SysRandom: namespace for system specific random-number generators.
//
//@SEE_ALSO:
//
//@AUTHOR: Mickey Sweatt (msweatt1)
//
//@DESCRIPTION: This component provides a namespace, 'bdlb::SysRandom', for a
// suite of functions used to generate random numbers from platform dependent
// random number generators.  Two variants are provided one which blocks, but
// which potentially sample from a stronger distribution.  The strength of
// these random numbers and the performance of these calls is strongly
// dependent on the underlying system.
//
///Usage
///-----
// This section illustrates intended use of this component
//..
//  template <class CHOICE_TYPE>
//  class RandomChoice {
//    // This class manages selecting pseudo-random elements out of an array
//    // sampling with replacement.
//
//    // DATA
//      CHOICE_TYPE *d_choices;  // the possibilities (used not owned)
//      int          d_size;     // the number of elements to choose amongst
//
//    public:
//      // CREATORS
//      RandomChoice(CHOICE_TYPE choices[], int numChoices);
//          // Create an object to return a random one of the first specified
//          // 'numChoices' elements of the specified 'choices' array.
//
//      ~RandomChoice();
//          // Delete this object
//
//      // ACCESSOR
//      const CHOICE_TYPE& choice() const;
//          // Return a random member of the 'choices', sampling with
//          // replacement.
//  };
//
//  // CREATORS
//  template <class CHOICE_TYPE>
//  RandomChoice<CHOICE_TYPE>::RandomChoice(CHOICE_TYPE choices[],
//                                          int         numChoices)
//  : d_choices(choices), d_size(numChoices)
//  {
//  }
//
//  template <class CHOICE_TYPE>
//  RandomChoice<CHOICE_TYPE>::~RandomChoice()
//  {
//  }
//
//  // ACCESSORS
//  template <class CHOICE_TYPE>
//  const CHOICE_TYPE& RandomChoice<CHOICE_TYPE>::choice() const
//  {
//      int index;
//      bdlb::SysRandom::getRandomBytesNonBlocking(
//                                   reinterpret_cast<unsigned char *>(&index),
//                                   sizeof(index));
//      return d_choices[index % d_size];
//  }
//..
//  Initialize an array of colors to choose between.
//..
//      string colors[] = {"Red" , "Orange", "Yellow", "Green",
//                         "Blue", "Indigo", "Violet"};
//      unsigned numColors = sizeof(colors)/sizeof(colors[0]);
//..
// Request a random color.
//..
//   RandomChoice<string> chooseColor(colors, numColors);
//..
// Finally we stream the value of this color to 'stdout':
//..
//  if (verbose)
//      cout << chooseColor.choice() << endl;
//..

#ifndef INCLUDED_BDLSCM_VERSION
#include <bdlscm_version.h>
#endif

#ifndef INCLUDED_BSLS_TYPES
#include <bsls_types.h>
#endif

namespace BloombergLP {
namespace bdlb {

                        // ================
                        // struct SysRandom
                        // ================

struct SysRandom {
    // This 'struct' provides a namespace for a suite of functions used for
    // acquiring random numbers from the system.
    //TYPES
    typedef bsls::Types::size_type size_t;       // for brevity of name

    // CLASS METHODS
    static int getRandomBytes(unsigned char *buffer, size_t numBytes);
        // Read the the specified 'numBytes' from the system random number
        // generator into the specified 'buffer'.  Returns 0 on success,
        // non-zero otherwise.  Note that this method may block if called
        // repeatedly or if 'numBytes' is high.

    static int getRandomBytesNonBlocking(unsigned char *buffer,
                                         size_t         numBytes);
        // Read the the specified 'numBytes' from the system non-blocking
        // random number generator into the specified 'buffer'.  Returns 0 on
        // success, non-zero otherwise.
};

}  // close package namespace

}  // close enterprise namespace

#endif

// ----------------------------------------------------------------------------
// NOTICE:
//      Copyright (C) Bloomberg L.P., 2014
//      All Rights Reserved.
//      Property of Bloomberg L.P. (BLP)
//      This software is made available solely pursuant to the
//      terms of a BLP license agreement which governs its use.
// ----------------------------- END-OF-FILE ----------------------------------
/// class of enum flag
///
/// Implementation of a template based enum class for flag handling
///
/// @note Not thread safe
///
//  Copyright (c) MAN Diesel & Turbo
//  @li %date_created:   Tue Dec 10 13:02:51 2013 % 
//  @li %derived_by:  tobl %
//  @li %full_filespec:   enum_flag.h~2:incl:1 %
/// @file

#ifndef ENUM_FLAG_H
#define ENUM_FLAG_H

//#ifndef ASRT_H
//#include <bes/base/asrt/asrt.h>
//#endif

#include <stddef.h>

namespace bes { namespace gcore {

/// @brief Enum flag class
/// 
/// @warning This class handle enum as a flag which means that the enum values must be in power of 2 and not start on 0
/// 
/// The default constructor will reset the flag to zero equal to the clear member.
/// 
/// This means that the following examples must be observed for correct behaviour of the Enum_flag class:
/// @code
/// 
/// /*bit related enums*/
/// 
///  enum Correct
/// {
///   open   = 0x01,
///   oead   = 0x02,
///   write  = 0x04,
///   exec   = 0x08,
/// };
/// 
/// /*auto incremented enums*/
/// 
/// enum Bad
/// {
///   red,
///   green,
///   blue   
/// };
/// 
/// /*user defined enum values not in power of 2*/
/// 
/// enum Bad
/// {
///   circle   = 0x0,   /* bad */
///   square   = 0x1,   /**good */
///   triangle = 0x3    /* bad */
/// };
/// 
/// @endcode
/// 
/// Example usage:
/// 
/// @code
/// 
/// enum Event_type
/// {
///    no_event = 0x01,
///    rise     = 0x02,
///    fall     = 0x04,
///    low      = 0x08,
///    high     = 0x10
/// };
/// 
/// /* unmask */
/// 
/// Enum_flag<Event_type> flag(low);
/// flag |= high;
/// flag.remove(low);
/// 
/// /* mask */
/// Enum_flag<Event_type> flag(no_event);
/// 
/// if ( flag.test_flag(no_event) )
/// {
///   /* then no events has occurred
/// }
///
/// flag |= rise;
/// 
/// if ( flag.test_flag(rise) )
/// {
///   /* then a rise event has occurred */
/// }
/// 
/// @endcode
/// 
template <class TEnum_type,typename U>
class Enum_flag
{
   typedef Enum_flag<TEnum_type> Enum_flag_type;

public:
//   typedef uint32_t Mask;
   typedef U Mask;

   /// @brief ctor with init enum value.
   /// @param val  Initialize Enum_flag with val
   explicit Enum_flag(TEnum_type val);
   /// @brief default ctor.
   /// Initialize Enum_flag with zero
   Enum_flag();

   // enum flag interface
   
   /// @brief test flag.
   /// @param [in] flag  test this object for flag enum
   /// @retval bool  returns true if flag is set in this object    
   bool        test_flag( TEnum_type flag ) const;
   /// @brief set flag.
   /// @param [in] flag  Set this object to flag
   void        set(TEnum_type flag);
   /// @brief get flag.
   /// @retval uint32_t  Return this object flag value
   uint32_t    get() const;
   /// @brief remove flag from Enum_flag.
   /// @param [in] flag  remove flag value from this object
   /// @retval Enum_flag  Performs a remove of the flag from this object and stores the result in this Enum_flag object. Returns a reference to this object.
   Enum_flag_type&  remove(TEnum_type flag);
   /// @brief clear flag.
   /// Clear  flag value
   void        clear(void);

   // operator interface
   // 
   /// @brief get flag.
   /// @retval uint32_t  flag value is returned
    uint32_t   operator()(void) const;
   /// @brief operator&
   /// @param [in] mask  mask value to AND with Enum_flag object
   /// @retval Enum_flag  Returns a Enum_flag object containing the result of the bitwise AND operation on this object and mask
   Enum_flag_type   operator& ( const uint32_t mask ) const;
   /// @brief operator&
   /// @param [in] enum_type  enum value to AND with Enum_flag object
   /// @retval Enum_flag_type  Returns a Enum_flag object as a result of the bitwise AND operation on this object and enum_type
   Enum_flag_type   operator& ( const TEnum_type enum_type) const;
   /// @brief operator&
   /// @param [in] other  Enum_flag object to AND 
   /// @retval Enum_flag_type  Returns a Enum_flag object containing the result of the bitwise AND operation on this object and other object
   Enum_flag_type   operator& ( const Enum_flag_type& other ) const;
   /// @brief operator&=
   /// @param [in] mask  mask value to AND with Enum_flag object and saves it in this object
   /// @retval Enum_flag_type  Performs a bitwise AND operation with mask and stores the result in this Enum_flag object. Returns a reference to this object.
   Enum_flag_type & operator&= ( const uint32_t mask );
   /// @brief operator&=
   /// @param [in] other  Enum_flag object to AND and save it in this object
   /// @retval Enum_flag_type  Performs a bitwise AND operation with other and stores the result in this Enum_flag object. Returns a reference to this object
   Enum_flag_type & operator&= ( const Enum_flag_type & other );
   /// @brief operator=
   /// @param [in] other  other object to assign this object
   /// @retval Enum_flag_type  Assigns other to this object stores the result in the this object. Returns a reference to this object.
   Enum_flag_type & operator= ( const Enum_flag_type & other );
   /// @brief operator=
   /// @param [in] enum_type  Enum to OR with this object
   /// @retval Enum_flag_type  Assigns other to this object stores the result in the this object. Returns a reference to this object.
   Enum_flag_type & operator= ( const TEnum_type enum_type );
   /// @brief operator^
   /// @param [in] other  Enum_flag object to bitwise xor
   /// @retval Enum_flag_type  Returns a Enum_flag object containing the result of the bitwise XOR operation on this object and other.
   Enum_flag_type   operator^ ( const Enum_flag_type & other ) const;
   /// @brief operator^=
   /// @param [in] other  Enum_flag object to bitwise xor and save it in this object
   /// @retval Enum_flag_type  Performs a the bitwise XOR operation on this object and other and stores the result in the this object. Returns a reference to this object
   Enum_flag & operator^= ( const Enum_flag_type & other);
   /// @brief operator|
   /// @param [in] other  Enum_flag object to OR
   /// @retval Enum_flag_type  Returns a Enum_flag object containing the result of the OR operation on this object and other.
   Enum_flag_type operator| ( const Enum_flag_type & other ) const;
   /// @brief operator|
   /// @param [in] enum_type  Enum to OR with this object
   /// @retval Enum_type  Returns a Enum_flag object containing the result of the OR operation on this object and other.
   Enum_flag_type operator| ( const TEnum_type enum_type  ) const;
   /// @brief operator|=
   /// @param [in] other  Enum_flag object to OR and save it in this object
   /// @retval Enum_flag_type  Performs a the OR operation on this object and other and stores the result in the this object. Returns a reference to this object.
   Enum_flag_type & operator|= ( const Enum_flag_type & other );
   /// @brief operator|=
   /// @param [in] enum_type  Enum to OR with this object and save it in this object
   /// @retval Enum_type  Performs a the OR operation on this object and enum_type and stores the result in the this object. Returns a reference to this object.
   Enum_flag_type & operator|= ( const TEnum_type enum_type );
   /// @brief operator~
   /// @retval Enum_flag_type  Returns a Enum_flag object that contains the bitwise negation of this object
   Enum_flag_type   operator~ () const;

private:
   explicit Enum_flag(uint32_t flags);

//   uint32_t    enum_flag_;
   U enum_flag_;
};

// Implementations

template <class TEnum_type>
inline               Enum_flag<TEnum_type>::Enum_flag(TEnum_type val) : enum_flag_(val)
{
}

template <class TEnum_type>
inline               Enum_flag<TEnum_type>::Enum_flag() : enum_flag_(0)
{
}


template <class TEnum_type>
inline               Enum_flag<TEnum_type>::Enum_flag(uint32_t flags) : enum_flag_(flags)
{
}

template <class TEnum_type>
inline  bool         Enum_flag<TEnum_type>::test_flag( TEnum_type flag ) const
{
   return ((enum_flag_ & flag) != 0);
}


template <class TEnum_type>
inline   uint32_t    Enum_flag<TEnum_type>::get() const
{
   return enum_flag_;
}

template <class TEnum_type>
inline void          Enum_flag<TEnum_type>::set(TEnum_type flag)
{
   enum_flag_ |= flag;
}

template <class TEnum_type>
inline Enum_flag<TEnum_type>&    Enum_flag<TEnum_type>::remove(TEnum_type flag)
{
   enum_flag_ &= ~flag;
   return *this;
}

template <class TEnum_type>
inline void          Enum_flag<TEnum_type>::clear(void)
{
   enum_flag_ = 0;
}

template <class TEnum_type>
inline   uint32_t    Enum_flag<TEnum_type>::operator()(void) const
{
   return enum_flag_;
}

template <class TEnum_type>
inline   Enum_flag<TEnum_type>   Enum_flag<TEnum_type>::operator& ( const TEnum_type enum_type ) const
{
   Enum_flag<TEnum_type>   temp(enum_flag_ & enum_type);
   return temp;
}

template <class TEnum_type>
inline   Enum_flag<TEnum_type>   Enum_flag<TEnum_type>::operator& ( const uint32_t mask ) const
{
   Enum_flag<TEnum_type>   temp(enum_flag_ & mask);
   return temp;
}

template <class TEnum_type>
inline   Enum_flag<TEnum_type>   Enum_flag<TEnum_type>::operator& ( const Enum_flag<TEnum_type> & other ) const
{
   Enum_flag<TEnum_type>   temp(enum_flag_ & other.get());
   return temp;
}

template <class TEnum_type>
inline   Enum_flag<TEnum_type>&  Enum_flag<TEnum_type>::operator&= ( const uint32_t mask )
{
   enum_flag_ &= mask;
   return  *this;
}

template <class TEnum_type>
inline   Enum_flag<TEnum_type>&   Enum_flag<TEnum_type>::operator&= ( const Enum_flag<TEnum_type> & other )
{
   enum_flag_ &= other();
   return  *this;
}

template <class TEnum_type>
inline   Enum_flag<TEnum_type>&  Enum_flag<TEnum_type>::operator= ( const Enum_flag<TEnum_type> & other )
{
   enum_flag_ = other();
   return *this;
}

template <class TEnum_type>
inline   Enum_flag<TEnum_type>&  Enum_flag<TEnum_type>::operator= ( const TEnum_type enum_type )
{
   enum_flag_ = enum_type;
   return *this;
}

template <class TEnum_type>
inline   Enum_flag<TEnum_type>   Enum_flag<TEnum_type>::operator^ ( const Enum_flag<TEnum_type> & other ) const
{
   Enum_flag<TEnum_type>   temp(enum_flag_ ^ other());
   return temp;
}

template <class TEnum_type>
inline   Enum_flag<TEnum_type>&  Enum_flag<TEnum_type>::operator^= ( const Enum_flag<TEnum_type> & other)
{
   enum_flag_ ^= other();
   return *this;
}

template <class TEnum_type>
inline   Enum_flag<TEnum_type>  Enum_flag<TEnum_type>::operator| ( const Enum_flag<TEnum_type> & other ) const
{
   Enum_flag<TEnum_type>   temp(enum_flag_ | other.get());
   return temp;
}

template <class TEnum_type>
inline   Enum_flag<TEnum_type>  Enum_flag<TEnum_type>::operator| ( const TEnum_type enum_type ) const
{
   Enum_flag<TEnum_type>   temp(enum_flag_ | enum_type);
   return temp;
}

template <class TEnum_type>
inline   Enum_flag<TEnum_type>&  Enum_flag<TEnum_type>::operator|= ( const Enum_flag<TEnum_type> & other )
{
   enum_flag_ |= other();
   return *this;
}

template <class TEnum_type>
inline Enum_flag<TEnum_type>& Enum_flag<TEnum_type>::operator|= ( const TEnum_type enum_type )
{
   enum_flag_ |= enum_type;
   return *this;
}

template <class TEnum_type>
inline   Enum_flag<TEnum_type>  Enum_flag<TEnum_type>::operator~ () const
{
   Enum_flag<TEnum_type>   temp(~enum_flag_);
   return temp;
}


}} //namespace end

#endif

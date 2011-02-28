#pragma once

#include <iostream>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>

#ifndef WINNT
#include <netinet/in.h>
#include <netdb.h>
#else
#include <winsock.h>
#endif

#include "name_af.h"

namespace af
{

class Af
{
public:
   Af();
   virtual ~Af();

   void write( Msg * msg );

   virtual void stdOut( bool full = false ) const;
   virtual const std::string generateInfoString( bool full = false) const;
   virtual void generateInfoStream( std::ostringstream & stream, bool full = false) const;

protected:
   void read( Msg * msg );
   virtual void readwrite( Msg * msg );

   static void rw_data(        char *          data,     Msg * msg, int size);
   static void  w_data(  const char *          data,     Msg * msg, int size);
   static void rw_bool(        bool        &boolean,     Msg * msg);
   static void rw_uint8_t (    uint8_t     &integer,     Msg * msg);
   static void rw_uint16_t(    uint16_t    &integer,     Msg * msg);
   static void rw_uint32_t(    uint32_t    &integer,     Msg * msg);
   static void rw_int8_t (     int8_t      &integer,     Msg * msg);
   static void rw_int16_t(     int16_t     &integer,     Msg * msg);
   static void rw_int32_t(     int32_t     &integer,     Msg * msg);
   static void rw_float(       float       &floating,    Msg * msg);
   static void rw_String(      std::string &string,      Msg * msg);
   static void rw_QString(     QString     &qString,     Msg * msg);
   static void rw_QStringList( QStringList &qStringList, Msg * msg);
   static void rw_QRegExp(     QRegExp     &qRegExp,     Msg * msg);

   static void rw_Int8_List(   std::list   <   int8_t > &list, Msg * msg);
   static void rw_Int32_List(  std::list   <  int32_t > &list, Msg * msg);
   static void rw_Int32_Vect(  std::vector <  int32_t > &vect, Msg * msg);
   static void rw_UInt32_List( std::list   < uint32_t > &list, Msg * msg);
   static void rw_UInt32_Vect( std::vector < uint32_t > &vect, Msg * msg);
};
}

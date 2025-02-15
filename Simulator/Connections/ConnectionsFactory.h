/**
 * @file ConnectionsFactory.h
 * 
 * @ingroup Simulator/Connections
 *
 * @brief A factory class for creating Connections objects.
 */

#pragma once

#include "Connections.h"
#include "Global.h"
#include <map>
#include <memory>
#include <string>

using namespace std;

class ConnectionsFactory {
public:
   ~ConnectionsFactory();

   static ConnectionsFactory &getInstance()
   {
      static ConnectionsFactory instance;
      return instance;
   }

   /// Invokes constructor for desired concrete class
   shared_ptr<Connections> createConnections(const string &className);

   /// Delete these methods because they can cause copy instances of the singleton when using threads.
   ConnectionsFactory(ConnectionsFactory const &) = delete;
   void operator=(ConnectionsFactory const &) = delete;

private:
   /// Constructor is private to keep a singleton instance of this class.
   ConnectionsFactory();

   /// Defines function type for usage in internal map
   typedef Connections *(*CreateFunction)(void);

   /// Defines map between class name and corresponding ::Create() function.
   typedef map<string, CreateFunction> ConnectionsFunctionMap;

   /// Makes class-to-function map an internal factory member.
   ConnectionsFunctionMap createFunctions;

   /// Register connection class and it's create function to the factory.
   void registerClass(const string &className, CreateFunction function);
};

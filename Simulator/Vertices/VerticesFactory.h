/**
 * @file VerticesFactory.h
 * 
 * @ingroup Simulator/Vertices
 *
 * @brief A factory class for creating Vertices objects.
 */

#pragma once

#include "AllVertices.h"
#include "Global.h"
#include <map>
#include <memory>
#include <string>

using namespace std;

class VerticesFactory {
public:
   ~VerticesFactory();

   static VerticesFactory &getInstance()
   {
      static VerticesFactory instance;
      return instance;
   }

   // Invokes constructor for desired concrete class
   shared_ptr<AllVertices> createVertices(const string &className);

   /// Delete these methods because they can cause copy instances of the singleton when using threads.
   VerticesFactory(VerticesFactory const &) = delete;
   void operator=(VerticesFactory const &) = delete;

private:
   /// Constructor is private to keep a singleton instance of this class.
   VerticesFactory();

   /* Type definitions */
   /// Defines function type for usage in internal map
   typedef AllVertices *(*CreateFunction)(void);

   /// Defines map between class name and corresponding ::Create() function.
   typedef map<string, CreateFunction> VerticesFunctionMap;

   /// Makes class-to-function map an internal factory member.
   VerticesFunctionMap createFunctions;

   /// Register vertex class and it's create function to the factory.
   void registerClass(const string &className, CreateFunction function);
};

/**
 * @file RecorderFactory.h
 *
 * @ingroup Simulator/Recorders
 * 
 * @brief A factory class for creating Recorder objects.
 */

#pragma once

#include "Global.h"
#include "IRecorder.h"
#include <map>
#include <memory>
#include <string>

using namespace std;

class RecorderFactory {
public:
   ~RecorderFactory();

   static RecorderFactory &getInstance()
   {
      static RecorderFactory instance;
      return instance;
   }

   // Invokes constructor for desired concrete class
   shared_ptr<IRecorder> createRecorder(const string &className);

   /// Delete these methods because they can cause copy instances of the singleton when using threads.
   RecorderFactory(RecorderFactory const &) = delete;
   void operator=(RecorderFactory const &) = delete;

private:
   /// Constructor is private to keep a singleton instance of this class.
   RecorderFactory();

   /// Defines function type for usage in internal map
   typedef IRecorder *(*CreateFunction)(void);

   /// Defines map between class name and corresponding ::Create() function.
   typedef map<string, CreateFunction> RecorderFunctionMap;

   /// Makes class-to-function map an internal factory member.
   RecorderFunctionMap createFunctions;

   /// Register neuron class and it's create function to the factory.
   void registerClass(const string &className, CreateFunction function);
};

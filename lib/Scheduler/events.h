////////////////////////////////////////////////////////////////////////////////
/// @brief input-output scheduler event handling
///
/// @file
///
/// DISCLAIMER
///
/// Copyright 2014 ArangoDB GmbH, Cologne, Germany
/// Copyright 2004-2014 triAGENS GmbH, Cologne, Germany
///
/// Licensed under the Apache License, Version 2.0 (the "License");
/// you may not use this file except in compliance with the License.
/// You may obtain a copy of the License at
///
///     http://www.apache.org/licenses/LICENSE-2.0
///
/// Unless required by applicable law or agreed to in writing, software
/// distributed under the License is distributed on an "AS IS" BASIS,
/// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
/// See the License for the specific language governing permissions and
/// limitations under the License.
///
/// Copyright holder is ArangoDB GmbH, Cologne, Germany
///
/// @author Dr. Frank Celler
/// @author Achim Brandt
/// @author Copyright 2014, ArangoDB GmbH, Cologne, Germany
/// @author Copyright 2008-2013, triAGENS GmbH, Cologne, Germany
////////////////////////////////////////////////////////////////////////////////

#ifndef ARANGODB_SCHEDULER_EVENTS_H
#define ARANGODB_SCHEDULER_EVENTS_H 1

#include "Basics/Common.h"

namespace triagens {
  namespace rest {

    struct Watcher;

// -----------------------------------------------------------------------------
// --SECTION--                                                         constants
// -----------------------------------------------------------------------------

////////////////////////////////////////////////////////////////////////////////
/// @brief event loop identifier
////////////////////////////////////////////////////////////////////////////////

    typedef uint32_t EventLoop;

////////////////////////////////////////////////////////////////////////////////
/// @brief event handler identifier
////////////////////////////////////////////////////////////////////////////////

    typedef Watcher* EventToken;

////////////////////////////////////////////////////////////////////////////////
/// @brief event type identifier
////////////////////////////////////////////////////////////////////////////////

    typedef uint32_t EventType;

// -----------------------------------------------------------------------------
// --SECTION--                                                         constants
// -----------------------------------------------------------------------------

////////////////////////////////////////////////////////////////////////////////
/// @brief socket read event
////////////////////////////////////////////////////////////////////////////////

    uint32_t const EVENT_SOCKET_READ = 1;

////////////////////////////////////////////////////////////////////////////////
/// @brief socket write event
////////////////////////////////////////////////////////////////////////////////

    uint32_t const EVENT_SOCKET_WRITE = 2;

////////////////////////////////////////////////////////////////////////////////
/// @brief asynchronous event
////////////////////////////////////////////////////////////////////////////////

    uint32_t const EVENT_ASYNC = 4;

////////////////////////////////////////////////////////////////////////////////
/// @brief timer event
////////////////////////////////////////////////////////////////////////////////

    uint32_t const EVENT_TIMER = 8;

////////////////////////////////////////////////////////////////////////////////
/// @brief periodic event
////////////////////////////////////////////////////////////////////////////////

    uint32_t const EVENT_PERIODIC = 16;

////////////////////////////////////////////////////////////////////////////////
/// @brief signal event
////////////////////////////////////////////////////////////////////////////////

    uint32_t const EVENT_SIGNAL = 32;

////////////////////////////////////////////////////////////////////////////////
/// @brief automatically select an io backend
////////////////////////////////////////////////////////////////////////////////

    uint32_t const BACKEND_AUTO = 0;
    
// -----------------------------------------------------------------------------
// --SECTION--                                                Watcher base class
// -----------------------------------------------------------------------------

    struct Watcher {
      Watcher (EventType type) 
        : type(type) {

      }

      EventType const type;
    };
  }
}

#endif

// -----------------------------------------------------------------------------
// --SECTION--                                                       END-OF-FILE
// -----------------------------------------------------------------------------

// Local Variables:
// mode: outline-minor
// outline-regexp: "/// @brief\\|/// {@inheritDoc}\\|/// @page\\|// --SECTION--\\|/// @\\}"
// End:

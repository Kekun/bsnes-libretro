#ifndef SNES_HPP
#define SNES_HPP

#include <base/base.hpp>
#include <processor/arm/arm.hpp>
#include <processor/hg51b/hg51b.hpp>
#include <processor/upd96050/upd96050.hpp>

namespace SNES {
  namespace Info {
    static const char Name[] = "bsnes";
    static const unsigned SerializerVersion = 24;
  }
}

/*
  bsnes - SNES emulator
  author: byuu
  license: GPLv3
  project started: 2004-10-14
*/

#include <libco/libco.h>

#if defined(GAMEBOY)
  #include <gb/gb.hpp>
#endif

namespace SNES {
  struct Thread {
    cothread_t thread;
    unsigned frequency;
    int64 clock;

    inline void create(void (*entrypoint)(), unsigned frequency) {
      if(thread) co_delete(thread);
      thread = co_create(65536 * sizeof(void*), entrypoint);
      this->frequency = frequency;
      clock = 0;
    }

    inline void serialize(serializer &s) {
      s.integer(frequency);
      s.integer(clock);
    }

    inline Thread() : thread(nullptr) {
    }

    inline ~Thread() {
      if(thread) co_delete(thread);
    }
  };

  #include <snes/memory/memory.hpp>
  #include <snes/cpu/core/core.hpp>
  #include <snes/smp/core/core.hpp>
  #include <snes/ppu/counter/counter.hpp>

  #if defined(PROFILE_ACCURACY)
  #include "profile-accuracy.hpp"
  #elif defined(PROFILE_COMPATIBILITY)
  #include "profile-compatibility.hpp"
  #elif defined(PROFILE_PERFORMANCE)
  #include "profile-performance.hpp"
  #endif

  #include <snes/controller/controller.hpp>
  #include <snes/system/system.hpp>
  #include <snes/chip/chip.hpp>
  #include <snes/cartridge/cartridge.hpp>
  #include <snes/cheat/cheat.hpp>
  #include <snes/interface/interface.hpp>

  #include <snes/memory/memory-inline.hpp>
  #include <snes/ppu/counter/counter-inline.hpp>
}

#endif

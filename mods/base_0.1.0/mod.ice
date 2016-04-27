import { PreInitEvent, InitEvent, PostInitEvent, Server, Client, Common } from <mod_kit.ice>;

object ModInfo
  mod_id   :: "base";
  mod_name :: "Base";

  version_major :: "0";
  version_minor :: "1";
  version_patch :: "0";
end

class Mod
  PreInit: func( e: borrow ^PreInitEvent ) -> void
    e.ServerPreInit( func( server: borrow ^Server ) -> void

    end );

    e.ClientPreInit( func( client: borrow ^Client ) -> void

    end );

    e.CommonPreInit( func( common: borrow ^Common ) -> void

    end );
  end

  Init: func( e: borrow ^InitEvent ) -> void
    e.ServerInit( func( server: borrow ^Server ) -> void

    end );

    e.ClientInit( func( client: borrow ^Client ) -> void

    end );

    e.CommonInit( func( common: borrow ^Common ) -> void

    end );
  end

  PostInit: func( e: borrow ^PostInitEvent ) -> void
    e.ServerPostInit( func( server: borrow ^Server ) -> void

    end );

    e.ClientPostInit( func( client: borrow ^Client ) -> void

    end );

    e.CommonPostInit( func( common: borrow ^Common ) -> void

    end );
  end
end

//////////////////////////////////////

import { to_lower } from <string.ice>;

things := [..]string{ "Hello", "Darkness", "My", "Old", "Friend" };
others : [100]string = ---;

for ( some borrow ^in things )
  to_lower( some );
end

//////////////////////////////////////

enum Days : byte
  MONDAY,
  TUESDAY,
  WEDNESDAY,
  THURSDAY,
  FRIDAY,
  SATURDAY,
  SUNDAY
end

Days.count;
Days.low;
Days.high;
Days.

//////////////////////////////////////

ping: func( comm: # string ) -> void
  print( <- comm );
  comm <- "World";
end

main: func() -> void
  comm := # string;

  start ping( comm );

  comm <- "Hello";
  print( <- comm );
end

//////////////////////////////////////

mything = new thing();
defer delete mything;

array[2]string
slice[1..10]string
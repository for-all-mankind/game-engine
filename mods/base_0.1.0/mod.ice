import { PreInitEvent, InitEvent, PostInitEvent, Server, Client, Common } from <mod_kit.ice>;

object Mod
  mod_id   :: "base";
  mod_name :: "Base";

  version_major :: "0";
  version_minor :: "1";
  version_patch :: "0";

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
package com.example.multibackend;

import org.libsdl.app.SDLActivity;

public class DemoActivity extends SDLActivity {
    @Override
    protected String[] getLibraries() {
        // SDL symbols are statically linked into libmain.so via bundled SDL2.
        return new String[] {"main"};
    }
}

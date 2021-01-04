package edu.harvard.cs50.pokedex;


import java.io.Serializable;

import androidx.annotation.NonNull;
import androidx.annotation.Nullable;

public class Pokemon implements Serializable {
    private String name;
    private String url;
    private static final String TAG = "cs50 Pokemon";
    private boolean catched;

    Pokemon(String name, String url) {
        this.name = name;
        this.url = url;
    }

    public String getName() {
        return name;
    }

    public String getUrl() {
        return url;
    }

    public boolean isCatched() {
        return catched;

    }

    public void setCatched(boolean catched) {
        this.catched = catched;
    }


}

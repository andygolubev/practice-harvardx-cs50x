package edu.harvard.cs50.pokedex;

import androidx.appcompat.app.AppCompatActivity;

import android.content.Context;
import android.content.SharedPreferences;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.os.AsyncTask;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.ImageView;
import android.widget.TextView;

import com.android.volley.Request;
import com.android.volley.RequestQueue;
import com.android.volley.Response;
import com.android.volley.VolleyError;
import com.android.volley.toolbox.JsonObjectRequest;
import com.android.volley.toolbox.Volley;

import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

import java.io.IOException;
import java.net.URI;
import java.net.URL;
import java.util.ArrayList;
import java.util.List;

public class PokemonActivity extends AppCompatActivity {
    private TextView nameTextView;
    private TextView numberTextView;
    private TextView type1TextView;
    private TextView type2TextView;
    private TextView description;
    private ImageView imageView;
    private String url;
    private String urlForDescription;
    private RequestQueue requestQueue;
    private Button buttonView;
    private Pokemon current;
    private static final String TAG = "cs50 PokemonActivity";

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_pokemon);

        requestQueue = Volley.newRequestQueue(getApplicationContext());
        url = getIntent().getStringExtra("url");
        current = (Pokemon) getIntent().getSerializableExtra("pokemon");
        nameTextView = findViewById(R.id.pokemon_name);
        numberTextView = findViewById(R.id.pokemon_number);
        type1TextView = findViewById(R.id.pokemon_type1);
        type2TextView = findViewById(R.id.pokemon_type2);
        buttonView = findViewById(R.id.catch_button);
        imageView = findViewById(R.id.pokemon_image);
        description = findViewById(R.id.pokemon_description);

        load();

    }

    public void load() {
        type1TextView.setText("");
        type2TextView.setText("");
        description.setText("");

        JsonObjectRequest request = new JsonObjectRequest(Request.Method.GET, url, null, new Response.Listener<JSONObject>() {

            @Override
            public void onResponse(JSONObject response) {
                try {
                    nameTextView.setText(response.getString("name"));
                    numberTextView.setText(String.format("#%03d", response.getInt("id")));

                    JSONArray typeEntries = response.getJSONArray("types");
                    for (int i = 0; i < typeEntries.length(); i++) {
                        JSONObject typeEntry = typeEntries.getJSONObject(i);
                        int slot = typeEntry.getInt("slot");
                        String type = typeEntry.getJSONObject("type").getString("name");

                        if (slot == 1) {
                            type1TextView.setText(type);
                        }
                        else if (slot == 2) {
                            type2TextView.setText(type);
                        }
                    }

                    String imageURL = response.getJSONObject("sprites").getString("front_default");
                    Log.i("cs50 JSON imageURL", imageURL);

                    new DownloadSpriteTask().execute(imageURL);

                    urlForDescription = response.getJSONObject("species").getString("url");
                    Log.i("cs50 JSON descURL", urlForDescription);

                        description.setText("");

                        JsonObjectRequest requestDescription = new JsonObjectRequest(Request.Method.GET, urlForDescription, null, new Response.Listener<JSONObject>() {
                            @Override
                            public void onResponse(JSONObject response) {
                                try {
                                    Log.i(TAG, "onResponse: " + response);


                                    JSONArray descEntries = response.getJSONArray("flavor_text_entries");
                                    if (descEntries != null) {
                                        Log.i("cs50 JSON log", "Enter the loop");
                                        for (int i = 0; i < descEntries.length(); i++) {
                                            JSONObject descEntry = descEntries.getJSONObject(i);
                                            String desc = descEntry.getString("flavor_text");
                                            String lang = descEntry.getJSONObject("language").getString("name");

                                            if (lang.equals("en")) {
                                                description.setText(desc);
                                                Log.i("cs50 JSON desc", desc);
                                                break;
                                            }
                                        }
                                    } else{
                                        Log.i("cs50 JSON log", "NULL response!!!!!");
                                    }


                                } catch (JSONException e) {
                                    Log.e("cs50", "Pokemon json error", e);
                                }
                            }
                        }, new Response.ErrorListener() {
                            @Override
                            public void onErrorResponse(VolleyError error) {
                                Log.e("cs50", "Pokemon description error", error);
                            }
                        });



                        requestQueue.add(requestDescription);


                } catch (JSONException e) {
                    Log.e("cs50", "Pokemon json error", e);
                }
            }
        }, new Response.ErrorListener() {
            @Override
            public void onErrorResponse(VolleyError error) {
                Log.e("cs50", "Pokemon details error", error);
            }
        });



        requestQueue.start();
        requestQueue.add(request);

        SharedPreferences sharedPref = getApplicationContext().getSharedPreferences("PREFERENCE_FILE_KEY", Context.MODE_PRIVATE);
        Log.i(TAG, "sharedPref: " + sharedPref.toString());

        current.setCatched(sharedPref.getBoolean(current.getName(), false));

        if (!current.isCatched())
            buttonView.setText("Catch");
        else
            buttonView.setText("Release");
    }



    public void toggleCatch(View view){
        if(!current.isCatched()){
            current.setCatched(true);
            buttonView.setText("Release");
        }
        else{
            current.setCatched(false);
            buttonView.setText("Catch");
        }

        SharedPreferences sharedPref = getApplicationContext().getSharedPreferences("PREFERENCE_FILE_KEY", Context.MODE_PRIVATE);
        SharedPreferences.Editor editor = sharedPref.edit();
        editor.putBoolean(current.getName(), current.isCatched());
        editor.apply();

    }

    class DownloadSpriteTask extends AsyncTask<String, Void, Bitmap> {
        @Override
        protected Bitmap doInBackground(String... strings) {
            try {
                URL url = new URL(strings[0]);
                return BitmapFactory.decodeStream(url.openStream());
            }
            catch (IOException e) {
                Log.e("cs50", "Download sprite error", e);
                return null;
            }
        }

        @Override
        protected void onPostExecute(Bitmap bitmap) {
            //imageView = findViewById(R.id.pokemon_image);
            imageView.setImageBitmap(bitmap);

        }
    }
}

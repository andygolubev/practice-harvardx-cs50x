package edu.harvard.cs50.notes;

import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;

import androidx.appcompat.app.AppCompatActivity;

public class NoteActivity extends AppCompatActivity {
    private EditText editText;
    private Button button;
    private int id;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_note);

        editText = findViewById(R.id.note_edit_text);
        button = findViewById(R.id.note_delete);
        String contents = getIntent().getStringExtra("contents");
        id = getIntent().getIntExtra("id", 0);
        editText.setText(contents);
    }

    @Override
    protected void onPause() {
        super.onPause();

        MainActivity.notesDatabase.noteDAO().save(editText.getText().toString(), id);
    }
    public void deleteNote(View v){
        MainActivity.notesDatabase.noteDAO().delete(id);
    }
}
package edu.harvard.cs50.notes;

import java.util.List;

import androidx.room.Dao;
import androidx.room.Query;

@Dao
public interface NoteDAO {

    @Query("INSERT INTO notes (contents) VALUES ('New note')")
    void create();

    @Query("SELECT * FROM notes")
    List<Note> getAllNotes();

    @Query("UPDATE notes SET contents = :contents WHERE id = :id")
    void save(String contents, int id);

    @Query("DELETE FROM notes where id = :id")
    void delete (int id);

}

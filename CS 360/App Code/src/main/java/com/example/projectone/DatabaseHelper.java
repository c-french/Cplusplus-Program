package com.example.projectone;

import android.content.ContentValues;
import android.content.Context;
import android.database.Cursor;
import android.database.sqlite.SQLiteDatabase;
import android.database.sqlite.SQLiteOpenHelper;
import android.widget.Toast;

import androidx.annotation.Nullable;

public class DatabaseHelper extends SQLiteOpenHelper {
    private Context context;
    private static final String DATABASE_NAME = "weights.db";
    private static final int DATABASE_VERSION = 1;

    private final String TABLE_NAME = "my_weights";
    private static final String COLUMN_ID = "_id";
    private static final String COLUMN_DATE = "measurement_date";
    private static final String COLUMN_WEIGHT = "measurement_weight";
    private static final String COLUMN_GOAL = "goal_weight";
    public DatabaseHelper(@Nullable Context context) {
        super(context, DATABASE_NAME, null, DATABASE_VERSION);
        this.context = context;
    }

    @Override
    public void onCreate(SQLiteDatabase db) {
        String query =
                "CREATE TABLE " + TABLE_NAME +
                        " (" + COLUMN_ID + " INTEGER PRIMARY KEY AUTOINCREMENT, " +
                        COLUMN_DATE + " TEXT, " +
                        COLUMN_WEIGHT + " TEXT, " +
                        COLUMN_GOAL + " TEXT);";
        db.execSQL(query);
    }

    @Override
    public void onUpgrade(SQLiteDatabase db, int i, int i1) {
        db.execSQL("DROP TABLE IF EXISTS " + TABLE_NAME);
        onCreate(db);
    }

    void addWeight(String date, String weight, String goal){
        SQLiteDatabase db = this.getWritableDatabase();
        ContentValues cv = new ContentValues();
        cv.put(COLUMN_DATE,date);
        cv.put(COLUMN_WEIGHT, weight);
        cv.put(COLUMN_GOAL, goal);

        long result = db.insert(TABLE_NAME, null, cv);
        if(result == -1){
            Toast.makeText(context, "Failed to add data", Toast.LENGTH_SHORT).show();
        } else {
            Toast.makeText(context, "Weight logged!", Toast.LENGTH_SHORT).show();
        }
    }

    Cursor readAllData(){
        String query = "SELECT * FROM " + TABLE_NAME;
        SQLiteDatabase  db = this.getReadableDatabase();

        Cursor cursor = null;
        if(db != null){
            cursor = db.rawQuery(query, null);
        }
        return cursor;
    }

    void updateData(String row_id, String date, String weight){
        SQLiteDatabase db = this.getWritableDatabase();
        ContentValues cv = new ContentValues();
        cv.put(COLUMN_DATE, date);
        cv.put(COLUMN_WEIGHT, weight);


       long result = db.update(TABLE_NAME, cv, "_id=?", new String[]{row_id});
       if (result == -1){
           Toast.makeText(context, "Failed to Update", Toast.LENGTH_SHORT).show();
       }else{
           Toast.makeText(context, "Updated entry!", Toast.LENGTH_SHORT).show();
       }

    }

    void deleteRow(String row_id){
       SQLiteDatabase db = this.getWritableDatabase();
       long result = db.delete(TABLE_NAME, "_id=?", new String[]{row_id});
       if (result == -1){
           Toast.makeText(context, "Failed to delete entry", Toast.LENGTH_SHORT).show();
       }else{
           Toast.makeText(context, "Deleted entry", Toast.LENGTH_SHORT).show();
       }
    }
}

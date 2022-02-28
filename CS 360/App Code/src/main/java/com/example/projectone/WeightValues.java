package com.example.projectone;

import android.content.Intent;
import android.database.Cursor;
import android.os.Bundle;
import android.view.View;
import android.widget.Toast;

import androidx.annotation.Nullable;
import androidx.appcompat.app.AppCompatActivity;
import androidx.recyclerview.widget.LinearLayoutManager;
import androidx.recyclerview.widget.RecyclerView;

import com.google.android.material.floatingactionbutton.FloatingActionButton;

import java.util.ArrayList;

public class WeightValues extends AppCompatActivity {
    RecyclerView recyclerView;
    FloatingActionButton addButton;
    DatabaseHelper db;
    ArrayList<String> weight_id, weight_date, weight_measurement, weight_goal;
    RecyclerAdapter recyclerAdapter;

    @Override
    protected void onCreate(Bundle savedInstanceState){
        super.onCreate(savedInstanceState);
        setContentView(R.layout.weight_values);

        recyclerView = findViewById(R.id.weightRecycler);
        addButton = findViewById(R.id.addButton);
        addButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                Intent intent = new Intent(WeightValues.this, AddActivity.class);
                startActivity(intent);
            }
        });

        db = new DatabaseHelper(WeightValues.this);
        weight_id = new ArrayList<>();
        weight_date = new ArrayList<>();
        weight_measurement = new ArrayList<>();
        weight_goal = new ArrayList<>();

        displayData();

        recyclerAdapter = new RecyclerAdapter(WeightValues.this, this, weight_id, weight_date, weight_measurement, weight_goal);
        recyclerView.setAdapter(recyclerAdapter);
        recyclerView.setLayoutManager(new LinearLayoutManager(WeightValues.this));
    }

    @Override
    protected void onActivityResult(int requestCode, int resultCode, @Nullable Intent data) {
        super.onActivityResult(requestCode, resultCode, data);
        if(requestCode == 1){
            recreate();
        }
    }

    void displayData(){
        Cursor cursor = db.readAllData();
        if(cursor.getCount() == 0){
            Toast.makeText(this, "No data to read.", Toast.LENGTH_SHORT).show();
        }else{
            while(cursor.moveToNext()){
                weight_id.add(cursor.getString(0));
                weight_date.add(cursor.getString(1));
                weight_measurement.add(cursor.getString(2));
                weight_goal.add(cursor.getString(3));
            }
        }
    }


}

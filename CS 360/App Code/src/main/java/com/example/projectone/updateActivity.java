package com.example.projectone;

import androidx.appcompat.app.AlertDialog;
import androidx.appcompat.app.AppCompatActivity;

import android.content.DialogInterface;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.Toast;

public class updateActivity extends AppCompatActivity {
    String dateEntry, weightEntry, idEntry, id;
    EditText date, weight;
    Button update, delete;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_update);

        date = findViewById(R.id.editDate2);
        weight = findViewById(R.id.editWeight2);
        update = findViewById(R.id.addButton2);
        delete = findViewById(R.id.deleteButton);
        getIntentData();
        update.setOnClickListener(new View.OnClickListener(){

            @Override
            public void onClick(View view) {


                DatabaseHelper db = new DatabaseHelper(updateActivity.this);
                getIntentData();


                db.updateData(id, dateEntry, weightEntry);
                finish();
            }
        });

        delete.setOnClickListener(new View.OnClickListener(){

            @Override
            public void onClick(View view) {
                confirmDialog();
            }
        });

    }

    void getIntentData(){
        if(getIntent().hasExtra("weight") && getIntent().hasExtra("date")){
            id = getIntent().getStringExtra("id");
            dateEntry = getIntent().getStringExtra("date");
            weightEntry = getIntent().getStringExtra("weight");

            date.setText(dateEntry);
            weight.setText(weightEntry);
        }else{
            Toast.makeText(this, "No data", Toast.LENGTH_SHORT).show();
        }
    }

    void confirmDialog(){
        AlertDialog.Builder builder = new AlertDialog.Builder(this);
        builder.setTitle("Delete " + date.getText() + " ?");
        builder.setMessage("Are you sure you want to delete " + date.getText() + " ?");
        builder.setPositiveButton("Yes", new DialogInterface.OnClickListener() {
            @Override
            public void onClick(DialogInterface dialogInterface, int i) {
                DatabaseHelper db = new DatabaseHelper(updateActivity.this);
                db.deleteRow(id);
                finish();
            }
        });
        builder.setNegativeButton("No", new DialogInterface.OnClickListener() {
            @Override
            public void onClick(DialogInterface dialogInterface, int i) {

            }
        });
        builder.create().show();
    }
}
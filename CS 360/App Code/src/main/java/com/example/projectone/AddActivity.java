package com.example.projectone;

import androidx.appcompat.app.AppCompatActivity;

import android.content.Intent;
import android.os.Bundle;
import android.telephony.SmsManager;
import android.telephony.SmsMessage;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;

public class AddActivity extends AppCompatActivity {
private Button add;
private EditText date;
private EditText weight;
private static String goal = "200.00";
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_add);
        date = requireViewById(R.id.editDate);
        weight = requireViewById(R.id.editWeight);

        add = requireViewById(R.id.addButton);
        add.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                DatabaseHelper db = new DatabaseHelper(AddActivity.this);
                db.addWeight(date.getText().toString().trim(), weight.getText().toString().trim(), goal);
                if(weight.getText().toString() == goal){
                    SmsManager smsManager = SmsManager.getDefault();
                    smsManager.sendTextMessage("phoneNo", null, "Congratulations!", null, null);
                }
            }
        });

    }
}
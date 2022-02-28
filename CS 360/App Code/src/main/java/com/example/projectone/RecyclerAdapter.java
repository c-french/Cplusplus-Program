package com.example.projectone;

import android.app.Activity;
import android.content.Context;
import android.content.Intent;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.LinearLayout;
import android.widget.TextView;

import androidx.annotation.NonNull;
import androidx.recyclerview.widget.RecyclerView;

import org.w3c.dom.Text;

import java.util.ArrayList;

public class RecyclerAdapter extends RecyclerView.Adapter<RecyclerAdapter.MyViewHolder> {

    private Context context;
    Activity activity;
    private ArrayList id, date, weight, goal;
    int position;
    RecyclerAdapter(Activity activity, Context context, ArrayList id, ArrayList date, ArrayList weight, ArrayList goal){
        this.activity = activity;
        this.context = context;
        this.id = id;
        this.date = date;
        this.weight = weight;
        this.goal = goal;
    }

    @NonNull
    @Override
    public MyViewHolder onCreateViewHolder(@NonNull ViewGroup parent, int viewType) {
        LayoutInflater inflater = LayoutInflater.from(context);
        View view = inflater.inflate(R.layout.my_row, parent, false);
        return new MyViewHolder(view);
    }

    @Override
    public void onBindViewHolder(@NonNull RecyclerAdapter.MyViewHolder holder, int position) {
    this.position = position;

    holder.weight_id.setText(String.valueOf(id.get(position)));
    holder.weight_date.setText(String.valueOf(date.get(position)));
    holder.weight_measurement.setText(String.valueOf(weight.get(position)));
    holder.mainLayout.setOnClickListener(new View.OnClickListener() {

        @Override
        public void onClick(View view) {
            Intent intent = new Intent(context, updateActivity.class);
            intent.putExtra("id", String.valueOf(id.get(position)));
            intent.putExtra("weight", String.valueOf(weight.get(position)));
            intent.putExtra("date", String.valueOf(date.get(position)));
            activity.startActivityForResult(intent, 1);
        }
    });

    }

    @Override
    public int getItemCount() {
        return goal.size();
    }

    public class MyViewHolder extends RecyclerView.ViewHolder {
        TextView weight_id, weight_date, weight_measurement;
        LinearLayout mainLayout;
        public MyViewHolder(@NonNull View itemView) {
            super(itemView);
            weight_id = itemView.findViewById(R.id.weight_id_text);
            weight_date = itemView.findViewById(R.id.weight_date);
            weight_measurement = itemView.findViewById(R.id.weight_measurement);
            mainLayout = itemView.findViewById(R.id.mainLayout);
        }
    }
}

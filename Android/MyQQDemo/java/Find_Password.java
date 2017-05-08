package com.example.dada.myqqdemo;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;


public class Find_Password extends BaseActivity {

    private TextView find_password_back;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_find__password);

        find_password_back = (TextView) findViewById(R.id.find_password_back);
        find_password_back.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Find_Password.this.finish();
            }
        });
    }
}

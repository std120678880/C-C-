package com.example.dada.myqqdemo;

import android.content.Intent;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;

public class ChoiceActivity extends BaseActivity {

    private Button loginButton,newuserButton;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_choice);

        loginButton = (Button)findViewById(R.id.choice_loginButton);
        newuserButton = (Button)findViewById(R.id.choice_newUserButton);

        loginButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent intent = new Intent(ChoiceActivity.this,LoginActivity.class);
                startActivity(intent);
            }
        });

        newuserButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                //跳转到新用户注册界面
            }
        });
    }
}

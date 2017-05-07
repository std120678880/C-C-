package com.example.dada.myqqdemo;

import android.graphics.Color;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.text.Editable;
import android.text.TextWatcher;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;

public class Phone_Login extends BaseActivity {

    public TextView backText;
    public Button nextButton;
    private EditText phoneNumber;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_phone__login);

        backText = (TextView)findViewById(R.id.phone_login_back);

        nextButton = (Button)findViewById(R.id.phone_login_nextStep);
        phoneNumber = (EditText)findViewById(R.id.phone_login_phoneNumber);
    }

    @Override
    protected void onStart() {
        super.onStart();
        phoneNumber.addTextChangedListener(new EditChangeListener());
        backText.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Phone_Login.this.finish();
            }
        });
    }

    class EditChangeListener implements TextWatcher{

        private CharSequence temp;
        @Override
        public void beforeTextChanged(CharSequence s, int start, int count, int after) {
            temp = s;
        }

        @Override
        public void onTextChanged(CharSequence s, int start, int before, int count) {

        }

        @Override
        public void afterTextChanged(Editable s) {
            if(temp.toString().length() == 11){
                nextButton.setBackgroundColor(Color.parseColor("#3eadec"));
                nextButton.setTextColor(Color.parseColor("#ffffff"));
                nextButton.setEnabled(true);
            }
            else{
                nextButton.setBackgroundColor(Color.parseColor("#e9ebec"));
                nextButton.setTextColor(Color.parseColor("#c0c0c0"));
                nextButton.setEnabled(false);
            }
        }
    }
}
